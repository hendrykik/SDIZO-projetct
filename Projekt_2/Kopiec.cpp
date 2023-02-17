#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <string>
#include "Kopiec.h"


using namespace std;

bool Kopiec::wczytajKopiec(string pliczek){
    ifstream plik;
    plik.open( pliczek.c_str() );//otwieranie pliku
    if( !plik.good() )
    {
         return false;
    }
    int number;
    plik >> ile;//wczytanie liczby elementow

	 for(int i=0; i<ile; i++)
    {
        plik >> number;//wczytanie wartosci z pliku
    	tab[i]=number;
        naprawUp(i);
	}

	plik.close();
    return true;
}

int Kopiec::l(int i){
    int b;
    if(i==0) b=1;
    else b=2*i+1;
    return b;
}

int Kopiec::r(int i){
    int b;
    if(i==0) b=2;
    else b=2*i+2;
    return b;
}

int Kopiec::rodzic(int i){
    if(i==2) return 0;
    return floor((i-1)/2);
}

void Kopiec::nowyKop(){
    for(int i=0;i<100;i++){
        tab[i]= NULL;
    }
    tab[0]=-1;
}
void Kopiec::naprawUp(int i){
    if (i>ile) return;
    if(i == 0 ) return;

    if(tab[i] > tab[rodzic(i)]){
        swap(tab[rodzic(i)],tab[i]);
    }
    naprawUp(rodzic(i));
}

void Kopiec::dodajKop(int num){
    ile+=1;
    tab[ile-1]=num;
    if(ile!=1)(naprawUp(ile-1));
}

bool Kopiec::usunKop(int ind){
    if(ind==1 && ile ==1) return false;
    else{
    swap(tab[ind],tab[--ile]);
    tab[ile+1]=NULL;
    naprawDown(ind);
    naprawUp(ind);}
    return true;
}

bool Kopiec::znajdz(int ind){
    for (int i=0;i<ile;i++){
        if(ind == tab[i]) return true;
    }
    return false;
}

void Kopiec::naprawDown(int i){
    if(i>ile) { return;}
    int pier = i;

    if(l(i) < ile && tab[i] < tab[l(i)] && tab[l(i)]!=NULL){
        pier = l(i);
    }
    if(r(i) < ile && tab[pier] < tab[r(i)] && tab[r(i)]!=NULL){
        pier = r(i);
    }

    if(pier != i){
        swap(tab[i],tab[pier]);
        naprawDown(pier);
    }
}

void Kopiec::wysLin(){
    for(int i=0; i<ile;i++)printf("%i   ",tab[i]);
    cout<<endl;
}

void Kopiec::wysKop(const string& prefix, int i, bool isLeft){
    if(i<ile)
    {
        cout << prefix;

        cout << (isLeft ? "|-- " : "\\-- " );

        // print the value of the node
        cout << tab[i] << endl;

        // enter the next tree level - left and right branch
        Kopiec::wysKop( prefix + (isLeft ? "|   " : "    "), l(i), true);
        Kopiec::wysKop( prefix + (isLeft ? "|   " : "    "), r(i), false);
    }
}

void Kopiec::random(int ind){
    int number;
    for (int i=0; i<ile; i++){
        number = rand() %1000;
        tab[i]=number;
        naprawUp(i);
    }
}

void Kopiec::wysAll(const std::string& prefix, int i, bool isLeft){
    Kopiec::wysLin();
    Kopiec::wysKop(prefix,i,isLeft);
}

