echo "Clearing resources"
rm -rf ./lib/resources

echo "Copying resources"
mkdir -p ./lib/          # Make sure lib dir exists
mkdir -p ./lib/resources # Make sure resources dir exists

echo "- webpage"
echo "- favicon for reasons beyond your understanding"
cp -R ./WebGLaSS/WebPage/* ./lib/
echo "- all resource folders"
find . -wholename "**/resources/*" -type d -prune -exec cp -R "{}" "./lib/resources/" \;

CPP_FILEPATHS=$(find src/ -name "*.cpp" -not -path "*/\.vshistory/*" | tr '\n' ' ') 

emsdk/upstream/emscripten/emcc WebGLaSS/WebGLaSS.a $CPP_FILEPATHS \
-fexceptions \
-O0 \
-s LLD_REPORT_UNDEFINED \
-s WASM=1 \
-s MAX_WEBGL_VERSION=2 \
-s USE_GLFW=3 \
-o ./lib/index.js \
-fsanitize=undefined \
--preload-file ./lib/resources@/ \
-L./external-libs -lfreetype