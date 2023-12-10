#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cell.h"
#include "list.h"
#include "list.c"
#include "cell.c"
#include "timer.h"
#include "timer.c"

//Exemples de résultats attendus, pour une liste à 5 niveaux

void test_niveaux_null() {
    //niveau a 5
    t_level_list *myList = create_level_list(5);

   // printf("Affichage de tous les niveaux de la liste :\n");
   // display_all_levels(myList);

    printf("\nAffichage de tous les niveaux de la liste avec alignement :\n");
    display_all_levels_aligned(myList);

   //   for (int level = 0; level < myList->max_levels; level++) {
   //     display_cells_at_level(myList, level);
   // }


}




void niveaux_implementees() {
    //niveau a 5
    t_level_list *myList = create_level_list(5);
    insert_sorted(myList, create_level_cell(32, 5));
    insert_sorted(myList, create_level_cell(56, 3));
    insert_sorted(myList, create_level_cell(18, 4));
    insert_sorted(myList, create_level_cell(25, 1));
    insert_sorted(myList, create_level_cell(31, 2));   
    insert_sorted(myList, create_level_cell(59, 5));
    insert_sorted(myList, create_level_cell(59, 1));
    insert_sorted(myList, create_level_cell(91, 3));

    printf("Affichage de tous les cellules a un nv donne :\n");
    display_cells_at_level(myList,3);

    printf("Affichage de tous les niveaux de la liste :\n");
    display_all_levels(myList);
   

    printf("\nAffichage de tous les niveaux de la liste avec alignement :\n");
    display_all_levels_aligned(myList);

   //   for (int level = 0; level < myList->max_levels; level++) {
   //     display_cells_at_level(myList, level);
   // }

 
}


void recherche_rand_val() {
    int initial_level = 7;
    int final_level = 16;
    int searches_per_level = 100000; // Nombre de recherches par niveau

    FILE *log_file = fopen("log.txt","w");
    if (!log_file) {
        perror("Erreur d'ouverture du fichier de log");
    }

    srand(time(NULL)); 

    for (int level = initial_level; level <= final_level; level++) {
        int max_value = pow(2, level) - 1;
        t_level_list *myList = create_level_list(level);

        // Création des cellules dans la liste
        for (int i = 0; i < max_value; i++) {
            insert_sorted(myList, create_level_cell(i, rand() % level + 1));
        }

        // Recherche au niveau 0
        startTimer();
        for (int i = 0; i < searches_per_level; i++) {
            search_level_0(myList, rand() % max_value);
        }
        stopTimer();
        double time_level_0 = _timer._msecs/1000; 
        //char *time_level_0 = getTimeAsString();

        // recherche à partir du niveau le plus haut


        startTimer();
        for (int i = 0; i < searches_per_level; i++) {
            search_all_levels(myList, rand() % max_value);
        }
        stopTimer();
        double all_levels = _timer._msecs/1000; 
        //char *time_all_levels = getTimeAsString();

        // Enregistrement des résultats dans le fichier log
        fprintf(log_file, "%d %07.3f %07.3f\n", level, time_level_0, all_levels);
        printf("Niveau: %d, Temps Niveau 0: %07.3f msTemps Tous Niveaux: %07.3f ms\n", level, time_level_0, all_levels);
    }

    fclose(log_file);
   
}


void recherche_val_inexist() {
    int initial_level = 7;
    int final_level = 16;
    int searches_per_level = 100000; // Nombre de recherches par niveau

    FILE *log_file = fopen("log.txt","w");
    if (!log_file) {
        perror("Erreur d'ouverture du fichier de log");
    }

    srand(time(NULL)); 

    for (int level = initial_level; level <= final_level; level++) {
        int max_value = pow(2, level) - 1;
        int hors_list = max_value +1 ;
        t_level_list *myList = create_level_list(level);

        // Création des cellules dans la liste
        for (int i = 0; i < max_value; i++) {
            insert_sorted(myList, create_level_cell(i, rand() % level + 1));
        }

        // Recherche au niveau 0
        startTimer();
        for (int i = 0; i < searches_per_level; i++) {
            search_level_0(myList, hors_list);
        }
        stopTimer();
        double time_level_0 = _timer._msecs/1000; 
        //char *time_level_0 = getTimeAsString();

        // recherche à partir du niveau le plus haut
       

        startTimer();
        for (int i = 0; i < searches_per_level; i++) {
            search_all_levels(myList, hors_list);
        }
        stopTimer();
        double all_levels = _timer._msecs/1000; 
        //char *time_all_levels = getTimeAsString();

        // Enregistrement des résultats dans le fichier log
        fprintf(log_file, "%d %07.3f %07.3f\n", level, time_level_0, all_levels);
        printf("Niveau: %d, Temps Niveau 0: %07.3f msTemps Tous Niveaux: %07.3f ms\n", level, time_level_0, all_levels);
    }

    fclose(log_file);
   
}

int main(){

    //test_niveaux_null();
           
    //niveaux_implementees();
             
    recherche_rand_val();
             
    recherche_val_inexist();
    
}