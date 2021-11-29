run `bin/export.sh`

Compiles all files required for a WebGLaSS project installation, depends on:
- All resources, shaders, textures, models, etc
- Whole include folder
- All .hpp files
- bin/install/download-emsdk.sh
- bin/install/download-freetype.sh
- exported-bin/compile.sh
- bin/dev-server.sh

Ideally a user would then only need to run
- bin/install.sh
- bin/dev-server.sh
and
- bin/compile.sh

This is exported in `export.zip`