#ifndef S21_CAT_H_
#define S21_CAT_H_
#define _GNU_SOURCE

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int customOptionB;
  int customOptionE;
  int customOptionN;
  int customOptionS;
  int customOptionT;
  int customOptionV;
  int customNumberFiles;
} CustomOptions;

void CustomScanOptions(int argc, char **argv, CustomOptions *customConfig,
                       int *customFlagError);
FILE *CustomCheckOptions(FILE *customFile, CustomOptions *customConfig);
void CustomShowCharacter(char customCharacter, int *customChangeCharacter);
void CustomCountEmptyStrings(char *customCharArray, int *customEmptyStringFlag);

void CustomShowFlagBOrN(CustomOptions *customConfig, int *customLineCounter,
                        char *customCharArray);
void CustomShowFlagE(char customCharArray, int *customChangeCharacter);
void CustomShowFlagT(char customCharArray, int *customChangeCharacter);
void CustomPrintCharacter(int customStringLength, CustomOptions *customConfig,
                          char *customCharArray);

#endif  // S21_CAT_H_
