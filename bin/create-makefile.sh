CPP_FILEPATHS=$(find src/ -name "*.cpp" -not -path "*/\.vshistory/*" | tr '\n' ' ') 

echo "AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = index
AM_LDFLAGS = -fexceptions \
-O0 \
-s LLD_REPORT_UNDEFINED \
-s WASM=1 \
-s MAX_WEBGL_VERSION=2 \
-s USE_GLFW=3 \
-o ./lib/index.js \
-fsanitize=undefined \
--preload-file ./lib/resources@/ \
-L./external-libs -lfreetype
index_SOURCES=$CPP_FILEPATHS" > Makefile.am