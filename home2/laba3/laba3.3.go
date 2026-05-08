package main

import (
	"fmt"
	"math"
)

// НОД
func gcd(a, b int) int {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func main() {
	var a, b int
	fmt.Print("Введите a и b: ")
	fmt.Scan(&a, &b)

	if b == 1 {
		fmt.Println("infinity")
		return
	}

	var sum float64 = 0.0
	var term float64

	for n := 1; n <= 1000; n++ {
		term = math.Pow(float64(n), float64(a)) / math.Pow(float64(b), float64(n))
		if term < 1e-15 {
			break
		}
		sum += term
	}

	den := 1
	for math.Abs(sum*float64(den)-math.Round(sum*float64(den))) > 1e-10 && den < 100000 {
		den++
	}

	num := int(math.Round(sum * float64(den)))
	g := gcd(num, den)
	num /= g
	den /= g

	fmt.Printf("%d/%d\n", num, den)
}
