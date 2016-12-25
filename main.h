#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include <stdlib.h>

//MAX_NAME opisuje ilosc rekordow w tablicy NAME[]
#define MAX_NAME 200
#define LIM_UTWOR 100
#define MAX_ART 1000


pthread_mutex_t lock_sklep;
pthread_mutex_t lock_mgr;
pthread_mutex_t lock_kolejka;

int nagrane_utwory = 0;

enum typ {ARTYSTA, UTWOR, IMIONA};
typedef enum typ typListy;

typedef struct elem elem;
struct elem{
	void * val;
	elem *next;
	elem *prev;
};

typedef struct lista{
	typListy opis; //zmienna opisuje jaki typ danych przechowuje
	elem *first;	
	elem *last;
}lista;

typedef struct menager{
	int zapotrzebowanie;
	int posiadane;
	lista * utwory; //utwory przyniesione ze sklepu
} menager;


typedef struct art{
	bool inQueue;
	int  klasa;
	char *name;
}art;

typedef struct utwor{
	lista * imiona;
} utwor;

//inicjalizacja listy
lista * initList(typListy l);

//funkcja zwraca wartosc true jesli lista ma 0 elem
bool isEmpty(lista *list);

//funkcja ma drukowac liste na standardowe wyjscie
void print_list(lista *list); 

//funkcja ma dopisywac do listy
void append(void *in, lista *list); 

//funkcja dziala dla list typu artysta, usuwa z niej artyste o danym typie liczac od poczatku kolejki
/*
	założenia do funkcji:
	-obiekt danego typu należy do listy
	-dziala tylko na liscie typu
	
	-musi zwracac imie usunietego artysty jako niezalezny char*
*/
char * usunTyp(int typ, lista *list); 

//z mysla o listach typu utwor, usuwa pierwszy element z listy
utwor * delFirst(lista *list);


