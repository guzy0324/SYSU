(define (domain boxman)
  (:requirements :strips :typing:equality
                  :universal-preconditions
                  :negative-preconditions)
  (:types box loc)
  (:predicates
    (blank ?p - loc)
    (man ?p - loc)
    (at ?b - box ?p - loc)
    (line ?p0 ?p1 ?p2 -loc)
    (adjacent ?p1 ?p2 -loc)
  )   

  (:action move
    :parameters (?from ?to - loc)
    :precondition (and (man ?from) (blank ?to) (adjacent ?from ?to))
    :effect (and (not (man ?from)) (not (blank ?to))
                  (man ?to) (blank ?from))
    )

  (:action push
    :parameters (?box - box ?p1 ?p2 ?p3 - loc)
    :precondition (and (man ?p1) (at ?box ?p2) (blank ?p3)
                        (line ?p1 ?p2 ?p3))
    :effect (and (not (man ?p1)) (not (at ?box ?p2)) (not (blank ?p3))
                  (man ?p2) (at ?box ?p3) (blank ?p1))
  )
)