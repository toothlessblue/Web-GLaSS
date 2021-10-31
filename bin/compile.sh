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

               # Find all cpp files in   # Exclude any file           # Replace newlines
               # src/                    # in a .vshistory folder     # with space
CPP_FILEPATHS=$(find src/ -name "*.cpp" -not -path "*/\.vshistory/*" | tr '\n' ' ') 

# Creates the Makefile.am file
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

echo "Running emmake..."
emsdk/upstream/emscripten/emmake make

echo ""
echo "Compilation complete"
echo ""

# Move output files to lib folder - TODO could probably specify this in the makefile.am but w/e
mv index lib/index.js
mv index.data lib/
mv index.wasm lib/