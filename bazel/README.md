# Bazel Tutorial

Version: 6.4.0

References:

- <https://bazel.build/install/ubuntu>
- <https://bazel.build/install/bazelisk>

## Install Bazel

### macOS

```bash
brew install bazel
```

### Ubuntu 18.04/22.04

#### Option 1: via Bazelisk

```bash
wget https://github.com/bazelbuild/bazelisk/releases/download/v1.19.0/bazelisk-linux-amd64
chmod +x bazelisk-linux-amd64
sudo mv bazelisk-linux-amd64 /usr/local/bin/bazelisk
sudo ln -s /usr/local/bin/bazelisk /usr/local/bin/bazel

# Install buildifier
go install github.com/bazelbuild/buildtools/buildifier@latest

# Create .bazelversion and specify Bazel version
echo "6.4.0" > .bazelversion
```

#### Option 2: via Custom APT Repository

```bash
sudo apt install apt-transport-https curl gnupg -y
curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor >bazel-archive-keyring.gpg
sudo mv bazel-archive-keyring.gpg /usr/share/keyrings
echo "deb [arch=amd64 signed-by=/usr/share/keyrings/bazel-archive-keyring.gpg] https://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list

sudo apt update && sudo apt install bazel
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
