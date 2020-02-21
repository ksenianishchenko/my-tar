#include "header.h"

int sizeOfFile(FILE *fp, long int offset) {
  char fileSize[12];
  long int fileSizeOffset = offset + 124;
  int size;

  fseek(fp, fileSizeOffset, SEEK_SET);

  fread(fileSize, 1, 12, fp);

  size = atoi(fileSize);

  return size;
}


void filesNamesInArchive(char *tarFile) {

  FILE *fp = fopen(tarFile, "rb");

  fseek(fp, 0L, SEEK_END);
  long int lenOfTarFile = ftell(fp); /*Length of tar file*/

  if (fp == NULL) {
      printf("can not open tar file!");
      return;
  }

  char name[100];
  int fileSize;
  long int offset = 0;

  while (offset < lenOfTarFile) {
    fileSize = sizeOfFile(fp, offset);

    fseek(fp, offset, SEEK_SET);
    fread(name, 1, 100, fp);

    printf("%s\n", name);

    offset = offset + 512 + fileSize;
  }

  fclose(fp);
}


void extractFilesFromArchive(char *tarFile) {

  FILE *fp = fopen(tarFile, "rb");

  fseek(fp, 0L, SEEK_END);
  long int lenOfTarFile = ftell(fp); /*Length of tar file*/

  if (fp == NULL) {
      printf("can not open tar file!");
      return;
  }

  char name[100];
  int fileSize;
  long int offset = 0;

  while (offset < lenOfTarFile) {

    FILE *file;

    fileSize = sizeOfFile(fp, offset); /*Find a size of current file*/

    fseek(fp, offset, SEEK_SET); /*Point to position that we need*/
    fread(name, 1, 100, fp);

    file = fopen(name, "wb");

    /*Add content to a new file*/

    fseek(fp, offset + 512, SEEK_SET); /*point to the begining of content */

    char *buffer = (char*)malloc(fileSize * sizeof(char*) + 1);

    size_t bytes = fread( buffer, 1, fileSize, fp );
    fwrite( buffer, 1, bytes, file);

    free(buffer);

    fclose(file);

    offset = offset + 512 + fileSize; /*Offset to the next file in tar file*/

  }


  fclose(fp);
}
