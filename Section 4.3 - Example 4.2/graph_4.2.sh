#!/usr/bin/gnuplot -persist
unset key
unset parametric
set view map scale 1
set style data lines
set xtics border in scale 0,0 mirror norotate  autojustify
set ytics border in scale 0,0 mirror norotate  autojustify
set ztics border in scale 0,0 nomirror norotate  autojustify
set rtics axis in scale 0,0 nomirror norotate  autojustify
set title "Car rental policy" 
set xrange [0:20] noreverse nowriteback
set x2range [ * : * ] noreverse writeback
set xlabel "Cars at second location"
set yrange [0:20] noreverse nowriteback
set y2range [ * : * ] noreverse writeback
set ylabel "Cars at first location"
set zrange [ * : * ] noreverse writeback
set cblabel "Cars Moved" 
set cbrange [-5:5] noreverse nowriteback
set rrange [ * : * ] noreverse writeback
set palette rgbformulae 33, 13, 10
NO_ANIMATION = 1
splot "car_rental_policy.dat" matrix with image

# https://gnuplot.sourceforge.net/demo/heatmaps.1.gnu