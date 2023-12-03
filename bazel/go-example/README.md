# Bazel + Go + gazelle

References:

- <https://github.com/bazelbuild/rules_go>
- <https://github.com/bazelbuild/bazel-gazelle>

```bash
# Under the root directory of the workspace
# - Generate BUILD files for the Go project
bazel run //go-example:gazelle-update-repos

# Run the binary
bazel run //go-example

# Run tests
bazel test //go-example/...
```
