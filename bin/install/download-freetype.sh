if [ ! -f "external-libs/libfreetype.a" ]; then
    echo 'Downloading freetype'
    mkdir ./external-libs
    cd ./external-libs

    # https://download.savannah.gnu.org/releases/freetype/
    wget https://download.savannah.gnu.org/releases/freetype/freetype-2.10.0.tar.bz2 -q -O freetype.tar.bz

    echo 'Extracting freetype'
    tar -xf freetype.tar.bz

    echo 'Removing archive'
    rm freetype.tar.bz

    echo 'Building for WASM, takes ~ 30 seconds'
    cd freetype-2.10.0
    mkdir build
    cd build

    ../../../emsdk/upstream/emscripten/emcmake cmake -s ..
    ../../../emsdk/upstream/emscripten/emmake make -s
    ../../../emsdk/upstream/emscripten/emmake make -s install

    echo 'Moving libfreetype.a to external-libs'
    mv libfreetype.a ../../

    echo 'Removing freetype-2.10.0'
    cd ../../
    rm -rf freetype-2.10.0

    cd ../../../

    echo 'FreeType is installed'
else
    echo "libfreetype found, did you mean to reinstall? Remove external-libs/libfreetype.a"
fi