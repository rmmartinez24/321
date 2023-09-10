#!/bin/bash

# i. Change directory to your home directory.
cd ~

# ii. Create a child directory called mycode.
mkdir mycode

# iii. Change to the mycode directory.
cd mycode

# iv. Copy all files that end with .c to the mycode directory.
cp ~/path_to_your_c_files/*.c .

# v. Navigate up a directory.
cd ..

# vi. Create a new child directory called mycode2.
mkdir mycode2

# vii. Copy all files from the mycode directory to the mycode2 directory.
cp -r mycode/* mycode2/

# viii. Rename the mycode directory to deadcode.
mv mycode deadcode

# ix. Remove the deadcode directory and all its files.
rm -rf deadcode

echo "Script completed successfully."
