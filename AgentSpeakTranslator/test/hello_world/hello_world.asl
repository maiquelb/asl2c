!start.

+!start : not(started)
  <- print("starting...");
     +started;
     +testSetable(0);
     !count. // new focus!
     
+!count : testSetable(X)
  <-  print("counting...");
      +testSetable(X);
      !count.
  

