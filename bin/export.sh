# Compiles all files required for a WebGLaSS project installation, depends on:
# - All resources, shaders, textures, models, etc
# - Whole include folder
# - All .hpp files
# - bin/install/download-emsdk.sh
# - bin/install/download-freetype.sh
# - exported-bin/compile.sh 
# - bin/dev-server.sh 
#
# Ideally a user would then only need to run
# - bin/install.sh
# - bin/dev-server.sh
# and
# - bin/compile.sh

echo ""

mkdir ./export

source ./bin/compile.sh || exit 1

OBJECT_FILEPATHS=$(find src/ -name "*.o" -not -path "*/\.vshistory/*" | tr '\n' ' ')


echo "Setting up structure"
mkdir ./export/WebGLaSS/
mkdir ./export/WebGLaSS/resources/
mkdir ./export/bin/
mkdir ./export/bin/install/
mkdir ./export/include/

echo "Copying default web page"
cp -R ./src/WebPage/ ./export/WebGLaSS/

echo "Copying include folder"
cp -R ./include/ ./export/

echo "Copying WebGLaSS headers"
cd ./src/
    # I don't understand how this works, but it copies the headers into /export/include/WebGLaSS???
    # It's what I need but shoudn't it copy into /export/include? ah well.
    find . -name "*.hpp" -not -path "*/\.vshistory/*" -exec cp --parents \{\} ../export/include \;
cd ..

echo "Copying sh scripts"
cp ./bin/install/download-emsdk.sh ./export/bin/install/
cp ./bin/install/download-freetype.sh ./export/bin/install/
cp ./bin/install/install.sh ./export/bin/install/
cp ./exported-bin/compile.sh ./export/bin/
cp ./bin/dev-server.sh ./export/bin/

echo "Copying WebGLaSS resources"
find . -wholename "**/resources/*" -type d -prune -exec cp -R "{}" "./export/WebGLaSS/resources/" \;

echo "Creating library file export/WebGLaSS.a"
emsdk/upstream/emscripten/emar -r export/WebGLaSS/WebGLaSS.a $OBJECT_FILEPATHS

echo ""
echo "Zipping files..."
zip -r "export.zip" "export"

echo "Cleaning up..."
rm -rf ./export