#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Fat.h"

/*DATA DECLARATION*/
unsigned short fat[NUM_CLUSTER];
unsigned char boot_block[CLUSTER_SIZE];
dir_entry_t root_dir[ENTRY_BY_CLUSTER];
data_cluster clusters[4086];

void init()
{
	FILE* ptr_file;
	int i;
	ptr_file = fopen(fat_name,"wb");
	for (i = 0; i < 2; ++i)
		boot_block[i] = 0xbb;

	fwrite(&boot_block, sizeof(boot_block), 1,ptr_file);

	for (i = 0; i < NUM_CLUSTER; ++i)
		fat[i] = 0xfffe;

	fwrite(&fat, sizeof(fat), 1, ptr_file);

    memset(root_dir, 0x00, sizeof(root_dir));
	fwrite(&root_dir, sizeof(root_dir), 1,ptr_file);

    memset(clusters, 0x00, sizeof(clusters));
    fwrite(&clusters, sizeof(clusters), 1,ptr_file);
    
	fclose(ptr_file);


	//colocar tabela fat na memoria
	
}

void load()
{
	FILE* ptr_file;
	int i;
	ptr_file = fopen(fat_name, "rb");
	fseek(ptr_file, sizeof(boot_block), SEEK_SET);
	fread(fat, sizeof(fat), 1, ptr_file);
	fread(root_dir, sizeof(root_dir), 1, ptr_file);
	fclose(ptr_file);
}