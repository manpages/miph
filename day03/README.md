ASM and C Flow Control (en)
===

Theory
---

###C basics @avelenko
 
 - Переменные и типы данных (char, short, long, long long, int, float, double)
 - базовые операции (&, |, ~, &&, ||, !, <<, >>, +, -, ++, --, +=, -=, ==, !=). Шутка про китайский язык и иероглифы
 - Ветвление
  - синтаксис
  - асм
 = Циклы
  - Как бегать по массиву
  - Запомните паттерн, пользуйтесь им. while - везде, где есть циклы. for - там где С.
  - Синтаксис
  - АСМ
 - Пойнтеры
  - Адресы в памяти
  - Массивы
  - Pointer arithmetic
  - Cycles revisited
 - Функции
  - Сигнатура функции
  - асм
  - СТЭК
  - Скоуп
  - Пас бай вэлью, пас бай рэференс
  - Кажая экономия на предыдущем этапе приводит к тройным затратам на последующем
 

###Tolchain

 - Как скомпилировать прогу для самых маленьких
  - linux address, pwd, home, cd, ls, editor(?), gcc -W -Wall -0 source result, ./
  - Параметры командной строки в коде
	

###Brainwashing
 - Читаемость - приоритет (!!!!!!!!!!!!!!)
 - function pointers
 - void *, casting

###OS

 - Больше чем 1 программа - что делать?
 - Файловая система
 - Драйверы
 - Open, Close, Read, Write, buffer


 Practice
--

 + Work with filesystem in C @avelenko
 Implement reverse a string, remove double letters, CP, MOV, copy file in reverse, remove all instances of some letter in a file, remove all instances of some pattern in a file (simple grep)

Dark Side
---
EITHER 


"Tail Recursion — the declarative alternative to loops".
Lecture plan:

 + Recap what are the implications of functional languages
 + Immutability and loops
 + Transforming a loop into recursive calls
 + Tail recursion optimization

OR

"The philosophy of recursion"
Lecture plan:

 + Definition of recursion
 + Recursive sequences
 + Methodology of recursion (What can we learn from recursive sequences as programmers?)
 + (if we have nuff time) Tail recursion

Контроль потока выполнения на ассамблерах и языке C (ru)
===

TODO
