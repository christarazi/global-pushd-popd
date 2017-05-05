#!/bin/bash

# Copyright (C) 2017 Chris Tarazi
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

mkdir build bin

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
