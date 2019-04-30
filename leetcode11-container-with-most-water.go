package main

import "fmt"

////////////////////////////////////////////
import "sort"

type ListNode struct {
	idx  int
	prev int
	next int
}

type List struct {
	array []ListNode
	head  int
	tail  int
	size  int
}

func (lst *List) Head() int {
	return lst.head
}
func (lst *List) Tail() int {
	return lst.tail
}
func NewList(size int) *List {
	lst := &List{
		array: make([]ListNode, size),
		head:  0,
		tail:  size - 1,
		size:  size,
	}
	for i := 0; i < size; i++ {
		lst.array[i].idx = i
		lst.array[i].prev = i - 1
		lst.array[i].next = i + 1
	}
	return lst
}
func (lst *List) Remove(i int) {
	prev := lst.array[i].prev
	next := lst.array[i].next

	if lst.head != i {
		lst.array[prev].next = next
	} else {
		lst.head = next
	}

	if lst.tail != i {
		lst.array[next].prev = prev
	} else {
		lst.tail = prev
	}
}
func (lst *List) Forward() []int {
	res := make([]int, 0, lst.size)
	for i := lst.head; i <= lst.tail; i = lst.array[i].next {
		res = append(res, i)
	}
	return res
}
func (lst *List) Backward() []int {
	res := make([]int, 0, lst.size)
	for i := lst.tail; i >= lst.head; i = lst.array[i].prev {
		res = append(res, i)
	}
	return res
}

type HeightNode struct {
	idx    int
	height int
}
type HeightSlice []HeightNode

func (s HeightSlice) Len() int {
	return len(s)
}
func (s HeightSlice) Less(i, j int) bool {
	return s[i].height < s[j].height
}
func (s HeightSlice) Swap(i, j int) {
	s[i], s[j] = s[j], s[i]
}
func NewHeightSlice(height []int) HeightSlice {
	var s HeightSlice = make([]HeightNode, len(height))
	for i, h := range height {
		s[i].idx = i
		s[i].height = h
	}
	sort.Sort(s)
	return s
}

func maxArea(height []int) int {
	length := len(height)

	lst := NewList(length)
	slce := NewHeightSlice(height)
	//fmt.Printf("lst:%v, slce:%v\n", lst, slce)

	max := 0
	for i := 0; i < length-1; i++ {
		idx := slce[i].idx
		h := slce[i].height

		if idx == lst.Head() || idx == lst.Tail() {
			area := h * (lst.Tail() - lst.Head())
			if max < area {
				max = area
			}
		}
		lst.Remove(idx)
		//fmt.Printf("idx:%v, h:%v, lst:%v, max:%v\n", idx, h, lst, max)
	}

	return max
}

func (lst *List) String() string {
	return fmt.Sprintf("%v[%v <-> %v]%v", lst.Head(), lst.Forward(), lst.Backward(), lst.Tail())
}

/////////////////////////////////////////////////////////////

func maxAreaBrute(height []int) int {
	length := len(height)

	max := 0
	for i := 0; i < length-1; i++ {
		for j := i + 1; j < length; j++ {
			h := height[i]
			if height[j] < h {
				h = height[j]
			}
			area := h * (j - i)
			if max < area {
				max = area
			}
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
