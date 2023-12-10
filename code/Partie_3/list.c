#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CONTACTS 1000
Contact ContactList[MAX_CONTACTS];
int contactCount = 0;

void addContact(const char *nom, const char *prenom) {
    if (contactCount < MAX_CONTACTS) {
        ContactList[contactCount].nom = strdup(nom);
        ContactList[contactCount].prenom = strdup(prenom);
        contactCount++;
    }
}

void autoCompleteContact(char *input) {
    int length = strlen(input);
    if (length < 3) {
        printf("Continuez à entrer des caractères...\n");
        return;
    }

    printf("Suggestions:\n");
    bool found = false;
    for (int i = 0; i < contactCount; i++) {
        if (strncmp(ContactList[i].nom, input, length) == 0) {
            printf("%s %s\n", ContactList[i].nom, ContactList[i].prenom);
            found = true;
        }
    }

    if (!found) {
        printf("Aucun contact trouvé.\n");
    }
}

void addRendezVousToContact(Contact *contact, RendezVous rv) {
    if (contact->nombreRendezVous < 10) { // 10 est le nombre de rendez-vous par contact(on pourrais prendre n'inporte quel chiffre)
        contact->rendezVous[contact->nombreRendezVous++] = rv;
    }
}

void afficherRendezVousDuContact(const char *nom, const char *prenom) {
    for (int i = 0; i < contactCount; i++) {
        if (strcmp(ContactList[i].nom, nom) == 0 && strcmp(ContactList[i].prenom, prenom) == 0) {
            printf("Rendez-vous pour %s %s:\n", nom, prenom);
            for (int j = 0; j < ContactList[i].nombreRendezVous; j++) {
                RendezVous rv = ContactList[i].rendezVous[j];
                printf("%02d/%02d/%04d à %02d:%02d - %s\n", rv.jour, rv.mois, rv.annee, rv.heure, rv.minute, rv.objet);
            }
            return;
        }
    }
    printf("Contact non trouvé.\n");
}


void creerEtInsererContact(const char *nom, const char *prenom) {
    if (contactCount >= MAX_CONTACTS) {
        printf("Limite de contacts atteinte.\n");
        return;
    }

    // Création du nouveau contact
    Contact nouveauContact;
    nouveauContact.nom = strdup(nom);
    nouveauContact.prenom = strdup(prenom);
    nouveauContact.nombreRendezVous = 0;

    // Trouver l'emplacement d'insertion
    int i = 0;
    while (i < contactCount && strcmp(ContactList[i].nom, nom) < 0) {
        i++;
    }

    // Décaler les contacts pour faire de la place
    for (int j = contactCount; j > i; j--) {
        ContactList[j] = ContactList[j - 1];
    }

    // Insérer le nouveau contact
    ContactList[i] = nouveauContact;
    contactCount++;
}


void creerRendezVousPourContact(const char *nom, const char *prenom, RendezVous rv) {
    for (int i = 0; i < contactCount; i++) {
        if (strcmp(ContactList[i].nom, nom) == 0 && strcmp(ContactList[i].prenom, prenom) == 0) {
            addRendezVousToContact(&ContactList[i], rv);
            return;
        }
    }

    // Si le contact n'existe pas, le créer et ajouter le rendez-vous
    creerEtInsererContact(nom, prenom);
    addRendezVousToContact(&ContactList[contactCount - 1], rv);
}

void supprimerRendezVous(Contact *contact, int jour, int mois, int annee, int heure, int minute) {
    for (int i = 0; i < contact->nombreRendezVous; i++) {
        RendezVous rv = contact->rendezVous[i];
        if (rv.jour == jour && rv.mois == mois && rv.annee == annee && rv.heure == heure && rv.minute == minute) {
            // Décalage des rendez-vous suivants
            for (int j = i; j < contact->nombreRendezVous - 1; j++) {
                contact->rendezVous[j] = contact->rendezVous[j + 1];
            }
            contact->nombreRendezVous--;
            return;
        }
    }
    printf("Rendez-vous non trouvé.\n");
}



void sauvegarderRendezVous(const char *nomFichier) {
    FILE *fichier = fopen("rdv.txt", "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    for (int i = 0; i < contactCount; i++) {
        Contact contact = ContactList[i];
        for (int j = 0; j < contact.nombreRendezVous; j++) {
            RendezVous rv = contact.rendezVous[j];
            fprintf(fichier, "%s %s - %02d/%02d/%04d %02d:%02d - %s\n", 
                    contact.nom, contact.prenom, 
                    rv.jour, rv.mois, rv.annee, rv.heure, rv.minute, rv.objet);
        }
    }

    fclose(fichier);
}

void chargerRendezVous(const char *nomFichier) {
    FILE *fichier = fopen("rdv.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    char nom[50], prenom[50], objet[100];
    int jour, mois, annee, heure, minute;
    while (fscanf(fichier, "%s %s - %d/%d/%d %d:%d - %[^\n]", 
                  nom, prenom, &jour, &mois, &annee, &heure, &minute, objet) == 8) {
        RendezVous rv = {jour, mois, annee, heure, minute};
        strcpy(rv.objet, objet);
        creerRendezVousPourContact(nom, prenom, rv);
    }

    fclose(fichier);
}

