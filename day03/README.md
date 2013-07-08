ASM and C Flow Control (en)
===

Theory
---

 + C basics @avelenko
 
 1) Переменные и типы данных (char, short, long, long long, int, float, double)
 
 2) базовые операции (&, |, ~, &&, ||, !, <<, >>, +, -, ++, --, +=, -=, ==, !=). Шутка про китайский язык и иероглифы
 
 3) Ветвление

	3.1) синтаксис
	
	3.2) асм
 
 4) Циклы

	4.1) Как бегать по массиву
	
	4.2) Запомните паттерн, пользуйтесь им. while - везде, где есть циклы. for - там где С.
	
	4.3) Синтаксис
	
	4.4) АСМ
 
 5) Пойнтеры

	5.1) Адресы в памяти
	
	5.2) Массивы
	
	5.3) Pointer arithmetic
	
	5.4) Cycles revisited
 
 6) Функции

	6.1) Сигнатура функции
	
	6.2) асм
	
	6.3) СТЭК
	
	6.5) Скоуп
	
	6.6) Пас бай вэлью, пас бай рэференс
	
	6.7) Кажая экономия на предыдущем этапе приводит к тройным затратам на последующем
 
/////////////////////////////////////////////

 7) Как скомпилировать прогу для самых маленьких

	7.1) linux address, pwd, home, cd, ls, editor(?), gcc -W -Wall -0 source result, ./

	7.2) Параметры командной строки в коде
	
/////////////////////////////////////////////
 7) Читаемость - приоритет
 8) function pointers
 9) void *, casting
/////////////////////////////////////////////
 1) OS basics @avelenko
 2) Больше чем 1 программа - что делать?
 3) Файловая система
 4) Драйверы
 5) Open, Close, Read, Write, buffer


 Practice
--

 + Work with filesystem in C @avelenko
 Implement reverse a string, remove double letters, CP, MOV, copy file in reverse, remove all instances of some letter in a file, remove all instances of some pattern in a file (simple grep)

Dark Side
---

"Tail Recursion — the declarative alternative to loops".
Lecture plan:

 + Recap what are the implications of functional languages
 + Immutability and loops
 + Transforming a loop into recursive calls
 + Tail recursion optimization

Контроль потока выполнения на ассамблерах и языке C (ru)
===

TODO
