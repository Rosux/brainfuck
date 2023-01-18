#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){

    unsigned char* stack;
    unsigned int stackSize = 1;
    unsigned int loopDepth = 0;
    stack = calloc(stackSize, sizeof(unsigned char));
    unsigned char *ptr = stack;
    unsigned int offset;

    char *code;
    if(argc > 1){
        code = (char*)malloc(strlen(argv[1]) * sizeof(char));
        if(code == NULL){
            printf("Error: Couldn't allocate memory!");
            return 1;
        }
        strcpy(code, argv[1]);
    }else{
        code = (char*)malloc(164 * sizeof(char));
        if(code == NULL){
            printf("Error: Couldn't allocate memory!");
            return 1;
        }
        strcpy(code, ">++++++++[<+++++++++>-]<.>++++[<+++++++>-]<+.+++++++..+++.>>++++++[<+++++++>-]<++.------------.>++++++[<+++++++++>-]<+.<.+++.------.--------.>>>++++[<++++++++>-]<+.");
    }

    unsigned int codeLength = strlen(code);
    
    for(unsigned int i = 0; i < codeLength; i++){
        switch (code[i]){
            case '>':
                if(((++ptr) - stack) > stackSize){
                    offset = ptr - stack;
                    stack = realloc(stack, sizeof(unsigned char) * ++stackSize);
                    if(stack == NULL){
                        printf("Error: Couldn't allocate new stack memory!");
                        return 1;
                    }
                    ptr = stack + offset;
                }
                break;
            case '<': --ptr; break;
            case '+': ++*ptr; break;
            case '-': --*ptr; break;
            case '.': putchar(*ptr); break;
            case ',': *ptr = getchar(); break;
            case '[':
                if(!*ptr){
                    while(++i){
                        if(i > codeLength){
                            printf("Error: no coresponding closing ] found!");
                            return 1;
                        }
                        if(code[i] == ']' && !loopDepth){
                            break;
                        }else if(code[i] == ']'){
                            loopDepth--;
                        }else if(code[i] == '['){
                            loopDepth++;
                        }
                    }
                }
                break;
            case ']':
                if(*ptr){
                    while(--i){
                        if (code[i] == '[' && !loopDepth){
                            break;
                        }else if(code[i] == ']'){
                            loopDepth++;
                        }else if(code[i] == '['){
                            loopDepth--;
                        }
                        if(i == 0){
                            printf("Error: no coresponding opening [ found!");
                            return 1;
                        }
                        continue;
                    }
                }
                break;
            default:
                break;
        }
    }
    printf("\n\nPress any button to exit\n");
    getch();
    free(ptr);
    free(stack);
    return 0;
}