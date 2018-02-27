#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ddn {
    int j;
    int m;
    int a;
}ddn;

typedef struct Cid {
    int NumCarte;
    char nom[20];
    char prenom[20];
    char sexe;
    ddn naissance;
    char ville[20];
} Cid;
//PROTOTYPE
void Ecriture();
void Lecture();
void Saisie(Cid*IDcarte);
void Menu();

//----------Main----------//
int main(){
    Menu();
    return 0;
}
//----------Menu principal----------//
void Menu(Cid IDcarte, int resultat){
    int *ptresult;
    int varaide=0;
    ptresult=&resultat;
    do{
        puts("Que voulez vous faire ?");
        puts("1 : Suppression + Ecriture dans le fichier");
        puts("2 : Ecrire a la suite du fichier");
        puts("3 : Lire les cartes sur le fichier");
        puts("4 : Quitter");
        scanf ("%d",ptresult);
        switch (*ptresult)
        {                               //Switch de redirection vers les procedures
            case 1 :
                Saisie(&IDcarte);
                Ecriture(&IDcarte);
                break;
            case 2 :
                Saisie(&IDcarte);
                Ecriture(&IDcarte);
                break;
            case 3 :
                Lecture();
                break;
            case 4 :
                varaide=1;
                puts("Bye !");
                break;
        }
    }while(varaide!=1);
}
//----------Procedure de Saisie----------//
void Saisie (Cid *IDcarte)
{
    printf ("Saisissez numero : \n");       //Saisie des infos de la carte
    scanf ("%d",&IDcarte->NumCarte);
    printf ("Nom : \n");
    scanf ("%s",IDcarte->nom);
    fflush(stdin);
    printf ("Prenom : \n");
    scanf ("%s",IDcarte->prenom);
    fflush(stdin);
    do{
        printf("Date de naissance : JJ MM AAAA : \n");
        scanf ("%d%d%d",&IDcarte->naissance.j,&IDcarte->naissance.m,&IDcarte->naissance.a);
    }while(!((IDcarte->naissance.j >=1 && IDcarte->naissance.j <= 31) &&            //Test des input pour la ddn
        (IDcarte->naissance.m >=1 && IDcarte->naissance.m <= 12) &&
        (IDcarte->naissance.a >= 1900 && IDcarte->naissance.a <= 2019)));
    printf("Ville : \n");
    scanf("%s",IDcarte->ville);
    fflush(stdin);
}
//----------Mode Ecriture----------//
void Ecriture (Cid *IDCarte, int resultat)
{
    FILE *MonFichier;
    if (resultat==1) {
        MonFichier = fopen("MonFichier.bin", "wb"); //Réecriture (suppression)
    }else{
        MonFichier = fopen("MonFichier.bin", "ab"); //Ecriture à la suite
    }
    char buffer[sizeof(Cid)];                       //Set du buffer
    memcpy(buffer, &(*IDCarte), sizeof(Cid));

    if (MonFichier != NULL)
    {
        fwrite(buffer, sizeof(Cid),1, MonFichier);   //Ecriture dans le fichier grace au buffer
        fclose(MonFichier);
    }
    else{
        printf ("Echec de l'ouverture");
    }
}
//----------Mode lecture----------//
void Lecture()
{
    FILE *MonFichier;
    Cid *buffer;

    MonFichier = fopen("MonFichier.bin", "rb");
    if (MonFichier == NULL)                             //Verif de l'existence du fichier
    {
        fputs ("Impossible de lire MonFichier.bin", stderr);
        exit(1);
    }
    rewind(MonFichier);                                 //On replace le curseur au début du fichier
    buffer = malloc(sizeof(Cid));                       //Set de la memoire tampon
    if (buffer == NULL) {                               //Test de la size du set de la memoire tampon
        fputs ("Probleme de memoire",stderr);
        exit(2);
    }
    while(fread(buffer, sizeof(Cid), 1, MonFichier) == 1){      //Boucle d'écriture des structures
        printf("Num Carte: %d\n", buffer->NumCarte);
        printf("Nom: %s\n", buffer->nom);
        printf("Prenom: %s\n", buffer->prenom);
        printf("Naissance: %d/%d/%d\n", buffer->naissance.j, buffer->naissance.m, buffer->naissance.a);
        printf("Ville: %s\n\n\n", buffer->ville);
    }
    fclose (MonFichier);                //Fermeture du fichier
    free (buffer);                      //Free la memoire du buffer
}
