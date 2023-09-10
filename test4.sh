#!/bin/bash

# Echo the script file name
echo "File Name: $0"

# Echo the first parameter
echo "First Parameter : $1"

# Echo the second parameter
echo "Second Parameter : $2"

# Echo all parameters as a quoted string
echo "Quoted Values: $@"

# Echo all parameters as a single quoted string
echo "Quoted Values: $*"

# Echo the total number of parameters
echo "Total Number of Parameters : $#"

# Take a screenshot of the console output
# Use 'scrot' or an appropriate screenshot tool as mentioned in test3.sh
# Adjust the screenshot command based on your system.
scrot screenshot_test4.png

# Optionally, you can open the screenshot using a viewer.
# Replace 'eog' with an image viewer available on your system.
eog screenshot_test4.png
