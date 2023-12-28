#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char prenom[20];
    char nom[30];
    int capital;
    int historique[100];
} client;

typedef struct {
    client *val;
    struct stack_element *next;
} stack_element;

typedef struct {
    stack_element *first;
    unsigned nb_values;
} stack;


void push(stack *s, client *cli) {
    stack_element *e = malloc(sizeof(stack_element));
    if (e) {
        e->val = cli;
        e->next = s->first;
        s->first = e;
        s->nb_values++;
    }
}


client pop(stack *s){
    stack_element *e;
    client *p;
    if (s->first!=NULL){
        e=s->first;
        p=e->val;
        s->first=e->next;
        s->nb_values--;
        free(e);
        return (*p);
    }
}




void menu() {
    int rep;
    printf("1-gestion des comptes\n");
    printf("2-gestion des operations\n");
    printf("3-quitter le programme\n");
    printf("Tapez le num correspond a loption que vous avez choisi=\n");

    do {
        scanf("%d", &rep);
    } while (rep != 1 && rep != 2 && rep != 3);

    switch (rep) {
        case 1:
            gestion_comp();
            break;
        case 2:
            // gestion_oper();
            break;
        case 3:
            printf("au revoir\n");
            break;
    }
}

void gestion_comp() {
    int rep;
    printf("1-creer un  nouveau compte\n");
    printf("2-mise a jour d info d un compte existant \n");
    printf("3-supprimer un compte existant\n");
    printf("4-afficher les details d un compte existant\n");
    printf("5-afficher la liste des clients\n");
    printf("6-retour au menu principale\n");
    printf("7-quitter le programme\n");
    printf("Tapez le num correspond a loption que vous avez choisi=\n");

    do {
        scanf("%d", &rep);
    } while (rep < 1 || rep > 7);

    switch (rep) {
        case 1:
            cree_compte();
            break;
       case 2:
            maj_compte();
            break

        case 3:{
            supp_compte();

        }
        case 4:{
         aff_compte();
         break;

        }

        case 6:{
         menu();
        }

        case 7:
            printf("au revoir!!\n");
            break;
    }
}

void cree_compte() {
    FILE *file = fopen("donnee.txt", "a");

    if (file != NULL) {
        client nvcli;
        printf("ecrire l id de nouveau client\n");
        scanf("%d", &nvcli.id);
        printf("ecrire le nom de nouveau client\n");
        scanf("%s", &nvcli.nom);
        printf("ecrire le prenom de nouveau client\n");
        scanf("%s", &nvcli.prenom);

        printf("ecrire le capital de nouveau client\n");
        scanf("%d", &nvcli.capital);

        for (int i = 0; i < 100; i++) {
            nvcli.historique[i] = 0;
        }

        fwrite(&nvcli, sizeof(client), 1, file);
        fclose(file);
    }
    printf("client ajouté avec succés\n");
    printf("--------------------------------------------\n");
    return;

}


void maj_compte() {
    stack s;
    s.first = NULL;
    s.nb_values = 0;

    client nv_client;
    printf("ecrire l id de client a modifier ces donnees\n");
    scanf("%d", &nv_client.id);
    printf("ecrire le nouveau nom\n");
    scanf("%s", nv_client.nom);
    printf("ecrire le nouveau prenom\n");
    scanf("%s", nv_client.prenom);
    printf("ecrire le nouveau capital\n");
    scanf("%d", &nv_client.capital);

    FILE *file = fopen("donnee.txt", "r");
    if (file != NULL) {
        client cl;

        while (fread(&cl, sizeof(client), 1, file) == 1) {
            if (cl.id != nv_client.id) {
                push(&s, &cl);
            }
        }

        fclose(file);
    }

    push(&s, &nv_client);

    remove("donnee.txt");
    FILE *f1 = fopen("data.txt", "a");
    stack_element *e, *e_next;

    if (f1 != NULL) {
        for (e = s.first; e; e = e_next) {
            fwrite(e->val, sizeof(client), 1, f1);
            e_next = e->next;
        }

        fclose(f1);
    }


    rename("data.txt", "donnee.txt");


    while (s.first != NULL) {
        stack_element *temp = s.first;
        s.first = s.first->next;
        free(temp);
    }
}



void supp_compte(){
    stack *s;
    client *cl;
    client supp_client;
    printf("ecrire l id de client a supprimer\n");
    scanf("%d",&supp_client.id);
    FILE *file=fopen("donnee.txt",'r');
    if (file=!NULL){
        while (fread(cl,sizeof(client),1,file)){
                if ((*cl).id!=supp_client.id){
                    push(s,cl);
                }

        }
    }

    fclose(file);
    remove("donnee.txt");
    FILE *f1=fopen("data.txt",'a');
    stack_element *e,*e_next;


    if (f1!=NULL){
            for (e = s->first; e; e = e_next){
                    fwrite(&(s->first->val),sizeof(client),1,f1);
                    e_next=e->next;

            }



       }

    fclose("data.txt");
    rename("data.txt","donnee.txt");
}











