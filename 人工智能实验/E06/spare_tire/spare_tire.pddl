(define (problem prob)
 (:domain spare_tire)
 (:objects Flat Spare -physob Axle Trunk Ground - location)
 
 (:init 
  (Tire Flat)
  (Tire Spare)
  (At Flat Axle)
  (At Spare Trunk)

)
 (:goal
  (At Spare Axle)
 ))
