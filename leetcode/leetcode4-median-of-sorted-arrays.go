package main

import "fmt"

func getIdx(nums []int, i int, j int, targetNum int) int {
    for i < j {
        mid := (i + j) / 2
        if nums[mid] == targetNum {
            return mid
        }
        if nums[mid] < targetNum {
            i = mid + 1
        }
        if nums[mid] > targetNum {
            j = mid
        }
    }
   	return i - 1
}

func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
   
    var doSearch func(targetCount int, i1, j1, i2, j2 int) int
    doSearch = func(targetCount int, i1, j1, i2, j2 int) int {
    	//fmt.Printf("doSearch: targetCount:%v, i1:%v, j1:%v, i2:%v, j2:%v\n", targetCount, i1, j1, i2, j2) //DEBUG

        if i1 == j1 {
            return nums2[i2 + targetCount - 1]
        }
        if i2 == j2 {
            return nums1[i1 + targetCount - 1]
        }
        
        if j1 > i1 + targetCount {
            j1 = i1 + targetCount
        }
        if j2 > i2 + targetCount {
            j2 = i2 + targetCount
        }
        
        idx2 := (i2 + j2) / 2
        targetNum2 := nums2[idx2]
        idx1 := getIdx(nums1, i1, j1, targetNum2)
        //fmt.Printf("getIdx: idx1:%v, i1:%v, j1:%v, idx2:%v, targetNum2:%v\n", idx1, i1, j1, idx2, targetNum2)

        count1, count2 := idx1 - i1 + 1, idx2 - i2 + 1
        //fmt.Printf("targetCount:%v, idx1:%v, count1:%v, idx2:%v, count2:%v\n", targetCount, idx1, count1, idx2, count2) //DEBUG
        if count1 + count2 == targetCount {
            return targetNum2
        }
        if count1 + count2 < targetCount {
            return doSearch(targetCount - count1 - count2, idx1+1, j1, idx2+1, j2)
        }
        return doSearch(targetCount, i1, idx1+1, i2, idx2)
    }

    //fmt.Println("nums1:", nums1)
    //fmt.Println("nums2:", nums2)

    length := len(nums1) + len(nums2)
    targetCount := (length + 1) / 2
    if length % 2 == 1 {
	    return float64(doSearch(targetCount, 0, len(nums1), 0, len(nums2)))
	} else {
		return float64(doSearch(targetCount, 0, len(nums1), 0, len(nums2)) + doSearch(targetCount+1, 0, len(nums1), 0, len(nums2))) / 2.0
	}
}

func main() {
    nums := []int{1, 3, 5, 7, 9}
    idx := getIdx(nums, 0, len(nums), 11)
    fmt.Println(idx)

	nums1 := []int{3, 4}
	nums2 := []int{1, 2}

	res := findMedianSortedArrays(nums1, nums2)

    fmt.Println(res)
}
