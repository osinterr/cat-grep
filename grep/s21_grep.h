#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int countFiles;
  int lineNumber;
  int countMatches;
  char *patterns;
  int successfulMatch;
  int printNameFile;
} Options;

int scanOptions(int argc, char **argv, Options *config);
void setConfig(Options *config, char *optarg);
void setConfigF(Options *config, char *optarg);
void addFirstPattern(Options *config, char *optarg);
void addPatterns(Options *config, char *optarg);

void useGrep(char *fileName, Options *config);

void printString(char *charArray, Options *config, char *fileName,
                 int lenCharArray);
void printCOption(Options *config, char *fileName);
void printLOption(Options *config, char *fileName);
void printLCOption(Options *config, char *fileName);

#endif  // SRC_GREP_S21_GREP_H_
