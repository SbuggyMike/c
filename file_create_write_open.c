/* Get a list of files in the directory and write it to a file */

#include <stdio.h>
#include <dirent.h>

int main() {
  // open a directory
  DIR * directory;
  if((directory = opendir("/home/ajax")) == NULL){
    perror("No directory found.");
    return 1;
  }

  // create a pointer for directory files
  struct dirent *file;

  // create and open the file for writing
  FILE * writer;
  writer = fopen("file_list.txt", "w");

  // write file list to file
  while((file = readdir(directory))) fprintf(writer, "%s\n", file->d_name);

  // close the file for writing
  fclose(writer);

  // open the file for reading
  FILE * reader;
  reader = fopen("file_list.txt", "r");

  // display the contents of the file
  int c;
  while(!feof(reader)){
    c = fgetc(reader);
    putchar(c);
  }
      
  // close the file for reading
  fclose(reader);

  // delete the file
  remove("file_list.txt");
  
  return 0;
}
