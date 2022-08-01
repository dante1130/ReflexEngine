# ReflexEngine

![reflex-logo](https://i.imgur.com/TXfAfwS.png)

## Table of Contents

* [Cloning the repository](#cloning)
* [Building](#building)
  * [Visual Studio](#vs)
  * [VSCode](#vscode)
* [Contributing](#contributing)
* [License](#license)

## Cloning the repository

```bash
git clone https://github.com/dante1130/ReflexEngine
git submodule update --init --recursive
```

## Building

### Visual Studio

#### Install build tools

* [Visual Studio](https://visualstudio.microsoft.com/downloads/)
* Install the component "`C++ CMake tools for Windows`".

#### Building ReflexEngine in Visual Studio

1. Open `Visual Studio` as Administrator.
2. Choose the option “`Continue without code`”.
3. Navigate to the top left and select `File -> Open -> CMake`.
4. Navigate to the root directory of `ReflexEngine`.
5. Open `CMakeLists.txt`.
6. Navigate to `Project` on the navigation bar and click “`Generate cache for ReflexEngine`”.
7. Once the output window says “`CMake generation finished`”, ensure you are targeting `ReflexEngine.exe` and you are on the `Release` build as shown in the image below.
8. Press on `ReflexEngine.exe` play button to run the project. If it is your first time running the engine, you will need to build it, but it will do it automatically once you press `ReflexEngine.exe`. It can be done manually by going build-> then on rebuild ReflexEngine.

### VSCode

#### Install extensions

* [VSCode](https://code.visualstudio.com/download)
* Install the extension [CMake tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools).

#### Building ReflexEngine in VSCode

* Open `VSCode`.
* Navigate to the top left and select `File -> Open folder...`.
* Select to open to the root directory of `ReflexEngine`.
* Open command palette. (Ctrl+Shift+P)
  * `CMake: Select a kit` -> Your compiler of choice (`Clang` or `MSVC`)
  * `CMake: Select variant` -> `Release` or `RelWithDebInfo`
  * `CMake: Set build target` -> `ReflexEngine`
  * `CMake: Build`
  * `CMake: Run without debugging`

## Contributing

Please refer to the [contributing guide](CONTRIBUTING.md).

## License

This project is licensed under the [MIT license](LICENSE.md).
