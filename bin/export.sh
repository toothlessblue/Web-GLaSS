echo ""

rm -rf ./export
mkdir ./export

source ./bin/compile.sh || exit 1

OBJECT_FILEPATHS=$(find src/ -name "*.o" -not -path "*/\.vshistory/*" | tr '\n' ' ')


echo "Setting up structure"
mkdir ./export/WebGLaSS/
mkdir ./export/WebGLaSS/resources/
mkdir ./export/bin/
mkdir ./export/bin/install/
mkdir ./export/include/
mkdir ./export/include/

echo "Copying default web page"
cp -R ./src/WebPage/ ./export/WebGLaSS/

echo "Copying include folder"
cp -R ./include/ ./export/

echo "Copying WebGLaSS headers"
cd ./src/
    find . -name "*.hpp" -not -path "*/\.vshistory/*" -exec cp --parents \{\} ../export/include \;
cd ..

echo "Copying sh scripts"
cp ./bin/install/download-emsdk.sh ./export/bin/install/
cp ./bin/install/download-freetype.sh ./export/bin/install/
cp ./bin/usr/install.sh ./export/bin/install/
cp ./bin/usr/compile.sh ./export/bin/
cp ./bin/dev-server.sh ./export/bin/

echo "Copying WebGLaSS resources"
find . -wholename "**/resources/*" -type d -prune -exec cp -R "{}" "./export/WebGLaSS/resources/" \;

echo "Creating library file export/WebGLaSS.a"
emsdk/upstream/emscripten/emar -r export/WebGLaSS/WebGLaSS.a $OBJECT_FILEPATHS

echo ""

