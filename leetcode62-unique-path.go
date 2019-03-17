package main

import "fmt"

func uniquePaths(m int, n int) int {
	if m <= 0 || n <= 0 {
		return 0
	}

	var bottom int64 = int64((m - 1) + (n - 1))
	var top int64 = int64(n - 1)
	if int64(m-1) < top {
		top = int64(m - 1)
	}

	var res int64 = 1
	var i int64
	for i = 0; i < top; i++ {
		res *= (bottom - i)
	}
	for i = 0; i < top; i++ {
		res /= (top - i)
	}

	return int(res)
}

func main() {
	type Matrix struct {
		m int
		n int
	}
	cases := []Matrix{
		{3, 2},
		{7, 3},
	}

	for _, c := range cases {
		fmt.Printf("%v x %v: %v\n", c.m, c.n, uniquePaths(c.m, c.n))
	}
}
