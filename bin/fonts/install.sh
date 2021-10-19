echo "Requires sudo privelages"
echo "Runs:"
echo "- sudo apt update"
echo ""
echo "Installs:"
echo "- python3"
echo ""
read -p "Continue? " -n 1 -r
echo    # (optional) move to a new line
if [[ ! $REPLY =~ ^[Yy]$ ]]
then
    [[ "$0" = "$BASH_SOURCE" ]] && exit 1 || return 1 # handle exits from shell or function but don't exit interactive shell
fi

sudo apt update
sudo apt install python3