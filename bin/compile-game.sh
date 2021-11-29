# Compiles the whole engine with the files in the TestGame directory

echo "Compiling with dev game..."
echo "Clearing resources"
rm -rf ./lib/resources

echo "Copying resources"
mkdir -p ./lib/          # Make sure lib dir exists
mkdir -p ./lib/resources # Make sure resources dir exists

echo "- webpage"
echo "- favicon for reasons beyond your understanding"
cp -R ./src/WebPage/* ./lib/
echo "- all resource folders"
find . -wholename "**/resources/*" -type d -prune -exec cp -R "{}" "./lib/resources/" \;

CPP_FILEPATHS=$(find src/ -name "*.cpp" -not -path "*/\.vshistory/*" | tr '\n' ' ') 
CPP_DEV_GAME_FILEPATHS=$(find TestGame/ -name "*.cpp" -not -path "*/\.vshistory/*" | tr '\n' ' ') 
NPROCS=$(grep -c 'processor' /proc/cpuinfo)

# Creates the Makefile.am file
echo "CXXFLAGS = -Wc++17-extensions
AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = index
MAKEFLAGS = -j$NPROCS
AM_LDFLAGS = -fexceptions \
-O3 \
-s LLD_REPORT_UNDEFINED \
-s WASM=1 \
-s MAX_WEBGL_VERSION=2 \
-s USE_GLFW=3 \
-o ./lib/index.js \
-fsanitize=undefined \
--preload-file ./lib/resources@/ \
-L./external-libs -lfreetype
index_SOURCES=$CPP_FILEPATHS $CPP_DEV_GAME_FILEPATHS" > Makefile.am

echo ""
echo "Running emmake..."
emsdk/upstream/emscripten/emmake make -s || exit 1

echo ""
echo "Compilation complete - compiled with test game"
echo ""

# Move output files to lib folder - could probably specify this in the makefile.am but w/e
mv index lib/index.js
mv index.data lib/
mv index.wasm lib/