# Shell-project: MFshell
## About
Made by Muhamed Mulić and Faris Muhović
We coded a shell for the Linux operating system in the C programming language. It works remarkably well given that we've got no experience in programming of this kind. We implemented the main loop of the shell, where it forks itself and runs the given command(s). We have also implemented piping and redirection into files. It lacks certain features of bash, such as jobs, but it has full line editing, local history, and a custom prompt (_note: the prompt cannot be customized by the user, we have customized it for them_). We did all the tasks from the document, every single one. We tried to make the shell good enough that it could actually reasonably be used in the real world. We think we have succeeded. We have also added some custom things to the `fortune` command, and an original feature not found in _any other shell!_ More about that in the commentary section below.

## Files:
|File| Description|
|---|---|
|bomb.c| Forkbomb and forkbomb killer, not compiled and not linked. Only an example|
|builtins.c| Contains common functions the shell has such as echo, cp, and free|
|builtins.h| Header file with function signatures|
|defines.h| Header file that contains constants used in the code (such as size of buffer), for easier editing|
|fortune.c| Contains the fortune command as well as all it's ASCII art|
|fortune.h| Header file with function signatures|
|history.c| Logic for saving and reading command history using a file|
|history.h| Header file with function signatures|
|main.c| Entry point of the shell, contains the main loop and forking logic|
|main.h| Mostly there for the makefile to work, but its useful too|
|makefile| The makefile, contains make targets|
|README.md| This|
|utils.c| Has many useful utility functions essential for the functioning of the shell and debugging|
|utils.h| Header file with function signatures|

## Compilation and Installation
Using the makefile, you can fully compile and run the shell using `make`. If you want to only build it without running, you can do so with `make build`. The makefile compiles all the source files into objects (with the exception of bomb.c), and links all of them into one ELF binary. The build files are placed in `build/...`, which you can delete with `make clean`.
You will need to have make and gcc installed. If, for some reason, your system does not contain the development headers for GNU readline, you should install them with `sudo apt install libreadline-dev` on Debian-based systems, `sudo zypper in readline-devel` on openSUSE. Most systems do contain the header files (they are part of the GNU standard) so this should not be a problem.
Finally, you can permanantly install the shell, if you so choose, using `sudo make install`. Then you can run `MFshell` from anywhere.

## Commentary
This was quite a difficult and challenging task, it took us quite a while to finish. From the start we had the makefile which made development significantly easier. Not having to recompile the entire shell on every change was a time saver - as well as being able to do everything automatically with only one command- `make`. We used a macro so that matches any .c file into an .o file, as long as it's in the build target dependencies.
Our shell was pretty ugly, that is until we added a prompt theme and used the GNU readline library. String manipulation in C is absolutely awful and insecure, which the compiler kept complaining about. We almost wanted to make our own string abstraction class with methods such as split(), but in the end we decided not to, since we would only use it a couple of times.
Because we were conditioned by programming in Java the last semester, we completely forgot how C works with the stack, which led to some very strange bugs in development. This was because we had declared a string inside of a function and returned it's address. Since it was stack allocation, it got overwritten with the next functioncall. Here *gdb* was really helpful, and we got rid of the use-after-return bug.
Particularly, we struggled with piping and timing the prompt to only print after _all_ child processes finish. Piping was quite problematic at first, because we didn't understand how the `pipe()` syscall worked in kernel space, and the child of the pipe would never close. It was quite easy to fix, we just closed the corresponding pipes after forking so that the parent _only_ has the write end, and the child _only_ has the read end. This way the child finished when the parent finished. As for timing, the shell would print the prompt before the last command in the pipeleing finished. This was because, after the first command finished and killed itself, the child process would reparent onto init, and the `wait()` syscall could not wait for it. The solution to the timing problem was to call a `prctl` function that designates the shell process as a "reaper" (so orphaned processes will reparent onto it), which instantly made our shell unportable (not of much concern for us, it's only meant to run on Linux systems). One last thing worth mentioning is that piping is very strict, a pipe character *must* be preceeded and succeeded by a space character. This is not a bug, but a feature. It prevents the user from making stupid mistakes by forcing them to pay attention to what they are typing. This does not apply to redirection, the `>` and `>>` can be placed wherever and it will output it into the specified file.

