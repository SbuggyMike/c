#ifndef DESK_H_
#define DESK_H_

// print some intro text when programme is started
void intro_text(void);

// find the right abbreviation to enable selection from a list of items
char abbrev(char * tester, char tracker[16], int d);

// find out which of a list of items was selected 
int selector(char abbreviations[16]);

// print a line of -- to break up screen
void line();

// find out where to look for desktop files
void get_location(char * location);

void get_exception(char * select_ptr);

// edit xinitrc
void edit_xinitrc(char * select_ptr);

#endif
