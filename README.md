# stepper-motors
Данный репозиторий содержит библиотеку на основе фреймворка Arduino по управлению шаговым мотором с помощью драйвера ШД A4988.

# Докуметация
В библиотеке реализован следующий функционал:
1. Линейное перемещение на отрезок заданной длины
2. Линейное перемещение по заданным координатам
3. Поворот мотора на заданный угол
4. Поддержка всех возможных для данного драйвера дроблений шага (1, 1/2, 1/4, 1/8, 1/16)
5. Управление направлением вращения двигателя
6. Установка текущей позиции мотора

## Линейное перемещение на отрезок заданной длины
Данная функция предназначена для линейного перемещения на заданное расстояние.  
 *  omega - необходимая угловая скорость в радианах в секунду.
 *  S - модуль перемещения в мм.
 *  step_split - параметр, отвечающий за дробление шага; он может принимать следующие значения: 
1 - полный шаг, 2 - полушаговый режим, 3 - дробление шага 1/4, 4 - дробление шага 1/8 и 5 - дробление шага 1/16. По умолчанию step_split=1.
 *  trigger - параметр, отвечающий за направление вращения двигателя.
Он принимает значения 0 (вращение против часовой стрелки) или 1 (вращение по часовой стрелке). По умолчанию trigger=1

`linear_displacement_S(float omega, float S, int step_split=1, int trigger=1)`


