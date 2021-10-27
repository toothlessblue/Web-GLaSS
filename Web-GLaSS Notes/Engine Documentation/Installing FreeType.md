### Compiling FreeType for Web ASM
Introducing, 2 weeks of faf in 30 lines.

- Download https://download.savannah.gnu.org/releases/freetype/
- Inside folder, follow these steps
https://stackoverflow.com/questions/61049517/build-latest-freetype-with-emscripten
>```
mkdir build
cd build
emcmake cmake ..
emmake make
emmake make install
>```

- copy `libfreetype.a` to `/usr/local/lib`

If include header files are missing in project, copy them from the include folder in the downloaded folder.

// TODO 
^ that but automatically in the init script, and copy libfreetype to some place in the project folder and change the compile script to use that file instead of /usr/local/lib