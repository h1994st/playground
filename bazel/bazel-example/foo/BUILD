load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
  name = "foo_utils_lib",
  srcs = ["foo_utils.c"],
  hdrs = ["foo_utils.h"],
)

cc_binary(
  name = "foo",
  srcs = ["foo.c"],
  deps = [
    ":foo_utils_lib",
    "//bar:bar_utils_lib"
  ]
)
