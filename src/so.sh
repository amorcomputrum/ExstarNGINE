#!/bin/bash
cc -c -o exstar.o -I../include  Exstar.cpp -fPIC
g++ -shared -o libexstar.so exstar.o
mv libexstar.so ../lib
sudo cp ../lib/libexstar.so /usr/lib
