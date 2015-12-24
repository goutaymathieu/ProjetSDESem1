all: generateur_traffic coordinateur

generateur_traffic: generateur_traffic.o boite_aux_lettres_type.h
	gcc generateur_traffic.o -o generateur_traffic -Wall

coordinateur: coordinateur.o boite_aux_lettres_type.h
	gcc coordinateur.o -o coordinateur -Wall

generateur_traffic.o: generateur_traffic.c boite_aux_lettres_type.h
	gcc -c generateur_traffic.c -o generateur_traffic.o -Wall

coordinateur.o: coordinateur.c boite_aux_lettres_type.h
	gcc -c coordinateur.c -o coordinateur.o -Wall
