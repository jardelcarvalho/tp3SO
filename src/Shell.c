#include "Shell.h"
#include "Fat.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void ls(char param[]){
    
    //caminhar na arvore de diretorios até achar o diretorio     
    int posicao = -1;
    for(int i=0;i<ENTRY_BY_CLUSTER;i++){
        if(strcomp(root_dir[i].filename,param)){
            posicao = i;
        }
    }
    if(posicao > -1){
        //listar o diretorio aqui
    }

}

void mkdir(char param[]){
    //preciso escrever um novo diretorio


    //encontrar posicao livre
    int posicao = -1;    
    for(int i=0;i<ENTRY_BY_CLUSTER;i++){
        if(&root_dir[i] != 0x00){
            posicao = i;
        }
    }

    if(posicao > -1){
        &root_dir[posicao] = malloc(sizeof(dir_entry_t));
        root_dir[posicao].filename = param;
        root_dir[posicao].first_block = last_pos_root;
        //size in bytes
        root_dir[posicao].size = 2;
        root_dir[posicao].attributes = 1; //1 para diretorio e 0 para arquivo        
    }
    //preciso persistir isso no disco
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