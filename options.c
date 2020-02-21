#include "header.h"

void init_opts(t_opts *opts) {
    opts->opts_c = FALSE;
    opts->opts_r = FALSE;
    opts->opts_t = FALSE;
    opts->opts_u = FALSE;
    opts->opts_x = FALSE;
    opts->opts_v = FALSE;
    opts->opts_C = FALSE;
    opts->opts_f = FALSE;
    opts->opts_k = FALSE;
    opts->opts_L = FALSE;
    opts->opts_v = FALSE;
};

t_opts get_opts(char *str) {
    t_opts opts;
    init_opts(&opts);
    int count = 0;

    while(*str != '\0') {
      switch(*str) {
          case 'c':
            opts.opts_c = TRUE;
            break;
          case 'r':
            opts.opts_r = TRUE;
            break;
          case 't':
            opts.opts_t = TRUE;
            break;
          case 'f':
            opts.opts_f = TRUE;
            break;
          case 'x':
            opts.opts_x = TRUE;
            break;
      };

      str++;
      count++;
    };

    return opts;
};

void checkOptions (t_opts *options) {
    if (!options->opts_f) {
        printf("%s\n", "Option -f is required");
        return;
    }

    if (options->opts_c && options->opts_x) {
        printf("%s\n", "Option -c and -x can not be use together");
        return;
    }

    if (options->opts_t && options->opts_c) {
        printf("%s\n", "Option -c and -t can not be use together");
        return;
    }

    if (options->opts_r && options->opts_c) {
        printf("%s\n", "Option -c and -r can not be use together");
        return;
    }
}
