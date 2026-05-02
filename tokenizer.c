#include<stdio.h>
#include<string.h>
#include<regex.h>
#include<ctype.h>

char *category[9] = {"a keyword","an identifier","a number","a string","an operator","a comment","punctuation","a whitespace","unknown"};
char *keywords[19] = {"int","int*","float","float*","double","double*","char","char*","do","while","for","ssize_t","size_t","bool","if","else","break","continue","return"};

int line_count;
char temp_token[1024];
char name[1024];
int init_count;

int wtf;
int chaos;

FILE *h;
FILE *f;

int is_number(char *token) {
	regex_t r;
	regcomp(&r,"^[0-9]+$",REG_EXTENDED);
	int a = regexec(&r,token,0,NULL,0);
	regfree(&r);

	return (a == 0);
}

int is_keyword(char *token) {
	for(int i=0;i<19;i++) {
		if(strcmp(token,keywords[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

int is_identifier(char *string) {
regex_t r;

regcomp(&r,"^[a-zA-Z_][a-zA-Z0-9_]*$",REG_EXTENDED);

int a = regexec(&r,string,0,NULL,0);

regfree(&r);

/*if (a == 0) {
    if (strcmp("init",string) == 0) {
    fprintf(h,"%d %s\n",init_count,temp_token);
    init_count += 1;
    }

}*/

return a == 0; 

}

char *operators = "+-*/=><!^%|&?";
char *operators2 = "><=|&";

int is_operator2(char s) {
	int yes = 0;
	for (int i=0;i<strlen(operators2);i++) {
		if(s == operators2[i]) {
			yes = -i-1;
		}
	}
	return yes;
}

int is_operator_single(char s) {
	int yes = 0;
	for (int i=0;i<strlen(operators);i++) {
		if(s == operators[i]) {
			yes = 1;
		}
	}
	return yes;
}

int is_operator(char *token) {
	int yes = 0;

	int len = strlen(token);
	
	if (len > 2) {
		return 0;
	}
	for (int i=0;i<strlen(operators);i++) {
		if(token[0] == operators[i]) {
			if(len == 2 && is_operator2(token[0]) < 0 && is_operator2(token[1]) < 0) {
				yes = 1;
				break;
			}
			else if (len == 2 && token[1] == '=') {
				yes = 1;
				break;
			}
			else if (len == 1) {
				yes = 1;
				break;
			}
		}
	}
	return yes;
}

long depth;
int init_at_depth;

void nested (unsigned char c) {

    depth += ((c == '(') ? 1:-1);

}

int what_is(char *token) {
	//fprintf(f,"i received %s\n",token);
	if (is_keyword(token)) {
		//fprintf(f,"keyword %s\n",token);
		return 0;
	}
	else if (is_number(token)) {
		return 2;
	}
	else if (is_identifier(token)) {
		//fprintf(f,"identifier %s\n",token);

        if (strcmp(token,"init") == 0) {
            if (chaos == 9) { 
                //printf("bonjour, je suis chaos et je est 9\n");
                strcpy(name,temp_token);
                fprintf(stdout,"found init, and the variable name was %s\n",name);
            }
            //fprintf(f,"chaos est %d\n",chaos);
            //fprintf(stdout,"found init, and the variable name was %s\n",name);
            //fprintf(h,"%d %s\n",init_count,temp_token);
            if (chaos != 9) {
                strcpy(name,"init was called without any ptr name");
                fprintf(stdout,"found init, and the variable name wasnt declared\n");
            }
            init_count += 1;
            chaos = 8;
            init_at_depth = depth;
        }

        strcpy(temp_token,token);
		return 1;
	} 
	else if (is_operator(token)) {
		//fprintf(f,"operator %s\n",token);
		return 4;
	}
	else return 8;
}

int main(int argc,char *argv[]) {
	FILE *g = fopen(argv[1],"r");
    f = fopen("tok.txt","w");
    h = fopen("input.txt","w");
    FILE *temp = fopen("stuff.c","r+");
    init_count = 0;
    line_count = 1;
    init_at_depth = 0;

	int c;
	char token[1024];
	int i = 0;
	wtf = 0;
    chaos = 0;
    depth = 0;

	/*
	wtf = 0 when nothing special is going on
    wtf = 1 when searching for double operators
	wtf = 2 when traversing through a string
	wtf = 3 when u have found a '/' and are ensuring that the next is a '/' or '*'
	wtf = 4 when traversing through an identifier or keyword
	wtf = 5 when traversing through a block comment
	wtf = 6 when traversing through a line comment
	wtf = 7 when u have encountered a single quote and maybe there is a double quote inside it and it might ruin the whole tokenizing process which u obviously don't want, do you?
    */

    /*
    chaos = 0 when no chaos, duh
    chaos = 8 when u have encounetered init
    chaos = 9 when u have encounetered '=' and u dont know whether the next thing is gonna be init or something... like when u encounter init, and chaos isnt 9, then it was not declared
    chaos = 10 when chaos was 8 and '(' was found, so now searching for ')' with same depth
    */

	while ((c = fgetc(g)) != EOF) {
        //fprintf(f,"bonjour, l'depth est %ld\n",depth);
        //fprintf(f,"%d:  ",line_count);
        //printf("bonjour, chaos est %d\n",chaos);
        fputc(c,temp);
        //printf("bonjour! wtf = %d and c is %c and i is %d\n",wtf,c,i);
		if((isalnum(c) || (unsigned char)c == '_') && wtf != 2 && wtf !=3 && wtf != 5 && wtf != 6 && wtf != 7) {
			if (wtf == 1) {
				if (is_operator_single(token[i - 1])) {
					token[1] = '\0';
					fprintf(f,"%s is an operator\n",token);
					i = 0;
					wtf = 0;
				}
			}
			token[i] = (unsigned char)c;
			i += 1;
			wtf = 4;
		}
        
        if ((c == 39 || wtf == 7) && wtf != 2 && wtf != 3 && wtf != 5 && wtf != 6) {
            //fprintf(f,"bonjour, wtf est %d et c est %c (%d)\n",wtf,(unsigned char)c,c);
            if (i >= 1 && wtf != 7) {
                token[i] = '\0';
                //fprintf(f,"bonjour, je m'appele %c et je suis %s\n",(unsigned char)c,category[what_is((char[]){(unsigned char)c})]);
                fprintf(f,"%s is %s\n",token,category[what_is(token)]);
                i = 0;
                wtf = 0;
            }

            if (c == 39 && wtf != 7) {
                wtf = 7;
                continue;
            }
            if (wtf == 7 && c != 39) {
               token[i] = (unsigned char)c;
               i += 1;
               
               continue;
            }
            
            if (wtf == 7 && c == 39) {
                token[i] = '\0';
                i = 0;

                fprintf(f,"%s is under single quotes\n",token);
                wtf = 0;
                continue;
            }

        }

		if (((unsigned char)c == '"' || wtf == 2) && wtf != 3 && wtf != 5 && wtf != 6 && wtf != 7) {
            
			
			if (i == 1 && wtf != 2) {
				if (is_operator_single(token[i - 1])) {
					token[1] = '\0';
					fprintf(f,"%s is an operator\n",token);
					i = 0;

				}
			}
			else if (wtf == 2 && (unsigned char)c != '"') {
				token[i] = (unsigned char)c;
				i += 1;
			}
			else if ((unsigned char)c == '"' && wtf == 2) {
				token[i] = '\0';
				fprintf(f,"'%s' is a string\n",token);
				i = 0;
				wtf = 0;
				continue;
			}
			wtf = 2;
		}

		if (((unsigned char)c == '/' || wtf == 3 || wtf == 5 || wtf == 6) && wtf != 2 && wtf != 7) {
			//fprintf(f,"bonjour! wtf = %d i = %d\n",wtf,i);
			
			if (i >= 1 && wtf != 3 && wtf != 5 && wtf != 6) {
				token[i] = '\0';
				//fprintf(f,"bonjour token so far is %s and i is %d and wtf is %d\n",token,i,wtf);
				fprintf(f,"%s is %s\n",token,category[what_is(token)]);
				i = 0;
				wtf = 0;
			}
			if ((unsigned char)c == '/' && wtf == 3 && i == 0) {
				wtf = 6;
				//fprintf(f,"oui\n");
				continue;
			}

			if ((unsigned char)c == '/' && i == 0) {
				wtf = 3;
				//fprintf(f,"bonjour wtf = %d char is %c\n",wtf,(unsigned char)c);
				continue;
			}
			//fprintf(f,"oui\n");
			if (i == 0 && wtf == 3 && (unsigned char)c != '/' && (unsigned char)c != '*') {
				//fprintf(f,"bonjour wtf = %d char is %c\n",wtf,(unsigned char)c);
				if ((unsigned char)c == '=') {
					fprintf(f,"/= is an operator\n");
					wtf = 0;
				}
				else if (isspace(c)) {
					fprintf(f,"/ is an operator\n");
					fprintf(f,"%s is a whitespace\n",((c == 32) ? "\" \"":((c == 10) ? "\\n":((c == 9) ? "\\t":"\\v"))));
					wtf = 0;
				}
				else if (isalnum(c)) {
					fprintf(f,"/ is an operator\n");
					token[i] = (unsigned char)c;
					i += 1;
					wtf = 4;
				}
				continue;
			}	
					
			else if ((unsigned char)c == '*' && i == 0 && wtf == 3) {
				wtf = 5;
				continue;
			}
			else if (wtf == 5 && (unsigned char)c != '*') {
				token[i] = (unsigned char)c;
				i += 1;
			}
			else if ((unsigned char)c == '*' && wtf == 5) {
				wtf = 3;
				continue;
			}
			if ((unsigned char)c != '/' && wtf == 3 && i != 0) {
				token[i] = '*';
				i += 1;
				token[i] = (unsigned char)c;
				i += 1;
				wtf = 5;
				continue;				
			}
			else if ((unsigned char)c == '/' && wtf == 3 && i != 0){
				token[i] = '\0';
				fprintf(f,"'%s' is one type of comment\n",token);
				i = 0;
				wtf = 0;
				continue;
			}
			if (wtf == 6 && c != 10) {
				token[i] = (unsigned char)c;
				i += 1;
			}
			if (wtf == 6 && c == 10) {
				token[i] = '\0';
				fprintf(f,"'%s' is another type of comment\n",token);
				i = 0;
				wtf = 0;
			}
		}

		if (ispunct(c) && is_operator_single((unsigned char)c) == 0 && wtf != 2 && wtf != 3 && wtf != 5 && wtf != 6 && wtf != 7) {
            //fprintf(f,"bonjour, je suis %c\n",(unsigned char)c);
            if (i > 0 && (unsigned char)c != '_') {
				token[i] = '\0';
				fprintf(f,"%s is %s\n",token,category[what_is(token)]);
				i = 0;
			}
            
			if (i > 0 && ((unsigned char)c == '_' && wtf == 4)) {
                /*token[i] = '_';
                i += 1;*/
                continue;
            }
            
            if (i == 0 && ((unsigned char)c == ')' || (unsigned char)c == '(')) {
                nested((unsigned char)c);
            }

            if (i == 0)
                fprintf(f,"%c is punctuation\n",(unsigned char)c);

            if ((unsigned char)c == ';' && chaos == 9) {
                chaos = 0;
            }

            if ((unsigned char)c == ',' && chaos == 9 && depth == init_at_depth) {
                chaos = 0;
            }

            /*if (((unsigned char)c == ';' && chaos == 8) || (chaos == 8 && (unsigned char)c == ',' && init_at_depth == depth)) {
                //printf("at the end\n"); 
                fseek(temp,-2,SEEK_CUR);
                char d = (unsigned char)fgetc(temp);;
                
                while (d != ')') {
                    fseek(temp,-2,SEEK_CUR);
                    d = (unsigned char)fgetc(temp);
                }

                fseek(temp,-1,SEEK_CUR);
                fprintf(temp,",\"%s\")%c",name,(unsigned char)c);
                chaos = 0;
                continue;
            }*/

            if ((unsigned char)c == '(' && chaos == 8) {
                chaos = 10;
            }

            if ((unsigned char)c == ')' && chaos == 10 && depth == init_at_depth) {
		        fseek(temp,-1,SEEK_CUR);
                fprintf(temp,",\"%s\")",name);
                chaos = 0;
                continue; 
            }
        }
		
		if (isspace(c) && wtf != 2 && wtf != 3 && wtf != 5 && wtf != 6 && wtf != 7){
			//fprintf(f,"%s%c",token,(c == '\n') ? 10:32);
			if (i > 0) {
				token[i] = '\0';
				//fprintf(f,"i received %s\n",token);

				fprintf(f,"%s is %s\n",token,category[what_is(token)]);
			}
			i = 0;
			wtf = 0;
            line_count += ((c == 10) ? 1:0);
            
			fprintf(f,"%s is a whitespace\n",((c == 32) ? "\" \"":((c == 10) ? "\\n":((c == 9) ? "\\t":"\\v"))));
            
		}

		if (is_operator_single((unsigned char)c) && wtf != 2 && wtf != 3 && wtf != 5 && wtf != 6 && wtf != 7) {
			//fprintf(f,"i received %c\n",(unsigned char)c);
            if ((unsigned char)c == '=') {
                chaos = 9;
            }

			if (i == 1 && is_operator_single(token[i - 1])) {
				token[1] = (unsigned char)c;
				i += 1;
				token[i] = '\0';
				fprintf(f,"%s is an operator\n",token);
				i = 0;
				wtf = 0;
			}
			else if (i == 0) {
				token[i] = (unsigned char)c;
				i += 1;	
				wtf = 1;
			}
			else if (i >= 1) {
				token[i] = '\0';
                i = 0;
				fprintf(f,"%s is %s\n",token,category[what_is(token)]);
				token[i] = (unsigned char)c;
				i += 1;
				wtf = 1;	
			}
		}
	}
    //fprintf(f,"%s\n",temp_token);
	fclose(f);
    fclose(g);
    fclose(h);

	//SO HAPPY!!!!!
}
