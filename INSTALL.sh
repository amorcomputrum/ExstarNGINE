#!/bin/bash
cmake . -DCMAKE_INSTALL_PREFIX:PATH=/usr -Wno-dev -Wnarrowing
make install