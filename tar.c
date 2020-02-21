#include "header.h"


void getStatsForHeader (struct tarHeader *header, char *file, int contentLength) {

    struct stat stats;
    stat(file, &stats);

    snprintf( header->name, 100, "%s", file );
    snprintf( header->size, 12, "%d", contentLength );
    snprintf( header->modified, 12, "%ld ", stats.st_mtime );
    snprintf( header->mode, 8, "%o ", stats.st_mode );
}

void copyContentOfFile(FILE *sourse, FILE *tarFile, char *file) {

    struct stat stats;
    stat(file, &stats);
    char *buffer;
    while( !feof(sourse) ){
        buffer = (char*)malloc(stats.st_size * sizeof(char));
        size_t read = fread( buffer, 1, stats.st_size, sourse );
        fwrite( buffer, 1, read, tarFile);
    }
    free(buffer);

}


void addToTar (FILE *tarFile, char *file) {
    FILE *sourse = fopen(file, "rb"); /*Open current file for reading*/
    size_t lenOfTarFile;

    if (sourse == NULL) {
      printf("%s\n", "No such file in directory");
      return;
    }

    /*find the size of tar file*/
    fseek(tarFile, 0L, SEEK_END);
    int startForHeader = ftell(tarFile); /*For header*/


    /*Copy content of file at the end of tar file*/

    lenOfTarFile = ftell(tarFile);

    int contentStart = lenOfTarFile + 512;

    fseek(tarFile, contentStart, SEEK_SET); /*set pointer at the end of file*/

    copyContentOfFile(sourse, tarFile, file);

    lenOfTarFile = ftell(tarFile);

    int contentLength = lenOfTarFile - contentStart;  /*Get content length*/

    /*Add header with info before content*/
    struct tarHeader header;
    memset(&header, 0, sizeof( struct tarHeader ));

    getStatsForHeader(&header, file, contentLength);

    fseek(tarFile, startForHeader, SEEK_SET);
    fwrite(&header, 1, sizeof(struct tarHeader), tarFile);

    fclose(sourse);

}
