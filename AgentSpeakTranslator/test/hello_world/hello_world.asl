// initial beliefs
testBelief(0).

// initial goal
!start.

+!start : not started
  <- print;
     +started;
     +testSetable(0);
     !start. // new focus!
  

