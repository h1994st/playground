Apache Thrift Tutorial
===

Version: 0.14.1

References:

- <https://github.com/apache/thrift/tree/master/tutorial>
- <https://diwakergupta.github.io/thrift-missing-guide/>

## Install Apache Thrift

```bash
brew install thrift
```

## Example

### Thrift File

- `struct` is a basic type that can group related items together
- `include` allows the author to use Thrift objects in other files
    - Included objects are accessed using the name of the Thrift file as a prefix
        - Assuming that we include `foo.thrift`, which contains the definition of a struct `Bar`
        - Then, in the current Thrift file, we use `foo.Bar`

### Code Generation

For C++

```bash
thrift -r \              # -r: recursively generate codes for input file and its included files
       --gen cpp \       # --gen cpp: generate C++ codes
       bookstore.thrift  # input file
```
