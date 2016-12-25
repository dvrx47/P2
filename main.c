#include "main.h"

art opis[ MAX_ART ];
lista * kolejka; //bufor gorny z grafu
lista * sklep;
menager mgrOpis;

//procesy obslugujace
void * artysta(void * data);
void * studio(void * data);
void * menadzer(void * data);



int main(){
	
	int liczba_artystow;
	int liczba_typ;

	//wczytanie danych poczatkowych
	printf("podaj liczbe artystow: ");
	scanf("%d", &liczba_artystow);
	
	printf("\npodaj liczbe typow artystow: ");
	scanf("%d", &liczba_typ);

	//okreslenie poprawnosci danych startowych
	if( liczba_typ>liczba_artystow || liczba_typ<=0 || liczba_artystow<=0 || liczba_artystow > MAX_ART )
		return 1;

	//wszystkie procesy
	pthread_t artysci_thread[liczba_artystow];
	pthread_t studio_thread, menager_thread;
	

	kolejka = initList( ARTYSTA );
	sklep   = initList( UTWOR );
	
	//inicjalizacja menagera
	mgrOpis.zapotrzebowanie = 0;
	mgrOpis.posiadane = 0;
	mgrOpis.utwory = initList( UTWOR );
	
	
	//Inicjalizacja artystów-opisow
	for(int i=0; i<liczba_artystow; ++i){
		opis[i].inQueue = false;
		opis[i].klasa = i % liczba_typ;
		opis[i].name = NAME[i % MAX_NAME]; 
	}	

	//inicjalizacja muteksow
	pthread_mutex_init(&lock_sklep, NULL);
	pthread_mutex_init(&lock_mgr, NULL);
	pthread_mutex_init(&lock_kolejka, NULL);
	
	//tworzenie utworu startowego
	utwor * start = malloc(sizeof(*start));
	start->imiona = initList( IMIONA );
	//jeszcze mutex nie potrzebny
	append(start, sklep);
	//tworzenie wątku dla studia
	pthread_create(&studio_thread, NULL, studio, &liczba_typ);

	//tworzenie wątku dla menagera
	pthread_create(&menager_thread, NULL, menadzer, NULL);

	//tworzenie wątków dla artystow
	for(int i=0; i<liczba_artystow; ++i)
		pthread_create(&artysci_thread[i], NULL, artysta, &opis[i]);
		
	
	//oczekiwanie na zakonczenie wątków
	pthread_join(studio_thread, NULL);
	pthread_join(menager_thread, NULL);

	for(int i=0; i < liczba_artystow; i++)
		pthread_join(artysci_thread[i], NULL);


	pthread_mutex_destroy(&lock_sklep);
	pthread_mutex_destroy(&lock_mgr);
	pthread_mutex_destroy(&lock_kolejka);
	
	
	printf("\nNagrano %d utworow, lista zlecen sie skonczyla\n", LIM_UTWOR);
	
	return 0;
}
//================PROCESY===================

void * artysta(void * data){
	art *opis = (art*) data;
	
	while( nagrane_utwory < LIM_UTWOR){
		if( !(opis -> inQueue) ){
			if( opis -> klasa == 0){
				//robie to zgodnie z ideą algorytmu bankiera
				mgrOpis.zapotrzebowanie++; //zglasza zapotrzebowanie na utwor
				bool err = true;
				while(err == true && nagrane_utwory < LIM_UTWOR){
					pthread_mutex_lock(&lock_mgr);
				
					if( mgrOpis.posiadane > 0 ){ 
						err = false; 
						delFirst( mgrOpis.utwory );
						mgrOpis.posiadane--;
					}
				
					pthread_mutex_unlock(&lock_mgr); 
				}
			}
		//na tym etapie artysta dowolnego typu jest gotowy do zapisania
		
			pthread_mutex_lock(&lock_kolejka);
			append(opis, kolejka);
			pthread_mutex_unlock(&lock_kolejka);
		}
	}
	


	return NULL;
}

void * studio(void * data){
	
	int potrzebni = *((int*)data);
	bool tab[ potrzebni ];
	while( nagrane_utwory < LIM_UTWOR){
		//sprawdzanie czy jest mozliwosc nagrania utworu
		for(int i=0; i < potrzebni; ++i) tab[i] = false;
	
		elem *pom = kolejka -> first;
		while(pom != NULL){
			tab[ ((art*)(pom->val))->klasa ] = true;
			pom = pom->next;
		}

		int count = 0;
		for(int i=0; i < potrzebni; ++i){
			if(tab[i]) count++;
		}
		//koniec sprawdzania
		
		if( count >= potrzebni ){
			
			//tworzenie nowego utworu
			utwor * new = malloc( sizeof(*new) );
			
			new -> imiona = initList(IMIONA);
			
			for(int i=0; i < potrzebni; i++){
				pthread_mutex_lock(&lock_kolejka);
				append( usunTyp(i, kolejka), new->imiona );
				pthread_mutex_unlock(&lock_kolejka);
			}
			
			nagrane_utwory++;
			
			printf("utwor %d nagrali: ", nagrane_utwory);
			print_list( new->imiona );
			printf("=========================\n\n");
			
			//dodanie nowego utworu do sklepu
			pthread_mutex_lock(&lock_sklep);
			append( new, sklep );
			pthread_mutex_unlock(&lock_sklep);
			
			
			
			
			
		}
	}

	return NULL;
}

//pierwsza czesc dobrze 
void * menadzer(void * data){
	while( nagrane_utwory < LIM_UTWOR){
		if( mgrOpis.zapotrzebowanie > 0 ){
			if( !isEmpty(sklep) ){
				pthread_mutex_lock(&lock_sklep);
				//pobierz utwor ze sklepu
				utwor * new = delFirst(sklep);
				mgrOpis.zapotrzebowanie--;
				mgrOpis.posiadane++;
				pthread_mutex_unlock(&lock_sklep);
				
				
				pthread_mutex_lock(&lock_mgr);
				append(new, mgrOpis.utwory );
				pthread_mutex_unlock(&lock_mgr);
				
			}
		}
	}

	return NULL;
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
	
	
	if( list -> opis == ARTYSTA ){ 
		elem *it = list -> first;
		while( it != NULL ){
			printf("Imie: %s, Typ: %d\n", ((art*)(it->val))->name, ((art*)(it->val))->klasa);
			it = it->next;
		}
	}
	else{
		elem * it = list->first;
		while( it != NULL ){
			printf("%s, ", ((char*)(it->val)));
			it = it->next;
		}
		printf("\n");
	}
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


char * usunTyp(int typ, lista *list){
	
	if( list->opis != ARTYSTA ) return NULL; //nie obsluguje list innego typu niz artysta	
	
	elem *it = list ->first;
	
	while( ((art*)(it->val ))->klasa != typ) it = it -> next;
	
	if( it == list->first ) list->first = list->first->next;
	else
	{
		if( it == list->last ){
			if(list->last == list->first){
				list->last = list->first = NULL;
			}
			else{
				list->last = list->last->prev;
				list->last->next = NULL;
			}
		}
		else{
			it -> prev ->next = it->next;
			it -> next ->prev = it->prev;
		}
	}
	
	((art*)( it->val ))->inQueue = false;
	return ((art*)(it->val ))->name;

} 


utwor * delFirst(lista *list){
	if( isEmpty(list) ) return NULL;
	elem * temp = list -> first;
	list -> first = list -> first ->next;
	if(list->first == NULL){
		list->last = NULL;
	}
	else{
		if(list->first == list->last) list->last->prev = NULL;
		list->first->prev = NULL;
	}	
	return (utwor*)temp->val;
}
