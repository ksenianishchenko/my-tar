#include "header.h"

int filesInDir(char *path, int argc, char **argv, char *tarFile) {
    DIR *folder = opendir(path);
    struct dirent *entry = NULL;

    FILE *tar = fopen( tarFile, "w+" );

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

      for (int i = 1; i < argc; i++) {

        if (strcmp(entry->d_name, argv[i]) == 0 && strcmp(entry->d_name, tarFile) != 0) {
          addToTar(tar, entry->d_name);
        }

      }

    }

    fclose(tar);

    closedir(folder);

    return 0;
};

char *getOptions(int argc, char **argv) {
  char *optionsStr;
  int argvLen = 0;
  int n = 0;
  int j = 0;

    for (int i = 1; i < argc; ++i) {
        argvLen = argvLen + strlen(argv[i]);
    };

  optionsStr = malloc(sizeof(char) * argvLen + 1);

  for (int i = 0; i < argc; i++) {
    if (argv[i][0] == '-') {
      int tempLeng = strlen(argv[i]);
      for (int j = 0; j < tempLeng; j++) {
          optionsStr[n] = argv[i][j];
          n++;
      }
    }
  }

  if(!optionsStr[0]) {
    printf("%s\n", "Specify options: -c, -f, -t, -x");
    return NULL;
  }

  optionsStr[n] = '\0';

  return optionsStr;
}

char *initTarFile(int argc, char **argv) {
  char *tarFileName;
  for (int i = 0; i < argc; i++) {
    if (argv[i][0] == '-') {
      int tempLeng = strlen(argv[i]);
      if(argv[i][tempLeng - 1] == 'f') {
        tarFileName = (char *)malloc(sizeof(char) * strlen(argv[i+1]) + 1);
        tarFileName = argv[i + 1];
      }
    }
  }

  return tarFileName;
}

int main(int argc, char **argv) {

    char *optionsFromCommandLine = getOptions(argc, argv);
    t_opts options = get_opts(optionsFromCommandLine);
    char *tar = initTarFile(argc, argv);

    checkOptions(&options);

    if(options.opts_c) {

      filesInDir(".", argc, argv, tar);

    }

    if(options.opts_t && options.opts_f) {

        filesNamesInArchive(tar);

    }

    if(options.opts_x && options.opts_f) {

        extractFilesFromArchive(tar);

    }

    return 0;
}
