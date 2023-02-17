#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Lista.h"


using namespace std;

struct Node{
	   int liczba;
	   struct Node* przed;
	   struct Node* next;
};

struct Node* createNode(int num){
	   struct Node* myNode = new Node;
	   myNode->liczba =num;
	   myNode->przed =nullptr;
	   myNode->next =nullptr;
	   return myNode;
};

bool Lista::wczytajListe(string pliczek){
    if(head!=nullptr) delAll();
    ifstream plik;
    plik.open( pliczek.c_str() );//otwieranie pliku
    if( !plik.good() )
    {
         return false;
    }
    int number;
    plik >> ile;//wczytanie liczby elementow
    plik >> number;//wczytanie pierwszego elementu wartosci z pliku
	Node* wsk = createNode(number);
    head = wsk;

	 for(int i=1; i<ile; i++)
    {
    	plik >> number;
        Node *wskz=head;//wkaznik na glowe/poczatek listy

        while (wskz->next != nullptr) {//szukanie ktory elemnt jest ostatni poprzez zobaczenie czy ma wskaznik na nastepny elemnt listy
            wskz = wskz->next;
        }
        wskz->next = createNode(number);//przypisanie watosc elementu liczby listy
        wskz->next->przed=wskz;//przypisanie wskaznika na poprzedni element elementu liczby listy
        wskz->next->next = nullptr;//przypisanie NULL na wskaznik na nastepny element bo nie wiadomo czy bedzie kolejny
		ogon = wskz->next;
	}

	plik.close();
    return true;
}
bool Lista::szukaj(int &ind, int lib){
	int num;
	Node *wskc;
	wskc = head;//wskaznik na pierwszy element listy
	for(int i=0;i<ile;i++){
		num = wskc->liczba;//num przyjmuje wartosc liczb kolejnych elementow listy
		if(lib == num){
			ind=i;
			return true;
		}
		wskc = wskc -> next;//przechodzenie z wkzaniku elementu na wkaznik elementu kolejnego
	}
	return false;
}
void Lista::delListafront(){
    Node *wsk;
    wsk=head->next;
    free(head);//zwalnianie pamieci
    wsk->przed=nullptr;
    head = wsk;
}

void Lista::delListaback(){
    Node *wsk;
    wsk=ogon->przed;
    free(ogon);//zwalnianie pamieci
    wsk->next=nullptr;
    ogon = wsk;
}
void Lista::delListamid(int ind){
    if(ind==ile-1){
				Node *wsk;
				wsk=ogon->przed;
				free(ogon);//zwalnianie pamieci
				wsk->next=nullptr;
				ogon = wsk;
				}
			if(ind>0 && ind<ile-1){
				Node *wskb=head;
				Node *poz;
				for(int i=0; i<ind-1 && wskb->next != nullptr;i++){
					wskb=wskb->next;
				}
				poz = wskb->next;
				wskb->next = poz->next;
				poz->next->przed = wskb;
				free(poz);
			}
}
void Lista::delAll(){
    Node *wsk = ogon;
    if(head!=ogon){
    do{
        wsk = wsk->przed;
        free(wsk->next);
    }while(wsk->przed!=nullptr);}
    head=nullptr;
    ogon=nullptr;
}
void Lista::addListafront(int num){
        Node* wsk = createNode(num);
        if(head == nullptr){
            head = wsk;
            ogon = head;
            }
		else{
            head->przed = wsk;
            wsk->next = head;
            head = wsk;
		}
}

void Lista::addListamid(int num,int ind){
    Node *wsk=head;
    Node *wsk2;
    for(int i=0;i<ind-1 && wsk->next!=nullptr;i++){
        wsk = wsk->next;
    }
    wsk2 = wsk->next;
    wsk->next = createNode(num);
    wsk->next->przed= wsk;
    wsk2->przed = wsk->next;
    wsk->next->next=wsk2;
    if(ind == ile){
        ogon = wsk->next;
    }
}

void Lista::addListaback(int num){
        Node* wsk = createNode(num);
        if(head == nullptr){
            head = wsk;
            ogon = head;
            }
        else {ogon->next = wsk;
        wsk->przed = ogon;
        ogon = wsk;}
}
void Lista::random(){
    int number = rand()%100;
	 for(int i=0; i<ile; i++)
    {
    	number = rand() % 1000;
        addListafront(number);
	}
}
void Lista::wyswietlListe(){
    cout<<endl;
	cout<<"z przodu"<<endl;
    Node *wskz=head;//wskaznk na pierwszy element listy
    do{
        printf("%i", wskz->liczba);//wypisywanie liczb danych elementow listy
        printf("  ");
        wskz = wskz->next;//zmienienie na nastepny element
	}while (wskz != nullptr);//sprawdzenie czy jest kolejny element

	cout<<endl;
	cout<<"z tylu"<<endl;
    Node *wsko=ogon;//wskaznk na pierwszy element listy
    do{
        printf("%i", wsko->liczba);//wypisywanie liczb danych elementow listy
        printf("  ");
        wsko = wsko->przed;//zmienienie na nastepny element
	}while (wsko != nullptr);//sprawdzenie czy jest kolejny element
}


