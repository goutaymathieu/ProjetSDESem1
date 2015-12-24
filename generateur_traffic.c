#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include"boite_aux_lettres_type.h"

int periode =1;
int id;

int rand_a_b(int a, int b);

void main(){
    if ((id=msgget(1, 0666))==-1){
        printf("Pas de file de message\n");
        exit(1);
    }
    while(1){
        long depuis = rand_a_b(1,5);
        periode=rand_a_b(1,4);
        sleep(periode);
        int vers = rand_a_b(0,2);
        printf("Générateur_traffic.c : une  voiture vient d'arriver sur la route %ld et veut tourner à gauche? %d\n", depuis, vers);
        MESSAGE new;
        new.mtype= depuis;   
        new.vers=vers;
        int envoye;
        envoye = msgsnd(id, &new, sizeof(MESSAGE), 0);
        if(envoye==-1){
            printf("Erreur d'envoi d'une voiture normale\n");
        }


    }
}

int rand_a_b(int a, int b){
    srand(time(NULL));
    return rand()%(b-a) +a;
}





