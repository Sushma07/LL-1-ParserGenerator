#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
# define MAX 100

char *startSymbol;
bool EOP;
char *parseTable[MAX][MAX];
char *terminals[MAX];
char *nonTerminals[MAX];
int p =0, nt=0, t = 0, st =1;
bool epsilon = false;
char *stack[MAX];

struct prodRule{
char* ruleStart;
char* theRule;
char** thecharRule;
};

int length(char *pointer)
{
   int c = 0;
 
   while( *(pointer + c) != '\0' )
      c++;
 
   return c;
}

struct prodRule* productionRules[MAX];

void reverse(char *s) 
{
   int len, c;
   char *begin, *end, temp;
 
   len = length(s);
   begin  = s;
   end    = s;
 
   for (c = 0; c < len - 1; c++)
      end++;
 
   for (c = 0; c < len/2; c++)
   {        
      temp   = *end;
      *end   = *begin;
      *begin = temp;
 
      begin++;
      end--;
   }
}

 

char* stackPop(){
 char* tep = stack[st-1];
 stack[st-1]='\0';
 st--;
 return tep;
}
char* stackTop(){
return stack[st-1];
}




char *removeSpaces(char *str){
int count = 0;
 for (int i = 0; str[i]; i++)
   if (str[i] != ' ')
     str[count++] = str[i]; 
   str[count] = '\0';
 return str;
}

char *removeNewLine(char *str){
int count = 0;
 for (int i = 0; str[i]; i++)
   if (str[i] != '\n'  && str[i]!='\t')
     str[count++] = str[i]; 
   str[count] = '\0';
 return str;
}


char* getProductionRule(char* s, int idx, char *val){
 int i=0;
 struct prodRule *curr= malloc(sizeof(struct prodRule));
 for(int i=0; i<idx; i++){
  *curr = *productionRules[i];
   if(strcmp (curr->ruleStart,s)==0 && strcmp(curr->theRule,val)==0 )
    return curr->theRule;
       
   }
 //printf("test |%s|\n",input[in-1]);  printf("not found |%s|\n",val);
  for(int i=0; i<idx; i++){
  *curr = *productionRules[i];
    if(strcmp (curr->ruleStart,s)==0)
   return curr->theRule;
   }
  return '\0';
 }

void setTerAndNonTerminals(char* arr[MAX], bool flags[MAX], int idx){
int i;
//printf("setting values %d %s\n",idx, arr[idx]);
 for(int i=0; i< idx; i++){
    if(flags[i]){
	t++;
	terminals[t] = malloc(sizeof(char) * 10);
	terminals[t] = arr[i];
    }  
    else{
	 nt++;
	 nonTerminals[nt] = malloc(sizeof(char) * 10);
	 nonTerminals[nt] = arr[i];
    }
 }
} 

int getTerminalIndex(char* a){
  int i;
  for(i=1; i<= t; i++){
 //  printf("test :|%s| \t |%s| \n",terminals[i], a);
     if(strcmp(terminals[i], a) == 0)
      return i;
  }
 return -1;   
}

int getNonTerminalIndex(char* a){
  int i;
  for(i=1; i<= nt; i++){
      if(strcmp(nonTerminals[i], a) == 0)
      return i;
  }
 return -1;   
}
 
void setParseTable (char* value, int i, int j){

 parseTable[i][j] = malloc(sizeof(char) * 10 * 10);
 parseTable[i][j] = value;

} 

void printParseTable(){
 int i,j;
 for(i=1; i<= nt; i++){
  for(j=1; j<= t; j++){
   printf("[%s:%s] %s\t", nonTerminals[i],terminals[j],parseTable[i][j]);
  }
  printf("\n");
 }
}




int contains(char *arr[MAX], char* S, int idx){
 for(int i=0; i< idx; i++){
  if(strcmp(arr[i],S)==0)
  return i;
 }
 return -1;
}

void printEntries( char *arr[MAX],bool flag[MAX], int idx){
 int i;
 for(i=0; i<idx; i++){
 printf("entry : %s isTerminal : %d \n",arr[i],flag[i]);
 }
}

// inclusive start, exclusive end
char *subSt(char *string, int position, int end) 
{
int length = end - position;
   char *pointer;
   int c;
   pointer = malloc(length+1);
   if (pointer == NULL){
       printf("Unable to allocate memory.\n");
      exit(1);
   }
   for (c = 0 ; c < length ; c++){
      *(pointer+c) = *(string+position);      
      string++;   
   }
 
   *(pointer+c) = '\0';
 
   return pointer;
}

int idOf(char* st, int from, int till, char s){
  for(int i= from; i<till; i++){
    if(st[i] ==  s){
    return i;
    }
  }
  if(!EOP){
     EOP = true;
     return till;
  }
 return -1;
}

