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
}*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct _course {
	int cid;
	int km;
} course;


int kilometrage_total;
pthread_mutex_t lock_kt;

 
void *faire_course(void* arg) {
	course *une_course = (course *)arg;
	int km_total;
	printf("Acquisition de la course : %d\n", une_course->cid);
	pthread_mutex_lock(&lock_kt);
	kilometrage_total += une_course->km;
	km_total = kilometrage_total;
	pthread_mutex_unlock(&lock_kt);
	printf("Kilometrage total mis à jour après course %d : %d\n", une_course->cid, km_total);
	pthread_exit(NULL);
}


int main(int argc, char**argv) { // arg utilisateur
	int ptc;
	int nbCourses = atoi(argv[1]);
	printf("Nb de courses : %d\n", nbCourses);
	pthread_t threads[nbCourses];
	course courses[nbCourses];
	kilometrage_total = 0;
	pthread_mutex_init(&lock_kt, NULL);
	for (int i = 0; i < nbCourses; ++i) {
		courses[i].cid = i;
		courses[i].km = (i + nbCourses) * nbCourses;
		if ((ptc = pthread_create(&threads[i], NULL, faire_course, &courses[i]))) {
			fprintf(stderr, "erreur pthread_create : %d\n", ptc);
			return EXIT_FAILURE;
		}
	}
	for (int i = 0; i < nbCourses; ++i) {
		pthread_join(threads[i], NULL);
	}

	printf("\nKilometrage total à la fin de toutes les courses : %d\n", kilometrage_total);

	return EXIT_SUCCESS;
} 

