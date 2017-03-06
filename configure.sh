#!/bin/bash

PREFIX='/usr/local/bin'
CC='g++'
EXES='bin'

print_usage() {
	cat <<-EOF
	Usage: $0 [-h|--help] [--prefix=DIR]

	Options:
	  -h, --help      Prints this help.

	  --prefix=DIR    Set installation directory.
	                  Default value is $PREFIX.
	EOF
}

# Sanity check arguments
if [[ $# -gt 1 ]]; then
	print_usage && exit -1
elif [[ $# -eq 1 ]]; then
	if [[ $1 =~ --prefix=.+ ]]; then
		PREFIX="${1/--prefix=/}"
	elif [[ $1 == "-h" || $1 == "--help" ]]; then
		print_usage && exit
	else
		print_usage && exit -1
	fi
fi

# Check for g++
if [[ ! -x $(which $CC) ]]; then
	echo "$CC is required." && exit -1
fi

# Check for make
if [[ ! -x $(which make) ]]; then
	echo "make is required." && exit -1
fi

echo "root privileges may be required for installation."

make && cp $EXES/* -t $PREFIX
ERR=$?

if [[ $ERR -gt 0 ]]; then
	exit $ERR
fi

echo "Successfully installed to $PREFIX."

cat <<EOF

# Function for wrapping the output of global_pop_dir so we can cd.
function gpopdir() {
	if [[ "\$#" -eq 0 ]]
	then
		cd "\$(global_pop_dir)"
	else
		global_pop_dir "\$@"
	fi
}

Please add the above function to your .bashrc file and you can begin using
this tool.
EOF

make clean > /dev/null
