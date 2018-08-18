

%{ 
#include<stdio.h>
#define MAX 100
char* tokens[MAX];
char *temp;
int p=0;
%}

digit [0-9]
digits {digit}*
letter [A-Za-z]
id ({letter}|{digits})({letter}|{digit})*
Op [+|*|(|)]
End [$]

%%
{End} { tokens[p] = malloc(sizeof(char)*10); tokens[p] = "$"; p++;yyterminate();}
[[:space:]]|[[:space:]]+
{Op} {tokens[p] = malloc(sizeof(char)*10); temp = strdup(yytext); tokens[p] = temp; p++; }
{id} {tokens[p] = malloc(sizeof(char)*10); tokens[p] = "ID"; p++; } 
%%

int main(void)
{
  yylex();
  int i;
  FILE *fp = fopen("input.txt","wb");
  if(fp == NULL){
    perror("File can't be opened\n");
    exit(EXIT_FAILURE);
    }
   
  for(i=0; i<p; i++){
    fprintf(fp, "%s", tokens[i]);
    fprintf(fp, "%s"," ");
    }
    
  
 fclose(fp);
  return 0;  
} 


