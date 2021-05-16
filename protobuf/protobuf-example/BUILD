load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@rules_proto//proto:defs.bzl", "proto_library")

proto_library(
    name = "bookstore_proto",
    srcs = ["bookstore.proto"],
    deps = [":date_proto"],
)

cc_proto_library(
    name = "bookstore_cc_proto",
    deps = [":bookstore_proto"],
)

proto_library(
    name = "date_proto",
    srcs = ["date.proto"],
)

cc_proto_library(
    name = "date_cc.proto",
    deps = [":date_proto"],
)

cc_binary(
    name = "bookstore",
    srcs = ["bookstore.cc"],
    deps = [":bookstore_cc_proto"],
)
