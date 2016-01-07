# global-pushd-popd
A global pushd/popd-like utlilty designed to behave exectly like `pushd` and `popd` except that it has a global stack. 

The stack is not bound by a terminal process. You can push a directory from one terminal process and pop it into another. I developed this because it comes in handy when I have muiltiple terminals open.

## Info

- Utilizes IPC in from of shared memory. The stack is stored in shared memory which makes it "global".
- Adds a function in `.bashrc` that wraps the call to the popping utility. The reason for this is because a process cannot change a terminal's working direcotry, so we need a way to have the terminal "make" the call. The funciton is very simple:

```shell
function gpopdir() {
  cd "$(global_pop_dir)"
}
```

- Basically, this takes the output of the popping utility (a directory which has been popped) and does a `cd` into it. Thanks to [this Stack Exchange answer](http://unix.stackexchange.com/questions/14721/changing-current-working-dir-with-a-script).
- The stack is set to a max of `100` elements. 

## Installation

- `./configure.sh` will compile the files, modify the `.bashrc`, and copy the executables to `/usr/local/bin/`.
  - Note: this will need `sudo` privledges.

## Usage

- `$ gpushdir <directory>` will push a directory onto the stack.
- `$ gpushdir -r` will deallocate the shared memory (stack).
- `$ gpopdir` will pop a directory from the stack and `cd` into it.

## Todo

- Remove the `-r` option and implement the deallocation of the shared memory when the stack is being popped when empty.
