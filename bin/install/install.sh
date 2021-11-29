echo "Setting up file structure"
mkdir lib
mkdir lib/resources
mkdir src/
echo ""

source ./bin/install/download-emsdk.sh
echo ""

source ./bin/install/download-freetype.sh
echo ""

if [ ! -f "src/main.cpp" ]; then
    touch src/main.cpp
    echo '
    // Code is ran once
    extern "C" void Start() {

    }

    // Code is ran every frame
    extern "C" void Update() {

    }
    ' > src/main.cpp
else
    echo "src/main.cpp already exists. Do you want the default back? Delete src/main.cpp and run this script again."
fi

echo ""