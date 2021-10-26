#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


void *afficheVers(void *arg) {
    const char *vers;
    vers = (char *) arg;
    puts(vers);
    return 0;
}

pthread_t cree_tache(void *(*start_routine)(void *), void *arg) {
    pthread_t id;
    int erreur;
    erreur = pthread_create(&id, NULL, start_routine, arg);
    if (erreur != 0) {
        perror("Echec creation de tâche Posix");
        exit(-1);
    }
    return id;
}

int main() {
    const char *const l1 = "Souvent, pour s’amuser, les hommes d’équipage";
    const char *const l2 = "Prennent des goélands, vastes oiseaux des mers,";
    const char *const l3 = "Qui suivent, indolents compagnons de voyage,";
    const char *const l4 = "Le navire glissant sur les gouffres amers.";

    pthread_t th1;
    pthread_t th2;
    pthread_t th3;
    pthread_t th4;

    th1 = cree_tache(afficheVers, (void *) l1);
    pthread_join(th1, NULL);

    th2 = cree_tache(afficheVers, (void *) l2);
    pthread_join(th2, NULL);

    th3 = cree_tache(afficheVers, (void *) l3);
    pthread_join(th3, NULL);

    th4 = cree_tache(afficheVers, (void *) l4);
    pthread_join(th4, NULL);

   /* while (1) { ;
    }*/
}
