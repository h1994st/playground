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
}
