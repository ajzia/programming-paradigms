// go run philosophers.go 12 17
package main

import (
	"hash/fnv"
	"fmt"
	"math/rand"
	"os"
	"sync"
	"time"
	"strconv"
)

var dining_philosophers sync.WaitGroup 
 
type Fork struct { 
	sync.Mutex
} 

const max_waiting_time = 50 * time.Millisecond

func philosopher(name string, left_fork *Fork, right_fork *Fork, no_meals int) {
  fmt.Printf("[%s] has joined the table:)\n", name)

	// sleeping for random amount of time
  h := fnv.New64a()
	h.Write([]byte(name))
  rg := rand.New(rand.NewSource(int64(h.Sum64())))
  sleep := func() {	time.Sleep(max_waiting_time/2 + time.Duration(rg.Int63n(int64(max_waiting_time)))) }

  for meals := no_meals; meals > 0; meals-- {
		left_fork.Lock() 
		fmt.Printf("[%s] has picked up left fork\n", name)
  	right_fork.Lock()
		fmt.Printf("[%s] has picked up right fork\n", name)

  	fmt.Printf("[%s] is eating meal om nom nom\n", name)
  	sleep()

  	left_fork.Unlock() 
		fmt.Printf("[%s] has put down left fork\n", name)
  	right_fork.Unlock()
		fmt.Printf("[%s] has put down right fork\n", name)

  	fmt.Printf("[%s] is thinking about the weather\n", name)
  	sleep()
  }

  dining_philosophers.Done()
  fmt.Printf("[%s] left the table\n", name)
}

func main() {
	// Check if the number of arguments is correct
	if len(os.Args) != 3 {
		fmt.Println("Usage: go run main.go <number of philosophers> <number of meals>")
		os.Exit(1)
	}

	// Argument checks
	no_philosophers, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Println("Usage: go run main.go <number of philosophers> <number of meals>")
		os.Exit(1)
	} else if no_philosophers <= 1 {
		fmt.Println("Number of philosophers must be greater than 1")
		fmt.Println("Usage: go run main.go <number of philosophers> <number of meals>")
		os.Exit(1)
	}

	no_meals, err := strconv.Atoi(os.Args[2])
	if err != nil {
		fmt.Println("Usage: go run main.go <number of philosophers> <number of meals>")
		os.Exit(1)
	} else if no_meals <= 0 {
		fmt.Println("Number of meals must be greater than 0")
		fmt.Println("Usage: go run main.go <number of philosophers> <number of meals>")
		os.Exit(1)
	}
	
	// Create philosophers
	var philosophers []string
	for i := 0; i < no_philosophers; i++ {
		philosophers = append(philosophers, strconv.Itoa(i+1))
	}

  dining_philosophers.Add(no_philosophers)

	// Create forks
  first_fork := &Fork{}
  left_fork := first_fork

  for i := 1; i < len(philosophers); i++ {
  	right_fork := &Fork{}
  	go philosopher(philosophers[i], left_fork, right_fork, no_meals)
  	left_fork = right_fork
  }

  go philosopher(philosophers[0], first_fork, left_fork, no_meals)
	
  dining_philosophers.Wait() 
}
