#!/bin/sh

if [ -d "build" ]; then 
    rm -rf build;
fi 

mkdir build

BUILDER=$(if command -v ninja > /dev/null; then echo ninja; else echo make; fi )

# if [ "${BUILDER}" == "ninja" ] ; then
#     BNAME=Ninja
# else 
#     BName="Unix Makefiles"
# fi

cmake -G Ninja -B build -S . -DCMAKE_BUILD_TYPE=DEBUG

cd build && ninja -j$(grep -c ^processor /proc/cpuinfo)