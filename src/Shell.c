#include "Shell.h"
#include "Fat.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void ls(char param[]){
    
}

void mkdir(char param[]){

}

void create(char param[]){
    
}

void unlink(char param[]){

}

void read(char param[]){

}

void write(char str[], char param[]){

}

void append(char str[], char param[]){

}


int main(){
    char cmd[6], str[100], param[100];

    printf("Shell\n");
    while(1){
        printf("/> ");
        scanf("%s", cmd);

        if(!strcmp(cmd, "init")){
            //init
            init();
        }else if(!strcmp(cmd, "load")){
            //load
            load();
        }else if(!strcmp(cmd, "exit")){
            //exit
            return 0;
        }else if(!strcmp(cmd, "ls")){
            scanf("%s", param);
            //ls
            ls(param);
        }else if(!strcmp(cmd, "mkdir")){
            scanf("%s", param);
            //mkdir
            mkdir(param);
        }else if(!strcmp(cmd, "create")){
            scanf("%s", param);
            //create
            create(param);
        }else if(!strcmp(cmd, "unlink")){
            scanf("%s", param);
            //unlink
            unlink(param);
        }else if(!strcmp(cmd, "read")){
            scanf("%s", param);
            //read
            read(param);
        }else if(!strcmp(cmd, "write")){
            scanf("%s", str);
            scanf("%s", param);
            //write
            write(str, param);
        }else if(!strcmp(cmd, "append")){
            scanf("%s", str);
            scanf("%s", param);
            //append
            append(str, param);
        }else{
            printf("msg: comando inválido\n");
        }

        //printf("%s %s %s", cmd, str, param);
    }

    return 0;
}