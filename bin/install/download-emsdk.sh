echo "installing emsdk:"
echo "- cloning repo"

git clone https://github.com/emscripten-core/emsdk.git

cd emsdk
    echo "- running ./emsdk install"
    ./emsdk install latest

    echo "- running ./emsdk activate"
    ./emsdk activate latest
cd ..

echo 'emsdk is installed'