package main

import "fmt"

/**
 * @param k: An integer
 * @param n: An integer
 * @return: An integer denote the count of digit k in 1..n
 */
import "math"
func digitCounts (k int, n int) int {
    // write your code here
    s := func(n int) int {
        if n == k {
            return 1
        } else {
            return 0
        }
    }
    
    cache := make(map[int]int)
    
    var fn func(n int, toCache bool) (r int)
    fn = func(n int, toCache bool) (r int) {
        if n < 10 {
            if n >= k {
                return 1
            } else {
                return 0
            }
        } else {
            if toCache {
                var ok bool
                r, ok = cache[n]
                if ok {
                    return r
                }
            }

            // n: 345
            base := int(math.Pow(10.0, float64(int(math.Log10(float64(n)))))) // base: 100
            high := n / base // high: 3
            low := n % base // low: 45
            
            result := 0
            
            // 299 ~ 0
            if k > 0 && k <= high-1 {
                result += base
            }
            if high > 0 {
                result += high * fn(base - 1, true)
            }
            
            // 345 ~ 300
            result += s(high)*(low+1) + fn(low, false) // s(3) * [0...45] + fn(45)
            
            if toCache {
                cache[n] = result
            }
            return result
        }
    }
    
    return fn(n, false)
}


func digitCounts2 (k int, n int) int {
    // write your code here
    s := func(n int) int {
        if n == k {
            return 1
        } else {
            return 0
        }
    }
    
    var fn func(n int) (r int)
    fn = func(n int) (r int) {
        if n < 10 {
            if n >= k {
                return 1
            } else {
                return 0
            }
        } else {
            base := int(math.Pow(10.0, float64(int(math.Log10(float64(n))))))
            high := n / base
            low := n % base
            return s(high)*(low+1) + fn(low) + fn(high*base-1)
        }
    }
    return fn(n)
}


func main() {
	result := 0
	for i:=0; i<1000000; i++ {
		result = digitCounts2(9, 99999999)
	}
	fmt.Println(result)
}