//tablica nazw
char* NAME[] = {
	"Mckenzie Lutterman",
	"Maudie Berns",
	"Michelle Collard",
	"Shavonda Tuck",
	"Shelly Rashid",
	"Romaine Lahr",
	"Micki Snoddy",
	"Hailey Kirkbride",
	"Carolina Connon",
	"Rachelle Iverson",
	"Lashaunda Venters",
	"Bernetta Hubbs",
	"Kristofer Gierlach",
	"Enoch Bronder",
	"Julian Troche",
	"Ngoc Melvin",
	"Dorthey Blakley",
	"Shirely Hamlet",
	"Ben Wesely",
	"Bernadette Youngquist",
	"Kate Ardis",
	"Muoi Stalter",
	"Joe Harcrow",
	"Janetta Uplinger",
	"Aleta Esh",
	"Velma Sabatino",
	"Lizeth Willbanks",
	"Dewitt Boatright",
	"Shandi Tompkins",
	"Kaila Shunk",
	"Nathan Fannin",
	"Cherlyn Vince",
	"Korey Shutter",
	"Tenisha Garrick",
	"Cori Pelfrey",
	"Ouida Mcgonagle",
	"Russ Stansel",
	"Jonna Carnley",
	"Kum Herring",
	"Elma Fessenden",
	"Karisa Lenox",
	"Michale Symons",
	"Sadie Twist",
	"Rina Boddie",
	"Davina Evens",
	"Norma Winkler",
	"Damion Pehrson",
	"Season Leduc",
	"Marquerite Badillo",
	"Beckie Dowe",
	"Brent Gorham",
	"Matthew Ritts",
	"Khalilah Bragan",
	"Sade Polson",
	"Emerita Strahl",
	"Maranda Mansker",
	"Lottie Mulvey",
	"Ervin Corsi",
	"Reginald Dunker",
	"Shannon Baver",
	"Lindy Breen",
	"Hoyt Ocallaghan",
	"Lauran Ditmore",
	"Gabriela Lieberman",
	"Santiago Amann",
	"Edgardo Wykoff",
	"Novella Wilcoxon",
	"Bobbie Bezanson",
	"Winford Lent",
	"Simone Ketchum",
	"Bruno Hisle",
	"Jenifer Sheckler",
	"Lucinda Derouen",
	"Faustino Guerin",
	"Karena Mauer",
	"Beatriz Kremer",
	"Tena Ceja",
	"Elinor Grave",
	"Graham Kuehner",
	"Marvel Kottwitz",
	"Cameron Dash",
	"Silas Geiser",
	"Jazmin Marksberry",
	"Curt Mccants",
	"Lesli Calcagno",
	"Trinity Umphrey",
	"Keren Sterner",
	"Krista Wimberley",
	"Detra Mau",
	"Cesar Rowse",
	"Beatrice Boger",
	"Frieda Keatts",
	"Kiersten Robison",
	"Suzette Noss",
	"Lashunda Stalker",
	"Precious Armor",
	"Ruthie Sauseda",
	"Enid Coache",
	"Beckie Petway",
	"Mathilde Strom",
  	"Noelle Duffin",
	"Kenyatta Cassella",
	"Junior Curfman",
	"Deirdre Wald",
	"Leigh Launius",
	"Mardell Patchen",
	"Warren Teer",
	"Augustine Spivey",
	"Nova Elzey",
	"Bree Bothwell",
	"Libbie Chagoya",
	"Rex Fuquay",
	"Johnnie Troiano",
	"Mitchel Mckittrick",
	"Dalia Klein",
	"Veronique Sturtz",
	"Kimber Major",
	"Dalila Gammons",
	"Millicent Word",
	"Krystle Alers",
	"Will Hoeppner",
	"Karma Warburton",
	"Anh Towell",
	"Andera Ross",
	"Letty Sheen",
	"Dominga Brabham",
	"Marilee Morano",
	"Honey Francoeur",
	"Ouida Slusher",
	"Griselda Mcglown",
	"Jae Bohon",
	"Raymonde Kovacs",
	"Constance Woolery",
	"Ronni Rainwater",
	"Ashlea Gurrola",
	"Odette Angulo",
	"Rana Millender",
	"Micah Earnest",
	"Hong Kilcrease",
	"Clint Killough",
	"Burton Wiegand",
	"Loris Esters",
	"Daisey Dial",
	"Georgetta Manes",
	"Sharonda Leisy",
	"Ana Duffer",
	"Ela Dang",
	"Marhta Krahn",
	"Estelle Vanderslice",
	"Leida Canales",
	"Iluminada Gosier",
	"Billye Nowack",
	"Simone Toussaint",
	"Albina Billick",
	"Jannet Figueiredo",
	"Tatum Cauble",
	"Concepcion Petree",
	"Omer Backhaus",
	"Heike Lafayette",
	"Stefany Dominique",
	"Kimberlee Siler",
	"Sparkle Chretien",
	"Donovan Lipps",
	"Sally Stinson",
	"Jayme Lucky",
	"Tamie Yeoman",
	"Trula Steiner",
	"Felicita Moczygemba",
	"Lakeesha Laskowski",
	"Sid Quinley",
	"Shemeka Tuley",
	"Carin Aslett",
	"Phillis Zobel",
	"Olene Singleterry",
	"Linwood Villagran",
	"Jamee Mcneece",
	"Mason Amyx",
	"Robena Rehn",
	"Olevia Struble",
	"Casimira Huddleston",
	"Verdell Laino",
	"Herman Brockett",
	"Keenan Gallaway",
	"Jani Suazo",
	"Lorie Armes",
	"Brianna Eguia",
	"Alonso Gloster",
	"Russel Mullett",
	"Dagny Alston",
	"Helen Sylva",
	"Leighann Jasso",
	"Faith Klann",
	"Rana Chennault",
	"Jimmie Hardin",
	"Titus Leverette",
	"Karleen Cann",
	"Brigitte Debus",
	"Marshall Brick",
	"Lanita Cothron",
	"Reuben Calle"
};

#endif
