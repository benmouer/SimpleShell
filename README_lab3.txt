NAME: Benjamin Mouer
CSC-241 - Lab 3

The purpose of this lab is to understand how to create a simple shell and run commands from inside that shell. This lab requires the use of execvp(), waitpid(), malloc(), and fork(). Without understanding of these functions, the lab would not be possible. 

My lab is thoroughly described through comments in the code. Here is a simple brief summary of how it runs:
1.) Get the line from the command line and create a string of words.
2.) Take that string and though use of strtok(), split the line into words inside an array.
3.) Use this array of words, a forked child process, and execvp() to run the command specified by "command [file or directory]"
4.) If the command ends with a "&" then run the command in the background. for example "ls& -la"
5.) Run in the background by not waiting for a child to complete the process before requesting a new command. 
6.) if "exit" is the first word typed, then the program will terminate and exit the shell. 

To compile: in Unix, type "gcc -o lab3.out lab3.c"
To run: in Unix, type "./lab3.out"

