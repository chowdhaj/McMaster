package main

import (
  "fmt" 
  "os"
  "strconv"
)

const MAX int = 1000000

func doit(a []int64, from int, to int, c chan int64) {
  fmt.Println("doing ",from," -- ",to)
  sum := int64(0)
  for i := from; i <= to; i++ {
    a[i] = int64(i)+1
    sum = sum + a[i]
  }
  c <- sum // send sum to c
}


func main() {
  var a[MAX] int64
  
  if len(os.Args) != 2 {
    fmt.Println("usage: program <number-of-goroutines>")
    return
  }
  nof_goroutines, err := strconv.Atoi(os.Args[1])

  if err != nil {
    fmt.Println("Wrong command line argument")
    return
  }

  fmt.Println("number of goroutines = ",nof_goroutines)
  
  slice := MAX / nof_goroutines
  remainder := MAX % nof_goroutines
  fmt.Println("slice = ",slice)
  c := make(chan int64)
  from := 0
  to := 0   
  
  for true {
    to = from+slice-1
    if remainder > 0 {
      to = to+1
      remainder = remainder-1
    }
    if to > MAX-1 { 
      to = MAX-1
    }
    go doit(a[:],from,to,c)
    from = to+1
    if from >= MAX {
      break
    }   
  }
    
  y := int64(0)
  for nof_goroutines > 0 {
    x := <-c
    y = y+x
    nof_goroutines = nof_goroutines-1
  }

  fmt.Println(y)
}
