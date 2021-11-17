#!/bin/bash
cc -c -o exstar.o -I../include  Exstar.cpp -fPIC
g++ -shared -o libExstar.so exstar.o
mv libExstar.so ../lib
sudo cp ../lib/libExstar.so /usr/lib
