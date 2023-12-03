#include "s21_cat.h"

int main(int argc, char **argv) {
  CustomOptions customConfig = {0};
  int customFlagError = 0;
  if (argc > 1) {
    CustomScanOptions(argc, argv, &customConfig, &customFlagError);

    if (!customFlagError) {
      while ((customConfig.customNumberFiles) < argc) {
        FILE *customFile = fopen(argv[customConfig.customNumberFiles], "r");
        if (customFile != NULL) {
          fclose(CustomCheckOptions(customFile, &customConfig));
        } else {
          fprintf(stderr, "%s: No such file or directory\n",
                  argv[customConfig.customNumberFiles]);
        }

        customConfig.customNumberFiles += 1;
      }
    }
  } else {
    fprintf(stderr, "argument command line not found\n");
  }

  return 0;
}

void CustomScanOptions(int argc, char **argv, CustomOptions *customConfig,
                       int *customFlagError) {
  int customOption;
  const char *customShortOptions = "+beEnstTv";
  const struct option customLongOptions[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};

  while ((customOption = getopt_long(argc, argv, customShortOptions,
                                     customLongOptions, NULL)) != -1) {
    switch (customOption) {
      case 'n':
        customConfig->customOptionN = 1;
        break;
      case 'b':
        customConfig->customOptionB = 1;
        break;
      case 'e':
        customConfig->customOptionE = 1;
        customConfig->customOptionV = 1;
        break;
      case 'E':
        customConfig->customOptionE = 1;
        break;
      case 's':
        customConfig->customOptionS = 1;
        break;
      case 't':
        customConfig->customOptionT = 1;
        customConfig->customOptionV = 1;
        break;
      case 'T':
        customConfig->customOptionT = 1;
        break;
      case 'v':
        customConfig->customOptionV = 1;
        break;
      case '?':
        *customFlagError = 1;
    }
  }
  if (customConfig->customOptionB == 1 && customConfig->customOptionN == 1) {
    customConfig->customOptionN = 0;
  }
  customConfig->customNumberFiles = optind;
}

FILE *CustomCheckOptions(FILE *customFile, CustomOptions *customConfig) {
  char *customCharArray = NULL;
  int customStringLength = 0;
  int customEmptyStringFlag = 0;
  int customLineCounter = 1;
  int customNoOutputString = 0;
  size_t customLength = 0;

  while ((customStringLength =
              getline(&customCharArray, &customLength, customFile)) != -1) {
    if (customConfig->customOptionS || customConfig->customOptionB) {
      CustomCountEmptyStrings(customCharArray, &customEmptyStringFlag);

      if (customEmptyStringFlag > 1 && customConfig->customOptionS) {
        customNoOutputString = 1;
      } else {
        customNoOutputString = 0;
      }
    }
    if (!customNoOutputString) {
      CustomShowFlagBOrN(customConfig, &customLineCounter, customCharArray);
      CustomPrintCharacter(customStringLength, customConfig, customCharArray);
    }
  }
  if (customCharArray != NULL) {
    free(customCharArray);
  }

  return customFile;
}

void CustomPrintCharacter(int customStringLength, CustomOptions *customConfig,
                          char *customCharArray) {
  for (int i = 0; i < customStringLength; i++) {
    int customChangeCharacter = 0;

    if (customConfig->customOptionV) {
      CustomShowCharacter(customCharArray[i], &customChangeCharacter);
    }

    if (customConfig->customOptionE) {
      CustomShowFlagE(customCharArray[i], &customChangeCharacter);
    }
    if (customConfig->customOptionT) {
      CustomShowFlagT(customCharArray[i], &customChangeCharacter);
    }

    if (!customChangeCharacter) {
      printf("%c", customCharArray[i]);
    }
  }
}

void CustomShowFlagT(char customCharArray, int *customChangeCharacter) {
  if (customCharArray == 9) {
    putchar('^');
    putchar('I');
    *customChangeCharacter += 1;
  }
}

void CustomShowFlagE(char customCharArray, int *customChangeCharacter) {
  if (customCharArray == 10) {
    putchar('$');
    putchar('\n');
    *customChangeCharacter += 1;
  }
}

void CustomShowFlagBOrN(CustomOptions *customConfig, int *customLineCounter,
                        char *customCharArray) {
  if (customConfig->customOptionN) {
    printf("%6d\t", *customLineCounter);
    *customLineCounter += 1;
  } else if (customConfig->customOptionB) {
    if (customCharArray[0] != '\n') {
      printf("%6d\t", *customLineCounter);
      *customLineCounter += 1;
    }
  }
}

void CustomShowCharacter(char customCharacter, int *customChangeCharacter) {
  if (customCharacter < -96) {
    printf("M-^%c", customCharacter + 192);
    *customChangeCharacter += 1;
  } else if (customCharacter < 0) {
    printf("M-%c", customCharacter + 128);
    *customChangeCharacter += 1;
  } else if ((0 <= customCharacter && customCharacter <= 31) &&
             (customCharacter != 10) && (customCharacter != 9)) {
    putchar('^');
    putchar(customCharacter + 64);
    *customChangeCharacter += 1;
  } else if (customCharacter == 127) {
    putchar('^');
    putchar('?');
    *customChangeCharacter += 1;
  }
}

void CustomCountEmptyStrings(char *customCharArray,
                             int *customEmptyStringFlag) {
  if (customCharArray[0] == '\n') {
    *customEmptyStringFlag += 1;
  } else {
    *customEmptyStringFlag = 0;
  }
}
