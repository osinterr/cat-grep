#include "s21_grep.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    Options *config = NULL;
    config = calloc(1, sizeof(Options));
    if (config != NULL) {
      int fileCounter = scanOptions(argc, argv, config);
      for (; fileCounter < argc; fileCounter++) {
        useGrep(argv[fileCounter], config);
      }
      if (config->patterns != NULL) {
        free(config->patterns);
      }
      free(config);
    } else {
      fprintf(stderr, "memory not alloc");
    }
  } else {
    printf("didn't have argument command line");
  }
  return 0;
}

void printLCOption(Options *config, char *fileName) {
  if (config->countFiles > 1 && (!(config->h))) {
    printf("%s:", fileName);
  }
  if (config->successfulMatch > 0) {
    printf("1\n");
  } else {
    printf("0\n");
  }
  printLOption(config, fileName);
}

void printLOption(Options *config, char *fileName) {
  if (config->successfulMatch) {
    printf("%s\n", fileName);
  }
}

void printCOption(Options *config, char *fileName) {
  if (config->countFiles > 1 && (!(config->h))) {
    printf("%s:", fileName);
  }
  printf("%d\n", config->successfulMatch);
}

void useGrep(char *fileName, Options *config) {
  FILE *filePointer = NULL;
  filePointer = fopen(fileName, "r");
  char *charArray = NULL;
  size_t len = 0;
  int lenCharArray;

  if (filePointer != NULL) {
    config->lineNumber = 0;
    while ((lenCharArray = getline(&charArray, &len, filePointer)) != -1) {
      config->lineNumber += 1;
      printString(charArray, config, fileName, lenCharArray);
    }
    free(charArray);

    if (filePointer != NULL) {
      fclose(filePointer);
    }
    if (config->c && config->l) {
      printLCOption(config, fileName);
      config->successfulMatch = 0;
    } else if (config->c) {
      printCOption(config, fileName);
      config->successfulMatch = 0;
    } else if (config->l) {
      printLOption(config, fileName);
      config->successfulMatch = 0;
    }

  } else if (config->s == 0) {
    fprintf(stderr, "grep: %s: No such file or directory\n", fileName);
  }
}

void printString(char *charArray, Options *config, char *fileName,
                 int lenCharArray) {
  regex_t regex;
  regmatch_t rm[1];
  char *end = charArray;
  int flag = REG_EXTENDED;
  if (config->i) {
    flag = REG_ICASE;
  }

  if (regcomp(&regex, config->patterns, flag) == 0) {
    if (regexec(&regex, end, 1, rm, 0) == config->v) {
      config->successfulMatch += 1;

      if ((config->c || config->l) == 0) {
        if (config->countFiles > 1 && (!(config->h))) {
          printf("%s:", fileName);
        }

        if (config->n) {
          printf("%i:", config->lineNumber);
        }
        if (config->v || !(config->o)) {
          printf("%s", charArray);
          if (charArray[lenCharArray - 1] != '\n') {
            printf("\n");
          }
        } else if (config->o && (config->v == 0)) {
          do {
            printf("%.*s\n", (int)(rm[0].rm_eo - rm[0].rm_so),
                   end + rm[0].rm_so);
            end = end + (int)rm[0].rm_eo;
          } while (regexec(&regex, end, 1, rm, 0) == 0);
        }
      }
    }
    regfree(&regex);
  }
}

int scanOptions(int argc, char **argv, Options *config) {
  int sym = 0;
  opterr = 0;
  const char *shortOptions = "e:ivclnhsf:o";
  while ((sym = getopt_long(argc, argv, shortOptions, NULL, NULL)) != (-1)) {
    switch (sym) {
      case 'i':
        config->i = 1;
        break;
      case 'v':
        config->v = 1;
        break;
      case 'c':
        config->c = 1;
        break;
      case 'l':
        config->l = 1;
        break;
      case 'n':
        config->n = 1;
        break;
      case 'h':
        config->h = 1;
        break;
      case 's':
        config->s = 1;
        break;
      case 'o':
        config->o = 1;
        break;
      case 'e':
        setConfig(config, optarg);
        config->e += 1;
        break;
      case 'f':
        setConfigF(config, optarg);
        break;
    }
  }

  if (config->patterns == NULL) {
    addFirstPattern(config, argv[optind]);
    optind++;
  }

  config->countFiles = argc - optind;

  return optind;
}

void setConfig(Options *config, char *optarg) {
  if (!(config->e || config->f)) {
    addFirstPattern(config, optarg);
  } else {
    addPatterns(config, optarg);
  }
}

void setConfigF(Options *config, char *optarg) {
  FILE *filePointer = NULL;
  char *charArray = NULL;
  size_t len = 0;
  filePointer = fopen(optarg, "r");

  if (filePointer != NULL) {
    int length = 0;
    while ((length = getline(&charArray, &len, filePointer)) != -1) {
      if (charArray[length - 1] == '\n') {
        charArray[length - 1] = '\0';
      }

      setConfig(config, charArray);
      config->f += 1;
    }
    free(charArray);

  } else if (config->s == 0) {
    printf("grep: %s: No such file or directory\n", optarg);
  }

  if (filePointer != NULL) {
    fclose(filePointer);
  }
}

void addFirstPattern(Options *config, char *optarg) {
  config->patterns = malloc(sizeof(char) * (strlen(optarg) + 1));
  if (config->patterns == NULL) {
    printf("ERROR1");
    exit(EXIT_FAILURE);
  }
  strcpy(config->patterns, optarg);
}

void addPatterns(Options *config, char *optarg) {
  int len = strlen(config->patterns) + strlen(optarg) + 2;
  config->patterns = realloc(config->patterns, len);
  if (config->patterns == NULL) {
    printf("ERROR2");
    exit(EXIT_FAILURE);
  }
  strcat(config->patterns, "|");
  strcat(config->patterns, optarg);
}
