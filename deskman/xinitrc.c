#include <stdio.h>
#include <string.h>
#include <unistd.h>

void edit_xinitrc(char * select_ptr){
  // make a string with the user ID in it to find home directory
  char user[32];
  char home[64] = {'/', 'h', 'o', 'm', 'e', '/'};
  char tail[10] = {'/', '.', 'x', 'i', 'n', 'i', 't', 'r', 'c'};
  strcpy(user, getlogin());
  strcat(home, strcat(user, tail));
  // open the xinitrc file
  FILE * xinitrc;
  if((xinitrc = fopen(home, "r")) == NULL){
    printf("%s file not found.\n", home);
     return;
  }

  // open a file to copy xinitrc to (to remove any existing exec line)
  FILE * xinitrc2;
  char line_to_copy[256];
  xinitrc2 = fopen("copy", "w");

  // copy everything apart from the exec line
  while((fgets(line_to_copy, 256, xinitrc))){
    if((strncmp(line_to_copy, "exec", 4) != 0 && (strncmp(line_to_copy, "\n", 1)) != 0)) fprintf(xinitrc2, "%s\n\n", line_to_copy);
  }

  // copy the new exec line
  fprintf(xinitrc2, "exec %s", select_ptr);

  fclose(xinitrc);
  fclose(xinitrc2);

  // copy the new file
  rename("copy", home);
    
  return;
}
