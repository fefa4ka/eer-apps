# Build
mkdir build

cmake -DCMAKE_BUILD_TYPE=Debug ../
cmake --build .

# Target Build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../lego/eer/toolchain/generic-gcc-riscv.cmake -DHAL=ch573 ../


## Test Build
make test

Time sensitive tests could not passed on slower host machines caused rich logger activity.
