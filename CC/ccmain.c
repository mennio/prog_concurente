#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t value = PTHREAD_MUTEX_INITIALIZER;
int KM_TOTAL;

typedef struct _course {
    int cid; // identifiant de la course
    int km; // longueur de la course
} Course;

void faire_course(Course* c){
    pthread_mutex_lock(&value);
    KM_TOTAL += c -> km;
    printf(" km : %d \n", KM_TOTAL);
    pthread_mutex_unlock(&value);
}

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

int main (int argc, char **argv){
    int nbCourse = atoi(argv[1]); // comme scanf  
    printf("test scanf : %d \n", nbCourse);
    Course tabCourse[nbCourse];
    pthread_t tabPthread[nbCourse];
    for(int i=0; i<= nbCourse; ++i){
        tabCourse[i].cid = i;
        tabCourse[i].km = (i+nbCourse) * nbCourse;
        //tabPthread[nbCourse] = cree_tache(faire_course, &tabCourse[i]);
        pthread_create(&tabPthread[i], NULL,faire_course,&tabCourse[i]);
    }
    
    KM_TOTAL =0;
    return 0;
}