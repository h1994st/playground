load("@bazel_gazelle//:def.bzl", "gazelle")
load("@io_bazel_rules_go//go:def.bzl", "go_binary", "go_library")

# gazelle:prefix github.com/h1994st/playground/bazel/go-example
gazelle(name = "gazelle")

gazelle(
    name = "gazelle-update-repos",
    args = [
        "-from_file=go-example/go.mod",
        "-to_macro=deps.bzl%go_dependencies",
        "-prune",
    ],
    command = "update-repos",
)

go_library(
    name = "go-example_lib",
    srcs = ["main.go"],
    importpath = "github.com/h1994st/playground/bazel/go-example",
    visibility = ["//visibility:private"],
    deps = ["//go-example/utils"],
)

go_binary(
    name = "go-example",
    embed = [":go-example_lib"],
    visibility = ["//visibility:public"],
)
