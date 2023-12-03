package utils

func Add64(a int64, b int64) int64 {
	return a + b
}

func Sum64(nums ...int64) int64 {
	var total int64 = 0
	for _, num := range nums {
		total += num
	}
	return total
}
