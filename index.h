#ifndef INDEX_H
#define INDEX_H
  
#include "structs.h"
int write_ibloc(char a[30], Index *bloc, int position);
int read_ibloc(char a[30], Index *bloc, int position);
Index load(char a[30]);
void save(char a[30],Index *b);
void add(Index b,Entry_index s,char *a);
int searchind(Index *b, char *id);
Index delete(Index b,int i,char *id );
Entry_index* search(Index *b, char *id);
#endif // INDEX_H