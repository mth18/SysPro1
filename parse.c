#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "parse.h"


int main()
{
	Param_t * param = createParam(); //Create new Parameter
	param = stringtokenizer(param); //get commands and tokenize

	deleteParam(param);
	return 0;
}

Param_t * createParam()
{
	Param_t * param = (Param_t *)malloc(sizeof(Param_t) +1); //Allocate enough space for new parameter (+1 byte for error reasons?)
	param = clearParam(param); //clear/reset parameter values
	return param; //return new cleared/allocated parameter
}

Param_t * clearParam(Param_t * param)
{
	param->inputRedirect = '\0'; //set filename '\0', don't use NULL because you will lose the only reference you had to memory and can't free it.
	param->outputRedirect = '\0'; //set filename to an empty string
	param->background = 0; //clear bg
	param->argumentCount = 0; //reset argc
	int i;
	//loop through all argv's
	for(i = 0; i < MAXARGS; i++)
	{
		param->argumentVector[i] = '\0'; //set all argv's in array to empty strings
	}
	return param;	//return cleared param
}

Param_t * deleteParam(Param_t * param)
{
	free(param);
	return param;
}


Param_t * stringtokenizer(Param_t * param)
{
	int streamch, buff = 8, currsize = 0;
	
	prompt(); //display prompt sequence
	currsize = buff;
	char *inputstr = (char*)malloc(sizeof(char)*currsize); //allocate enough initial space for the input char array
	if(inputstr!=NULL)//Test to see if the space was allocated
	{
		int i = 0;
		while((streamch=getchar())!='\n')
		{
			*(inputstr+i++)=(char)streamch; //convert streamch to char and save it in memory
			//reallocate more space until we're done scanning
			if(i==currsize)
			{
				currsize+=buff;
				inputstr = (char*)realloc(inputstr,sizeof(char)*currsize);
			}
		}
		inputstr[i] = '\0'; //add end of sequence character
	}
	printf("Testing input string: %s\n",inputstr); //check the input string
	param = stringbreaker(inputstr,param); //tokenize the input string
	return param;
}

//display prompt sequence
void prompt()
{
	printf("$$$ ");
}


Param_t * stringbreaker(char*str, Param_t *param)
{
	char *t; //create new temporary character array
	char *stringcount[MAXARGS]; //create array of character pointers
	int i=0;
	t=strtok(str," \n\t"); //tokenize first argument based on where " ", "\t", and "\n" are located
	printf("Temp String: %s\n",t); //print the temporary string

	//tokenize the rest of the string
	while(t != NULL)
	{
		printf("\nThe token is: %s", t);
		stringcount[i] = t; //add temp char to string array
		param->argumentCount++; //increment argc
		t = strtok(NULL," \n\t"); //tokenize
		i++;
	}
	
	
	parseParams(stringcount,param); //
	printParams(param); //print params, returns nothing
	//theshell(param) //fork to new process id, show child process and wait
	param = clearParam(param);
	return param;
}

void printParams(Param_t * param)
{
	int i;
	//not started
	printf ("InputRedirect: [%s]\n", (param->inputRedirect != NULL) ? param->inputRedirect:"NULL");
	//not started
	printf ("OutputRedirect: [%s]\n", (param->outputRedirect != NULL) ? param->outputRedirect:"NULL");
	//not started
	printf ("Background: [%d]\n", param->background);
	//finished
	printf ("ArgumentCount: [%d]\n", param->argumentCount);
	for (i = 0; i < param->argumentCount; i++)
		printf("ArgumentVector[%2d]: [%s]\n", i, param->argumentVector[i]);
}

Param_t *parseParams(char **strings, Param_t *param)
{
	char *t;
	int i;
	for(i = 0; i < param->argumentCount; i++)
	{
		t = strings[i];
		param = parseStrings(t, param); //parse each string command to see what it does
	}
	//param = setArgV(param);
	return param;
}

Param_t *parseStrings(char* str, Param_t *param)
{
	//test input redirect
	if(isInputRedirect(str))
	{
		if(param->inputRedirect != NULL)
			printf("input redirect is already filled");
		else
			param->inputRedirect = str;
	}
	//test output redirect
	else if(isOutputRedirect(str))
	{
		if(param->outputRedirect != NULL)
			printf("output redirect is already filled");
		else
			param->outputRedirect = str;
	}
	//test background
	else if(isBackground(str))
	{
		param->background = 1;
	}
	else
	{
		//add all other parameters to the argument vector
		//param->argumentvector[i]
	}
	return param;
}

//test to see if there is an input redirect
int isInputRedirect(char *t)
{
	if(t[0]=='>' && t[1] != '\0')
		return 1;
	else
		return 0;
}

//test to see if there is an output redirect
int isOutputRedirect(char *t)
{
	if(t[0]=='<' && t[1] != '\0')
		return 1;
	else
		return 0;
}

//test to see if there is a backgrounding
int isBackground(char *t)
{
	int i=0;
	while(t[i++]!='\0')
	{
		if(t[i] == '&')
			return 1;
		else
			return 0;
	}
}


