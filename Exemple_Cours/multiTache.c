#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

/*La fonction pthread_join () attend que le thread spécifié par thread se termine. Si ce thread s'est déjà terminé, alors
pthread_join () retourne immédiatement. Le thread spécifié par thread doit être joignable.*/



//fonction affiche
    void *affCar(void *arg){
        char c;
        c = * (char *)arg;
        while(1){
            putchar(c);
        }
    }

    void *affCar2(void *arg){
        char c;
        int i;
        c = * (char *)arg;
        for (i=0; i<1000; i++){
            putchar( c );
        }
    }

//fonction permettant de creer une tache
pthread_t cree_tache(void * (*start_routine)(void *), void * arg){
    pthread_t id;
    int erreur;
    erreur = pthread_create( &id, NULL, start_routine, arg);
    if (erreur != 0){
    perror( "Echec creation de tâche Posix" );
    exit(-1);
    }
    return id;
}

//main
int main (void){
/***********************************************************************************************************************************************************************/
    /*//déclaration pointeur variable affiche
    char *leCar;

    //déclaration de deux taches
    pthread_t tache_Posix_B;
    pthread_t tache_Posix_C;

    //qui permettent à la tâche Posix créée d'avoir un espace propre pour désigner lecaractère passé en paramètre; il se pourrait sinon que le créateur modifie la valeur de
    //ce caractère avant que la tâche créée n'ait eu le temps de sauvegarder la valeur
    //initiale.
    leCar = (char*) malloc(1*sizeof(char)); *leCar = 'B';

    //création de la tache mais on peut faire appel à une fonction de création
    pthread_create( &tache_Posix_B, NULL, affCar, (void*) leCar);
    leCar = (char*) malloc(1*sizeof(char)); *leCar = 'C';
    pthread_create( &tache_Posix_C, NULL, affCar, (void*) leCar);

    //boucle pour afficher les caractère
    while(1){
        putchar('z');
    }*/

/***********************************************************************************************************************************************************************/
        /* Exemple de terminaison non controlé car les processus sont en aléatoire il manque pthread_join
        char *leCar; int i;
        pthread_t tache_Posix_B;
        pthread_t tache_Posix_C;
        leCar = (char*) malloc(1*sizeof(char)); *leCar = 'B';
        tache_Posix_B = cree_tache( affCar2, (void*) leCar);
        leCar = (char*) malloc(1*sizeof(char)); *leCar = 'C';
        tache_Posix_C = cree_tache( affCar2, (void*) leCar);
        for (i=0; i<1000; i++){
            putchar('z');
        }*/
/***********************************************************************************************************************************************************************/
        /*Exemple de terminaison controlé car il y a pthread_join
        char *leCar; int i;
        pthread_t tache_Posix_B;
        pthread_t tache_Posix_C;
        leCar = (char*) malloc(1*sizeof(char)); *leCar = 'B';
        tache_Posix_B = cree_tache( affCar2, (void*) leCar);
        leCar = (char*) malloc(1*sizeof(char)); *leCar = 'C';
        tache_Posix_C = cree_tache( affCar2, (void*) leCar);
        for (i=0; i<1000; i++){
            putchar('z');
        }
        pthread_join( tache_Posix_B, NULL);
        pthread_join( tache_Posix_C, NULL);*/
/***********************************************************************************************************************************************************************/

    return 0;
}