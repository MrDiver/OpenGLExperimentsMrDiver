#!/bin/bash
git submodule update --init
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DGLFW_BUILD_DOCS=OFF -S . -B build
