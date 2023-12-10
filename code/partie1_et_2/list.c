#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "list.h"

//Parti1

t_level_list *create_level_list(int max_levels) {
    // Allocation de mémoire pour la structure de la liste à niveaux
    t_level_list *list = malloc(sizeof(t_level_list));
    // Définition du nombre maximal de niveaux de la liste
    list->max_levels = max_levels;
    // Création de la cellule de tête avec le niveau maximal
    list->head = create_level_cell(-1, max_levels);
    // Retour de la liste à niveaux nouvellement créée
    return list;
}

void insert_cell_at_head(t_level_list *list, t_cell *new_cell) {
    // Parcours des niveaux de la nouvelle cellule
    for (int i = 0; i < new_cell->levels; i++) {
        // Vérification si le niveau est inférieur au maximum de la liste
        if (i < list->max_levels) {
            // Insertion de la cellule en tête au niveau actuel
            new_cell->next[i] = list->head->next[i];
            list->head->next[i] = new_cell;
        }
    }
}
void display_cells_at_level(t_level_list *list, int level) {
   // Affichage des cellules du niveau donné
    t_cell *current = list->head->next[level];
    printf("Cellules au niveau %d: ", level);

    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next[level];
    }

    printf("\n");
}


//Affichage simple
void display_all_levels(t_level_list *list) {
    // Vérification de la validité de la liste
    if (list == NULL) {
        printf("Liste non valide.\n");
        return;
    }
    // Affichage des cellules pour chaque niveau
    for (int level = 0; level < list->max_levels; level++) {
        t_cell *current = list->head->next[level];
        printf("[list head_%d @-]", level);

        while (current != NULL) {
            printf("-->[%d|@]", current->value);
            current = current->next[level];
        }

        printf("-->NULL\n");
    }
}

//Affichage alignee

void display_all_levels_aligned(t_level_list *list) {
    // Vérification de la validité de la liste
    if (list == NULL) {
        printf("Liste non valide.\n");
        return;
    }
    // Calcul du nombre total de cellules au niveau 0
    int total_cells = 0;
    t_cell *current = list->head->next[0];
    while (current != NULL) {
        total_cells++;
        current = current->next[0];
    }

    // Affichage des cellules pour chaque niveau avec alignement
    for (int level = 0; level < list->max_levels; level++) {
        current = list->head->next[level];
        printf("[list head_%d @-]", level);

      

        t_cell *current_level_0 = list->head->next[0];
        for (int i = 0; i < total_cells; i++) {
            if (current != NULL && current_level_0 != NULL && current->value == current_level_0->value) {
                printf("-->[ %d|@- ]", current->value);
                current = current->next[level];
                current_level_0 = current_level_0->next[0];
            } else {
                printf("------------");
                if (current_level_0 != NULL) {
                    current_level_0 = current_level_0->next[0];
                }
            }
        }
        printf("-->NULL\n");
    }
}



void insert_sorted(t_level_list *list, t_cell *new_cell) {
    // Vérification de la validité de la liste et de la nouvelle cellule
    if (list == NULL || new_cell == NULL) {
        return; 
    }
    // Initialisation du tableau pour stocker les cellules précédentes
    t_cell *update[list->max_levels];
    t_cell *current = list->head;

    // Recherche de la position d'insertion pour chaque niveau
    for (int level = list->max_levels - 1; level >= 0; level--) {
        while (current->next[level] != NULL && current->next[level]->value < new_cell->value) {
            current = current->next[level];
        }
        update[level] = current;
    }
    // Insertion de la nouvelle cellule à chaque niveau concerné
    for (int level = 0; level < new_cell->levels; level++) {
        new_cell->next[level] = update[level]->next[level];
        update[level]->next[level] = new_cell;
    }
}




//Partie 2


t_cell *search_level_0(t_level_list *list, int value) {
    // Commence au début de la liste, qui est au niveau 0
    t_cell *current = list->head;  
    // Parcourt la liste au niveau 0
    while (current != NULL) {
        // Vérifie si la cellule courante a la valeur recherchée
        if (current->value == value) {
            return current; 
        }
        // Passe à la cellule suivante au niveau 0
        current = current->next[0];
    }

    return NULL;  
}
/*
t_cell* search_all_levels_from_head(t_level_list *list, int value) {
    // Commence depuis le niveau le plus élevé de la liste
    int level = list->max_levels - 1;
    t_cell *next = list->head->next[level];
    // Itère en descendant les niveaux
    while (level >= 0) {
        // Parcourt vers l'avant au niveau courant
        while (next != NULL && next->value  < value) {
            next = next->next[level];
        }
        // Vérifie si la cellule au niveau courant a la valeur recherchée
        if (next != NULL && next->value == value) {
            return next;  
        }
        // Descend d'un niveau pour la prochaine itération
        level--;
        if (level >= 0) {
            next = list->head->next[level];
        }
    }

    return NULL; 
}
*/
t_cell* search_all_levels(t_level_list *list, int value) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    t_cell *current = list->head;
    int level = list->max_levels - 1;
    // Parcourt tous les niveaux de la liste de saut
    while (level >= 0) {
        // Parcourt le niveau courant jusqu'à trouver un élément plus grand ou égal à la valeur recherchée
        while (current->next[level] != NULL && current->next[level]->value < value) {
            current = current->next[level];
        }
        // Vérifie si la valeur recherchée est trouvée au niveau courant
        if (current->next[level] != NULL && current->next[level]->value == value) {
            return current->next[level];  // Retourne l'élément trouvé
        }
        // Descend au niveau inférieur
        level--;
    }

    return NULL; // Retourne NULL si la valeur n'est pas trouvée
}
