#!/bin/bash

# Declare a local variable to save your name
name="Your Name"

# Declare another variable that stores your age
age=30

# Echo both variables to the screen
echo "Name: $name"
echo "Age: $age"

# Take a screenshot of the console output
# You can use the 'scrot' command to capture a screenshot if it's installed.
# Make sure to install it using 'sudo apt-get install scrot' on Ubuntu.
# Adjust the screenshot command based on your system.
scrot screenshot_test3.png

# Optionally, you can open the screenshot using a viewer.
# Replace 'eog' with an image viewer available on your system.
eog screenshot_test3.png
