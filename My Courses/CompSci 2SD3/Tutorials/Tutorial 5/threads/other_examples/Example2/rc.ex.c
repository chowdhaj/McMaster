counter++; // 1 line

// counter is in ram
// ram -> register

// lw x5, (counter)
// add counter, counter, 1
// sw x5, (counter)

COUNTER = 50000;
mutex;

## JIM
----- BLOCKED -----  // STUCK // FROZEN // HUNG JURY
// acquire the green_card/lock
// lw x5, (counter)          // x5 = 0        
// add counter, counter, 1   // x5 = 50000
// sw x5, (counter)          // counter = 50000

## BOB
---- BLOCKED ----
// try to acquire the green_card/lock // STUCK // FROZEN // HUNG JURY
// lw x5, (counter)         // x5 = 95000
// add counter, counter, 1  // x5 = 100000
// sw x5, (counter)
// release the green_card/lock
