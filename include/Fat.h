#ifndef FAT_H
#define FAT_H

/*DEFINE*/
#include <stdint.h>
#include <stdbool.h>


#define SECTOR_SIZE	512
#define CLUSTER_SIZE	2*(SECTOR_SIZE)
#define ENTRY_BY_CLUSTER CLUSTER_SIZE /sizeof(dir_entry_t)
#define NUM_CLUSTER	4096
#define fat_name	"fat.part"

struct _dir_entry_t
{
    unsigned char filename[18];
    unsigned char attributes;
    unsigned char reserved[7];
    unsigned short first_block;
    unsigned int size;
};

typedef struct _dir_entry_t  dir_entry_t;

struct _data_cluster
{
    dir_entry_t dir[ENTRY_BY_CLUSTER];
    char data[1000];
};

typedef struct _data_cluster data_cluster;

/*DATA DECLARATION*/
unsigned short fat[NUM_CLUSTER];
unsigned char boot_block[CLUSTER_SIZE];
dir_entry_t root_dir[ENTRY_BY_CLUSTER];
data_cluster clusters[4086];

void init();
void load();
void persisteDados();

#endif //TP3_SO_FAT_H