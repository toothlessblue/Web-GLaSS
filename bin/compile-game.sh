echo "Avoid using this, you should follow the README to setup CLion for compilation instead"
echo ""

# pre build
source ./bin/copy-resources.sh
source ./bin/generate-am-makefile.sh

# build
echo ""
echo "Running emmake..."
emsdk/upstream/emscripten/emmake make -s || exit 1

echo ""
echo "Compilation complete - compiled with test game"
echo ""