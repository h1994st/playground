load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "bar_utils_lib",
    srcs = ["bar_utils.cc"],
    hdrs = ["bar_utils.h"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "bar",
    srcs = ["bar.cc"],
    deps = [":bar_utils_lib"],
)
