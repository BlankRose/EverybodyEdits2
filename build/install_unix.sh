#!/bin/bash
# ############################################################################ #
#          .-.                                                                 #
#    __   /   \   __                                                           #
#   (  `'.\   /.'`  )   EverybodyEdits2 - install.sh                           #
#    '-._.(;;;)._.-'                                                           #
#    .-'  ,`"`,  '-.                                                           #
#   (__.-'/   \'-.__)   By: Rosie (https://github.com/BlankRose)               #
#       //\   /         Last Updated: Tuesday, July 18, 2023 7:49 PM           #
#      ||  '-'                                                                 #
# ############################################################################ #


#  Setup
# ############################## #

# Exit on error
set -e


#  Variables
# ############################## #

# The original directory (in case it has been sourced)
origin_dir=$(pwd)

# The repository to clone
repository='https://github.com/BlankRose/EverybodyEdits2.git'
sfml_baseurl='https://www.sfml-dev.org/files/'

# The target names
game_target='EverybodyEdits2'
sfml_target='SFML-2.6.0'

# Determines the SFML package to download
if [[ $(uname) == 'Darwin' ]]; then
	sfml_pkg=$sfml_baseurl$sfml_target'-macOS-clang-64-bit.tar.gz'
elif [[ $(uname) == 'Linux' ]]; then
	sfml_pkg=$sfml_baseurl$sfml_target'-linux-gcc-64-bit.tar.gz'
else
	echo 'Unsupported OS!'
	exit 1
fi

# Checks if used commands are available
if ! command -v curl &> /dev/null \
	|| ! command -v tar &> /dev/null \
	|| ! command -v git &> /dev/null \
	|| ! command -v make &> /dev/null \
	|| ! command -v c++ &> /dev/null; then
	echo 'Missing needed commands: curl, tar, git, make, c++'
	exit 1
fi


#  Read User Input
# ############################## #

# Retrieve the various options
echo ""
echo "EverybodyEdits2 Installer"
echo "-------------------------"
echo ""
echo "# -- OPTIONS -- #"
echo ""

echo "-- Where would you like to install EverybodyEdits2?"
install_dir=''
while [[ -z $install_dir ]]; do
	read -p 'Install location: ' -r install_dir
done
echo ""

echo "-- Where would you like to build EverybodyEdits2?"
build_dir=''
while [[ -z $build_dir ]]; do
	read -p 'Build location: ' -r build_dir
done
echo ""

echo "-- Would you like to remove the build directory after install?"
remove_build_dir=''
while [[ ! $remove_build_dir =~ ^[YyNnOo]$ ]]; do
	read -p 'Remove after install? [Y / N] ' -r remove_build_dir
done

# interpretes ~ as $HOME
build_dir=${build_dir/#\~/$HOME}
install_dir=${install_dir/#\~/$HOME}


#  Install Methods
# ############################## #

echo ""
echo "# -- INSTALLING -- #"
echo ""

# Create the build directory
mkdir -p $build_dir
cd $build_dir

# Install the dependencies (SFML 2.6.0)
if [ -d $sfml_target ]; then
	rm -rf $sfml_target
fi
echo 'Downloading SFML 2.6.0...'
curl -# -L $sfml_pkg -o $sfml_target.tar.gz

echo 'Extracting SFML 2.6.0...'
tar -xzf $sfml_target.tar.gz
rm $sfml_target.tar.gz

# Retrieve the project's source code
echo 'Retrieving EverybodyEdits2 source code...'
if [ -d build ]; then
	cd build
	git pull
	cd ..
else
	git clone -b dev $repository $game_target
fi

# Build the project and move the package to the install directory
echo 'Building EverybodyEdits2...'
make pkg -C $game_target
mkdir -p $install_dir
mv $build_dir/$game_target/build/pkg/** $install_dir

# Remove the build directory if requested
if [[ $remove_build_dir =~ ^[YyOo]$ ]]; then
	echo 'Removing build directory...'
	rm -rf $build_dir
fi

# Completes and returns to the original directory
# (in case it has been sourced)
echo ""
echo "# -- INSTALLATION COMPLETE -- #"
echo ""
cd $origin_dir
