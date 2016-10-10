package main

import "fmt"
import "sync"

const M, K, N int = 3, 2, 3

var A = [M][K]int{{1, 4}, {2, 5}, {3, 6}}
var B = [K][N]int{{8, 7, 6}, {5, 4, 3}}
var C = [M][N]int{}

func main() {

	var wg sync.WaitGroup

	for i := 0; i < M; i++ {
		for j := 0; j < N; j++ {
			//Increment WaitGroup
			wg.Add(1)
			//Calculate value with go routine (thread)
			go runner(i, j, &wg)
		}
	}

	//Wait for go routines to finish
	wg.Wait()

	//Print resulting Matrix
	for i := 0; i < M; i++ {
		for j := 0; j < N; j++ {
			fmt.Printf("%d ", C[i][j])
		}
		fmt.Printf("\n")
	}

}

func runner(i int, j int, wg *sync.WaitGroup) {

	sum := 0
	for n := 0; n < K; n++ {
		sum += A[i][n] * B[n][j]
	}

	C[i][j] = sum

	//Decrement waitGroup
	wg.Done()
}
