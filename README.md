# Build

```
mkdir build

cmake -DCMAKE_C_COMPILER=gcc-12 -DPROFILING=True -DCMAKE_BUILD_TYPE=Debug ../
cmake --build .
```

Tests for Debug build:
`make test`

# Target Build

```
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../lego/eer/toolchain/generic-gcc-riscv.cmake -DMCU=ch573 -DBOARD=ch573_evt ../
cmake --build .
```


