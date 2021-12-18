#!/usr/bin/racket
#lang racket

(require 2htdp/image)
(require 2htdp/universe)


(define LIGHT-RADIUS 10)
(define DIST (* LIGHT-RADIUS 3))
(define RED 0)
(define YELLOW 1)
(define GREEN 2)

(define (draw-tl-el state design)
  (circle LIGHT-RADIUS design state))

(define (generate-tl item-1 item-2 item-3)
  (overlay/xy
   item-1
   DIST 0
   (overlay/xy
    item-2
    DIST 0
    item-3)))

(define red-active
  (generate-tl (draw-tl-el "red" "solid")
               (draw-tl-el "yellow" "outline")
               (draw-tl-el "green" "outline")))
(define yellow-active
  (generate-tl (draw-tl-el "red" "outline")
               (draw-tl-el "yellow" "solid")
               (draw-tl-el "green" "outline")))
(define green-active
  (generate-tl (draw-tl-el "red" "outline")
               (draw-tl-el "yellow" "outline")
               (draw-tl-el "green" "solid")))

(define (tl-render ws)
  (cond [(= ws RED) red-active]
        [(= ws YELLOW) yellow-active]
        [(= ws GREEN) green-active]))

(define (tl-next ws)
  (modulo (+ ws 1) 3))

(define (traffic-light-simulation initial-state)
  (big-bang initial-state
    [to-draw tl-render]
    [on-tick tl-next 1]))

(traffic-light-simulation RED)
