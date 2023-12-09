#include "cell.h"
#include <stdlib.h>

//1. Creer une cellule
t_cell *create_level_cell(int value, int levels) {

    t_cell *cell = malloc(sizeof(t_cell));
    //On donne sa valeur et le nombre de niveaux 
    cell->value = value;   
    cell->levels = levels;
    // Allocation du tableau de pointeurs pour les niveaux
    cell->next = malloc(sizeof(t_cell*) * levels);
    // Initialisation des pointeurs à NULL
    for (int i = 0; i < levels; i++) {
        cell->next[i] = NULL;
    }

    return cell;
}