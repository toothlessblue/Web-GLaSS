Introducing, 2 weeks of faf in 30 lines.

- Inside lib folder, follow these steps
https://stackoverflow.com/questions/61049517/build-latest-freetype-with-emscripten
>```
mkdir build
cd build
emcmake cmake ..
emmake make
emmake make install
>```

If include header files are missing in project, copy them from the include folder in the downloaded folder.