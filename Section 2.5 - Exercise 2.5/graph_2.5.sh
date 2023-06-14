#!/bin/bash

paste Rr_sample.dat Rr_weighted.dat > Rr.dat && \
gnuplot -p -e "plot for [col=1:2] 'Rr.dat' using col with lines"