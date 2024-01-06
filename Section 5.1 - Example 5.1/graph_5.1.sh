#!/usr/bin/gnuplot -persist
# set terminal pngcairo  transparent enhanced font "arial,10" fontscale 1.0 size 600, 400 
# set output 'surface1.4.png'
#

#  set grid nopolar
# set grid xtics nomxtics ytics nomytics noztics nomztics nortics nomrtics \
#  nox2tics nomx2tics noy2tics nomy2tics nocbtics nomcbtics
# set grid layerdefault   lt 0 linecolor 0 linewidth 0.500,  lt 0 linecolor 0 linewidth 0.500
# set samples 21, 21
# set isosamples 11, 11
# set style data lines
# set title "Blackjack: Monte Carlo First-visit Prediction" 
# set xlabel "Agent State" 
# set xlabel  offset character -3, -2, 0 font "" textcolor lt -1 norotate
# set xrange [ -1.0 : 10.0000 ] noreverse nowriteback
# set x2range [ * : * ] noreverse writeback
# set ylabel "Dealer State" 
# set ylabel  offset character 3, -2, 0 font "" textcolor lt -1 rotate
# set yrange [ -1.0 : 20.0000 ] noreverse nowriteback
# set y2range [ * : * ] noreverse writeback
# set zlabel "Z axis" 
# set zlabel  offset character -5, 0, 0 font "" textcolor lt -1 norotate
# set zrange [ * : * ] noreverse writeback
# set cbrange [ * : * ] noreverse writeback
# set rrange [ * : * ] noreverse writeback
# set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
# NO_ANIMATION = 1
# splot 'V.dat'

 	

set title "Blackjack: Monte Carlo First-visit Prediction"
set xrange [-0.5:11]
set yrange [-0.5:21]

set grid
set hidden3d
splot 'V.dat' matrix with lines notitle

# based off of:
# http://gnuplot.info/demo/surface1.4.gnu