#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "file.h"
#include "index.h"


int  write_gbloc(TOF *tof, Gblock bloc, int position) {
    // Implementation...

    if (position == -1)
        position = 0;
    FILE *f = fopen(tof->fil, "r+b");
    if (tof->ent.nbb < position)
        return 0;
    // decaler le poiteur de lecture après l'entete
    fseek(f, sizeof(Entete) + (sizeof(Gblock) * position), SEEK_SET);
    fwrite(&bloc, sizeof(Gblock), 1, f);
    fclose(f);
    return 1;
}


int read_gbloc(TOF *tof, Gblock *bloc, int position) {
    // Implementation...
    if (position == -1)
        position = 0;

    FILE *f = fopen(tof->fil, "r+b");
    if (tof->ent.nbb == 0 || tof->ent.nbb < position)
        return -1;

    // decaler le poiteur de lecture après l'entete
    fseek(f, sizeof(Entete) + (sizeof(Gblock) * position), SEEK_SET);
    fread(bloc, sizeof(Gblock), 1, f);
    fclose(f);
    return 1;
}


Game create_game(int gid, const char *name, float price) {
    // Implementation...

    Game new_game;
    new_game.gid = gid;
    strncpy(new_game.name, name, sizeof(new_game.name) - 1);
    new_game.name[sizeof(new_game.name) - 1] = '\0'; // Ensure null-termination
    new_game.price = price;
    return new_game;
}


void insert_g(Game s, TOF *tof, Gblock bloc, int position) {
    // Implementation...
int i = read_gbloc(tof,&bloc,position);
if (i==-1){
	bloc.nc = 0;
    bloc.g[bloc.nc]=s;
       bloc.nc++;
       write_gbloc(tof,bloc,position);
        tof->ent.lid++;
        tof->ent.nbb++;
       write_entete(tof->ent,tof);

}
if(bloc.nc>=100){
    write_gbloc(tof,bloc,position);
    Gblock a;
	a.nc =0;
    a.g[bloc.nc] = s;
	a.nc++;
    write_gbloc(tof,a,position);
        tof->ent.lid++;
        tof->ent.nbb++;
       write_entete(tof->ent,tof);
}else{bloc.g[bloc.nc]=s;
       bloc.nc++;
       write_gbloc(tof,bloc,position);tof->ent.lid++;
      write_entete(tof->ent,tof); }

}


void addGame(TOF *gfile,Index b,char *a) {
    // Implementation...

    char s[50];float f;
    Gblock gb;
    printf("give the  game name");
    scanf("%s",&s);
     printf("give the  game price ");
    scanf("%f",&f);
    Game ga = create_game(rand()%1000,s,f);
    char id = (char)ga.gid;
      Entry_index is;
      if (b.d[b.ni - 1].enbr >= MAX)
      {is.block_number = b.d[b.ni - 1].block_number +1;
       is.enbr = 0;
       strcpy(is.id,id);
      }else
      {is.enbr = b.d[b.ni - 1].enbr +1;
       is.block_number = b.d[b.ni - 1].block_number;
       strcpy(is.id,id);
      }
      
      
     printf("\n your id is \n: %d \n",ga.gid);
    insert_g(ga,gfile,gb,gfile->ent.nbb-1);
    add(b,is,a);
    // Implement game addition logic here
}


Game *searchgame(TOF *tof,Index *gam, int id) {
    // Implementation...
       char gin = (char)id;
    Entry_index *gi = search(&gam,gin);
    if (gi== NULL){
      return NULL;
    
    }else
    {    Gblock ge;
        read_gbloc(tof,&ge,gi->block_number);
        return &ge.g[gi->enbr];
    }


}


void displayGames(TOF *tof) {
    // Implementation...
    printf("Displaying the games list...\n");
    int i =0;Gblock cb;int j =0;
while(i<tof->ent.nbb){
   if(read_gbloc(tof,&cb,i) == -1){
    printf("error");exit (1) ;
    }else{j=0;
        while(j<cb.nc){
         printf("game name : %s \n game price :%f \n game ID: %d",cb.g[j].name,cb.g[j].price,cb.g[j].gid);
            j++;
        }

    }
   i++;
}

}

