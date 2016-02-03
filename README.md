# global-pushd-popd
A global pushd/popd-like utility designed to behave exactly like `pushd` and `popd` except that it has a global stack. 

The stack is not bound by a terminal process. You can push a directory from one terminal process and pop it into another. I developed this because it comes in handy when I have multiple terminals open.

## Info

- Utilizes IPC in form of shared memory. The stack is stored in shared memory which makes it "global".
- To make the popping utility work, I needed to add a function in `.bashrc` that wraps the call to the popping utility. The reason for this is because a process cannot change a terminal's working directory, so we need a way to have the terminal "make" the call. The function is very simple:

```shell
# Function for wrapping the output of global_pop_dir so we can cd.
function gpopdir() {
	if [ "$#" -eq 0 ]
	then
		cd "$(global_pop_dir)"
	else
		global_pop_dir "$@"
	fi
}
```

- Basically, this takes the output of the popping utility (a directory which has been popped) and does a `cd` into it. Thanks to [this Stack Exchange answer](http://unix.stackexchange.com/questions/14721/changing-current-working-dir-with-a-script).
- The stack is set to a max of `100` elements. 

## Installation

- `./configure` will compile the files, modify the `.bashrc`, and copy the executables to `/usr/local/bin/` (or a directory of your choice).
  - Note: this will need `sudo` privileges to modify the `.bashrc` and to install to a system directory.

## Usage

- `$ gpushdir <directory>` will push a directory onto the stack.
- `$ gpushdir -r` will deallocate the shared memory (stack).
- `$ gpopdir` will pop a directory from the stack and `cd` into it.
- `$ gpopdir -l` will list all the contents of the stack from top to bottom.

## Todo

- Remove the `-r` option and implement the deallocation of the shared memory when the stack is being popped when empty.
- ~~Add ability to list the contents of the stack.~~
- Add ability to clear the stack.
- Add ability to have multiple stacks.
- Include `-u` option for automatic updating of the program.

## Contribution

- If you have an idea or found something to fix, please fork and submit a pull request. I appreciate your feedback as well.
