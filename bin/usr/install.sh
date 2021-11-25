mkdir lib
mkdir lib/resources
mkdir src/
touch src/main.cpp

source ./bin/install/download-emsdk.sh
source ./bin/install/download-freetype.sh

echo '
// Code is ran once
extern "C" void Start() {

}

// Code is ran every frame
extern "C" void Update() {

}
' > src/main.cpp