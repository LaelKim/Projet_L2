#ifndef CELL_H
#define CELL_H

typedef struct s_cell
{   
    int value;                                                                              // Valeur stockée dans la cellule
    int levels;                                                                             // Nombre de niveaux de la cellule
    struct s_cell **next;                                                                   // Tableau de pointeurs vers les cellules suivantes à différents niveaux
}t_cell;


t_cell *create_level_cell(int value, int levels);

#endif