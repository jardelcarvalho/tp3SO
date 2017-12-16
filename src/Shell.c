#include "Shell.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void debug(){
    printf("Debug");
}

int main(){
    char cmd[6], str[100], param[100];

    printf("Shell\n");
    while(1){
        printf("/> ");
        scanf("%s", cmd);

        if(!strcmp(cmd, "init")){
            //init
        }else if(!strcmp(cmd, "load")){
            //load
        }else if(!strcmp(cmd, "exit")){
            //exit
            return 0;
        }else if(!strcmp(cmd, "ls")){
            scanf("%s", param);
            //ls
        }else if(!strcmp(cmd, "mkparam")){
            scanf("%s", param);
            //mkparam
        }else if(!strcmp(cmd, "create")){
            scanf("%s", param);
            //create
        }else if(!strcmp(cmd, "unlink")){
            scanf("%s", param);
            //unlink
        }else if(!strcmp(cmd, "read")){
            scanf("%s", param);
            //read
        }else if(!strcmp(cmd, "write")){
            scanf("%s", str);
            scanf("%s", param);
            //write
        }else if(!strcmp(cmd, "append")){
            scanf("%s", str);
            scanf("%s", param);
            //append
        }else{
            printf("msg: comando inválido\n");
        }

        printf("%s %s %s", cmd, str, param);

    }

    return 0;
}