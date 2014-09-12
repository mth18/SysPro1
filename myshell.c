#include "Parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include "myshell.h"

int main()
{
    forkingtest();
    return 0;
}

void forkingtest()
{
     pid_t p; //predefined system type int
     int status; //use for wait pid
     p = fork();
     printf("%i child process number\n",p);
     if(p>0)
     {
            printf("Parent Process\n");
     }
     else
     {
         printf("Child Process\n");
     }
}