void setProdRule(char* s, char* prod, int idx){ 
char temp[10];// = malloc(sizeof(char)*10);
struct prodRule* pr = malloc(sizeof(struct prodRule));
		pr->ruleStart = s;
		pr->theRule = prod;
		//pr->thecharRule = chaR;
		productionRules[idx] = pr;
 //printf("osjdfn %s\n",pr->charRule[idx]);
}

char* tempPop(char* stck[MAX], int idx){
char* tep = stck[idx-1];
//printf("in tempPop %s\n",tep);
 stck[idx-1]='\0';
 return tep;

}

void stackPush(char *seq){
char *tempStack[MAX];
int len = length(seq);
int count = 0;
int start = 0;
char* temp;
bool End;
int space = 0;
while(space!=-1){
space = idOf(seq,start,len,' ');
//printf("start :%d\t space:%d\t |%s|",start,space, seq);
tempStack[count] = malloc(sizeof(char));
if(space!=-1){
temp = subSt(seq,start,space);
temp = removeNewLine(temp);
temp = removeSpaces(temp);
//printf("in push |%s|\n",temp);
if(strcmp(temp,"NULL")!=0){
tempStack[count] = temp;
count++;
}
start = space+1;


}
}

if(space == -1){
space = len;
tempStack[count] = malloc(sizeof(char));
temp = subSt(seq,start,space);
temp = removeNewLine(temp);
temp = removeSpaces(temp);
if(strcmp(temp,"NULL")!=0){
tempStack[count] = temp;
count++;
}
start = space+1;

}


while(count > 0){
stack[st] = malloc(sizeof(char));
stack[st] = tempPop(tempStack, count);
//printf("in rev push : |%s|\n",stack[st]);
st++;
count--;
}
/* for(i=0; i<10; i++){
 stack[st+i-1] = malloc(sizeof(char)*10);
 stack[st+i-1] = seq[i];
 }*/
} 

