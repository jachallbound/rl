#!/bin/bash

# graph -T X Rr_greedy.dat Rr_0.01.dat Rr_0.1.dat

graph -T png \
  -g 3 \
  -C --pen-colors "$pencolors" \
  Rr_0.01.dat Rr_greedy.dat Rr_0.1.dat \
  > graph.png