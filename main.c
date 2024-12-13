#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "file.h"
#include "custumer.h"
#include "game.h"
#include "rental.h"
#include "index.h"
void displayMenu() {
    // Implementation...

    printf("Main Menu:\n");
    printf("1. Add a rental\n");
    printf("2. Add a customer\n");
    printf("3. Add a game\n");
    printf("4. Search a rental\n");
    printf("5. Display the rentals list\n");
    printf("6. Display the customers list\n");
    printf("7. Display the games list\n");
    printf("0. Exit\n");
    printf("Choose an option (0-9): ");
}




int main() {

srand(time(NULL));
    char s;
    TOF *cfile, *gfile, *rfile;
    char gameindex ="gameindex.txt";
    char custindex ="custindex.txt";
    char rentrindex ="rentindex.txt";
    Index gamei;
    Index custi;
    Index renti;

    
    printf("\nIf you want to load data type A \nIf you want to create a new list type N\n");
    scanf(" %c", &s);
    switch (s)
    {
    case 'A':
        gamei = load(gameindex);
        custi = load(custindex);
        renti = load(rentrindex);
        break;
     case 'N':
        gamei.ni = 0;
        custi.ni = 0;
        renti.ni = 0;
        break;
    
    
    default:
        break;
    }
    cfile = open_file("c.txt", s);
    gfile = open_file("g.txt", s);
    rfile = open_file("r.txt", s);
    
    if (cfile == NULL || gfile == NULL || rfile == NULL) {
        printf("Error opening files.\n");
        return -1;
    }
   int id;
    int choice;
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addRental(rfile, cfile, gfile,custi,gamei,renti,rentrindex);
                break;
            case 2:
                addCustomer(cfile,custi,custindex);
                break;
            case 3:
                addGame(gfile,gamei,gameindex);
                break;
            case 4:
           
                 printf("give the id of the rental you want to search");
                 scanf("%d",&id);
                Rentalf s = searchRental(rfile,renti,id);
                if (s.rid == 0){
                    printf("rental not found ");
                }else{
                    Rental r;
                    r.a = searchcust(cfile,custi,s.cid);
                    r.b = *searchgame(gfile,&gamei,s.gid);
                    r.rid = s.rid ;
                    r.ren = s.t1;
                    r.rut = s.t2;
                    r.price = s.price ;
                    displayRental(&r);
                }
                break;
            case 5:
                displayRentals(rfile, cfile, gfile,custi,gamei);
                break;
            case 6:
                displayCustomers(cfile);
                break;
            case 7:
                displayGames(gfile);
                break;
            case 0:

                printf("Exiting...\n");
                save(custindex,&custi);
                save(gameindex,&gamei);
                save(rentrindex,&gamei);
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
    return 0;
}
