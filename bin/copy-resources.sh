# Copies all resources from the game engine into lib

echo "Compiling with dev game..."
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