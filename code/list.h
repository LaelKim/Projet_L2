#ifndef LEVEL_LIST_H
#define LEVEL_LIST_H

#include "cell.h"

typedef struct s_level_list {
    t_cell *head;
    int max_levels;
} t_level_list;

//Partie 1

t_level_list *create_level_list(int max_levels);

void insert_cell_at_head(t_level_list *list, t_cell *new_cell);

void display_cells_at_level(t_level_list *list, int level);

void display_all_levels(t_level_list *list);

void display_all_levels_aligned(t_level_list *list);

void insert_sorted(t_level_list *list, t_cell *new_cell);



#endif