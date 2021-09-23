
if [ ! -d "./emsdk" ]; then
    echo "installing emsdk"
    git clone https://github.com/emscripten-core/emsdk.git


    cd emsdk
        ./emsdk install latest
        ./emsdk activate latest
    cd ..
fi

echo 'initialised! please run:'
echo ''
echo 'source "./emsdk/emsdk_env.sh"'
echo ''
echo "For some reason running it in this bash script doesn't work, lucy prob knows ¯\_(o.o)_/¯"