# Shell Commands
This assignment makes us more familiar with the Unix system call interface and the shell by implementing several simple programs and several features in a small shell. 

## cp
main-cp238p.c program implements copy command.  
It should take two arguments: names of the input and the output files and copy the input file into the output file. 
It uses read() and write() system calls to read the input file and write the output.  
Example invocation which copies main.c into main-out.c (assuming you call your executable cp238p)  
cp238p main.c main-out.c

## ls
main-lsy238p.c program implements simple I/O redirection.  
It starts ls command but redirects its output into a y file. i.e., it do an equivalent of shell command ls > y  
It uses exec() system call.
Example invocation (assuming you call your executable lsy238p)  
lsy238p

## pipe
main-pipe238p.c progra implements pipe.  
It starts ls command but redirects its output into the grep "main" program, which itself redirects its output to the wc. i.e., it produces output equivalent of this shell command ls |grep "main" |wc  
It uses exec(), fork(), pipe(), close(), dup() system calls.  
Example invocation (assuming you call your executable pipe238p)  
pipe238p

## shell
sh.c implements general I/O redirection.  
sh-extra.c implements general pipe.  
t.sh and extra.sh are scripts to test the programs.

## Reference
- [OS interface and shell assignment](https://www.ics.uci.edu/~aburtsev/238P/hw/hw1-shell.html)
