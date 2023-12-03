package main

import (
	"fmt"

	"github.com/h1994st/playground/bazel/go-example/utils"
)

func main() {
	fmt.Println("Hello world!")

	nums := []int64{1, 2, 3, 4, 5, 6}
	fmt.Printf("sum(%v) = %d\n", nums, utils.Sum64(nums...))
}
