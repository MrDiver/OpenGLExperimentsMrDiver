#!/bin/bash
git submodule update --init
cmake -DGLFW_BUILD_DOCS=OFF -S . -B build