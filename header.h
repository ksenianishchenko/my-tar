#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef char boolean;

#define FALSE 0
#define TRUE 1

typedef struct Opts {
  boolean opts_c;
  boolean opts_r;
  boolean opts_t;
  boolean opts_u;
  boolean opts_x;
  boolean opts_v;
  boolean opts_C;
  boolean opts_f;
  boolean opts_k;
  boolean opts_L;
} t_opts;


struct tarHeader{
    char name[100];
    char mode[8];
    char owner[8];
    char group[8];
    char size[12];
    char modified[12];
    char checksum[8];
    char type[1];
    char link[100];
    char padding[255];
};

typedef struct LinkedList {
  void                *data;
  struct LinkedList   *next;
}t_llist;

void init_opts(t_opts *opts);
t_opts get_opts(char *str);
void *addNode(t_llist **head, void *data, size_t data_size);
void addToTar(FILE *tarFile, char *file);
void copyContentOfFile(FILE *sourse, FILE *tarFile, char *file);
void *addToArchive(t_llist **head, void *new_data, size_t data_size);
void filesNamesInArchive(char *tarFile);
void checkOptions (t_opts *options);
void extractFilesFromArchive(char *tarFile);
