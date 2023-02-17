#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Tablica.h"


using namespace std;

bool Tablica::wczytajTab(string pliczek){
    ifstream plik;
    plik.open( pliczek.c_str() );//otwieranie pliku
    if( !plik.good() )//sprawdzanie poprawnosc pliku
    {
         return false;
    }
    plik >> ile;
    wsk = new int[ile];//tworzenie tablicy o 'ile' elementach
	for(int i=0;i<ile;i++)
	{
		plik >> wsk[i];//nadawanie liczby jako elemnet liczby
	}
	plik.close();//zamykanie pliku
    return true;
}

void Tablica::delTab(int ind){
	while(true){
			if(ind==0){
				if(ile!=1){
					for(int i=0; i<ile-1; i++) wsk[i] = wsk[i+1];
					ile=ile-1;//zmiejszanie ilosci elemntow w talicy
					wsk=(int*)realloc(wsk,(ile)*sizeof(int));//zmiejszanie zajmowanej pamieci przez wsklice
					break;}
				else{
					ile=0;
					free(wsk);
					wsk=NULL;
					break;
				}
			}
			if(ind==ile-1){
				ile=ile-1;
				wsk=(int*)realloc(wsk,(ile)*sizeof(int));
				break;}

			if(ind>0 && ind<ile-1){
				for(int i=ind; i<ile-1; i++) wsk[i] = wsk[i+1];
				ile=ile-1;
				wsk=(int*)realloc(wsk,(ile)*sizeof(int));//zmiejszenie potrzebnej panieci dla wsklicy
				break;}
			else{
				std::cout<<"Nie ma takiego indeksu"<<std::endl;
				break;
			}
	}
}

void Tablica::delAll(){
    ile=0;
    free(wsk);
    wsk=NULL;
}

void Tablica::dodajTab(int ind,int num){
		while(true){
			if(ind==0){
				wsk=(int*)realloc(wsk,(ile+1)*sizeof(int));//zwiekszenie pamieci potrzebnej dla talicy
				for(int i=ile; i>0; i--) wsk[i] = wsk[i-1];//przesuniecie 'w prawo' elementow w wsklicy
				ile=ile+1;
				wsk[0]=num;
				break;}
			if(ind==ile){
				wsk=(int*)realloc(wsk,(ile+1)*sizeof(int));
				wsk[ile]=num;
				ile=ile+1;
				break;}
			if(ind>0 && ind<ile){
				wsk=(int*)realloc(wsk,(ile+1)*sizeof(int));
				for(int i=ile; i>ind; i--) wsk[i] = wsk[i-1];
				ile=ile+1;
				wsk[ind]=num;
				break;}
			else{
			std::cout<<"Zla liczba"<<std::endl;
			break;}
	}
}

bool Tablica::znajdzTab(int liba){
    for(int i=0; i<ile; i++)
	{
		if(wsk[i]==liba){//jezeli jest taka liczba to pentla przestaje dzialac bo szukamytylko jednej liczby
				return true;
		}
	}
	return false;
}

void Tablica::randomTab(){
    wsk = new int[ile];//tworzenie tablicy o 'ile' elementach
	for(int i=0;i<ile;i++)
	{
		wsk[i] = rand()%1000;//nadawanie liczby jako elemnet liczby
	}
}

void Tablica::wysTab(){
    std::cout<<std::endl;
	std::cout<<"od przodu"<<std::endl;
	for(int i=0;i<ile;i++)
    {
        std::cout<<wsk[i]<<"  ";//wyswietlanie po kolei kazdego elementu wsklicy
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"od tylu"<<std::endl;
    for(int i=ile-1;i>=0;i--)
    {
        std::cout<<wsk[i]<<"  ";//wyswietlanie po kolei kazdego elementu wsklicy
    }
    std::cout<<std::endl;
}
