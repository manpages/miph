Networking I (en)
===

Theory
---

### Computer networks @avelenko

#### Ehternet frames
 - Проблема передачи данных между компьютерами
 - Физика
  1. Понятие среды
  2. Приемник/передатчик
  3. Кодировка
  4. Шумы 
  5. Затухание
 - Логика
  1. Структура фрейма
  2. Обнаружение колизий
 
#### LAN
 - Проблема передачи информации между более чем двумя устройствами
 - Media Access Control
 - Методы расширения LAN
  1. Хаб
  2. Свич

#### Методы объединения LAN
  - Проблема передачи информации между физически отдалёнными устройствами

```
TODO: возможно надо сначала про маршрутизатор, а потом про IP
типа что "понатыкаем девайсов для объединения сеток" потом
а что если у нас будут колизии Media Access Control адресов
нужен как минимум новый address space
```

  - IP
   1. Структура IP пакета
   2. IPoE
  - Маршрутизатор
   1. Одновременное нахождение маршрутизатора в нескольких LAN
   2. Запрограммировано обеспечивать передачу IP пакетов
  - NAT
   1. IP Zones
   2. NAT
   3. NAT punching (?)

#### Контроль передачи данных
   - Проблема сетевого отказа
   - TCP
   - Класс задач для которых не нужен контроль прибытия и порядка прибытия пакетов
   - UDP

#### Одновременное использование сети
   - Проблема множества приложений
   - Как OS решает эту проблему
   - Port
   - TCP Socket, UDP Socket
   
// Настоятельно рекомендую выпилить нафиг из этого дня:

 8) Что делать с данными при получении? Сессионный и презентационный уровень. Конечные автоматы и формализация. 

 9) Уровень приложения. Браузер, хтмл, кофескрипт.

 10) Операционная система и инструменты. Ваер шарк, таблица маршрутизации.

 11) Сокеты в С.
 
 
Practice
---

 + Handling (virtual) sensor data in one thread using sockets

Dark Side
---

"Cowboy on Ranch: Accepting sockets in Erlang"

Here we look at the beautiful piece of software which Ranch/Cowboy is.
In order to figure out how can we accept a socket using this toolstack.

Lecture plan:

 + Recap: Erlang syntax and basic concepts
 + What is Ranch?
 + What is Cowboy?
 + How to accept sockets in this setup (reading source)?
 + How to send data over sockets in this setup (reading source)?
 + Okay, let's write it (live demo or handout [depending on amt of time]).

Сеть I (ru)
===

TODO
