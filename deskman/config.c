#include <stdio.h>
#include <string.h>

void get_location(char * location){
  //open config file
  FILE * config;
  config = fopen("config", "r");

  //array to hold line
  char line[256];

  while (fgets(line, 256, config)){
    if(!strncmp(line, "DIR: ", 5)) strcpy(location, line + 5);
  }

  fclose(config);

  return;
}

void get_exception(char *select_ptr){
  //open config file
  FILE * config;
  config = fopen("config", "r");

  //array to hold line
  char line[256];

  // read each line to check for exceptions
  while((fgets(line, 256, config))){
    if(!strncmp(line, "MOD: ", 5)){
      if(strstr(line, select_ptr) != NULL) strcpy(select_ptr, strrchr(line, ' ') + 1);
    }	
  } 

  // close config file
  fclose(config);

  return;
}
