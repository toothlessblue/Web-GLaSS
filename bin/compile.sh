echo "Clearing data"
rm -rf ./lib/data

echo "Copying data:"
mkdir -p ./lib/ # Make sure lib dir exists
mkdir -p ./lib/data # Make sure data dir exists

echo "- Shaders"
cp -R ./src/shaders ./lib/data # Copy shaders
echo "- WebPage"
cp -R ./src/WebPage/* ./lib

               # Find all cpp files in   # Exclude any file             # Replace newlines
               # src/                    # in a .vshistory folder       # with space
CPP_FILEPATHS=$(find src/ -name "*.cpp" -not -path "*/\.vshistory/*" | tr '\n' ' ') 

echo ""
echo "Compiling files: "
echo ${CPP_FILEPATHS}
echo ""

echo "Running emcc..."
./emsdk/upstream/emscripten/emcc ${CPP_FILEPATHS} -O0 -s LLD_REPORT_UNDEFINED -s WASM=1 -s USE_GLFW=3 -o ./lib/index.js --preload-file ./lib/data # Compile code

echo ""
echo "Compilation complete"
echo ""