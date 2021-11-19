#!/bin/bash
cc -c -o src/exstar.o -Iinclude src/Exstar.cpp -fPIC
g++ -shared -o src/libExstar.so src/exstar.o
mv src/libExstar.so lib/
sudo cp lib/libExstar.so /usr/lib
sudo cp -r include/* /usr/include
