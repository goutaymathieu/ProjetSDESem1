#include<sys/types.h>
#include<sys/ipc.h>
#include<stdio.h>
#include <signal.h>
#include <stdlib.h>


void quitterFeux();

main(){

  signal(SIGINT, quitterFeux);
  int periode =5; //periode alternance feux
  int idMemPart;
  if(idMemPart = open_shmem(100, 4)==-1){ //obtient id memoire partagee feux creee par coordinateur
  int idSem;
  if(idSem = open_semaphore(1)==-1) exit(1);
  int etat;
  etat = 0;
  //tableau en attendant mémoire partagée :
  int feux[4];

  key_t cle=100;
    printf("erreur ouverture memoire partagée feux par feux.c\n");
    exit(1);
  }
  attach_shmem(idMemPart);
  down(idSem);
  for(;;){
    if (etat==1){
      feux[0]=1;
      feux[1]=0;
      feux[2]=1;
      feux[3]=0;
      printf("feux.c : seuls les feux 0 et 2 allumés (axe nord sud vert)\n");
    }
    else {
      feux[0]=0;
      feux[1]=1;
      feux[2]=0;
      feux[3]=1;
      printf("feux.c : seuls les feux 1 et 3 allumés (axe est ouest vert)\n");
    }
    up(idSem);
    if(etat==1){
      etat=0;
    }else{
      etat=1;
    }
    sleep(periode);
  }
}

void quitterFeux(){
  exit(1);  
}
