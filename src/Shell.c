#include "Shell.h"
#include "Fat.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>



void mkdir(char param[]){
    if(param[0] != '/'){
        printf("\n\nO diretorio deve começar com /\n\n");
        return;
    }
    int posFinal = -1;
    for(int i=0;i<99;i++){
        if(param[i+1] == '/'){
            posFinal = i+1;
            break;
        }
    }
    if(posFinal == -1){
        printf("\n\nO diretorio deve terminar com / \n\n");
        return;
    }
    //FUNCAO QUE IRA CRIAR UM NOVO DIRETORIO

    //colocar entrada do diretorio em um espaço livre do root dir
    int posicao = -1;
    for (int i = 0; i < ENTRY_BY_CLUSTER; i++)
    {
        if (root_dir[i].size == 0)
        {
            //encontramos um posicao vazia no root dir
            posicao = i;
            break;
        }
    }
    //se achei a posicao vazia
    if (posicao > -1)
    {

        //encontrar posicao livre na fat de 2 bytes para ser o primeiro bloco do diretorio
        int posFat = 0;
        for (int i = 0; i < NUM_CLUSTER; i++)
        {
            if (fat[i] == 0)
            {
                //esta vazia
                posFat = i;
                fat[i] = 1;
                break;
            }
        }
        //coloca diretorio no cluster
        memcpy(clusters[posFat].dir[0].filename, param, sizeof(char) * 18);
        clusters[posFat].dir[0].attributes = 1;
        clusters[posFat].dir[0].reserved[0] = '1';
        clusters[posFat].dir[0].attributes = 1;
        clusters[posFat].dir[0].size = 2;

        //escrever no root dir
        memcpy(root_dir[posicao].filename, param, sizeof(char) * 18);
        root_dir[posicao].first_block = posFat;
        root_dir[posicao].reserved[0] = '0';
        root_dir[posicao].attributes = 1; //1 para diretorio e 0 para arquivo
        root_dir[posicao].size = 2;

        //chama função de pesistencia
        persisteDados();
    }
}

void create(char param[])
{
    //normaliza a criação dos arquivos
    if(param[0] != '/'){
        printf("\n\nO caminho do arquivo deve começar com /\n\n");
        return;
    }
    //FUNCAO QUE IRA CRIAR UM NOVO ARQUIVO

    //colocar entrada do arquivo em um espaço livre do root dir
    int posicao = -1;
    for (int i = 0; i < ENTRY_BY_CLUSTER; i++)
    {
        if (root_dir[i].size == 0)
        {
            //encontramos um posicao vazia no root dir
            posicao = i;
            break;
        }
    }
    //se achei a posicao vazia
    if (posicao > -1)
    {

        //encontrar posicao livre na fat de 2 bytes para ser o primeiro bloco do diretorio
        int posFat = 0;
        for (int i = 0; i < NUM_CLUSTER; i++)
        {
            if (fat[i] == 0)
            {
                //esta vazia
                posFat = i;
                fat[i] = 1;
                break;
            }
        }
        //coloca o arquivo no cluster
        memcpy(clusters[posFat].dir[0].filename, param, sizeof(char) * 18);
        clusters[posFat].dir[0].attributes = 1;
        clusters[posFat].dir[0].reserved[0] = '1';
        clusters[posFat].dir[0].attributes = 0; //0 para arquivo
        clusters[posFat].dir[0].size = 2;
        memset(clusters[posFat].data,'\0',1000);
        
        //escrever no root dir
        memcpy(root_dir[posicao].filename, param, sizeof(char) * 18);
        root_dir[posicao].first_block = posFat;
        root_dir[posicao].reserved[0] = '0';
        root_dir[posicao].attributes = 0; //1 para diretorio e 0 para arquivo
        root_dir[posicao].size = 2;

        persisteDados();
    }
}

void unlink(char param[])
{
    
    //deleta tudo que contenha o inicio da string especificada
    //na verdade só ocorre um desreferenciamento, mas os dados continuam
    for(int i=0;i<4086;i++){
        int exibe = 1;
        int tamanho_digitado = 0;
        for(int j=0;j<100;j++){            
            if(param[j] == '\0' || param[j] == '\n'){
                break;
            }            
            tamanho_digitado++;                        
        }

        char stringDigitada[tamanho_digitado];
        memcpy(stringDigitada,param,sizeof(char)*tamanho_digitado);
        char stringNome[tamanho_digitado];
        memcpy(stringNome,clusters[i].dir[0].filename,sizeof(char)*tamanho_digitado);        
        if (!strcmp(stringDigitada, stringNome)){                        	        
            memset(clusters[i].dir[0].filename,'\0',17);
            clusters[i].dir[0].size = 0;
         }
         //persisteDados();
    }
    
    


}

void read(char param[])
{
    //procura o arquivo
    int posicao = -1;
    for(int i=0; i<4086;i++){
        if(clusters[i].dir[0].attributes == 0 && !strcmp(param,clusters[i].dir[0].filename)){
            posicao = i;
            break;
        }
    }
    //se nao encontrou mostra erro
    if(posicao == -1){
        printf("\n\nO arquivo especificado nao foi encontrado\n\n");
        return;
    }
    //printa dados contidos no cluster
    printf("%s\n",clusters[posicao].data);
}

