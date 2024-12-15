#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct comic {
	int number;
	char *collection;
	struct comic *next;
}comic;

comic *nuevoNodo (int number, char *collection){
	comic *newNodo = (comic*)malloc(sizeof(comic));
	if (newNodo == NULL){
		printf("No se ha podido reservar memoria");
		exit(1);
	}
	else {
		newNodo->number = number;
		newNodo->collection = strdup(collection);
		newNodo->next = NULL;
	}
	return newNodo;
}
void anadirNodo(comic **head, int number,char *collection){
	comic *newNodo = nuevoNodo (number, collection);
	if (*head == NULL){
		*head = newNodo;	
	}
	else{
		comic *temp = *head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newNodo;
	}
}

comic substract_lists(comic *listaA, comic *listaB){
	comic *comicResultante = NULL;
	comic *tempA = listaA;
	while(tempA!=NULL){	
		int encontrado = 0;
		comic *tempB = listaB;
		while(tempB!=NULL){
			if(tempA->number == tempB->number && strcmp(tempA->collection, tempB->collection)==0){
				encontrado = 1;
				break;	
			}
			tempB = tempB->next;
		}
		if(encontrado == 0){
			anadirNodo(&comicResultante,tempA->number,tempA->collection);
		}
		tempA = tempA->next;
	}
	while (comicResultante != NULL){
		printf("Comic numero %d de la coleccion %s.\n", comicResultante->number,comicResultante->collection);
		comicResultante = comicResultante->next;
	}
	return *comicResultante;
}
void freeCollection (comic *head){
	comic *temp;
	while (head != NULL){
		temp = head;
		head = head->next;
		free(temp->collection);
		free(temp);
	}
}
int main(int argc, char **argv){
	comic *all = NULL;
	comic *DCcomics = NULL;
	
	anadirNodo(&all,1,"Marvel");
	anadirNodo(&all,2,"DC");
	anadirNodo(&all,3,"Imagen");
	anadirNodo(&all,4,"DC");
	
	anadirNodo(&DCcomics,2,"DC");
	anadirNodo(&DCcomics,4,"DC");
	
	substract_lists(all, DCcomics);
	
	freeCollection(all);
	freeCollection(DCcomics);
	free(all);
	free(DCcomics);
	return 0;
}
