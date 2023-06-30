Custom Skills Framework

Port of the 2.0 SKSE version by Parapets to Skyrim version 1.5.97.

## Requirements
* [CMake](https://cmake.org/)
	* Add this to your `PATH`
* [Vcpkg](https://github.com/microsoft/vcpkg)
	* Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
	* Desktop development with C++

## Register Visual Studio as a Generator
* Open `x64 Native Tools Command Prompt`
* Run `cmake`
* Close the cmd window

## Building
```
git clone https://github.com/Fuzzlesz/CustomSkills-1.5
cd CustomSkills-1.5
git submodule init
git submodule update
cmake --preset vs2022-windows
cmake --build build --config Release
```
