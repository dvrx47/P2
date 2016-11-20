#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

void* zespol(void* dane){
	while(true){
	//sprawdz czy mozesz pojsc do s1
	//sprawdz czy mozesz pojsc do s2
		
		//zablokuj studio x
		//jestem w studiu x
		//tu nie musi być losowania stylu
		//nagraj 
		//wrzuc nagranie do listy/tablicy
	}
	return NULL;
}

#define N 6

//wydawanie skladanek:
	//usun utwory z listy/tablicy
	// cos wypisz?

typedef struct {
	bool artysci[4]; 
	int styl;
//	void przydziel_artystow();
//	void losuj_styl();
// void wrzuc_nagranie();
} studio;

//	bufor s1[], s2[];
//	tablica/lista utworzonych utworow

int main(){
	/*
	 *		amator[0] - gitarzysta + basista
	 *		amator[1] - gitarzysta + wokalista
	 *		amator[2] - gitarzysta + perkusista
	 * 	amator[3] - perkusista + wokalista
	 *		amator[4] - perkusista + basista
	 * 	amator[5] - wokalista + basista
	 */	
	
	//jakas kolejka procesów?

	// format bool { gitarzysta, basista, perkusista, wokalista } 
	// opis[i] odpowiada opisowi amatorowi[i]
	pthread_t amator[N];
	bool opis[6][4] = {	{1,1,0,0}, 
								{1,0,0,1}, 
								{1,0,1,0}, 
								{0,0,1,1}, 
								{0,1,1,0}, 
								{0,1,0,1}   };

	for(int i=0; i<N; ++i){ 
		pthread_create(&amator[i], NULL, zespol, opis[i] ); 
		pthread_join(watek[i], NULL);
		//moze jakas kolejka - nie wiem nie ogarniam semafor/muteks/monitor
	}
		//w tym watku:	
		//* wylosuj dwie rozne pary (a,b) 0 <= a,b < 4, a =/= b
		//* wstaw je do studia
		//* losuj styl
		//	nagrywaj
		//
		//wydawaj skladanki
	
	return 0;
}
