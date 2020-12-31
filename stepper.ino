/*
MIT License

Copyright (c) 2020 GoshaTurkia

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <math.h>

// MS1, MS2, MS3 - порты, через которые на драйвере устанавливается режим шага (полношаговый, полушаговый, 1/4, 1/8 и 1/16 шага)
#define MS1 3
#define MS2 4
#define MS3 5

// STEP - порт, на который посылаются импульсы для управления двигателем. Каждый импульс соответствует 1 шагу (либо микрошагу, в зависимости от режима)
// DIR - порт, отвечающий за направление вращения двигателя
#define STEP 6
#define DIR 7

// Длина окружности шестерни в мм. Иначе говоря длина ремня, соответствующая одному обороту шестерни.
// Она рассчитывалась для стандартного двигателя Nema 17, как произведение количества зубьев на расстояние между двумя зубьями
const int l = 40;

// pin_steps - массив портов для задания режима работы двигателя
const int pin_steps[3] = {MS1, MS2, MS3};

// steps - массив, в котором записаны сигналы, посылаемые на порты MS1, MS2, MS3 для задания режима работы двигателя
const int steps[5][4]={
    {1,0,0,0}, // 1
    {2,1,0,0}, // 1/2
    {4,0,1,0}, // 1/4
    {8,1,1,0}, // 1/8
    {16,1,1,1} // 1/16
    };

// Константа пи
const float pi = 3.14159;

// Координата текущей позиции мотора
float coordinates = 0.0;


/* 
 *  Данная функция предназначена для линейного перемещения на заданное расстояние.  
 *  omega - необходимая угловая скорость в радианах в секунду.
 *  S - модуль перемещения в мм.
 *  step_split - параметр, отвечающий за дробление шага; он может принимать следующие значения: 
 *  1 - полный шаг, 2 - полушаговый режим, 3 - дробление шага 1/4, 4 - дробление шага 1/8 и 5 - дробление шага 1/16. По умолчанию step_split=1.
 *  trigger - параметр, отвечающий за направление вращения двигателя.
 *  Он принимает значения 0 (вращение против часовой стрелки) или 1 (вращение по часовой стрелке). По умолчанию trigger=1
 */

int linear_displacement_S(float omega, float S, int step_split=1, int trigger=1) {
  // Считаем количество микрошагов
  int microstep_count = round((S / l) * 200 * steps[step_split - 1][0]) - trunc((S / l) * 200) * steps[step_split - 1][0];
  
  // Считаем количество шагов
  int step_count = trunc(200 * S / l);

  if(microstep_count == 0) {
    step_count = step_count - 1;
    microstep_count = 200 *  steps[step_split - 1][0];
  }
  
  // Задаём направление вращения
  digitalWrite(DIR, trigger);
  
  int SPEED = round(1000 * S / (omega * l /(2 * pi)));
 
  if(step_count > 0) {
    // Задаем полношаговый режим
    for(int i = 0; i < 3; i++) {
      digitalWrite(pin_steps[i], steps[0][i + 1]);
    } 
    for(int i = 0; i < step_count; i++) {
      digitalWrite(STEP, 1);
      delay(SPEED);
      digitalWrite(STEP, 0);
      delay(SPEED);
    }
    
    // Задаем микрошаговый режим
    for(int i = 0; i < 3; i++) {
      digitalWrite(pin_steps[i], steps[step_split - 1][i + 1]);
    }
    for(int i = 0; i < microstep_count; i++) {
      digitalWrite(STEP, 1);
      delay(SPEED);
      digitalWrite(STEP, 0);
      delay(SPEED);
    }
  }
  else {
    // Задаем микрошаговый режим
    for(int i = 0; i < 3; i++) {
      digitalWrite(pin_steps[i], steps[step_split - 1][i + 1]);
    }
    for(int i = 0; i < microstep_count; i++) {
      digitalWrite(STEP, 1);
      delay(SPEED);
      digitalWrite(STEP, 0);
      delay(SPEED);
    }
  }
  if(trigger)
    coordinates = coordinates + S;
  else
    coordinates = coordinates - S;
}


/*
 * Данная функция предназначена для линейного перемещения по заданным координатам.
 * omega - необходимая угловая скорость в радианах в секунду.
 * finish_coordinate - координата конечной точки траектории.
 *  step_split - параметр, отвечающий за дробление шага; он может принимать следующие значения: 
 *  1 - полный шаг, 2 - полушаговый режим, 3 - дробление шага 1/4, 4 - дробление шага 1/8 и 5 - дробление шага 1/16. По умолчанию step_split=1.
 */

