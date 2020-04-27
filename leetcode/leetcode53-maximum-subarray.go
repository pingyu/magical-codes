package main

import "fmt"

func maxSubArray(nums []int) int {
	length := len(nums)
	if length <= 0 {
		return 0
	}

	last := nums[0]
	max := nums[0]

	for i := 1; i < length; i++ {
		v := nums[i]
		if last > 0 {
			v = v + last
		}
		if max < v {
			max = v
		}
		last = v
	}
	return max
}

func main() {
	numss := [][]int{
		{-2, 1, -3, 4, -1, 2, 1, -5, 4},
		{},
		{-2},
		{-2, -1, -10},
	}

	for _, nums := range numss {
		fmt.Printf("%v: %v\n", nums, maxSubArray(nums))
	}
}
