#!/usr/bin/gnuplot -persist

set title "Monte Carlo Blackjack Policy"
set xlabel "Dealer State" 
set ylabel "Agent State"
set xrange [-0.5:11]
set yrange [-0.5:11]

set palette rgbformula -7,7,-7
set cbrange [0:1]
set cblabel "Action"
unset cbtics

set view map
set hidden3d
splot 'P.dat' matrix with image

# based off of:
# https://gnuplot.sourceforge.net/demo/heatmaps.1.gnu