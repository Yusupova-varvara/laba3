package main

import "fmt"

func main() {
	var n, m int
	fmt.Scan(&n, &m)

	arr := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&arr[i])
	}

	pos := 0
	scoreP, scoreV := 0, 0
	lastOpponent := -1
	turn := 0

	for pos < n {
		maxSum := -1000000
		bestTake := 1
		leftover := n - pos

		for take := 1; take <= m && take <= leftover; take++ {
			if take == lastOpponent {
				continue
			}

			sum := 0
			for i := pos; i < pos+take; i++ {
				sum += arr[i]
			}

			if sum > maxSum {
				maxSum = sum
				bestTake = take
			}
		}

		lastOpponent = bestTake

		if turn == 0 {
			scoreP += maxSum
		} else {
			scoreV += maxSum
		}

		pos += bestTake
		turn = 1 - turn
	}

	if scoreP > scoreV {
		fmt.Println("1")
	} else {
		fmt.Println("0")
	}
}
