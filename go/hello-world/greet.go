// Package declaration
// `package main` means that this will be compiled into an executable
package main

// Import external packages
// We can import multiple packages using a single `import`
import (
	"fmt"
	// `t` is the alias for the imported `time` package
	t "time"
)

func main() {
	fmt.Println("Hello World")
	fmt.Println(t.Now())

	// Define variables without specifying the type
	var hoursInDay = 24
	// The following line is a special operator `:=`, omitting `var` and `=`
	minutesInHour := 60
	fmt.Println("There are", minutesInHour*hoursInDay, "minutes in a day")

	// Define multiple variables
	// Explicitly specify the type. Defined variables must be the same type
	var part1, part2 string = "Bears, Beets, Battlestar", "Galactica"
	fmt.Println(part1, part2)
	// With `:=` operator, variables can be different types
	quote, fact := "Bears, Beets, Battlestar Galactica", true
	fmt.Println(quote, fact)
}
