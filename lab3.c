#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/*Benjamin Mouer
 * CSC 241
 * Lab 3
 * 10/25/18
 * Dr.Cañas
 * */



/*Here i am declaring my functions that I am using and a global variable i, that i will use to identify the location of certain tokens*/

char *nextLine();
char **wordArray(char *line);
int exc(char ** words, int amp);
void exitCheck(char ** words);
int checkAmp(char *** words);
int i;



/*Here is my main, started with defining a char*, and pointer to my words(tokens), an exit status to keep my loop running and, a check for the & (ampersand) initialized to 0.
 *
 * I also use main(argc, **argv) to read directly from the console
 * */

int main(int argc, char **argv) {
    char *line;
    char **words;
    int exitStatus = 1;
    int amp = 0;


/*This is a while loop that keeps my shell running indefinitely unless the entire program is exited in one of the functions
 *
 * first, I print ">" to identify that the shell is still executing, then I read a line and split the line into words that are contained in an array. Then, since I am done using my i for that set of words, i set it back to 0. Then I check to see if I read "exit" and quit the shell if I do. Then I run execute on the words and set the exit status to 1 to ensure that I keep running my loop, and finally I print a newline and start over.
 * */

    while(exitStatus == 1) {
        printf(">");
        line = nextLine();
        words = wordArray(line);
        i = 0;
        exitCheck(words);
        amp = checkAmp(&words);
        exitStatus = exc(words, amp);
        printf("\n");
    }




}

/*This is a very simple function to read the next line in the console, I use getline() but have no use for the size or return value.
 *
 *
 *
 * I used https://stackoverflow.com/questions/12252103/how-to-read-a-line-from-stdin-blocking-until-the-newline-is-found for information on how to do this function.
 * */

char *nextLine(){
    char *line = NULL;
    unsigned long x = 0;
    getline(&line, &x, stdin);
    return line;
}


/*This is to split my lines into words and put them into a pseudo-array.
 *
 * I make sure to read null as my last word so I know when to stop reading a line this function returns a pointer to a list of words
 *
 *
 * I used the websites https://stackoverflow.com/questions/2993075/allocating-and-de-allocating-memory-for-char64-in-c and http://c-faq.com/aryptr/dynmuldimary.html to figure out how to allocate my memory for my char **words.
 *
 *
 * I used https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm and https://en.cppreference.com/w/c/string/byte/strtok to get information about strtok() and " \t\n"
 * */

char **wordArray(char *line){
    char **words = (malloc(sizeof(char *) * 64));
    char *word = strtok(line, " \t\n");
    i = 0;
    words[i] = word;
    i++;
    while ((word != NULL)){
        word = strtok(NULL, " \t\n");
        words[i] = word;
        i++;
    }
    return words;
}


/*This is my execute function. first I check to see if there was an ampersand in my command, then
 * I create a child which will run a function. If the child is not running then there are two options:
 * 1.) if the command is running in the background (checked using amp), then I go ahead and read the next line and let the child run whenever it wants to.
 * 2.) if the command is not running in background, I need to wait till the child function terminates (by exit(0))
 * and then, only after that, will I read the next command.
 *
 *
 * I used the lab manual for information on execvp()
 * I used https://www.tutorialspoint.com/c_standard_library/c_function_perror.htm for information on perror.
 * I used the lab manual for lab2 for info on how to wait for a child process to finish
 * */

int exc(char **words, int amp) {
    int procid;
    int err;
    int save_status;
    int backEx = amp;
    procid = fork();
    if (procid == 0) {
        err = execvp(words[0], words);
        if (err == -1) {
            perror("ERROR");
        }
        exit(0);
    } else {
        if (backEx == 0) {
            while ((procid =wait(&save_status))  != -1 );
        }
    }
    return 1;
}

/*This is a quick function to check if the first word is "exit"
 * if it is, then I will terminate the shell (exit the whole program)
 * */

void exitCheck(char **words){
    if((strcmp(words[0], "exit")) == 0){
        exit(0);
    }
}

/*This checks if the command (which is the first word) ends with "&".
 * example -> "ls& -la
 * if it does then I return a 1 to amp to identify that this command will run in the background.
 *
 *
 * I used https://www.programiz.com/c-programming/c-pointer-functions for information on pointers and how to successfully pass and manipulate the data within the pointers inside of functions.
 * */

int checkAmp(char *** words){
    char * word;
    char first[strlen(*words[0]) - 1];
    strcpy(first, *words[0]);
    char check = first[strlen(first) - 1];
    if (check == '&'){
        word = strtok(*words[0], "&");
        *words[0] = word;
        return 1;
    } else{
        return 0;
    }
}