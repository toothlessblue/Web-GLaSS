After [[Installing the engine]]

`main.cpp` contains two functions, `Start` and `Update`, which is where your initial code goes.
- Both functions MUST be defined somewhere in your project
- Neither function needs to contain any code, but I stress that they do NEED to exist.
- The file does not need to be called `main.cpp`, but that is the default, and the install script does test for it when it's ran.

Run `bin/compile.sh` to compile your game

Run `bin/dev-server.sh` to host a place where you can test run your game, usually at http://127.0.0.1:8000

`bin/dev-server.sh` is reliant on a python3 installation, but requires no extra python libs, so you may need to run `sudo apt install python3`
