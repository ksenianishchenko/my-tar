#include "header.h"

void filesFromArchiveToTar(char *tarFile, t_llist *archive) {

  FILE *tar = fopen( tarFile, "w+" );

  if( !tar ){
      printf( "%s", "Please specify a tar file name" );
      return;
  }

  while (archive != NULL) {
      addToTar(tar, archive->data);
      archive = archive->next;
  }

  fclose(tar);

}

int filesInDir(char *path, int argc, char **argv, t_llist *filesList) {
    DIR *folder = opendir(path);
    struct dirent *entry = NULL;

    FILE *tar = fopen( argv[2], "w+" );

    if( !tar ){
        printf( "%s", "Please specify a tar file name" );
        return 1;
    }

    if(argc < 3) {
      printf("%s", "Please specify some file names!");
    }

    if(folder == NULL) {
        puts("Unable to read directory");
        return(1);
    };

    while((entry=readdir(folder))) {

      for (int i = 3; i < argc; i++) {

        if (strcmp(entry->d_name, argv[i]) == 0) {
          addToArchive(&filesList, entry->d_name, sizeof(struct dirent));
        }

      }

    }

    filesFromArchiveToTar(argv[2], filesList);

    fclose(tar);

    closedir(folder);

    return 0;
};

int main(int argc, char **argv) {

    t_opts options = get_opts(argv[1]);
    t_llist *filesList = NULL;

    checkOptions(&options);

    if(options.opts_c) {

      filesInDir(".", argc, argv, filesList);

    }

    if(options.opts_t && options.opts_f) {

        filesNamesInArchive(argv[2]);

    }

    if(options.opts_x && options.opts_f) {

        extractFilesFromArchive(argv[2]);

    }

    return 0;
}
