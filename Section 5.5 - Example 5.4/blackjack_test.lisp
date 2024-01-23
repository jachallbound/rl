#!/usr/bin/sbcl --script
;; THERE IS NO GOD HERE. THESE LISPS ARE MADE OF BLOOD.

; Attempting to understand this line from Sutton:
; `for ratio = rho then (* ratio rho)` (blackjack3-rollout-one-state.lisp:37)
; I believe that if any value of rho is zero, all subsequent values of ratio will be zero
; Is this what we want?

; Define a vector
(defvar rho_v)
(setf rho_v (vector 0.1 0.2 0.0 0.4 0.5 0.6))

; Define an iterator
(defvar i 0)

; Loop, multiply each element of array rho_v(i) * rho_v(i-1) (sort of)
(loop with rho = 0.1                 ; starting rho value
    for ratio = 1 then (* ratio rho) ; start ratio at 1, then after first iterator: ratio = ratio * rho
    do (setq rho (aref rho_v i))     ; set rho to next value in rho_v
    (incf i)                         ; increment i iterator (index of rho_v)
    do (print i)                     ; Print
    do (print rho)                   ; Print
    do (print ratio)                 ; Print
    repeat 6                         ; Repeat loop length of rho_v
)

; Above loop expands Sutton's code (I think).
; Print out does indeed prove above hypothesis.