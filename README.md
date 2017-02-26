# global-pushd-popd
A global pushd/popd-like utility designed to behave exactly like `pushd` and
`popd` except with a global stack.

The stack is not bound by a terminal process unlike the original commands. You
can push a directory from one terminal process and pop it into another. I
developed this because it comes in handy when I have multiple terminals open.

## Info

- Utilizes IPC in form of shared memory. The stack is stored in shared memory
which makes it "global".
- The stack is set to a max of `100` elements.
- To make the popping utility work, a function in `.bashrc` needs to be added.
This is because the popping utility outputs the directory it has popped and a
child process (popping utility) cannot change the parent process's (terminal)
working directory. Therefore, we need to add a function to `.bashrc` so that
the terminal can capture the output of the popping utility and `cd` into it.
See more [here](http://unix.stackexchange.com/questions/14721/changing-current-working-dir-with-a-script).

## Installation

### Dependencies

 - g++
 - make
 - bash (`configure.sh` is a bash script)

The default installation assumes bash is the default shell, but it is not a
requirement.

```shell
$ ./configure.sh
```

This will compile and install the tool. You will need sudo privileges for the
default installation directory. Then add the function below to your shell's
configuration file.

**Note:** If you are using a different shell other than `bash`, please add the
function above to your shell's respective configuration file, i.e. if you
are using `zsh`, then it would go in `.zshrc`.

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

## Usage

```shell
$ gpushdir <directory>     # Push a directory onto the stack.
$ gpushdir -r              # Deallocate the shared memory (stack).
$ gpopdir                  # Pop a directory from the stack and `cd` into it.
$ gpopdir -l               # List contents of the stack from top to bottom.
```

## Todo

- Remove the `-r` option and implement the deallocation of the shared memory
when the stack is being popped when empty.
- ~~Add ability to list the contents of the stack.~~
- Add ability to clear the stack.
- Add ability to have multiple stacks.
- Include `-u` option for automatic updating of the program.

## Contribution

Please fork and submit a pull request. If you find a bug, submit an issue. I
welcome feedback as well.
