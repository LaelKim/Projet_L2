#ifndef LIST_H
#define LIST_H

#include "cell.h"


typedef struct Contact {
    char *nom;
    char *prenom;
    RendezVous rendezVous[10];
    int nombreRendezVous;
    // autres champs si nécessaire
} Contact;

void addContact(const char *nom, const char *prenom);
void addRendezVousToContact(Contact *contact, RendezVous rv);
void afficherRendezVousDuContact(const char *nom, const char *prenom);
void autoCompleteContact(char *input);
void creerEtInsererContact(const char *nom, const char *prenom);
void creerRendezVousPourContact(const char *nom, const char *prenom, RendezVous rv);
void supprimerRendezVous(Contact *contact, int jour, int mois, int annee, int heure, int minute);
void sauvegarderRendezVous(const char *nomFichier);
void chargerRendezVous(const char *nomFichier);




#endif // LIST_H
