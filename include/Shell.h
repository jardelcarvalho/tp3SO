#ifndef SHELL_H
#define SHELL_H

void init();
void load();
void ls(char param[]);
void mkdir(char param[]);
void create(char param[]);
void unlink(char param[]);
void read(char param[]);
void write(char str[], char param[]);
void append(char str[], char param[]);

#endif