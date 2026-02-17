# Скрипт для отображения всех методов интерполяции на одном графике
set encoding utf8
set samples 100

# Настройка терминала для вывода в новое окно
set terminal x11 persist enhanced font "Helvetica,12"

# Точки интерполяции
x1=0.896; x2=0.774; x3=0.955

# Точные коэффициенты полинома 5-й степени (из polyfit)
a5=6.67775349; a4=-22.9328474; a3=33.48568768
a2=-24.3730959; a1=10.05510155; a0=-1.35520392

# Полином интерполяции (Лагранж=Ньютон=Канонический)
f(x)=a5*x**5 + a4*x**4 + a3*x**3 + a2*x**2 + a1*x + a0
fL(x)=f(x); fN(x)=f(x); fC(x)=f(x)

# Настройка графика
set grid
set key left top
set xlabel "x"
set ylabel "y"
set title "Compersion of interpolation methods"

# Построение всех методов на одном графике
plot [0.65:1.05] '-' w p pt 7 ps 1.8 lw 3 lc rgb "black", \
     fL(x) w l lw 2 lc rgb "blue" t "lagrange", \
     fN(x) w l lw 2 lc rgb "green" dt 2 t "newton", \
     fC(x) w l lw 2 lc rgb "magenta" dt 3 t "canonical", \
     '-' u 1:2 w l lw 2.5 lc rgb "cyan" dt 4 t "linear", \
     '-' u 1:2 smooth csplines w l lw 2 lc rgb "red" t "spline"
0.68 0.80866
0.73 0.89492
0.80 1.02964
0.88 1.20966
0.93 1.34087
0.99 1.52368
e
0.68 0.80866
0.73 0.89492
0.80 1.02964
0.88 1.20966
0.93 1.34087
0.99 1.52368
e
0.68 0.80866
0.73 0.89492
0.80 1.02964
0.88 1.20966
0.93 1.34087
0.99 1.52368
e
