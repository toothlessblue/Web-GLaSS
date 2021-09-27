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

// TODO use make instead, should compile faster

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
--preload-file ./lib/data                           `# Data files to include in the virtual file system, adds index.data to output` \
 

echo ""
echo "Compilation complete"
echo ""