package main

import (
  "fmt"
  "os"
  "strconv"
)

// The program initializes a global int64 array array[1000000]
const MAX int = 1000000

// Inside a function, the := short assignment statement can be used in place of
// a var declaration with implicit type.
// Outside a function, every statement begins with a keyword (var, func, and so on)
// and so the := construct is not available.

// doit(array,from,to,c)
// each value array[i] = i+1 , and to sum up all the entries in the array.
// This arrays is defined, but not populated by data in the main routine.
// The values and the summation are performed by the goroutines.
func doit(a []int64, from int, to int, c chan int64) {
// Each goroutine displays what portion it is doing.
  fmt.Println("doing ",from," -- ",to)
  // initializes sum with 0

  // for i start from "from" to "to"
    // array[i] = i+1
    // sum = sum + array[i]

  // pass sum to the channel by "c <- sum"

}


func main() {
  var a[MAX] int64

  // The program obtains N ,
  // which is the number of goroutines it should run, via the command line arguments.
  // For that you must import into your program packages os and strconv .
  // The object os.Args is an array of command line arguments and its length
  // can be obtained using the built-in function len() , i.e. len(os.Args) will
  // return the numebr of how many words were on the command line when the program was started.
  if len(os.Args) != 2 {
    fmt.Println("usage: program <number-of-goroutines>")
    return
  }
  // you must use strconv to convert the first argument which is a string into
  // the corresponding number, i.e. N = strconv.Atoi(os.Args[1])
  nof_goroutines, err := strconv.Atoi(os.Args[1])
  // If the first command argument cannot be converted to a number,
  // display an error message and terminate the program.
  if err != nil { //err not equal to a zero value (no error)
    fmt.Println("Wrong command line argument")
    return
  }

  fmt.Println("number of goroutines = ",nof_goroutines)

  // When passing the array that is defined and created in the main routine,
  // you must pass it to the goroutine as a slice and not as an array,
  // otherwise the goroutine would choke on the size of the array. Hence,
  // if the goroutine is named doit() , you will pass it in this way:
  // go doit(array[0:],from,to,c) where the from and to indicate which portion
  // the goroutine should populate with data and sum up, while c is the communications
  // channel that will be used to send the partial sum to the main routine.
  // To pass the array as an array would be go doit(array,from,to,c) .

  // The main routine dispatches N goroutines.
  // Each goroutine gets a portion of the range of the array to process,
  // i.e. to populate it with data and sum it up.
  // The portions should be as equitably sized as possible so should not
  // be one goroutine doing a huge job and another doing a small job. Thus, the
  // portions of the range each goroutine gets assigned should be almost equal,
  // i.e. any two should differ at most by 1.

  // define slice by MAX / nof_goroutines
  // get the remainder of MAX / nof_goroutines as well
  fmt.Println("slice = ",slice)
  // initializes c as a channel
  c := make(chan int64)

  // initializes from and to

  // to distribute slices evenly, you are going to split up the remainder and add 1
  // to the first few slices
  // i.e. MAX = 11, N = 3
  // 11/3 = 3 .... 2
  // at first: slice 1 = 1 - 3, slice 2 = 4 - 6, slice 3 = 7 - 9
  // then add the remainder 2 to slice 1 and 2 to ensure that the max diff between slices is 1
  // slice 1 = 1 - 4, slice 2 = 5 - 8, slice 3 = 9 - 11

  // run doit N times with in the loop you created to distrubute slices
    go doit(a[:],from,to,c)

  // When a goroutine finishes its job, it it sends the result via a communication channel
  // to the main routine that adds or those partial sums together and displays it on the screen.

 // add all goroutines result together
 // initializes y
 // in a for loop, get the value from channel chan c with <- c and pass that to a variable
 // add all values form all goroutines
  for nof_goroutines > 0 {
    ...
    nof_goroutines = nof_goroutines-1
  }

  fmt.Println(y)
}
// run as go run assgn4.go #
