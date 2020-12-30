#include <math.h>

#define MS1 3
#define MS2 4
#define MS3 5
#define STEP 6
#define DIR 7

const int r = 20;
const int pin_steps[3] = {MS1, MS2, MS3};
const int steps[5][4]={
    {1,0,0,0}, // 1
    {2,1,0,0}, // 1/2
    {4,0,1,0}, // 1/4
    {8,1,1,0}, // 1/8
    {16,1,1,1} // 1/16
    };

const float pi = 3.1415;

float coordinates = 0.0;

/* Данная функция предназначена для линейного перемещения. step_split - параметр, отвечающий за дробление шага; он может принимать следующие значения: 
 *  1 - полный шаг, 2 - полушаговый режим, 3 - дробление шага 1/4, 4 - дробление шага 1/8 и 5 - дробление шага 1/16.
*/
int linear_displacement_S(float omega, float S, int step_split=1, int trigger=1) {
  // Считаем количество микрошагов
  int microstep_count = round((S / (2 * pi * r)) * 200 * steps[step_split - 1][0]) - trunc((S / (2 * pi * r)) * 200 * steps[step_split - 1][0]);
  // Считаем количество шагов
  int step_count = trunc(S / (2 * pi * r)) * 200;
  // Задаём направление вращения
  digitalWrite(DIR, trigger);
  int SPEED = round(S / (omega * r));
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


int linear_displacement_coordinate(float omega, float finish_coordinate, int step_split=1) {
  // Считаем перемещение
  float S = finish_coordinate - coordinates;
  // Задаём направление вращения и записываем конечные координаты
  if(S > 0) {
    digitalWrite(DIR, HIGH);}
  else {
    digitalWrite(DIR, LOW);}
  coordinates = finish_coordinate;
  // Считаем количество микрошагов
  int microstep_count = round((S / (2 * pi * r)) * 200 * steps[step_split - 1][0]) - trunc((S / (2 * pi * r)) * 200 * steps[step_split - 1][0]);
  // Считаем количество шагов
  int step_count = trunc(S / (2 * pi * r)) * 200;
  int SPEED = round(S / (omega * r));
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


int rotation_angle_control(float omega, float alpha, int step_split=1, int trigger=1) {
  // Считаем перемещение
  float S = 2 * pi * r * (alpha / 360);
  // Считаем количество микрошагов
  int microstep_count = round((S / (2 * pi * r)) * 200 * steps[step_split - 1][0]) - trunc((S / (2 * pi * r)) * 200 * steps[step_split - 1][0]);
  // Считаем количество шагов
  int step_count = trunc(S / (2 * pi * r)) * 200;
  // Задаём направление вращения
  digitalWrite(DIR, trigger);
  int SPEED = round(S / (omega * r));
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


int get_position() {
  return coordinates;
}
