<h1>Математическая модель 6-осевого робота</h1>

Внешний вид окна программы представлен на рисунке 1. 

![image](https://github.com/user-attachments/assets/e862d406-d202-4497-8d65-30279b7365c5)

Рисунок 1 – Рабочее окно программы

В левой части окна располагаются панель управления, содержащая набор входных параметров для шести сочленений (узлов), и настройки для поворота вида по трём осям. Правую часть окна занимает изображение трёхмерной системы координат, в которой по заданным входным параметрам будет строиться проекция положения робота (на рисунке изображена тёмно-зелёным цветом).

<h2>Краткое описание методики расчёта</h2>

Математическая модель основана на использовании параметров Денавита-Хартенберга, описывающих вращательные и поступательные связи между соседними звеньями кинематической цепи:

* Угол θ (°) – угол поворота вокруг оси Z предыдущего звена.

* Длина a (м) – расстояние между осями Z двух последовательных звеньев вдоль оси X.

* Длина d (м) – смещение вдоль оси Z от одного звена к следующему.

* Угол α (°) – угол наклона между осями Z двух звеньев относительно оси X.

Данные параметры используются для составления матриц Денавита-Хартенберга, которые можно записать следующим образом:

![image](https://github.com/user-attachments/assets/fd5da8f1-5ee0-458c-8ce8-da3e5055700a)

Можно заметить, что последний столбец матрицы T<sub>i</sub> содержит координаты положения i-го сочленения (значения в первых трёх строках). Последовательно перемножив матрицы каждого сочленения, можно найти координаты последнего сочленения, которые выводятся по результатам вычислений в статусной строке программы.

<h2>Использование и возможности программы</h2>

При запуске открывается окно программы с нулевыми начальными значениями параметров для каждого сочленения. Пользовательский ввод параметров запускает процесс расчёта координат, результаты которого схематично отображаются в выбранной системе координат и выводятся в статусной строке. 

Для удобства использования реализованы функции сохранения и загрузки параметров, доступные в меню «Файл». В данном репозитории для примера представлен файл «example-joints.json», который можно открыть с помощью функции загрузки параметров.

Систему координат можно свободно вращать вокруг трёх осей, таким образом симулируется трёхмерное представление схемы робота. По умолчанию проекция строится в плоскости XOZ. Для наблюдения проекции в плоскости XOY нужно установить поворот 90° вокруг оси OX.  Для наблюдения проекции в плоскости YOZ нужно установить поворот -90° вокруг оси OZ. 
