cd ./src/

find . -name "*.hpp" -not -path "*/\.vshistory/*" -exec cp --parents \{\} ../export \;

cd ..