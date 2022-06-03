#!/bin/bash
cmake . -DCMAKE_INSTALL_PREFIX:PATH=/usr -Wno-dev -Wnarrowing -DBUILD_STATIC=OFF
make install
