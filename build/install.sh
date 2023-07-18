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

origin_dir=$(pwd)
read -p 'Build location: ' build_dir
read -p 'Install location: ' install_dir

repository='git@github:BlankRose/EverybodyEdits2.git'
sfml_baseurl='https://www.sfml-dev.org/files/'

sfml_target='SFML-2.6.0'
if [[ $(uname) == 'Darwin' ]]; then
	sfml_pkg=$sfml_baseurl$sfml_target'-macOS-clang-64-bit.tar.gz'
elif [[ $(uname) == 'Linux' ]]; then
	sfml_pkg=$sfml_baseurl$sfml_target'-linux-gcc-64-bit.tar.gz'
fi

#  Install Methods
# ############################## #

# Function to install dependencies
install_deps() {
	# Create the build directory
	mkdir -p $build_dir
	cd $build_dir

	# Install the dependencies (SFML 2.6.0)
	if [ -d $sfml_target ]; then
		rm -rf $sfml_target
	fi
	curl -# -L $sfml_pkg -o $sfml_target.tar.gz
	tar -xzf $sfml_target
	rm $sfml_target.tar.gz

	# Retrieve the project's source code
	if [ -d build ]; then
		cd build
		git pull
		cd ..
	else
		git clone $repository build
	fi

	# Build the project and move the package to the install directory
	make pkg -C build
	mv build/pkg $install_dirs
}

echo $build_dir
echo $install_dir
