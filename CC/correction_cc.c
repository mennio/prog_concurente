#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condPro = PTHREAD_COND_INITIALIZER;
pthread_cond_t condConso = PTHREAD_COND_INITIALIZER;

typedef struct _course {
    int cid; // identifiant de la course
    int km; // longueur de la course
} course;
#define TAILLE_TAMPON 10

course Tampon[TAILLE_TAMPON];
int total;

void init() {
    for (int i = 0; i < TAILLE_TAMPON; i++) {
        Tampon[i].cid = (-1);
        Tampon[i].km = (-1);
    }
}

void *produire_course(void *arg) {
    int id = (int) arg;
    pthread_mutex_lock(&mu);
    /* pthread_mutex_lock(&mu);
     pthread_cond_wait (&condPro, &mu);*/
    printf("Producteur %d\n ", id);
    for (int i = 0; i < TAILLE_TAMPON; i++) {


        if ((Tampon[i].cid != -1) && (Tampon[i].km != -1)) {
            printf("j'att %d\n",id);
            pthread_cond_wait(&condPro, &mu);
        } else {

            pthread_cond_signal(&condConso);


            Tampon[i].cid = i;
            Tampon[i].km = (i + 1) * TAILLE_TAMPON;
            pthread_cond_signal(&condConso);

        }


    }
    pthread_mutex_unlock(&mu);
}


void *faire_course(void *arg) {
    int id = (int) arg;
    pthread_mutex_lock(&mu);
    printf("je suis consomateur %d\n", id);
    for (int i = 0; i < TAILLE_TAMPON; i++) {
        //pthread_mutex_lock(&mu);

        if ((Tampon[i].cid == -1) && (Tampon[i].km == -1)) {
           // pthread_cond_signal(&condPro);
           // pthread_cond_signal(&condPro);
            pthread_cond_signal(&condPro);
            pthread_cond_wait(&condConso, &mu);


        } else {

            printf("cette course lecture cid %d et Km %d\n", Tampon[i].cid, Tampon[i].km);
            total = total + Tampon[i].km;
            Tampon[i].cid = -1;
            Tampon[i].km = -1;


        }

        //pthread_mutex_unlock(&mu);

    }
    pthread_mutex_unlock(&mu);


    return NULL;


}

int main(int argc, char **argv) {
    int nbthreads = 7;//atoi(argv[1]);
    int nbProd = 3;//atoi((argv[3]));
    int nbCons = nbthreads - nbProd;
    //printf("HELLO\n");

    init();//initialisation du tab
    total = 0;
    pthread_t prod[nbProd];
    pthread_t conso[nbCons];
    for (int i = 0; i < nbProd; i++) {
        //boucle producteur
        pthread_create(&prod[i], NULL, produire_course, i);
    }

    for (int i = 0; i < nbCons; i++) {

        pthread_create(&conso[i], NULL, faire_course, i);
        //boucle cons
    }
    for (int i = 0; i < nbCons; i++) {

        pthread_join(conso[i], NULL);
    }
    for (int i = 0; i < nbProd; i++) {

        pthread_join(prod[i], NULL);
    }




    /*printf("HELLO\n");
    for (int i=0;i<TAILLE_TAMPON;i++){
        printf("%d cid",Tampon[i].cid);
        printf("%d km",Tampon[i].km);

    }*/
    printf("%d\n", total);
    return 0;
}