void write(char str[], char param[])
{
    //verificar se o arquivo existe
    int posicao = -1;
    for(int i=0; i<4086;i++){
        if(clusters[i].dir[0].attributes == 0 && !strcmp(param,clusters[i].dir[0].filename)){
            posicao = i;
            break;
        }
    }
    if(posicao == -1){
        printf("\n\nO arquivo especificado nao foi encontrado\nUtilize create para cria-lo.\n\n");
        return;
    }    
    //copia string digitada para o cluster
    memcpy(clusters[posicao].data,str,strlen(str));
    //persisteDados();    
}

void append(char str[], char param[])
{
 //verificar se o arquivo existe
    int posicao = -1;
    for(int i=0; i<4086;i++){
        if(clusters[i].dir[0].attributes == 0 && !strcmp(param,clusters[i].dir[0].filename)){
            posicao = i;
            break;
        }
    }
    if(posicao == -1){
        printf("\n\nO arquivo especificado nao foi encontrado\nUtilize create para cria-lo.\n\n");
        return;
    }    
    int pos=0;
    for(int i=0;i<1000;i++){
        pos++;
        if(clusters[posicao].data[i] == '\0'){
            break;            
        }        
    }
    //cola a str no \0 dos dados do arquivo e ai fica no final
    memcpy(&clusters[posicao].data[pos-1],str,strlen(str));
    //persisteDados();    

}

void ls(char param[]){
    //normaliza a entrada
    if(param[0] != '/'){
        printf("\n\nO diretorio deve começar com /\n\n");
        return;
    }
    int posFinal = -1;
    for(int i=0;i<99;i++){
        if(param[i+1] == '\0' && param[i] == '/'){
            posFinal = i+1;
            
        }
    }
    if(posFinal == -1){
        printf("\n\nO diretorio deve terminar com / \n\n");
        return;
    }

    

    char printados[30][100];
    //procura diretorios dentro da faixa da string digitada
    for(int i=0;i<4086;i++){
        int exibe = 1;
        int tamanho_digitado = 0;
        for(int j=0;j<100;j++){            
            if(param[j] == '\0' || param[j] == '\n'){
                break;
            }            
            tamanho_digitado++;                        
        }

        char stringDigitada[tamanho_digitado];
        memcpy(stringDigitada,param,sizeof(char)*tamanho_digitado);
        char stringNome[tamanho_digitado];
        memcpy(stringNome,clusters[i].dir[0].filename,sizeof(char)*tamanho_digitado);        
        //comparacao da string digitada com a string do cluster
        if (!strcmp(stringDigitada, stringNome)){
            //entrou, vou normalizar para ter certeza que devou exibir esse dado            
            int posFinal = -1;
            for(int j=0;j<99;j++){
                if(param[j+1] == '/'){
                    posFinal = j+1;
                    break;
                }else if(param[j+1] == '\n' || param[j+1] == '\0' ){
                    posFinal = j+1;
                    break;
                }
            }
            if(posFinal == -1){
                printf("<DIR> . \n");                
            }else{
                //se for um diretorio, imprimo ele
                if(clusters[i].dir[0].attributes == 1){
                    printf("<DIR> %s\n",clusters[i].dir[0].filename);
                }else{
                        //se for arquivo imprimo somente o nome dele
                        printf("<ARQ> ");
                        for(int j=0;j<posFinal;j++){
                            printf("%c",clusters[i].dir[0].filename[tamanho_digitado+j]);
                        }
                        printf("\n");
                                        
                }                                
            }

            
            
         }
    }
}

int main()
{
    char cmd[6], str[100], param[100];

    printf("Shell\n");
    while (1)
    {
        printf("/> ");
        scanf("%s", cmd);

        if (!strcmp(cmd, "init"))
        {
            //init
            init();
        }
        else if (!strcmp(cmd, "load"))
        {
            //load
            load();
        }
        else if (!strcmp(cmd, "exit"))
        {
            //exit
            return 0;
        }
        else if (!strcmp(cmd, "ls"))
        {
            scanf("%s", param);
            //ls
            ls(param);
        }
        else if (!strcmp(cmd, "mkdir"))
        {
            scanf("%s", param);
            //mkdir
            mkdir(param);
        }
        else if (!strcmp(cmd, "create"))
        {
            scanf("%s", param);
            //create
            create(param);
        }
        else if (!strcmp(cmd, "unlink"))
        {
            scanf("%s", param);
            //unlink
            unlink(param);
        }
        else if (!strcmp(cmd, "read"))
        {
            scanf("%s", param);
            //read
            read(param);
        }
        else if (!strcmp(cmd, "write"))
        {
            scanf("%s", str);
            scanf("%s", param);
            //write
            write(str, param);
        }
        else if (!strcmp(cmd, "append"))
        {
            scanf("%s", str);
            scanf("%s", param);
            //append
            append(str, param);
        }
        else
        {
            printf("msg: comando inválido\n");
        }

        //printf("%s %s %s", cmd, str, param);
    }

    return 0;
}

