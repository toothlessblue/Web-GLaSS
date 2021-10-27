if [ ! -d "./emsdk" ]; then
    source ./bin/install/download-emsdk.sh
fi


if [ ! -f "./external-libs/libfreetype.a" ]; then
    source ./bin/install/download-freetype.sh
fi

echo 'Project folder is initialised'
echo 'Use bin/dev-server.sh, and bin/compile.sh'