#ifndef MA_VOITURE
#define MA_VOITURE

struct msgbuf {
  long mtype; //origine voiture
  int vers; // O si va tout droit, 1 si tourne à gauche 
};

typedef struct msgbuf MESSAGE; 

#endif
