# "Generates" a brand new Makefile.am by finding all CPP files and using that as sources.
# Also resets NPROCS
# This completely replaces the current Makefile.am

CPP_FILEPATHS=$(find src/ -name "*.cpp" -not -path "*/\.vshistory/*" | tr '\n' ' ')
CPP_DEV_GAME_FILEPATHS=$(find TestGame/ -name "*.cpp" -not -path "*/\.vshistory/*" | tr '\n' ' ')
NPROCS=$(grep -c 'processor' /proc/cpuinfo)

# Creates the Makefile.am file
echo "CXXFLAGS = -Wc++17-extensions
AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = index
MAKEFLAGS = -j$NPROCS
AM_LDFLAGS = -fexceptions \
-O0 \
-s LLD_REPORT_UNDEFINED \
-s WASM=1 \
-s MAX_WEBGL_VERSION=2 \
-s USE_GLFW=3 \
-o ./lib/index.js \
-fsanitize=undefined \
--preload-file ./lib/resources@/ \
--memoryprofiler \
-L./external-libs -lfreetype
index_SOURCES=$CPP_FILEPATHS $CPP_DEV_GAME_FILEPATHS" > Makefile.am