
#include "main.h"

art opis[20];

int main(){
	/*
	int liczba_artystow;
	int liczba_typ;

	//wczytanie danych poczatkowych
	printf("podaj liczbe artystow: ");
	scanf("%d", &liczba_artystow);
	
	printf("\npodaj liczbe typow artystow: ");
	scanf("%d", &liczba_typ);

	//okreslenie poprawnosci danych startowych
	assert( liczba_typ>liczba_artystow || liczba_typ<=0 || liczba_artystow<=0 );
	*/

	lista * kolejka = initList(ARTYSTA);
	
	
	
	//Inicjalizacja artystów
	for(int i=0; i<20; ++i){
		opis[i].inQueue = false;
		opis[i].klasa = i % 5;
		opis[i].name = NAME[i % MAX_NAME]; 
	}

	for(int i=0; i<20; ++i){
		append(&opis[i], kolejka);
	}
	
	print_list(kolejka);
	printf("===================================\n");
	return 0;
}
//==========================================


lista * initList(typListy l){
	lista * res = malloc( sizeof(*res) );
	
	res -> opis = l; 
	res -> first = NULL;
	res -> last = NULL;
	
	return res;
}


bool isEmpty(lista *list){
	if( list->first == NULL) return true;
	return false;
}


void print_list(lista *list){
	elem *it = list -> first;
	
	if( list -> opis == ARTYSTA ){ 
		
		while( it != NULL ){
			printf("Imie: %s, Typ: %d\n", ((art*)(it->val))->name, ((art*)(it->val))->klasa);
			it = it->next;
		}
	}
	/*
		tu wypada zrobic else dla listy typu UTWOR
	*/
}

void append(void *in, lista *list){
	elem *new = malloc(sizeof(*new));
	
	//dostosowywanie nowego elementu
	new -> val = in;
	new -> prev = list->last;
	new -> next = NULL;
	
	if( isEmpty(list) ){
		list ->first = list -> last = new;
	}
	else {
		list->last -> next = new;
		list->last = new;
	}
	
	if( list->opis == ARTYSTA ) 
		((art*)(new->val))->inQueue = true;
}


void usunTyp(int typ, lista *list){
	//zalozenie do dzialania funkcji
	assert( list->opis != ARTYSTA );
	//cdn
} 
