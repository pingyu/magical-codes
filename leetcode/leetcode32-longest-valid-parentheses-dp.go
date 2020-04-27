package main

import "fmt"

func longestValidParentheses(s string) int {
	length := len(s)
	dp := make([]int, length)
	for i := range dp {
		dp[i] = -1
	}
	max := 0

	backward := func(i int) int {
		if i <= 0 {
			return -1
		}

		if s[i-1] == ')' {
			last := dp[i-1]
			if last >= 1 && s[last-1] == '(' {
				last = last - 1
				if last >= 1 && dp[last-1] >= 0 {
					return dp[last-1]
				}
				return last
			}
			return -1
		}
		// s[i-1] == '('
		last := i - 1
		if last >= 1 && dp[last-1] >= 0 {
			return dp[last-1]
		}
		return last
	}

	for i, c := range s {
		if c == ')' {
			dp[i] = backward(i)
			if dp[i] >= 0 && max < i-dp[i]+1 {
				max = i - dp[i] + 1
			}
		}
		//fmt.Printf("s:%v, dp:%v, max:%v\n", s[0:i+1], dp[0:i+1], max)
	}

	return max
}

func main() {
	ss := []string{
		"",
		"(",
		")",
		"))(()))()()())",
		"()(()",
		"()()",
	}

	for _, s := range ss {
		fmt.Printf("s:%v, max:%v\n", s, longestValidParentheses(s))
	}
}
