# Build

```
mkdir build

cmake -DCMAKE_C_COMPILER=gcc-12 -DPROFILING=True -DCMAKE_BUILD_TYPE=Debug ../
cmake --build .
```

# Target Build

```
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../lego/eer/toolchain/generic-gcc-riscv.cmake -DMCU=ch573 -DBOARD=ch573_evt ../
```

## Test Build

`make test`

Time sensitive tests could not passed on slower host machines caused rich logger activity.
