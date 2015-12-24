#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include"boite_aux_lettres_type.h"

#define periode 3

int rand_a_b(int a, int b);

void main(){
  int id;
  key_t cle=1;
  if ((id=msgget(cle, 0666))==-1){
    printf("je ne me suis pas attaché!\n");
    exit(1);
    }else{
      printf("je me suis bien attaché\n");
    }

  while(1){
    long depuis = (long)rand_a_b(1,5);
    sleep(periode);
    int vers = (int)rand_a_b(0,2);
    printf("Générateur_traffic.c : une  voiture vient d'arriver sur la route %ld et veut aller sur la  route %d\n", depuis, vers);

   Message message;
   message.mtype= depuis;   
   message.tGauche=vers;

   int envoye;
   envoye = msgsnd(id, &message, sizeof(int), 0);
   if(envoye==-1){
     printf("Erreur d'envoi d'une voiture normale, je me tue! (il faudra me tuer)\n");
  //   exit(-1);
   }
  } 
   /*
Message message
message.mtype = 2;
message.tGauche =1
int envoye = msgsnd(id, &message, sizeof(int), 0);
if(envoye== -1) printf("le message n'a pas été envoyé\n");
 */ 
}

/*int tirerVers (int depuis){
  int vers;
  do{
    vers=rand_a_b(0,4);
  }while(vers==depuis);
  return vers;
}
*/

int rand_a_b(int a, int b){
  srand(time(NULL));
      return rand()%(b-a) +a;
}