void aff_compte() {
    int id;
    printf("ecrire l id de client a afficher\n");
    scanf("%d", &id);

    FILE *file = fopen("donnee.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    client aff_client;  // Modification : Utilisation d'un objet client au lieu d'un pointeur
    int verif = 1;

    while (fread(&aff_client, sizeof(client), 1, file) && verif) {
        if (aff_client.id == id) {
            printf("son prenom: %s\n", aff_client.prenom);
            printf("son nom: %s\n", aff_client.nom);
            printf("son capital: %d\n", aff_client.capital);
            verif = 0;
        }
    }

    fclose(file);

    if (verif == 1) {
        printf("Id introuvable !\n");
    }
}


///////////////////////////////////////////////////////////////////////
void gestion_oper() {
    int rep;
    printf("1-gérer les transactions bancaires\n");
    printf("2-afficher les transactions bancaires d'un compte existant\n");
    printf("3-retour au menu principal\n");
    printf("Tapez le num correspond a l'option que vous avez choisie\n");

    do {
        scanf("%d", &rep);
    } while (rep != 1 && rep != 2 && rep != 3);

    switch (rep) {
        case 1:
            gerer_transaction();
            break;
        case 2:
            affiche_transaction();
            break;
        case 3:
            menu();
            break;
    }
}



void gerer_transaction(){
    int rep;
    printf("1-versement d argent\n");
    printf("2-retrait d argent ");
    printf("Tapez le num correspond a loption que vous avez choisi=\n");
    do{
          scanf("%d",&rep);
     }while(rep!=1&&rep!=2);
    switch (rep){
     case 1:{
         versement();
     }
     case 2:{
         effectuer_retrait();

     }
}


void effectuer_retrait() {
    int m, id, i = 0;
    int verif = 1;
    printf("ecrire le montant a prendre\n");
    scanf("%d", &m);
    printf("donner l'ID du client auquel il va faire son retrait ");
    scanf("%d", &id);

    stack s;  // Allocation de la mémoire pour la pile
    s.first = NULL;
    s.nb_values = 0;

    FILE *file = fopen("donnee.txt", "r");
    if (file != NULL) {
        client cl;

        while (fread(&cl, sizeof(client), 1, file) == 1) {
            if (cl.id != id) {
                push(&s, &cl);
            } else {
                if (cl.capital > m) {
                    cl.capital -= m;
                    while (i < 100 && verif) {
                        if (cl.historique[i] == 0) {
                            cl.historique[i] = -m;
                            verif = 0;
                        } else {
                            i++;
                        }
                    }
                    push(&s, &cl);
                } else {
                    push(&s, &cl);
                }
            }
        }

        fclose(file);
    }

    remove("donnee.txt");

    FILE *f1 = fopen("data.txt", "a");
    stack_element *e, *e_next;

    if (f1 != NULL) {
        for (e = s.first; e; e = e_next) {
            fwrite(e->val, sizeof(client), 1, f1);
            e_next = e->next;
        }

        fclose(f1);
    }


    fclose(f1);

    rename("data.txt", "donnee.txt");


    while (s.first != NULL) {
        stack_element *temp = s.first;
        s.first = s.first->next;
        free(temp);
    }
}



void vesrsement(){
    int m,id,i=0 ;
    int verif=1;
    printf("ecrire le montant a prendre\n");
    scanf("%d",&m);
    printf("donner l ID de client a laquelle il va faire son retrait ");
    scanf("%d",&id);
    stack *s;
    client *cl;
    FILE *file=fopen("donnee.txt",'r');
    if (file=!NULL){
        while (fread(cl,sizeof(client),1,file)){
                if ((*cl).id!=id){
                    push(s,cl);
                }
                else {
                         (*cl).capital+=m;
                          while (i<100&&verif){
                                if (cl->historique[i]==0){
                                    cl->historique[i]=m;
                                    verif=0;
                                }
                                else{i++;}
                            }
                            push(s,cl);


                }


                }
                }



    fclose(file);
    remove("donnee.txt");
    FILE *f1=fopen("data.txt",'a');
    stack_element *e,*e_next;


    if (f1!=NULL){
            for (e = s->first; e; e = e_next){
                    fwrite(&(s->first->val),sizeof(client),1,f1);
                    e_next=e->next;
            }
      }

    fclose("data.txt");
    rename("data.txt","donnee.txt");
}

void affiche_transaction(){
    int id;
    int i=0;
    printf("ecrire l id de client a supprimer\n");
    scanf("%d",&id);
    FILE *file=fopen("donnee.txt",'r');
    client *aff_client;
    int verif=1;


    while (fread(aff_client,sizeof(client),1,file)&&verif){
        if (aff_client->id==id){
            while (i<100){
                if (aff_client->historique[i]!=0){
                    if (aff_client->historique[i]>0){
                        printf("vous avez verser %d",abs(aff_client->historique[i]));
                    }
                    else{
                        printf("vous avez pris %d",abs(aff_client->historique[i]));

                    }
                }
            }
            verif =0;
        }
    }
    if (verif==1){
        printf("id introuvable !");
    }
}


int main() {
    menu();
    return 0;
}
