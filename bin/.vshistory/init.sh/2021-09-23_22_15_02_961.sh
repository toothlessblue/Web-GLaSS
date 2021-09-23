
if [ ! -d "./emsdk" ]; then
    echo "installing emsdk"
    git clone https://github.com/emscripten-core/emsdk.git

    cd emsdk
        ./emsdk install latest
        ./emsdk activate latest
    cd ..
fi

echo 'emsdk is installed! use bin/compile.sh'