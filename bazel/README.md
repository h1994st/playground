Bazel Tutorial
===

Version: 4.0.0

References:

- <https://docs.bazel.build/versions/4.0.0/install.html>

## Install Bazel

```bash
brew install bazel
```

## Example

### Configurations

- A `WORKSPACE` file lives at the root of the project's directory
- A directory in the workspace with a `BUILD` file is a package
    - Define build targets: `cc_binary`, `cc_library`, `cc_test`, etc.
- By default, a build target in a package is not visible to other packages
    - Make the whole package visible to others: `package(default_visibility = ["//visibility:public"])`
    - Configure the `visibility` for a specfic target: `cc_library(visibility = ...)`

### Build with Bazel

```bash
# build all targets
bazel build //...

# build a specfic target
bazel build //foo:foo
```
