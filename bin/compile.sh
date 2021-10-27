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

               # Find all cpp files in   # Exclude any file             # Replace newlines
               # src/                    # in a .vshistory folder       # with space
CPP_FILEPATHS=$(find src/ -name "*.cpp" -not -path "*/\.vshistory/*" | tr '\n' ' ') 

echo ""
echo "Compiling files: "
echo ${CPP_FILEPATHS}
echo ""

# TODO use make instead, will compile faster and lets us use a better incremental compiler
#   This will also allow disabling warnings like "warning: nested namespace definition is a C++17 extension; define each namespace separately"
#   Keep trying to complete this todo but always give up cause make looks like such a pain

# Uses WebGL 2, this is newer and has less support but gives us access to a bunch of fun tools
#  like compute shaders

echo "Running emcc..."
./emsdk/upstream/emscripten/emcc ${CPP_FILEPATHS}   `# Compile all c++ files` \
-fexceptions                                        `# Enable java script based c++ exceptions` \
`#-fwasm-exceptions                                  # Enable wasm based c++ exceptions - Faster but lacks support - https://webassembly.org/roadmap/` \
-O0                                                 `# The optimisation setting, O0 is slowest to run but fastest to compile, O3 is fastest to run but slowest to compile` \
-s LLD_REPORT_UNDEFINED                             `# Report errors for undefined access to variables (I think? It's handy)` \
-s WASM=1                                           `# Build to web assembly instead of pure js` \
-s MAX_WEBGL_VERSION=2                              `# Use WebGL 2 - Compute shaders + optimised` \
-s USE_GLFW=3                                       `# GL version to use` \
-o ./lib/index.js                                   `# Output file, specifying .js outputs index.wasm and index.js files` \
-fsanitize=undefined                                `# Much needed more detailed error info` \
--preload-file ./lib/resources@/                    `# Data files to include in the virtual file system, adds index.data to output` \
-L/usr/local/lib -lfreetype

echo ""
echo "Compilation complete"
echo ""