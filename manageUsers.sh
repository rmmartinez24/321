#!/bin/bash

# Check the number of arguments
if [ "$#" -ne 3 ]; then
  echo "Usage: $0 <input_filename> <group_name> <operation_flag>"
  exit 1
fi

input_file=$1
group_name=$2
operation_flag=$3

# Check if the group exists
getent group "$group_name" &> /dev/null
if [ $? -ne 0 ]; then
  echo "Group $group_name does not exist."
  exit 1
fi

# Function to add a user
add_user() {
  username=$1
  encrypted_password=$2
  home_directory="/home/$username"

  # Add the user to the system
  sudo useradd -m -d "$home_directory" -g "$group_name" -p "$encrypted_password" "$username"

  # Check if the user was added successfully
  if [ $? -eq 0 ]; then
    echo "User $username added successfully."
  else
    echo "Failed to add user $username."
  fi
}

# Function to remove a user
remove_user() {
  username=$1

  # Delete the user and the home directory
  sudo userdel -r "$username"

  # Check if the user was removed successfully
  if [ $? -eq 0 ]; then
    echo "User $username removed successfully."
  else
    echo "Failed to remove user $username."
  fi
}

# Read the input file and process each user
while IFS= read -r line || [[ -n "$line" ]]; do
  if [[ -n "$line" && ! "$line" =~ ^[[:space:]]*$ ]]; then
    read -r username password <<< "$line"

    if [ "$operation_flag" == "-a" ]; then
      add_user "$username" "$password"
    elif [ "$operation_flag" == "-r" ]; then
      remove_user "$username"
    else
      echo "Invalid operation flag. Use -a to add users or -r to remove users."
      exit 1
    fi
  fi
done < "$input_file"
