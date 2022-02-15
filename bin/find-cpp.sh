# Echos a list of ALL cpp files for copying into Makefile.am

CPP_FILEPATHS=$(find src/ -name "*.cpp" -not -path "*/\.vshistory/*" | tr '\n' ' ')
CPP_DEV_GAME_FILEPATHS=$(find TestGame/ -name "*.cpp" -not -path "*/\.vshistory/*" | tr '\n' ' ')

echo "$CPP_FILEPATHS $CPP_DEV_GAME_FILEPATHS"