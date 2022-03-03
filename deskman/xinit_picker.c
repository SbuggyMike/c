/* This programme finds a list of DEs/WMs
 * It then allows the user to pick one.
 * This then leads to a modification of the .xinitrc file.*/

const float dec_version = 0.1;

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// function declarations
#include "deskman.h"

int main() {
  // print some sort of intro message
  intro_text();

  // open the directory where desktop files are stored
  char desktop_location[256];
  get_lcation(&desktop_location[0]); 
  DIR * xsessions;
  desktop_location[strcspn(desktop_location, "\n")] = 0;
  xsessions = opendir(desktop_location);

  if(xsessions == NULL){
    printf("Error. Cannot find %s\n", desktop_location);
    return 1;
  }

  // return a list of desktop files
  printf("Available desktops:\n");
  struct dirent * desktop_files;

  // create an array of the desktop entries
  char desktop_entries[16][256];

  // create the list of abbreviations
  char abbreviations[16]; 

  // this will be used for moving along the file name and moving along the list of abbreviations
  int c;
  int d = 0;

  //check to make sure there are some desktop files
  // N.B. this currently doesn't work because no directories are regarded as empty
  if(!(desktop_files = readdir(xsessions))){
    perror("Error: No desktop files found.\n");
    return 1;
  }
  rewinddir(xsessions);

  while((desktop_files = readdir(xsessions))){
    // try to take out current and parent directory before printing
    // then print without the '.desktop' suffix'
    for(c = 0; c < 256 && desktop_files->d_name[c] != '.'; c++){
      //putchar(desktop_files->d_name[c]);
      desktop_entries[d][c] = desktop_files->d_name[c];
      // add the abbreviation
      if(c == 0){
	abbreviations[d] = abbrev(&desktop_files->d_name[c], abbreviations, d);
      }
    }
    if(c > 0) d++;
    // add the abbreviation character and print a new line (if the file entry wasn't a hidden file)
    // if(c > 0) printf("\t[%c]\n", abbreviations[d++]);
  }

  // print them out
  int e;
  for(e = 0; e < d; e++) printf("%s\t[%c]\n", desktop_entries[e], abbreviations[e]);
  line();

  // make a selection
  int selection = 17;
  while(selection == 17) {
    selection = selector(abbreviations);
  }

  get_exception(desktop_entries[selection]);

  printf("You have selected %s.\n", desktop_entries[selection]);

  // edit xinitrc
  edit_xinitrc(desktop_entries[selection]);

  system("startx");

  return 0;
}

void intro_text(){
  // display some intro text
  line();
  printf("Deskman %.2f\n", dec_version);
  printf("This programme allows the user to select from the installed DEs/WMs. It then \n");
  printf("edits the xinitrc file to reflect that selection.\n");
  line();
  return;
}

char abbrev(char * tester, char tracker[16], int d){
  int c;
  for(c = 0; c < d; c++) if(tracker[c] == *tester) (*tester)++;

  return *tester;
}

int selector(char abbreviations[16]){
  int selection;
  char selector;

  printf("Make a selection:\n");
  selector = getchar();
  // flush input
  int c;
  while ((c = getchar()) != '\n' && c != EOF) { }


  for(selection = 0; selection < 16; selection++) if(selector == abbreviations[selection]) return selection;

  printf("No valid selection made.\n");
  return 17;
}

#define WIDTH 80

void line(){
  int counter;
  // prints a line
  for(counter = 0; counter < WIDTH; counter++) printf("-");
  printf("\n");

  return;
}


