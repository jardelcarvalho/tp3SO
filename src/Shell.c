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
            if(strlen(param) > 0){
                //ls
            }else{
                printf("msg: parametros insuficientes para ls\n");
            }
        }else if(!strcmp(cmd, "mkparam")){
            scanf("%s", param);
            if(strlen(param) > 0){
                //mkparam
            }else{
                printf("msg: parametros insuficientes para mkparam\n");
            }
        }else if(!strcmp(cmd, "create")){
            scanf("%s", param);
            if(strlen(param) > 0){
                //create
            }else{
                printf("msg: parametros insuficientes para create\n");
            }
        }else if(!strcmp(cmd, "unlink")){
            scanf("%s", param);
            if(strlen(param) > 0){
                //unlink
            }else{
                printf("msg: parametros insuficientes para unlink\n");
            }
        }else if(!strcmp(cmd, "read")){
            scanf("%s", param);
            if(strlen(param) > 0){
                //read
            }else{
                printf("msg: parametros insuficientes para read\n");
            }
        }else if(!strcmp(cmd, "write")){
            scanf("%s", str);
            if(strlen(str) > 0){
                scanf("%s", param);
                if(strlen(param) > 0){
                    //write
                }else{
                    printf("mgs: parametros insuficientes para write\n");
                }
            }else{
                printf("mgs: parametros insuficientes para write\n");
            }
        }else if(!strcmp(cmd, "append")){
            scanf("%s", str);
            if(strlen(str) > 0){
                scanf("%s", param);
                if(strlen(param) > 0){
                    //write
                }else{
                    printf("mgs: parametros insuficientes para append\n");
                }
            }else{
                printf("mgs: parametros insuficientes para append\n");
            }
        }else{
            printf("msg: comando inválido\n");
        }

        printf("%s %s %s", cmd, str, param);

    }

    return 0;
}