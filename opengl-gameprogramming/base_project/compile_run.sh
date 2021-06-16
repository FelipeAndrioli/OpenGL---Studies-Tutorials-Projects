#!/bin/bash

echo 'Compiling file...'

g++ main.cpp -o main.exe -lglfw3 -lopengl32 -lgdi32 -lglu32

echo 'Executing file...'

./main.exe
