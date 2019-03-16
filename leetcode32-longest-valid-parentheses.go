package main

import "fmt"

type Stack struct {
	top     int
	storage []interface{}
}

func NewStack(size int) *Stack {
	return &Stack{
		top:     -1,
		storage: make([]interface{}, size),
	}
}
func (s *Stack) Push(in interface{}) {
	s.top++
	if s.top >= len(s.storage) {
		s.storage = append(s.storage, in)
	} else {
		s.storage[s.top] = in
	}
}
func (s *Stack) Pop() (interface{}, bool) {
	if s.top >= 0 {
		out := s.storage[s.top]
		s.top--
		return out, true
	}
	return nil, false
}
func (s *Stack) GetTop() interface{} {
	if s.top >= 0 {
		return s.storage[s.top]
	}
	panic("Stack.GetTop() out of top")
}
func (s *Stack) String() string {
	return fmt.Sprintf("top:%v, storage:%v", s.top, s.storage[0:s.top+1])
}

func longestValidParentheses(s string) int {
	length := len(s)
	stack := NewStack(length + 1)
	max := 0

	stack.Push(-1)
	//fmt.Printf("stack:%s, max:%v\n", stack, max)
	for i := 0; i < length; i++ {
		//fmt.Printf("i:%v, s[i]:%v\n", i, string(s[i]))
		if s[i] == '(' {
			stack.Push(i)
		} else { // ')'
			begin, ok := stack.Pop()
			if !ok || begin.(int) == -1 || s[begin.(int)] == ')' {
				stack.Push(i)
			} else if ok {
				len := i - stack.GetTop().(int)
				if max < len {
					max = len
				}
			}
		}
		//fmt.Printf("stack:%s, max:%v\n", stack, max)
	}

	return max
}

func main() {
	ss := []string{
		"))(()))()()())",
		"()(()",
		"()()",
	}

	for _, s := range ss {
		fmt.Printf("s:%v, max:%v\n", s, longestValidParentheses(s))
	}
}
