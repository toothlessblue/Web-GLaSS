echo "Clearing data"
rm -rf ./lib/data

echo "Copying data:"
mkdir -p ./lib/ # Make sure lib dir exists
mkdir -p ./lib/data # Make sure data dir exists

echo "- Shaders"
cp -R ./src/shaders ./lib/data # Copy shaders
echo "- WebPage"
cp -R ./src/WebPage/* ./lib

echo ""
echo "Compiling code"
emcc src/main.cpp -s WASM=1 -s USE_GLFW=3 -o ./lib/index.js --preload-file ./lib/data # Compile code

echo "Compilation complete"
echo ""