#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include"boite_aux_lettres_type.h"

key_t cle=1;
int id;
int pid_generateur_traffic;

void quit();

int main(){
    pid_generateur_traffic=fork();
    if (pid_generateur_traffic==0){
        if(execl("/home/goutay/Documents/TC-Exos/SDE/Projet/generateur_traffic", "generateur_traffic", NULL, NULL)==-1) printf("Erreur d'ouverture de generateur_traffic\n");
     }else{
         signal(SIGINT, quit);
         if ((id=msgget( cle, 0666|IPC_CREAT))==-1){//creee boite aux lettres, si problème création, message erreur
            exit(1);
        }

         int buffer1, buffer2, buffer3, buffer4; // on met en mémoire la direction de la dernière voiture provenant de 1,2,3,4
         int shareNS=0; // permet de regarder, sur l'axe Nord Sud, la voiture du Nord(1), du Sud(3), ou les 2 (0)
         int shareOE=0; // pareil pour Ouest-Est
         for(;;){
             MESSAGE message1, message2, message3, message4;


             while(1){//on prend que les voitures 1 et 3
                 if (shareNS==0|| shareNS==1){ // on regarde la voiture 1
                     if(((msgrcv(id, &message1, sizeof(MESSAGE), 1, IPC_NOWAIT)))>0){
                         printf("Coordinateur: voiture recue de type %d  recue qui va vers %d\n", message1.mtype, message1.vers);
                         buffer1=message1.vers;
                     }else{
                         buffer1=2; // Il n'y à rien dans la file
                     }
                 }
                 if (shareNS==0 || shareNS==3){
                     if(((msgrcv(id, &message3, sizeof(MESSAGE), 3, IPC_NOWAIT)))>0){
                         printf("Coordinateur: voiture recue de type %d  recue qui va vers %d\n", message3.mtype, message3.vers);
                         buffer3=message3.vers;
                     }else{
                         buffer3=2;
                     }
                 }



                 if (buffer1 == 2 || buffer3 ==2){ // une des deux voies ne contient pas de voiture
                     if (buffer1!=2){
                         printf("Passage de la voiture provenant de 1 et allant vers %d\n", buffer1);
                         shareNS=0;
                     }else if (buffer3!=2){
                         printf("Passage de la voiture provenant de 3 et allant vers %d\n", buffer3);
                         shareNS=0;
                     }else{
                         shareNS=0;
                         sleep(0.2);
                     }
                 }else if (buffer1==1 ||  buffer3==1){ //si une des deux veut tourner à gauche
                     if(buffer1!=1){ 	
                         printf("La voiture provenant de 1 va tout droit\n");
                         shareNS=1;
                     }else if (buffer3!=1){
                         printf("La voiture provenant de 3 va tout droit\n");
                         shareNS=3;
                     }else{
                         printf("Les deux voitures provenant de 1 et 3 tournent à gauche\n");
                         shareNS=0;
                     }
                 }else{
                     printf("Les voitures provenant de 1 et de 3 vont tout droit\n");
                     shareNS=0;
                 }
             }

             while(1){//on prend que les files 2 et 4
                 if (shareOE==0|| shareOE==2){ // on regarde la voiture 1
                     if(((msgrcv(id, &message2, sizeof(MESSAGE), 2, IPC_NOWAIT)))>0){
                         printf("Coordinateur: voiture recue de type %d  recue qui va vers %d\n", message2.mtype, message2.vers);
                         buffer2=message2.vers;
                     }else{
                         buffer2=2; // Il n'y à rien dans la file
                     }
                 }
                 if (shareOE==0 || shareOE==4){
                     if(((msgrcv(id, &message4, sizeof(MESSAGE), 4, IPC_NOWAIT)))>0){
                         printf("Coordinateur: voiture recue de type %d  recue qui va vers %d\n", message4.mtype, message4.vers);
                         buffer4=message2.vers;
                     }else{
                         buffer4=2;
                     }
                 }



                 if (buffer2 == 2 || buffer4 ==2){ // une des deux voies ne contient pas de voiture
                     if (buffer2!=2){
                         printf("Passage de la voiture provenant de 1 et allant vers %d\n", buffer1);
                         shareOE=0;
                     }else if (buffer4!=2){
                         printf("Passage de la voiture provenant de 3 et allant vers %d\n", buffer3);
                         shareOE=0;
                     }else{
                         shareOE=0;
                         sleep(0.2);
                     }
                 }else if (buffer2==1 ||  buffer4==1){ //si une des deux veut tourner à gauche
                     if(buffer2!=1){ 	
                         printf("La voiture provenant de 2 va tout droit\n");
                         shareOE=2;
                     }else if (buffer4!=1){
                         printf("La voiture provenant de 4 va tout droit\n");
                         shareOE=4;
                     }else{
                         printf("Les deux voitures provenant de 2 et 4 tournent à gauche\n");
                         shareOE=0;
                     }
                 }else{
                     printf("Les voitures provenant de 2 et de 4 vont tout droit\n");
                     shareOE=0;
                 }
             }
         }
     }
}

void quit(){
    kill(pid_generateur_traffic, SIGINT);
    sleep(0.2);
    if(msgctl(id, IPC_RMID, NULL)==-1){
        printf("Erreur de suppression de la file\n");
    }else{ 
        printf("La file a bien été supprimée\n");
    }
    exit(0);
}
