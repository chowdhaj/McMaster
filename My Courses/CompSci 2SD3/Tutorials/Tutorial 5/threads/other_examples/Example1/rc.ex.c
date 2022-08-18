counter++; // 1 line

// counter is in ram
// ram -> register

// lw x5, (counter)
// add counter, counter, 1
// sw x5, (counter)

COUNTER = 50000;

## JIM
// lw x5, (counter)          // x5 = 0        
// add counter, counter, 1   // x5 = 50000
// sw x5, (counter)          // counter = 50000

## BOB
// lw x5, (counter)         // x5 = 95000
// add counter, counter, 1  // x5 = 100000
// sw x5, (counter)
