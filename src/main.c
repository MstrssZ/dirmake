#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


void usage(FILE *stream, char *prgm){
  fprintf(stream, "Usage: %s [options] project_name\n", prgm);
  fprintf(stream, "Options:\n");
  fprintf(stream, "\t-h       \tPrint usage\n");
  fprintf(stream, "\t-n <name>\tCustom name for the main file\n");
}

int main(int argc, char **argv){

  int opt;
  char *prgm = argv[0];
  char *main_name = "main";
  
  if (argc < 2){
    fprintf(stderr, "Error: no project name given\n");
    usage(stderr, prgm);
    exit(1);
  }

  while ((opt = getopt(argc, argv, "n:h")) != -1){
    switch (opt){
    case 'h':
      usage(stdout, prgm);
      exit(0);
    case 'n':
      main_name = optarg;
      break;
    case '?':
      usage(stderr, prgm);
      exit(1);
      break;
    }}    
  char *project_name = argv[optind];
 
  fprintf(stdout, "project name: %s\n", project_name);

  fprintf(stdout, "main name: %s\n", main_name);

  struct stat st = {0};
  if (stat(project_name, &st) == -1){
    mkdir(project_name, 0755); //0755 is the standard permissions for a directory
    printf("INFO: Made folder: %s\n", project_name);
  }


  
  return 0;
}
