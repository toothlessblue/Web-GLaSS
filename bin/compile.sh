CPP_FILEPATHS=$(find src/ -name "*.cpp" -not -path "*/\.vshistory/*" | tr '\n' ' ') 
NPROCS=$(grep -c 'processor' /proc/cpuinfo)

# Creates the Makefile.am file
echo "CXXFLAGS = -Wc++17-extensions
AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = index
index_LINK = true
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
index_SOURCES=$CPP_FILEPATHS" > Makefile.am

echo "Running emmake..."
emsdk/upstream/emscripten/emmake make -s || exit 1

echo ""
echo "Compilation complete - generated .o files"
echo ""