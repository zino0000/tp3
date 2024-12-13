#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

int write_ibloc(char a[30], Index *bloc, int position) {
    // Implementation...
    if (position == -1)
        position = 0;
    FILE *f = fopen(a, "r+b");
   
    // decaler le poiteur de lecture après l'entete
    fseek(f,  + (sizeof(Index) * position), SEEK_SET);
    fwrite(&bloc, sizeof(Index), 1, f);
    fclose(f);
     return 1;
}

int read_ibloc(char a[30], Index *bloc, int position) {
    // Implementation...
    
    if (position == -1){
        position = 0;}

    FILE *f = fopen(a, "r+b");

    // decaler le poiteur de lecture après l'entete
    fseek(f, + (sizeof(Index) * position), SEEK_SET);
    fread(bloc, sizeof(Index), 1, f);
    fclose(f);
 return 1;
}

Index load(char a[30]){
Index *b ;
read_ibloc(a,b ,0);
return *b;
}
void save(char a[30],Index *b){
    write_ibloc(a,b,0);
}
void add(Index b,Entry_index s,char *a){
    b.d[b.ni] =s;
    b.ni++;
    save(a,&b);
}
int searchind(Index *b, char *id){
    int i =0;
while(i<b->ni){
if(strcmp(id,b->d[i].id)==0){
    return i ;
} 
   i++;
}
return -1;
}
Index delete(Index b,int i,char *id ){
 int n =searchind(&b,id );
 if(n==-1){
    printf("dont exist");
    return b;
 }else 
 {
    while (b.ni>n){
        b.d[n] =b.d[n+1];
        n++;
    }
    b.ni --;
    
   return  b;
 }

}


Entry_index* search(Index *b, char *id) {
    // Implementation...
int i =0;
while(i<b->ni){
if(strcmp(id,b->d[i].id)==0){
 Entry_index* s = &b->d[i];
    return s ;
} 
   i++;
}
return NULL;
}
