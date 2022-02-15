# You may need to run 
#   sudo apt install aclocal

aclocal
autoconf
automake --add-missing
emsdk/upstream/emscripten/emconfigure ./configure