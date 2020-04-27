package main

import "fmt"

func isMatch(s string, p string) bool {
    lenStr, lenPat := len(s), len(p)
    
    zeros := make([]byte, lenStr + 1)
    markLast := make([]byte, lenStr + 1)
    mark := make([]byte, lenStr + 1)
    
    mark[0] = 1
    
    i := 0
    for i < lenPat {
    	var c byte
        c, i = p[i], i + 1
        star := false
        if i < lenPat && p[i] == '*' {
            star = true
            i++
        }
        
        mark, markLast = markLast, mark
        copy(mark, zeros)

        match := false
        for j:=0; j<=lenStr; j++ {
            if markLast[j] == 1 && star {
                mark[j] = 1
                match = true
            }

            if (j<lenStr) && (markLast[j] == 1 || (star && mark[j]==1)) {
                if c=='.' || c==s[j] {
                    mark[j+1] = 1
                    match = true
                }
            }
        }

        fmt.Printf("c:%v-%v: mark: %v\n", string(c), star, mark)
        
        if !match {
            return false
        }
    }
    
    if mark[lenStr] == 1 {
        return true
    }
    return false
}

func main() {
	s := "a"
	p := "ab*"

	fmt.Println(s)
	fmt.Println(p)

	res := isMatch(s, p)
	fmt.Printf("res: %v\n", res)
}
