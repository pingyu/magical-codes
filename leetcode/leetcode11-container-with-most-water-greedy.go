package main

import "fmt"

func maxArea(height []int) int {
	length := len(height)

	max := 0
	i, j := 0, length-1
	for i < j {
		hi, hj := height[i], height[j]
		//fmt.Printf("%v:%v <--> %v:%v\n", i, hi, j, hj)

		if hi < hj {
			area := hi * (j - i)
			if max < area {
				max = area
			}

			k := i + 1
			for ; k < j && height[k] <= hi; k++ {
			}
			i = k
		} else { // hi >= hj
			area := hj * (j - i)
			if max < area {
				max = area
			}

			k := j - 1
			for ; k > i && height[k] <= hj; k-- {
			}
			j = k
		}
	}

	return max
}

func main() {
	type Case struct {
		height []int
		result int
	}
	cases := []Case{
		{[]int{1, 8, 6, 2, 5, 4, 8, 3, 7}, 49},
		{[]int{1, 8, 6}, 6},
		{[]int{}, 0},
	}
	for _, c := range cases {
		fmt.Printf("%v: %v vs. %v\n", c.height, c.result, maxArea(c.height))
	}
}
