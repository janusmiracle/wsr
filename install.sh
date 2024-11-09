#!/bin/bash

# Exit if any command fails
set -e

if [[ ! -f Makefile ]]; then
	echo "Makefile not found in the current directory."
	exit 1
fi

echo "Compiling the code with make..."
make

EXECUTABLE_NAME="wsr"

if [[ ! -f $EXECUTABLE_NAME ]]; then
	echo "Compilation failed: Executable not found."
	exit 1
fi

echo "Installing the executable to /usr/local/bin..."
sudo mv $EXECUTABLE_NAME /usr/local/bin/

if [[ $? -eq 0 ]]; then
	echo "$EXECUTABLE_NAME has been installed successfully and can be run as a global command."
else
	echo "Installation failed."
fi
