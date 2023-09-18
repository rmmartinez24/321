#!/bin/bash

password="_yashiMTZ_$24"
pass_length=$(echo -n "$password" | wc -m)

if [ "$pass_length" -lt 8 ]; then
    echo "Password length is less than 8 characters."
fi

if ! [[ "$password" =~ [0-9] ]]; then
    echo "Password does not contain a numeric character."
fi

if ! [[ "$password" =~ [@#$%&*+=-] ]]; then
    echo "Password does not contain a special character: @, #, $, %, &, *, +, -, =."
fi

if [ "$pass_length" -ge 8 ] && [[ "$password" =~ [0-9] ]] && [[ "$password" =~ [@#$%&*+=-] ]]; then
    echo "All password tests passed."
fi
