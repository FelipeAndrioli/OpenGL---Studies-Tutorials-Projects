clear

rm -r binaries

rm -r build

cmake -S . -B build -G "MinGW Makefiles" -D BUILD_ASSIMP=ON

cmake --build build

./binaries/main.exe
