#ifndef CELL_H
#define CELL_H

typedef struct RendezVous {
    int jour;
    int mois;
    int annee;
    int heure;
    int minute;
    char objet[100]; // ou utiliser char* pour une chaîne dynamique
    // autres champs si nécessaire
} RendezVous;

#endif // CELL_H
