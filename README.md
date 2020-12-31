# stepper-motors

Данный репозиторий содержит библиотеку на основе фреймворка Arduino по управлению шаговым мотором с помощью драйвера ШД A4988.

## Докуметация

В библиотеке реализован следующий функционал:
1. Линейное перемещение на отрезок заданной длины
2. Линейное перемещение по заданным координатам
3. Поворот мотора на заданный угол
4. Поддержка всех возможных для данного драйвера дроблений шага (1, 1/2, 1/4, 1/8, 1/16)
5. Управление направлением вращения двигателя
6. Установка текущей позиции мотора
7. Задание начальной позиции мотора

### Импорт
`#include "stepperLib"`

После этого все функции вызываются обычным образом. См. примеры

### Линейное перемещение на отрезок заданной длины
Данная функция предназначена для линейного перемещения на заданное расстояние.  
 *  omega - необходимая угловая скорость в радианах в секунду.
 *  S - модуль перемещения в мм.
 *  step_split - параметр, отвечающий за дробление шага; он может принимать следующие значения: 
1 - полный шаг, 2 - полушаговый режим, 3 - дробление шага 1/4, 4 - дробление шага 1/8 и 5 - дробление шага 1/16. По умолчанию step_split=1.
 *  trigger - параметр, отвечающий за направление вращения двигателя.
Он принимает значения 0 (вращение против часовой стрелки) или 1 (вращение по часовой стрелке). По умолчанию trigger=1

`linear_displacement_S(float omega, float S, int step_split=1, int trigger=1)`

### Линейное перемещение по заданным координатам
Данная функция предназначена для линейного перемещения по заданным координатам.
 * omega - необходимая угловая скорость в радианах в секунду.
 * finish_coordinate - координата конечной точки траектории (в мм).
 * step_split - параметр, отвечающий за дробление шага; он может принимать следующие значения: 
1 - полный шаг, 2 - полушаговый режим, 3 - дробление шага 1/4, 4 - дробление шага 1/8 и 5 - дробление шага 1/16. По умолчанию step_split=1.

`linear_displacement_coordinate(float omega, float finish_coordinate, int step_split=1)`

### Поворот мотора на заданный угол
Данная функция отвечает за поворот двигателя на заданный угол.
 * omega - необходимая угловая скорость в радианах в секунду.
 * alpha - угол поворота в градусах.
 * step_split - параметр, отвечающий за дробление шага; он может принимать следующие значения: 
1 - полный шаг, 2 - полушаговый режим, 3 - дробление шага 1/4, 4 - дробление шага 1/8 и 5 - дробление шага 1/16. По умолчанию step_split=1.
 *  trigger - параметр, отвечающий за направление вращения двигателя.
Он принимает значения 0 (вращение против часовой стрелки) или 1 (вращение по часовой стрелке). По умолчанию trigger=1.

`rotation_angle_control(float omega, float alpha, int step_split=1, int trigger=1)`

### Установка текущей позиции мотора
Данная функция возвращает текущую позицию двигателя (в мм). Она не принимает никаких параметров

`get_position()`

### Задание начальной позиции мотора
Данная функция позволяет задать текущую позицию двигателя (в мм). Это применимо, например, при начале движения или при ручном вмешательстве.
Она принимает единственный параметр - координаты начальной позиции.

`set_position(coordinate)`

### Поддержка всех возможных для данного драйвера дроблений шага и управление направлением вращения двигателя
Данный функционал реализован в каждой функции, связанной с перемещением. Он принимается в качестве параметров.

## Примеры использования
Важно! Код каждого примера исполняется независимо от других примеров. В общем случае (кроме двух последних примеров) начальная позиция имеет координату 0.0

1) `linear_displacement_S(3.0, 10.0);`

2) `linear_displacement_coordinate(3.0, -3.7, step_split=4);`

3) `rotation_angle_control(3.0, 45.0, trigger=0);`

4) `get_position();`

   Вывод: -5.0

5) `set_position(12.4);`

   `get_position();`

   Вывод: 12.4
6) `#include "stepperLib.h"`

   `void setup(){`
   
      `Serial.begin(9600);`
      
      `linear_displacement_S(3.0, 10.0);`
      
      `Serial.println(get_position());`
   `}`

   `void loop() {}`

Вывод: 10.0
