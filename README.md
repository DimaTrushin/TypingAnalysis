# Typing Analysis

## Description

An open source software to analyze the quality of your typing skills.

## How to Build

### Windows

#### Prerequisites

- [Visual Studio 2019](https://visualstudio.microsoft.com/downloads/)

- [Qt 5.15.7](https://www.qt.io/download) with source code

- [Conan 1.59](https://conan.io/)

- [Cuda Toolkit v 10.1 Update 2](https://developer.nvidia.com/cuda-toolkit)

#### Setup your Environment

1. Install Visual Studio 2019. You basically need the compiler and the debugger.

2. Install Conan 1.59. It is currently impossible to build the project with conan v2 because not all of the required recipes are compatible with conan v2. It is also worth setting the default profile. Usually it is done by default for Visual Studio. In case it is not, here is an example
```
[settings]
os=Windows
os_build=Windows
arch=x86_64
arch_build=x86_64
compiler=Visual Studio
compiler.version=16
build_type=Release
[options]
[build_requires]
[env]
```

3. Install Cuda Toolkit v.10.1 Update 2 (cuda_10.1.243_426.00_win10). Make sure the variables NVCUDASAMPLES_ROOT and CUDA_PATH are added to the PATH variable.

4. Install Qt. Install Qt Creator and the source code of Qt 5.15.7. Currently it is impossible to build the project with a newer version of Qt because qwt depends on this version.

#### Build Qt Statically

There are two options: build with static runtime library of with dynamic runtime library. The first option is not recommended but allows you to have one executable file with no dependencies.

###### Build Qt Statically with Static Runtime Library

1. Open Visual Studio command line x64 Native.

2. Suppose Qt_Source is the path to your Qt source code, Qt_Build is your current folder and Qt_Static is the install folder.

3. First you need to configure Qt using command

Qt_Source/configure.bat -debug-and-release -static -static-runtime -opengl desktop -platform win32-msvc -prefix "Qt_Static" -opensource -confirm-license -skip webengine -make libs -nomake tools -nomake tests -nomake examples

4. use
```
set CL=/MP
```
to make nmake multi-threaded

5. Build Qt using (or you may use jom here)
```
nmake
```

6. Install Qt using (or you may use jom here)
```
nmake install
```

7. Delete Qt_Build folder

###### Build Qt Statically with Dynamic Runtime Library

1. Open Visual Studio command line x64 Native.

2. Suppose Qt_Source is the path to your Qt source code, Qt_Build is your current folder and Qt_Static is the install folder.

3. First you need to configure Qt using command
```
Qt_Source/configure.bat -debug-and-release -static -opengl desktop -platform win32-msvc -prefix "Qt_Static" -opensource -confirm-license -skip webengine -make libs -nomake tools -nomake tests -nomake examples
```

4. use
```
set CL=/MP
```
to make nmake multi-threaded

5. Build Qt using (or you may use jom here)
```
nmake
```

6. Install Qt using (or you may use jom here)
```
nmake install
```

7. Delete Qt_Build folder

#### Configure QtCreator

1. Run QtCreator

2. Go to Tools->Options->Qt Versions and add statically build version of Qt 5.15.7.

3. Go to Tools->Options->Kits and add a kit for static version of the Qt. You should choose Microsoft Visual C++ Compiler (amd64) for C and C++ code. Make sure "Force UTF-8 MSVC compiler output" flag is checked. Use statically build Qt version for this kit.

4. Open TypingAnalysis.pro file in QtCreator.

5. Go to Project(icon on the left panel) Add "Conan install" as the first step before qmake for "Debug", "Release", and "Profile" modes.

6. If you compiled with static runtime, you should add an additional argument to Connan (in each building mode):
```
-s "compiler.runtime=MT"
```

### Known issues

Thrust library is used to speed up the computations. As a result CUDA is not used in debug mode.
