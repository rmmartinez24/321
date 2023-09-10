#!/bin/bash

# Echo current directory
echo "Current directory: $(pwd)"

# Change directory to your home directory
cd ~

# Change directory to a child directory within your home directory
cd child_directory_name   # Replace with the actual child directory name

# List all files that end with .c within the child directory
echo "List of .c files in the child directory:"
find . -type f -name "*.c"

# Navigate back to your home directory
cd ~
