`LD_PRELOAD` and constructor attribute
===

Reference:

- <https://gcc.gnu.org/onlinedocs/gcc-4.7.0/gcc/Function-Attributes.html>

## Build & Run

```bash
# Build
bazel build //...

# Run
LD_PRELOAD=./bazel-bin/libsock_hook.so ./bazel-bin/udp_client
```

## Constructor Attribute

```c
__attribute__((constructor))
void lib_ctor();

__attribute__((destructor))
void lib_dtor();
```

- The `constructor` attribute causes the function to be called when the shared library is loaded
- Oppositely, the function with the `destructor` attribute is called when the shared library is unloaded
