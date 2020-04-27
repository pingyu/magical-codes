package main

import "fmt"

func isMatchRecur(s string, p string) bool {
	lenS, lenPattern := len(s), len(p)
	if lenPattern == 0 {
		return lenS == 0
	}

	var matchFn func(idxP, idxS int) bool
	matchFn = func(idxP, idxS int) bool {
		fmt.Printf("(%v,%v)\t", idxS, idxP)
		if idxP == lenPattern {
			return idxS == lenS
		}

		if p[idxP] == '*' {
			return matchFn(idxP+1, idxS) || (idxS < lenS && matchFn(idxP, idxS+1))
		}
		if idxS < lenS && (p[idxP] == '?' || p[idxP] == s[idxS]) {
			return matchFn(idxP+1, idxS+1)
		}
		return false
	}

	return matchFn(0, 0)
}

func isMatch(s string, p string) bool {
	lenS, lenPattern := len(s), len(p)

	curr := make([]bool, lenS+1)
	next := make([]bool, lenS+1)
	zeros := make([]bool, lenS+1)

	curr[0] = true
	siBegin := 0
	for pi := 0; pi < lenPattern; pi++ {
		if pi+1 < lenPattern && p[pi] == '*' && p[pi+1] == '*' {
			continue
		}

		siMatched := -1
		for si := siBegin; si <= lenS; si++ {
			if curr[si] {
				if si < lenS && (p[pi] == '?' || p[pi] == s[si]) {
					next[si+1] = true
					if siMatched == -1 || siMatched > si+1 {
						siMatched = si + 1
					}
				} else if p[pi] == '*' {
					for k := si; k <= lenS; k++ {
						next[k] = true
					}
					if siMatched == -1 || siMatched > si {
						siMatched = si
					}
				}
			}
		}
		if siMatched == -1 {
			return false
		}
		siBegin = siMatched
		curr, next = next, curr
		copy(next, zeros)
	}
	return curr[lenS]
}

func main() {
	type Case struct {
		s      string
		p      string
		result bool
	}
	cases := []Case{
		{"aa", "a", false},
		{"aa", "*", true},
		{"aa", "*****", true},
		{"", "*", true},
		{"cb", "?a", false},
		{"adceb", "*a*b", true},
		{"acdcb", "a*c?b", false},
		{"bbbbbbbabbaabbabbbbaaabbabbabaaabbababbbabbbabaaabaab", "b*b*ab**ba*b**b***bba", false},
	}
	for _, c := range cases {
		fmt.Printf("%v <= %v: %v vs. %v\n", c.s, c.p, c.result, isMatch(c.s, c.p))
	}
}
