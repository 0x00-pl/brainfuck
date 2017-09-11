#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exit_error(const char *msg){
    printf("%s\n", msg);
    exit(-1);
}

size_t *preprocessing(char *prog){
    size_t prog_len;
    size_t *info;
    size_t *b_stack;
    size_t b_stack_top;
    size_t i,j;
    
    prog_len = strlen(prog);
    info = (size_t*)malloc(prog_len* sizeof(size_t));
    b_stack = (size_t*)malloc(prog_len* sizeof(size_t));
    b_stack_top = 0;
    if(info==NULL || b_stack==NULL){
        free(info);
        free(b_stack);
        exit_error("not enough memory, exit.");
    }
    for(i=0; i<prog_len;){
        switch(prog[i]){
            case '[':
                b_stack[b_stack_top] = i;
                b_stack_top++;
                i++;
                break;
            case ']':
                if(b_stack_top == 0){
                    exit_error("latex error, exit.");
                }
                b_stack_top--;
                info[i] = b_stack[b_stack_top];
                info[b_stack[b_stack_top]] = i;
                i++;
                break;
            case '+':
                for(j=0; prog[i+j]=='+'; j++){}
                info[i] = j;
                i += j;
                break;
            case '-':
                for(j=0; prog[i+j]=='-'; j++){}
                info[i] = j;
                i += j;
                break;
            case '<':
                for(j=0; prog[i+j]=='<'; j++){}
                info[i] = j;
                i += j;
                break;
            case '>':
                for(j=0; prog[i+j]=='>'; j++){}
                info[i] = j;
                i += j;
                break;
            case '.':
                i++;
                break;
            case ',':
                i++;
                break;
            default:
                free(info);
                free(b_stack);
                exit_error("unknow charcher, exit.\n");
                exit(-1);
        }
    }
    
    if(b_stack_top != 0){
        exit_error("latex error, exit.");
    }
    free(b_stack);
    return info;
}

void run_bf(size_t *info, char *prog){
    char cell[30000];
    size_t pprog;
    size_t pcell;
    int ch;
    
    bzero(cell, 30000);
    pprog = 0;
    pcell = 0;
    
    while(prog[pprog] != '\0'){
        switch(prog[pprog]){
            case ']':
                pprog = info[pprog];
            case '[':
                if(cell[pcell] == 0){
                    pprog = info[pprog];
                }
                pprog++;
                break;
            case '+':
                cell[pcell] = (char)((int)cell[pcell] + (int)info[pprog]);
                pprog += info[pprog];
                break;
            case '-':
                cell[pcell] = (char)((int)cell[pcell] - (int)info[pprog]);
                pprog += info[pprog];
                break;
            case '<':
                pcell = (pcell - info[pprog]) % 30000;
                pprog += info[pprog];
                break;
            case '>':
                pcell = (pcell + info[pprog]) % 30000;
                pprog += info[pprog];
                break;
            case ',':
                ch = getchar();
                if(ch == EOF){
                    exit_error("get EOF, exit.\n");
                }
                cell[pcell] = (char)ch;
                pprog++;
                break;
            case '.':
                putchar(cell[pcell]);
                pprog++;
                break;
            default:
                exit_error("unknow charcher, exit.\n");
                exit(-1);
        }
    }
}

int main(int argc, char **argv) {
    size_t *info;
    if(argc != 2){
        printf("useage: %s \"++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.\"\n", argv[0]);
        return 0;
    }
    info = preprocessing(argv[1]);
    run_bf(info, argv[1]);
    free(info);
    return 0;
}
