#include <fcntl.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "main.h"
#include "makefile.h"

void usage(FILE *stream, char *prgm){
  fprintf(stream, "Usage: %s [options] project_name\n", prgm);
  fprintf(stream, "Options:\n");
  fprintf(stream, "\t-h       \tPrint usage\n");
  fprintf(stream, "\t-n <name>\tCustom name for the main file\n");
  fprintf(stream, "\t-v       \tPrint logging info\n");
}

int main(int argc, char **argv){

  int opt;
  char *prgm = argv[0];
  char *main_name = "main.c";
  bool verbose = false;

  if (argc < 2){
    fprintf(stderr, "Error: no project name given\n");
    usage(stderr, prgm);
    exit(1);
  }

  while ((opt = getopt(argc, argv, "n:hv")) != -1){
    switch (opt){
    case 'h':
      usage(stdout, prgm);
      exit(0);
    case 'n':
      main_name = optarg;
      break;
    case 'v':
      verbose = true;
      break;
    case '?':
      usage(stderr, prgm);
      exit(1);
      break;
    }}
  char *project_name = argv[optind];
  /* size_t project_name_len = strlen(project_name); */

  fprintf(stdout, "project name: %s\n", project_name);

  fprintf(stdout, "main name: %s\n", main_name);

  struct stat st = {0};
  if (stat(project_name, &st) == -1){
    mkdir(project_name, 0755); //0755 is the standard permissions for a directory
    if (verbose) {
      printf("INFO: Made folder: %s\n", project_name);
    }
  } else if (verbose) {
    printf("INFO: Folder '%s' exists\n", project_name);
  }

  char *dir_path = strcat(project_name, "/");
  char *main_path = strdup(dir_path);
  main_path = strcat(main_path, main_name);

  FILE *main_fd = fopen(main_path, "w+");

  fprintf(main_fd, "%s", main_file_body);

  fclose(main_fd);

  char *makefile_path = strdup(dir_path);
  makefile_path = strcat(makefile_path, "Makefile");


  FILE *makefile_fd = fopen(makefile_path, "w+");

  fprintf(makefile_fd, "%s", makefile_file_body);

  fclose(makefile_fd);
  return 0;
}
