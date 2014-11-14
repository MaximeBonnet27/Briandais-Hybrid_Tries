#! /usr/bin/gnuplot

set terminal png medium size 1980,1020
set output "result.png"
set yrange [:] reverse
plot 'plot_result' using 2:3:1 with labels 


