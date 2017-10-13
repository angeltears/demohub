#pragma once
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>
void print_file_info(char *pathname);
void dir_order(char *pathname);
void print_file(char *pathname);
