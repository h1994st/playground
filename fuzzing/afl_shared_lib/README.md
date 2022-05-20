# Fuzzing Shared Library

```bash
mkdir shared-build
cd shared-build
cmake -DCMAKE_C_COMPILER=afl-clang-lto -DCMAKE_CXX_COMPILER=afl-clang-lto++ -DBUILD_SHARED_LIBS=ON ..
make
cd ..

mkdir in
echo AAA > in/0
export AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1
export AFL_SKIP_CPUFREQ=1
afl-fuzz -i in -o shared-out -- ./shared-build/bar
```

```bash
mkdir static-build
cd static-build
cmake -DCMAKE_C_COMPILER=afl-clang-lto -DCMAKE_CXX_COMPILER=afl-clang-lto++ -DBUILD_SHARED_LIBS=OFF ..
make
cd ..

mkdir in
echo AAA > in/0
export AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1
export AFL_SKIP_CPUFREQ=1
afl-fuzz -i in -o static-out -- ./static-build/bar
```
