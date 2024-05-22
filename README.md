# Description
>C++ library for graphics

# Interface
```cpp
namespace Graphics {

}
```
# Examples

# Use this Project
## Installation
At your desired location, type this command into the console.
``` console
git clone git@github.com:fburgerdev/graphics.git
```

## Include in Project
In your C++ project:
- add the include directory "PATH_TO_THIS_REPO/include" 
- add the library directory "PATH_TO_THIS_REPO/lib/DESIRED_CONFIG/" 
- link the library "libgraphics.a" (linux) or "graphics.lib" (windows)

## Build Yourself (optional)
### with Linux
In the _build_ folder, execute the following command in the console
``` console
make config=CONFIG
```
If you have not installed _make_, execute this command in the console first
``` console
sudo apt-get install make -y
```

### with Windows
Open the file "build/graphics.sln" with Visual Studio.
After you have selected your desired configuration, click on _Build > Build_ Solution.

__Note:__ Make sure you have the _Desktop developement with C++_ workload installed.