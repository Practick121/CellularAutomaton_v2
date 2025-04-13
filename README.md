# CellularAutomaton_v2
Программа позволяет выбрать конфигурацию и запустить симуляцию [клеточного автомата](https://ru.wikipedia.org/wiki/Клеточный_автомат) (К.А.). Написано с использованием библиотеки [SFML](https://www.sfml-dev.org/).\
Размер таблицы - 500 * 500.
На выбор предоставляются следующие клеточные автоматы:\
(Birth/Survive- количество соседних клеток, чтобы мёртвая клетка стала живой/чтобы живая клетка осталась живой)
- Жизнь: B3/S23
- Лабиринт: B3/S12345
- Пещеры: B5678/S45678
- ДеньНочь: B3678/S34678
- Диамёба: B35678/S5678
- Ковёр: B234/S

Отдельно разберу каждую кнопку:\
**RUN** - запускает симуляцию с заданным справа значением TPS (зелёные кнпоки). TPS - ticks per second или же сколько поколений сменится за секунду.\
**STOP** - останавливает симуляцию.\
**ONE STEP** - переводит симуляцию в следующее поколение, а затем останавливает.\
**GENERATE** - случайно заполняет таблицу. Шанс появления живой клетки - 50%.\
**GENERATE SQUARE** - заполняет центральный квадрат (21×21) живыми клетками, все остальные клетки делает мёртвыми. Хорошо подходит для таких клеточный автоматов, как лабиринт и ковёр.\
**CLEAN** - заполняет всё поле мёртвыми клетками.

Далее идут кнопки, переключающие режим клеточного автомата.\
**MAZE** - лабиринт. Заполняет всю карту проходами толщиной в одну клетку. Примечателен, если стартовать с квадрата.\
**CAVES** - пещеры. Генерирует карту, напоминающую систему пещер, или муравейник. При чередовании c Maze и стартом с квадрата может получится необычный рисунок напоминающий какой-то герб.\
**LIVE** - база всех к.а. Через некоторое время движени становится цикличным или его нету.\
**DAYNIGHT** - день и ночь, один из самых известных кл. автом. Примечателен тем что если все клетки инвертировать, то поведение симуляции будет таким с точностью до инверсии. Очень долго не прекращает активность.\
**AMOEBA** - амёба. Вообще, название я подсмотрел с вот этого сайта - [10 удивительно зрелищных простейших клеточных автоматов](https://habr.com/ru/articles/718620/) и вообще спасибо создателю сайта, он вдохновил меня на создание этого приложения. Симуляция будет состоять из крупных скоплений клеток, по поведению похожих на амёбу - поглощает, сливаясь воедино, стремится к округлым формам.\
**CARPET** - ковёр. Действительно, узор будет похож на ковёр, если начать с квадрата. Клеточный автомат, в котором никакая живая клетка не выживает в следующем поколении.\
В правом верхнем углу можно выбрать цвет кисти и рисовать в таблице.\
Также снизу находятся ещё две кнопки - **UPLOAD** - выгрузить данные таблицы в файл .txt, и **OPEN** - открыть .txt файл.\
Вот как преобразуется таблица в файл:\
![глайдер](https://github.com/user-attachments/assets/0738a0d6-b43f-4f3a-9479-b592e7116e8a "глайдер")\
->\
01000\
00100\
11100\
00000\
В таком же формате считывается открываемый файл.\
Открываемый файл - data.txt  
Выходной файл - out1.txt, out2.txt, .. out10.txt. **При наличии 10 файлов out, программа не будет делать upload!**\
Также в приложении реализовано приближение камеры - на колёсико мыши. Но пока эта функция работает не совсем корректно.

------
Программа написана на C++14 (это причина, почему программа стала отдельным репозиторием) с использование библиотеки [SFML](https://www.sfml-dev.org/) (2.6.2)
в среде разработки VisualStudio2022.


Это мой первый проект на C++, который к тому же использует многопоточность. Так как с C++ я знаком практически только со стороны олимпиадного программирования, в коде могут присутсвовать очень странные решения, 
кривое использование ООП. Буду признателен если вы укажете на недочёты в реализации.\
Проект будет обновляться
# Версии
## V2.0
#### Нововведения:
- Python -> C++.
- Добавлено приближение камеры.
- Большее разнообразие клеточных автоматов (3->6).
- Добавлен регулятор скорости (5, 15, 30, 60 TPS).
- ~~Больший размер таблицы~~ Более высокая скорость симуляции (размер таблицы - 200×200).
- Изменена иконка.
## V2.1
#### Нововведения:
- Добавление многопоточности. Один дополнительный поток для графики (отрисовки всех спрайтов), другой для взаимодействия с пользователем (то есть в нём проверяется нажатие кнопок и рисование кистью). \
Вследствии этого стало возможным увеличить размер таблицы. Теперь она **500×500**, а также скорость симуляции практически не зависит от скорости отрисовки. \
Но появились проблемы, которые пока не исправлены (я не знаю как их исправить, пока что), например - зум работает плохо: при резком увеличении таблица будет отрисовываться неправильно, но на следующем кадре уже будет всё норм. И другие мелкие.
- Добавлены текстуры для кнопок и задний фон, чтобы программа лучше выглядела :).
- Добавлена кнопка 120 tps.
#### Исправления:
- название программы отображается корректно.
- живые клетки не вылезают за границы таблицы.
## V2.2
#### Нововведения:
- Добавлена новая функция - теперь можно сгенерировать случайный клеточный автомат  (со случайными множеством чисел для рождения клетки и для выживания клетки) c помощью кнопки NEWRANDOM (также устанавливает этот К.А. в текущий). SETRANDOM устанавливает в текущий К.А. случайно сгенерированный (не генерирует новый К.А.). Также справа посередине экрана будет отображаться параметры текущего К.А.
- Добавлены ползунки, для скорости симуляции (TPS) и для шанса появления клетки при генерации (GENERATE и GENERATESQUARE). Старые кнопки для регуляции скорости убраны.
- Добавлена новая функция - теперь можно переключать тип проверки на соседство. TYPENEIGHBOURS:8 - соседями являюся клетки по стороне и по диагонали. TYPENEIGHBOURS:4 - соседями являются клетки по стороне.
- Теперь поверхность симуляции не ограниченный квадрат, а тор (т.е. клетка (499, 499) соседняя с (0, 0).
#### Другие изменения:
- Значительно улучшена производительность. Переделана отрисовка таблицы. Из-за этого **зум был убран**.
- Добавлена 32-битная версия в релиз (не факт что действительно работает).
#### Мелкие исправления:
- Теперь при расфокусе кнопки не будут нажиматься. Также кнопки теперь не нажимаются, если провести по ним зажатой мышью.
- Убран поток, взаимодействующий с пользователем. (Из-за него возникали проблемы - пока этот поток записывает изменения в таблицу, основной поток пересчитывает ее, из-за чего, в частности, кнопка Clean очищала только нижнюю часть экрана)
