package utils_test

import (
	"testing"

	"github.com/h1994st/playground/bazel/go-example/utils"
	"github.com/stretchr/testify/require"
)

func TestAdd64(t *testing.T) {
	require.Equal(t, int64(4), utils.Add64(1, 3))
	require.Equal(t, int64(4), utils.Add64(3, 1))
}

func TestSum64(t *testing.T) {
	require.Equal(t, int64(4), utils.Sum64(1, 1, 2))
	require.Equal(t, int64(4), utils.Sum64(1, 1, 1, 1))
}
