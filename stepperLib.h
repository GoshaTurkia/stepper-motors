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

#ifndef stepper_h
#define stepper_h
#include <Arduino.h>


// Объявление функций

/* 
 *  Данная функция предназначена для линейного перемещения на заданное расстояние.  
 *  omega - необходимая угловая скорость в радианах в секунду.
 *  S - модуль перемещения в мм.
 *  step_split - параметр, отвечающий за дробление шага; он может принимать следующие значения: 
 *  1 - полный шаг, 2 - полушаговый режим, 3 - дробление шага 1/4, 4 - дробление шага 1/8 и 5 - дробление шага 1/16. По умолчанию step_split=1.
 *  trigger - параметр, отвечающий за направление вращения двигателя.
 *  Он принимает значения 0 (вращение против часовой стрелки) или 1 (вращение по часовой стрелке). По умолчанию trigger=1
 */
 
int linear_displacement_S(float omega, float S, int step_split=1, int trigger=1);

/*
 * Данная функция предназначена для линейного перемещения по заданным координатам.
 * omega - необходимая угловая скорость в радианах в секунду.
 * finish_coordinate - координата конечной точки траектории.
 *  step_split - параметр, отвечающий за дробление шага; он может принимать следующие значения: 
 *  1 - полный шаг, 2 - полушаговый режим, 3 - дробление шага 1/4, 4 - дробление шага 1/8 и 5 - дробление шага 1/16. По умолчанию step_split=1.
 */
 
int linear_displacement_coordinate(float omega, float finish_coordinate, int step_split=1);

/*
 * Данная функция отвечает за поворот двигателя на заданный угол.
 * omega - необходимая угловая скорость в радианах в секунду.
 * alpha - угол поворота в градусах.
 * step_split - параметр, отвечающий за дробление шага; он может принимать следующие значения: 
 *  1 - полный шаг, 2 - полушаговый режим, 3 - дробление шага 1/4, 4 - дробление шага 1/8 и 5 - дробление шага 1/16. По умолчанию step_split=1.
 *  trigger - параметр, отвечающий за направление вращения двигателя.
 *  Он принимает значения 0 (вращение против часовой стрелки) или 1 (вращение по часовой стрелке). По умолчанию trigger=1.
*/

int rotation_angle_control(float omega, float alpha, int step_split=1, int trigger=1);

// Данная функция позволяет задать позицию мотора (например при старте)

int set_position(float coordinate);

// Данная функция возвращает текущую позицию двигателя

int get_position();

#endif
