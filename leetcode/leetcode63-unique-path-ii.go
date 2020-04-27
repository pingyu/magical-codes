package main

import "fmt"

func uniquePathsWithObstacles(obstacleGrid [][]int) int {
	rows := len(obstacleGrid)
	if rows <= 0 {
		return 0
	}
	cols := len(obstacleGrid[0])
	if cols <= 0 {
		return 0
	}

	dp := make([]int, cols+1)
	dpLast := make([]int, cols+1)
	zeros := make([]int, cols+1)

	dp[1] = 1
	for i := 1; i <= rows; i++ {
		dpLast, dp = dp, dpLast
		copy(dp, zeros)
		for j := 1; j <= cols; j++ {
			if obstacleGrid[i-1][j-1] == 1 {
				dp[j] = 0
			} else {
				dp[j] = dp[j-1] + dpLast[j]
			}
		}
		//fmt.Printf("dpLast:%v, dp:%v\n", dpLast, dp)
	}

	return dp[cols]
}

func main() {
	matrixs := [][][]int{
		{
			{0, 0, 0},
			{0, 1, 0},
			{0, 0, 0},
		},
		{},
		{
			{0, 0, 0},
		},
		{
			{0},
		},
		{
			{1},
		},
		{
			{0, 1},
		},
	}

	for _, m := range matrixs {
		fmt.Printf("%v: %v\n", m, uniquePathsWithObstacles(m))
	}
}
