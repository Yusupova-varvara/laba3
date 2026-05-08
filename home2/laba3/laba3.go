package main

import (
	"fmt"
	"math"
)

func main() {
	var x, y float64
	var Xn, Xk, dX float64

	fmt.Print("Введите Xнач: ")
	fmt.Scan(&Xn)
	fmt.Print("Введите Xкон: ")
	fmt.Scan(&Xk)
	fmt.Print("Введите шаг dX: ")
	fmt.Scan(&dX)

	fmt.Println()
	fmt.Println("x\ty")

	for x = Xn; x <= Xk+1e-10; x += dX {
		if x >= -5 && x <= -2 {
			y = -(x+3.5)*(x+3.5) + 2.25
		} else if x > -2 && x < 2 {
			y = -math.Sqrt(4 - x*x)
		} else if x >= 2 && x <= 8 {
			y = math.Log2(x) - 1
		} else if x > 8 && x <= 9 {
			y = -2*x + 18
		} else {
			fmt.Printf("%.1f\t—\n", x)
			continue
		}
		fmt.Printf("%.1f\t%g\n", x, y)
	}
}

