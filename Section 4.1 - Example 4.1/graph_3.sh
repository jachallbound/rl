#!/bin/bash

paste Rr_weighted_0.1.dat Rr_weighted_0.4.dat > Rr.dat && \
gnuplot -p -e "plot for [col=1:2] 'Rr.dat' using col with lines"