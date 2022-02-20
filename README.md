# test_apple_dragndrop
Small test task for one famous company.

## Requirements 
- Windows 11
- Qt6.2.2
- CMake 3.22

## Build Windows 11
Set CMAKE_PREFIX_PATH option to folder with Qt: `CMAKE_PREFIX_PATH="C:\Qt\6.2.2\msvc2019_64`

```sh
git clone git@github.com:ikvasir/test_apple_dragndrop.git
cd test_apple_dragndrop
mkdir build
cd build
```
```sh
cmake .. -D CMAKE_PREFIX_PATH="C:\Qt\6.2.2\msvc2019_64"
```
```sh
cmake --build .
```

## Last build
[build.xz.tar](https://github.com/ikvasir/test_apple_dragndrop/releases/tag/v1.0.0)

## How it ran on my pc
[Video here](https://youtu.be/q0VohpK6WbA)
