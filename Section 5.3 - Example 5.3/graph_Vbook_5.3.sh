#!/usr/bin/gnuplot -persist

set title "Monte Carlo Blackjack V"
set xlabel "Dealer State" 
set ylabel "Agent State"
set xrange [-0.5:11]
set yrange [-0.5:11]

set palette rgbformula -7,7,-7
set cbrange [-1:1]
set cblabel "Action"
unset cbtics

set grid
set hidden3d
splot 'V.dat' matrix with lines

# based off of:
# http://gnuplot.info/demo/surface1.4.gnu