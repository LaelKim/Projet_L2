#include "list.h"
#include "list.c"
#include <stdio.h>



void Ex1() {
    // Ajouter des contacts pour le test
    addContact("Dupont", "Jean");
    addContact("Durand", "Marie");


    char searchInput[100];
    printf("Entrez les premières lettres du nom du contact: ");
    fgets(searchInput, 100, stdin);
    searchInput[strcspn(searchInput, "\n")] = 0; // Enlève le caractère de nouvelle ligne

    autoCompleteContact(searchInput);

}


void Ex2() {
    // Ajouter des contacts et des rendez-vous pour le test
    addContact("Dupont", "Jean");

    // Créer et ajouter des rendez-vous pour le test
    RendezVous rv1 = {10, 10, 2023, 14, 30, "Rendez-vous dentiste"};
    addRendezVousToContact(&ContactList[0], rv1); // Ajouter à Dupont Jean

    // Afficher les rendez-vous d'un contact
    afficherRendezVousDuContact("Dupont", "Jean");

}


void Ex3() {
    // Test de la création et insertion de contact
    creerEtInsererContact("Martin", "Paul");
    creerEtInsererContact("Dupont", "Jean");
    // ... ajouter d'autres tests si nécessaire

    // Afficher tous les contacts pour vérifier l'insertion
    for (int i = 0; i < contactCount; i++) {
        printf("%s %s\n", ContactList[i].nom, ContactList[i].prenom);
    }

}

void Ex4() {
    // Test de la création de rendez-vous pour un contact
    RendezVous rv = {1, 1, 2024, 10, 30, "Réunion"};
    creerRendezVousPourContact("Dupont", "Jean", rv);

    // Afficher les rendez-vous du contact pour vérifier
    afficherRendezVousDuContact("Dupont", "Jean");

}


void Ex5() {
    // Test de la suppression de rendez-vous
    creerEtInsererContact("Dupont", "Jean");
    RendezVous rv1 = {1, 1, 2024, 10, 30, "Réunion"};
    RendezVous rv2 = {2, 2, 2024, 15, 45, "Dentiste"};
    addRendezVousToContact(&ContactList[0], rv1);
    addRendezVousToContact(&ContactList[0], rv2);

    // Supprimer un rendez-vous
    supprimerRendezVous(&ContactList[0], 1, 1, 2024, 10, 30);

    // Afficher les rendez-vous restants pour vérifier
    afficherRendezVousDuContact("Dupont", "Jean");

}

void Exo6() {
    // Ajouter des contacts et des rendez-vous pour le test
    creerEtInsererContact("Dupont", "Jean");
    RendezVous rv = {1, 1, 2024, 10, 30, "Réunion"};
    addRendezVousToContact(&ContactList[0], rv);

    // Sauvegarder les rendez-vous dans un fichier
    sauvegarderRendezVous("rdv.txt");


}


void Exo7() {
    // Charger les rendez-vous à partir d'un fichier
    chargerRendezVous("rdv.txt");

    // Afficher les rendez-vous d'un contact pour vérifier
    afficherRendezVousDuContact("Dupont", "Jean");


}




int main() {
    int choix;
    char nom[50], prenom[50];
    RendezVous rv;
    double tempsInsertion;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Rechercher un contact\n");
        printf("2. Afficher les rendez-vous d'un contact\n");
        printf("3. Créer un contact\n");
        printf("4. Créer un rendez-vous pour un contact\n");
        printf("5. Supprimer un rendez-vous\n");
        printf("6. Sauvegarder les rendez-vous\n");
        printf("7. Charger les rendez-vous\n");
        printf("8. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);
        getchar(); // Pour consommer le caractère de nouvelle ligne après le nombre

        switch (choix) {
            case 1:
                Ex1();
                break;
            case 2:
                Ex2();
                break;
            case 3:
                Ex3();
                break;
            case 4:
                Ex4();
                break;
            case 5:
                Ex5();
                break;
            case 6:
                Ex6();
                break;
            case 7:
                Ex7();
                break;
            case 8:
                printf("Fin du programme.\n");
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }

    return 0;
}