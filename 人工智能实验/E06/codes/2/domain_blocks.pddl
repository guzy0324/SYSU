(define (domain blocks)
    (:requirements :strips :typing:equality
                    :universal-preconditions
                    :conditional-effects
                    :negative-preconditions)
    (:types physob)
    (:predicates
        (ontable ?x - physob)
        (clear ?x - physob)
        (on ?x ?y - physob))
    (:action move
        :parameters (?x ?y - physob)
        :precondition (and (clear ?x) (clear ?y) (not (= ?x ?y)))
        :effect (and (forall (?z - physob)
                            (when (on ?x ?z)
                                (and (not (on ?x ?z)) (clear ?z))))
                        (when (ontable ?x) (not (ontable ?x)))
                        (not (clear ?y))
                        (on ?x ?y))
    )
    (:action moveToTable
        :parameters (?x - physob)
        :precondition (and (clear ?x) (not (ontable ?x)))
        :effect (and (forall (?z - physob)
                            (when (on ?x ?z)
                                (and (not (on ?x ?z)) (clear ?z))))
                        (ontable ?x))
    )
)