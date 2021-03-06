echo "Requires sudo privelages"
echo "Runs:"
echo "- sudo apt update"
echo "- pip install --upgrade pip"
echo ""
echo "Installs:"
echo "- python3"
echo "- python3-pip"
echo "- Pillow (py)"
echo "- tqdm (py)"
echo ""
read -p "Continue? " -n 1 -r
echo    # (optional) move to a new line
if [[ ! $REPLY =~ ^[Yy]$ ]]
then
    [[ "$0" = "$BASH_SOURCE" ]] && exit 1 || return 1 # handle exits from shell or function but don't exit interactive shell
fi

sudo apt update
sudo apt install python3
sudo apt install python3-pip

python3 -m pip install --upgrade pip
python3 -m pip install --upgrade Pillow
python3 -m pip install --upgrade tqdm