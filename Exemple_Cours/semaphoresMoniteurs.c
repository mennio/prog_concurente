//Coordination de 2 tâches par un verrou
/*#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static pthread_mutex_t sync = PTHREAD_MUTEX_INITIALIZER;
void *T1(void *arg) {
sleep(1); // I_1
printf("T1: fini sleep\n");
pthread_mutex_unlock(&sync);
return NULL;
} 
void *T2(void *arg) {
printf("T2: avant pthread_mutex_lock\n");
pthread_mutex_lock(&sync);
printf("T2: apres pthread_mutex_lock\n"); // I_2
return NULL;
} 
int main(void) {
pthread_t tache1, tache2;
pthread_mutex_lock(&sync);
if (pthread_create(&tache1,NULL,T1,NULL) == 0) {
if (pthread_create(&tache2,NULL,T2, NULL) == 0) {
pthread_join(tache1,NULL);
pthread_join(tache2,NULL);
return EXIT_SUCCESS;
}
}
return EXIT_FAILURE;
} */




//Rendez-vous entre 2 tâches
/*
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static pthread_mutex_t arriveA = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t arriveB = PTHREAD_MUTEX_INITIALIZER;
void *TacheA(void *arg) {
printf("a1");
pthread_mutex_lock(&arriveB);
pthread_mutex_unlock(&arriveA);
printf("a2");
return NULL;
} 
void *TacheB(void *arg) {
printf("b1");
pthread_mutex_unlock(&arriveB);
pthread_mutex_lock(&arriveA);
printf("b2");
return NULL;
} 
int main(void) {
pthread_t tacheA, tacheB;
pthread_mutex_lock(&arriveA);
pthread_mutex_lock(&arriveB);
if (pthread_create(&tacheA,NULL,TacheA,NULL) == 0) {
if (pthread_create(&tacheB,NULL,TacheB,NULL) == 0) {
pthread_join(tacheA,NULL);
pthread_join(tacheB,NULL);
return EXIT_SUCCESS;
}
}
return EXIT_FAILURE;
} */

/*
typedef int ValeurRegistre[TAILLE_REGISTRE]; //création et initialisation d'un mutex
pthread_mutex_t monMutex = PTHREAD_MUTEX_INITIALIZER; 
ValeurRegistre LeRegistre;
void f(void){
    int i, j;
    for(j=0; j < 1000000; j++){
        for(i=0; i<TAILLE_REGISTRE; i++){
            pthread_mutex_lock( &monMutex ); // on verouille le mutex
            LeRegistre[i] ++; // section critique atomique
            pthread_mutex_unlock( &monMutex ); //on deverouille le mutex
        }
    }
}