int main(void){
    FILE * fp;
    char *val;
    char ch;
    char *line ;
    size_t len = 0;
    ssize_t read;
    int arrow, start = 0, rule = 0, cr=0;
    int i=0, p=0;
    char *entries[MAX];
    bool isTerminal[MAX];
    char *currRule;
   // char * charRule;
    fp = fopen("grammar.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
 	 while ((read = getline(&line, &len, fp)) != -1) {
 	   memset(currRule,cr,0);
                cr =0 ;
	 	EOP = false;
	 	start = 0;
		arrow = idOf(line,start,read,'>');
		val = subSt(line, 0, arrow);
		val = removeNewLine(val);
		char* nt = strdup(val);
		currRule = subSt(line,arrow+1,read);
	        currRule = removeNewLine(currRule);
	     //   printf("currRule: |%s|\n",currRule);
		int pos = contains(entries,val,p);
		if(pos == -1 && strcmp(val,"\0")!=0){
			entries[p] = malloc(sizeof(char) * 10); 
			entries[p] = val;
			isTerminal[p] = false;
			p++;
		}
		else isTerminal[pos] = false;
		if(p == 1){
		startSymbol = malloc(sizeof(char)* 10);
		startSymbol = entries[p-1];
		//printf("startc:%s\n", startSymbol);
		}
		setProdRule(val,currRule, rule);
		rule++;
 	      while(arrow!=-1 && !EOP && strcmp(val,"\0")!=0){
			start = arrow+1;
			arrow = idOf(line, start, read,' ');
			val = subSt(line, start, arrow);
			val = removeNewLine(val);
			if(contains(entries,val,p) == -1 && strcmp(val,"\0")!=0){
				entries[p] = malloc(sizeof(char) * 10); 
				entries[p] = val;
				isTerminal[p] = true;
				p++;
			}
			
		  }
	        
			
	   } 
	   
   //printEntries(entries, isTerminal, p); 
    setTerAndNonTerminals(entries, isTerminal,p);
   
   /* for(i=0; i<rule; i++){
    struct prodRule* currRule = productionRules[i];
    printf("start: %s\t\trule:%s\n",currRule->ruleStart,currRule->theRule);
    }
  */
    fclose(fp);
    fp = fopen("first_follow.txt", "r");
    if (fp == NULL){
      perror("Unable to open first_follow.txt");
      exit(EXIT_FAILURE);
    }
   char* prod;
    
    while ((read = getline(&line, &len, fp)) != -1) {
                epsilon = false;
	 	start = 0;
		arrow = idOf(line,start,read,'{');
		val = subSt(line, 0, arrow);
		val = removeNewLine(val);
		val = removeSpaces(val);
		char* nonTer = strdup(val);
		int ntidx = getNonTerminalIndex(nonTer);
			
		arrow++;
		while( arrow !=-1 && strcmp(val,"\0")!=0  ){
		        start = arrow+1;
			arrow = idOf(line, start, read,' ');
			val = subSt(line, start, arrow);
			if(strcmp(val,"}")==0)
			  break;
			val = removeNewLine(val);
			val = removeSpaces(val);
			if(strcmp(val,"NULL") == 0)
			 epsilon = true;
			if(strcmp(val,"\0")!=0 ){
			prod = getProductionRule(nonTer,rule,val);
			int tidx = getTerminalIndex(val);
			setParseTable(prod,ntidx,tidx);
			
			}
	       }
	       if(epsilon){
	       arrow = idOf(line, start, read,'{');
	       arrow++;
	      while( arrow !=-1 && strcmp(val,"\0")!=0 ){
	       start = arrow+1;
	       arrow = idOf(line, start, read,' ');
	      	 if(arrow > 0){
	       	 val = subSt(line, start, arrow);
			if(strcmp(val,"}")==0)
			  break;
			val = removeNewLine(val);
			val = removeSpaces(val);
			if(strcmp(val,"\0")!=0 ){
			char* prod = getProductionRule(nonTer,rule,"NULL");
			int tidx = getTerminalIndex(val);
			setParseTable(prod,ntidx,tidx);
			
			}
		
            	 } 
             }
           }  
    }
    printf("--------------------------PARSE TABLE------------------------------\n");
    printParseTable();
    printf("\n");

   fclose(fp);
   if(line)
     free(line);
     
     /*------------------------------------module2-------------------------------------*/
     char *input[MAX];
     int in  =0;
     int inPtr=0 , stPtr=1;
     char *theProd;
     start = 0;
     stack[0] = malloc(sizeof(char) * 10);
     stack[0] = "$";
     
     stack[st] = malloc(sizeof(char) * 10);
     stack[st] = startSymbol;
     st++;
     fp = fopen("input.txt","r");
     if(fp == NULL){
      perror("Unable to open file");
      exit(EXIT_FAILURE);
      }
       // CHANGE THE INPUT TO STRING ARRAY    
       if((read = getline(&line, &len, fp)) != -1) {
       start = 0;
       arrow = 0;
       while(arrow!=-1 ){
     //  printf("check |%s| |%s| |%s|\n",line+0,line+1, line+2);
       arrow = idOf(line,start,read,' ');
      //printf("line : %s\nstart %d\t arrow %d\n",line,start, arrow);
		if(arrow!=-1){
		val = subSt(line, start, arrow);
		val = removeNewLine(val);
		val = removeSpaces(val);
		char* temp = strdup(val);
		if(strcmp(val,"\0")!=0){
		input[in] = malloc(sizeof(char) * 10);
		input[in] = temp;
		in++;
		 }
	start = arrow+1;
	}
       }
       input[in] = "$";
       in++;
       }
      // printf("here %d\n", strcmp(input[inPtr],"$")!= 0);
      /*for(i=0; i<=t; i++){
      printf("terminal :%s\n",terminals[i]);
      }*/
      while(strcmp(stackTop(),"$")!= 0){
       // printf("in \n");
       printf("stackTop : %s\t input : %s\t\t\t\t",stackTop(),input[inPtr]);
      
       if(strcmp(input[inPtr],stackTop()) ==0){
       printf("match %s\n",input[inPtr]);
         stackPop();
       inPtr++;
       }
       
       else if( getNonTerminalIndex(input[inPtr]) !=-1){
       printf("The input String is not Acceptable\n");
       exit(0);
       }
       
       else if  (parseTable[getNonTerminalIndex(stackTop())][getTerminalIndex(input[inPtr])] == NULL){
       if(strcmp(input[inPtr],"$")==0){
       theProd = parseTable[getNonTerminalIndex(stackTop())][getTerminalIndex("NULL")];
       printf("production %s->%s\n",stackTop(),theProd);
       }
      
       stackPop();
       if(st==0)
       break;
       }
       
       else{
       
       theProd = parseTable[getNonTerminalIndex(stackTop())][getTerminalIndex(input[inPtr])];
       printf("production %s->%s\n",stackTop(),theProd);
       stackPop();
       stackPush(theProd);
       }
        
      }
      
    //  printf("checkk %s\n",input[inPtr]);
      if((strcmp(input[inPtr],"$")==0) && st == 1)
      printf("Accepted\n");
      
      else
      printf("Rejected \n");
      
     
     fclose(fp);
     
   exit(EXIT_SUCCESS);
  
 
}



