#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rental.h"
#include "file.h"
#include "custumer.h"
#include "game.h"
#include "index.h"
int daysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            // Check for leap year
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                return 29;
            } else {
                return 28;
            }
        default:
            return -1; // Invalid month
    }
}

// Function to calculate the difference in days between two dates
int dateDifference( Date d1, Date d2) {
    int days1 = d1.d + (d1.m - 1) * daysInMonth(d1.m, d1.y) + d1.y * 365;
    int days2 = d2.d + (d2.m - 1) * daysInMonth(d2.m, d2.y) + d2.y * 365;

    return days2 - days1;
}
int  write_rbloc(TOF *tof, Rblock bloc, int position) {
    // Implementation...

    if (position == -1)
        position = 0;
    FILE *f = fopen(tof->fil, "r+b");
    if (tof->ent.nbb < position)
        return 0;
    // decaler le poiteur de lecture après l'entete
    fseek(f, sizeof(Entete) + (sizeof(Rblock) * position), SEEK_SET);
    fwrite(&bloc, sizeof(Rblock), 1, f);
    fclose(f);
    return 1;
}


int read_rbloc(TOF *tof, Rblock *bloc, int position) {
    // Implementation...
    if (position == -1)
        position = 0;

    FILE *f = fopen(tof->fil, "r+b");
    if (tof->ent.nbb == 0 || tof->ent.nbb < position)
        return -1;

    // decaler le poiteur de lecture après l'entete
    fseek(f, sizeof(Entete) + (sizeof(Rblock) * position), SEEK_SET);
    fread(bloc, sizeof(Rblock), 1, f);
    fclose(f);
    return 1;
}


Rental createRental(Custumer s, Game i, Date f, Date l) {
    // Implementation...
Rental r;
r.rid = rand()%10000;
r.a =s;
r.b =i;
r.ren = f;
r.rut = l;
r.price = i.price * dateDifference(f,l);
printf(" he id of the rental ids : %d \n ", i.price);
printf("the price of rental is %.2f \n ",r.price);
return r;

}

void insert_rent(Rentalf s, TOF *tof, Rblock bloc, int position) {
    // Implementation...
int i = read_rbloc(tof,&bloc,position);
if (i==-1){
        bloc.nr =0;
    bloc.r[bloc.nr]=s;
       bloc.nr++;
       write_rbloc(tof,bloc,position);
        tof->ent.lid++;
        tof->ent.nbb++;
       write_entete(tof->ent,tof);

}
if(bloc.nr>=100){
    write_rbloc(tof,bloc,position);
    Rblock a;a.nr=0;
    a.r[0] = s;
    write_rbloc(tof,a,position);
        tof->ent.lid++;
        tof->ent.nbb++;
       write_entete(tof->ent,tof);
}else{bloc.r[bloc.nr]=s;
       bloc.nr++;
       write_rbloc(tof,bloc,position);tof->ent.lid++;
      write_entete(tof->ent,tof); }

}


Rentalf *searchRental(TOF *tof,Index ren, int id) {
    
       char rin = (char)id;
    Entry_index *ri = search(&ren,rin);
    if (ri== NULL){
      return NULL;
    
    }else
    {   Rblock re;
        read_rbloc(tof,&re,ri->block_number);
        return &re.r[ri->enbr];
    }

}


void displayRental(const Rental *rental) {
    // Implementation...
    printf("Rental ID: %d\n", rental->rid);

    printf("Customer Information:\n");
    printf("  Customer ID: %d\n", rental->a.cid);
    printf("  First Name: %s\n", rental->a.fname);
    printf("  Surname: %s\n", rental->a.sname);
    printf("  Contact: %s\n", rental->a.contact);

    printf("Game Information:\n");
    printf("  Game ID: %d\n", rental->b.gid);
    printf("  Title: %s\n", rental->b.name);
    printf("  game Price per day: %f\n", rental->b.price);

    printf("Rental Date: %04d-%02d-%02d\n", rental->ren.y, rental->ren.m, rental->ren.d);
    printf("Return Date: %04d-%02d-%02d\n", rental->rut.y, rental->rut.m, rental->rut.d);
    printf("rental Price: %.2f\n", rental->price);
}


void displayRentals(TOF *tof, TOF *ctof, TOF *gtof,Index custindex,Index gameindex){
    // Implementation...
    printf("Displaying the rentals list :...\n");
    // Implement rental display logic here
    int i =0;Rblock cb;int j =0; Rental f;
while(i<tof->ent.nbb){
   if(read_rbloc(tof,&cb,i) == -1){
    printf("error") ;
    }else{j=0;
        while(j<cb.nr){
                f.a = searchcust(ctof,custindex,cb.r[j].cid);
                f.b = *searchgame(gtof,&gameindex,cb.r[j].gid);
                f.price =cb.r[j].price;
                f.ren =cb.r[j].t1;
                f.rut =cb.r[j].t2;
                f.rid = cb.r[j].rid;
                displayRental(&f);
            j++;}
        }
 i++;
    }


}

void addRental(TOF *rfile, TOF *cfile, TOF *gfile,Index cust,Index gami,Index b,char *a) {
    // Implementation...
    int id1,id2;
    Date t,t1;
    Rblock x;
    printf("give the your id \n");
   scanf("%d",&id1);
   Custumer s = searchcust(cfile,cust,id1);
    printf("give the game id \n");
   scanf("%d",&id2);
   Game s2 = *searchgame(gfile,&gami,id2);
    printf("give the date you want to rent in d-m- y \n");
   scanf("%d %d %d",&t.d,&t.m,&t.y);
    printf("give the date you want to return the game in d-m- y \n");
   scanf("%d %d %d",&t1.d,&t1.m,&t1.y);
    Rental r = createRental(s,s2,t,t1);
    Rentalf rf;
    rf.cid = r.a.cid;
    rf.gid = r.b.gid;
    rf.price = r.price;
    rf.rid = r.rid;
    rf.t1 = r.ren;
    rf.t2 = r.rut;
    char id = (char)rf.rid;
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
      add(b,is,a);
    insert_rent(rf,rfile,x,rfile->ent.nbb - 1);
    // Implement rental addition logic here

}
