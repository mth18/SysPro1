#include <stdio.h>

#ifndef PARSE_H_
#define PARSE_H_

/* donâ€™t test program with more than this many tokens for input */
#define MAXARGS 32
/* structure to hold input data */
struct PARAM
{
char *inputRedirect; /* file name or NULL */
char *outputRedirect; /* file name or NULL */
int background;/* either 0 (false) or 1 (true) */
int argumentCount;/* number of tokens in argument vector */
char *argumentVector[MAXARGS]; /* array of strings */
};
/* a typedef so we donâ€™t need to use "struct PARAM" all the time */
typedef struct PARAM Param_t;

void parsestr(char*);

Param_t * createParam();

Param_t * clearParam(Param_t * param);

Param_t * deleteParam(Param_t * param);

Param_t * stringtokenizer(Param_t * param);

void prompt();

Param_t * stringbreaker(char*str, Param_t * param);


void printParams(Param_t * param);

Param_t *parseParams(char **strings, Param_t *param);

Param_t *parseStrings(char* str, Param_t param);

#endif