int linear_displacement_coordinate(float omega, float finish_coordinate, int step_split=1) {
  // Считаем перемещение
  float S = finish_coordinate - coordinates;
  
  // Задаём направление вращения и записываем конечные координаты
  if(S > 0) {
    digitalWrite(DIR, HIGH);
  }
  else {
    digitalWrite(DIR, LOW);
    S = abs(S);
  }
  
  coordinates = finish_coordinate;
  
  // Считаем количество микрошагов
  int microstep_count = round((S / l) * 200 * steps[step_split - 1][0]) - trunc((S / l) * 200) * steps[step_split - 1][0];
  
  // Считаем количество шагов
  int step_count = trunc(200 * S / l);

  if(microstep_count == 0) {
    step_count = step_count - 1;
    microstep_count = 200 *  steps[step_split - 1][0];
  }
  
  int SPEED = round(1000 * S / (omega * l / (2 * pi)));
  
  if(step_count > 0) {
    // Задаем полношаговый режим
    for(int i = 0; i < 3; i++) {
      digitalWrite(pin_steps[i], steps[0][i + 1]);
    }
    for(int i = 0; i < step_count; i++) {
      digitalWrite(STEP, 1);
      delay(SPEED);
      digitalWrite(STEP, 0);
      delay(SPEED);
    }
    
    // Задаем микрошаговый режим
    for(int i = 0; i < 3; i++) {
      digitalWrite(pin_steps[i], steps[step_split - 1][i + 1]);
    }
    for(int i = 0; i < microstep_count; i++) {
      digitalWrite(STEP, 1);
      delay(SPEED);
      digitalWrite(STEP, 0);
      delay(SPEED);
    }
  }
  else {
    // Задаем микрошаговый режим
    for(int i = 0; i < 3; i++) {
      digitalWrite(pin_steps[i], steps[step_split - 1][i + 1]);
    }
    for(int i = 0; i < microstep_count; i++) {
      digitalWrite(STEP, 1);
      delay(SPEED);
      digitalWrite(STEP, 0);
      delay(SPEED);
    }
  }
}


/*
 * Данная функция отвечает за поворот двигателя на заданный угол.
 * omega - необходимая угловая скорость в радианах в секунду.
 * alpha - угол поворота в градусах.
 * step_split - параметр, отвечающий за дробление шага; он может принимать следующие значения: 
 *  1 - полный шаг, 2 - полушаговый режим, 3 - дробление шага 1/4, 4 - дробление шага 1/8 и 5 - дробление шага 1/16. По умолчанию step_split=1.
 *  trigger - параметр, отвечающий за направление вращения двигателя.
 *  Он принимает значения 0 (вращение против часовой стрелки) или 1 (вращение по часовой стрелке). По умолчанию trigger=1.
*/

int rotation_angle_control(float omega, float alpha, int step_split=1, int trigger=1) {
  // Считаем перемещение
  float S = l * (alpha / 360);
  
  // Считаем количество микрошагов
  int microstep_count = round((S / l) * 200 * steps[step_split - 1][0]) - trunc((S / l) * 200) * steps[step_split - 1][0];
  
  // Считаем количество шагов
  int step_count = trunc(200 * S / l);

  if(microstep_count == 0) {
    step_count = step_count - 1;
    microstep_count = 200 *  steps[step_split - 1][0];
  }
  
  // Задаём направление вращения
  digitalWrite(DIR, trigger);
  
  int SPEED = round(1000 * S / (omega * l / (2 * pi)));
  
  if(step_count > 0) {
    // Задаем полношаговый режим
    for(int i = 0; i < 3; i++) {
      digitalWrite(pin_steps[i], steps[0][i + 1]);
    }
    for(int i = 0; i < step_count; i++) {
      digitalWrite(STEP, 1);
      delay(SPEED);
      digitalWrite(STEP, 0);
      delay(SPEED);
    }
    
    // Задаем микрошаговый режим
    for(int i = 0; i < 3; i++) {
      digitalWrite(pin_steps[i], steps[step_split - 1][i + 1]);
    }
    for(int i = 0; i < microstep_count; i++) {
      digitalWrite(STEP, 1);
      delay(SPEED);
      digitalWrite(STEP, 0);
      delay(SPEED);
    }
  }
  else {
    // Задаем микрошаговый режим
    for(int i = 0; i < 3; i++) {
      digitalWrite(pin_steps[i], steps[step_split - 1][i + 1]);
    }
    for(int i = 0; i < microstep_count; i++) {
      digitalWrite(STEP, 1);
      delay(SPEED);
      digitalWrite(STEP, 0);
      delay(SPEED);
    }
  }
  if(trigger)
    coordinates = coordinates + S;
  else
    coordinates = coordinates - S;
}


// Данная функция возвращает текущую позицию двигателя

int get_position() {
  return coordinates;
}