We expanded on the standard features of bash by adding more ACII output and color options to the `fortune` command, as well as a _new and innovative method to shut down your computer_. The `rr` command (named after the fictional game of russian roulette) has a 1/6 chance of shutting down your system every time it is called.

Our code is very tidy, it is segmented into multiple files which makes working with the code a lot easier. The only other part is the fortune command, since it was too big we have placed it into it's own file in order not to "pollute" the other functions. The code is commented quite well, and is not complicated at all. Any complications are abstracted away into functions (_such as `buffer2vector()` or `run()`_).

## Sources and Materials
The man pages were the most useful resource; not only did they give a description of what each syscall does, but most also had example code at the bottom to demonstrate functionality. ChatGPT was surprisingly not very helpful as it made many mistakes, but it did point us to other great resources, such as the GNU readline library. The _geeksforgeeks_ website was also quite useful in explaining some things, though it was way too verbose. The online man websites were much better than the man page in the terminal, it was just easier to read and work with, even though they had the exact same text. The _cplusplus.com_ website helped us with many C standard library functions which were quite confusing (_e.g. strtok_).


## Answers to task 1.5

Question 1.5.1: Do the following actions require the OS to use kernel mode or user mode is
sufficient? Explain.
1. A program wants to read from disk.
2. Reading the current time from the hardware clock

Answer: 
1. Whenever a program wants to access files from a disk, kernel mode is needed because we are trying to directly access the computer resources which as we know the kernel is in charge of.
2. Reading the current time from hardware clock can be done in user mode because we are not accessing critical information that will endanger our system security.

Question 1.5.2: Explain the purpose of a system call. There are different sets of system calls:
list them and give at least 2 examples of a system call for each category.

Answer:
A system call is an interface between a process(a program during execution) and operating system. A system call transfers control into the operating system by raising hardware privilege level. We have two modes. User mode and kernel mode. User mode does not have access to memory and resources. Whenever a program crashes in user mode, It will not break the system. Kernel mode has all the resources and permissions. If a program crashes in kernel mode it will break the system. Most programs will use user mode because its much safer, but some of them will need those computer resources. Thats why system calls exist. Those programs will "call" system calls to the operating system, after the OS receives the request for a system call, It will switch the program permission mode to kernel(This is called mode switching.).
System calls can be grouped into five categories:
1. Process control: They are used to create,modify,manage and terminate system processes and threads, including functions such as fork(), exec(), wait(), exit()
2. File Management: These system calls are used to create, modify, and manage files and directories, including functions such as open(), read(), write(), and close().
3. Device Management: These system calls are used to access and manage hardware devices such as printers, disks, and network interfaces, including functions such as ioctl() and read().
4. Information Maintenance: These system calls are used to retrieve and update information about the system and its resources, including functions such as getpid(), getuid(), and getgid().
5. Communication: These system calls are used to facilitate interprocess communication and synchronization, including functions such as pipe(), socket(), and sendmsg().

Question 1.5.3: What are the possible outputs printed from this program shown below? You
may assume that the program runs on a modern Linux-like OS. You may ignore any output
generated from “some executable”.
```
int ret = fork();
if(ret == 0) {
printf(‘‘Hello1\n’’);
exec(‘‘some_executable’’);
printf(‘‘Hello2\n’’);
} else if(ret > 0) {
wait();
printf(‘‘Hello3\n’’);
} else {
printf(‘‘Hello4\n’’);
}
```
Answer: 
I. Fork and exec will succeed. Hello1 and Hello3 will be printed out to the console.
II. Fork will succeed. exec will fail. Hello1, Hello2 and Hello3 will be printed out to the console.
III. Fork will fail and Hello4 will be printed out.
