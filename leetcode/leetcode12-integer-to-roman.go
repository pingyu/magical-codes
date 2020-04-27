package main

import "fmt"

import "strings"

func intToRoman(num int) string {
	romans := map[int][10]string{
		//   0,
		1:    {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
		10:   {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
		100:  {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
		1000: {"", "M", "MM", "MMM"},
	}

	sb := strings.Builder{}
	for i := 1000; i >= 1; i /= 10 {
		high := num / i
		num = num % i
		//fmt.Printf("high:%v, num:%v, i:%v\n", high, num, i)
		if high > 0 {
			sb.WriteString(romans[i][high])
		}
	}

	return sb.String()
}

func main() {
	type Case struct {
		num int
		res string
	}
	cases := []Case{
		{3, "III"},
		{4, "IV"},
		{9, "IX"},
		{58, "LVIII"},
		{1994, "MCMXCIV"},
		{3999, "MMMCMXCIX"},
	}
	for _, c := range cases {
		fmt.Printf("%v -> %v vs. %v\n", c.num, c.res, intToRoman(c.num))
	}
}
