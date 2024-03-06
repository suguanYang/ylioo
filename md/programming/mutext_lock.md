the following code runs differently in go1.21 and go1.22
```go
package main

import (
	"fmt"
	"sync"
)

const NumWorkers = 3

func isGold(num uint64) bool {
	return num & 0xFFFFF == 0
}

func main() {
	var c = make(chan uint64)
	var m sync.Mutex
	for n, i := 0, uint64(0); n < NumWorkers; n++ {
		go func() {
			for {
				m.Lock()
				i++
				v := i
				m.Unlock()

				if isGold(v) {
					c <- v
				}
			}
		}()
	}

	for n := range c {
		fmt.Println("Found gold", n)
	}
}
```

this is because the variable mutex lock only locks on the variable i, but the i will be
initilised in every loop scope in go 1.22