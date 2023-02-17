#include "Lista.h"
#include "Tablica.h"
#include "Kopiec.h"
#include "avltree.h"
#include <iostream>
#include <stdlib.h>
#include <string>
//#include <windows.h>

using namespace std;

/*
double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if( !QueryPerformanceFrequency( & li ) )
         cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double( li.QuadPart ) / 1000.0;

    QueryPerformanceCounter( & li );
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter( & li );
    return double( li.QuadPart - CounterStart ) / PCFreq;
}*/

void menu()//menu na poczatku programow
{
	std::cout<<"\n    MENU"<<std::endl;
	std::cout<<"1 - zbuduj z pliku"<<std::endl;
    std::cout<<"2 - usun"<<std::endl;
	std::cout<<"3 - dodaj"<<std::endl;
	std::cout<<"4 - znajdz"<<std::endl;
    std::cout<<"5 - utworz losowa tablice"<<std::endl;
	std::cout<<"6 - wy�wietl"<<std::endl;
}

int main(){

	cout<<"1 - Operacje na liscie"<<endl;
	cout<<"2 - Operacje na tablicy"<<endl;
	cout<<"3 - Operacje na kopcu binarnym"<<endl;
	int wyb;
	cin>>wyb;
	Lista lista;
    lista.head = nullptr;
    lista.ile = 0;
    Tablica tab;
    tab.wsk = nullptr;
    tab.ile = 0;
    double czas = 0 ;


	if(wyb==1){
	while(true){

        menu();
        int Jak,lib,ind=nullptr;
        string nazwaP;
        cin>>Jak;

        switch(Jak){
        case 1:
            cout<<"Podaj nazwe pliku z rozszezeniem"<<endl;
            cin>>nazwaP;
            if( !lista.wczytajListe(nazwaP)){
                cout<<"Nie uda�o si� otworzyc pliku"<<endl;
                break;
            }
            if(lista.head!=nullptr)lista.wyswietlListe();
            else cout<<"Brak tablicy"<<endl;
            break;
        case 2:
            cout<<"Podaj liczbe"<<endl;
            cin>>lib;
            if(lista.szukaj(ind,lib) == false) {cout<<"Nie ma takiej liczby w tablicy"<<endl; break;}
            if(lista.head == lista.ogon){lista.delAll();lista.ile=0; if(lista.head!=nullptr)lista.wyswietlListe();
            else cout<<"Brak tablicy"<<endl;break;}
            if(ind==0){lista.delListafront(); lista.ile -=1; if(lista.head!=nullptr)lista.wyswietlListe();
            else cout<<"Brak tablicy"<<endl;break;}
            if(ind==lista.ile-1){lista.delListaback(); lista.ile -=1; if(lista.head!=nullptr)lista.wyswietlListe();
            else cout<<"Brak tablicy"<<endl;break;}
            if(ind>0 && ind<lista.ile){lista.delListamid(ind); lista.ile -=1; if(lista.head!=nullptr)lista.wyswietlListe();
            else cout<<"Brak tablicy"<<endl;break;}
            if(lista.head!=nullptr)lista.wyswietlListe();
            else cout<<"Brak tablicy"<<endl;
            break;
        case 3:
            cout<<"Podaj indeks"<<endl;
            cin>>ind;
            cout<<"Podaj liczbe"<<endl;
            cin>>lib;
            if(ind<0 || ind >lista.ile) {cout<<"Nie ma tylu elementow"<<endl; break;}
            if(ind==0){lista.addListafront(lib); lista.ile +=1; if(lista.head!=nullptr)lista.wyswietlListe();
            else cout<<"Brak tablicy"<<endl;break;}
            if(ind==lista.ile){lista.addListaback(lib); lista.ile +=1; if(lista.head!=nullptr)lista.wyswietlListe();
            else cout<<"Brak tablicy"<<endl;break;}
            if(ind>0 && ind<lista.ile){lista.addListamid(lib,ind); lista.ile +=1; if(lista.head!=nullptr)lista.wyswietlListe();
            else cout<<"Brak tablicy"<<endl;break;}

            break;
        case 4:
            cout<<"Podaj liczbe"<<endl;
            cin>>lib;
            if( lista.szukaj(ind,lib)==true) cout<<"Jest taka liczba w liscie"<<endl;
            else cout<<"Nie ma takiej liczby w liscie"<<endl;
            break;
        case 5:
            if(lista.head!=nullptr)lista.delAll();
            int il;
            cout<<"Podaj liczbe elementow"<<endl;
            cin>>il;
            lista.ile = il;
            lista.random();
            if(lista.head!=nullptr)lista.wyswietlListe();
            else cout<<"Brak tablicy"<<endl;
            break;
        case 6:
            if(lista.head!=nullptr)lista.wyswietlListe();
            else cout<<"Brak tablicy"<<endl;
            break;
        }

	}}

	if(wyb==2){
	while(true){
        menu();
        int Jak,lib,ind=nullptr;
        string nazwaP;
        cin>>Jak;

        switch(Jak){
        case 1:
            if(tab.wsk!=nullptr)tab.delAll();
            cout<<"Podaj nazwe pliku z rozszezeniem"<<endl;
            cin>>nazwaP;
            if( !tab.wczytajTab(nazwaP)){
                cout<<"Nie uda�o si� otworzyc pliku"<<endl;
                break;
            }
            if(tab.wsk!=nullptr)tab.wysTab();
            else cout<<"Brak tablicy"<<endl;
            break;
        case 2:
            cout<<"Podaj indeks"<<endl;
            cin>>ind;
            if(tab.wsk!=nullptr) {tab.delTab(ind);tab.wysTab();}
            else cout<<"Brak tablicy"<<endl;
            break;
        case 3:
            cout<<"Podaj indeks"<<endl;
            cin>>ind;
            cout<<"Podaj liczbe"<<endl;
            cin>>lib;
            tab.dodajTab(ind,lib);
            if(tab.wsk!=nullptr)tab.wysTab();
            else cout<<"Brak tablicy"<<endl;
            break;
        case 4:
            cout<<"Podaj liczbe"<<endl;
            cin>>lib;
            if( tab.znajdzTab(lib)==true) cout<<"Jest taka liczba w liscie"<<endl;
            else cout<<"Nie ma takiej liczby w liscie"<<endl;
            break;
        case 5:
            if(tab.wsk!=nullptr)tab.delAll();
            int il;
            cout<<"Podaj liczbe elementow"<<endl;
            cin>>il;
            tab.ile = il;
            tab.randomTab();
            if(tab.wsk!=nullptr)tab.wysTab();
            else cout<<"Brak tablicy"<<endl;
            break;
        case 6:
            if(tab.wsk!=nullptr)tab.wysTab();
            else cout<<"Brak tablicy"<<endl;
            break;
        }}
        }
    if(wyb==3){
    Kopiec kop;
    kop.ile =0;
    kop.nowyKop();
    int men, liczba1;
    string plikk;

    while(true){
        menu();
        cout<<"Podaj liczbe"<<endl;
        cin>>men;
        switch(men){
        case 1:
            kop.nowyKop();
            cout<<"Podaj nazwe pliku"<<endl;
            cin>>plikk;
            kop.wczytajKopiec(plikk);
            kop.wysAll("",0,false);
            break;
        case 2:
            cout<<"Podaj indeks liczby do usuniecia od 0"<<endl;
            cin>>liczba1;
            if(liczba1<=kop.ile){ if (kop.usunKop(liczba1) !=true) cout<<"Nie ma takiego indeksu"<<endl;;}
            else cout<<"Nie ma takiego indeksu"<<endl;
            kop.wysAll("",0,false);
            break;
        case 3:
            cout<<"Podaj liczbe"<<endl;
            cin>>liczba1;
            kop.dodajKop(liczba1);
            kop.wysAll("",0,false);
            break;
        case 4:
            int liczba1;
            cout<<"Podaj liczbe"<<endl;
            cin>>liczba1;
            if (kop.znajdz(liczba1)== true) cout<<"Jest taka liczba w kopcu"<<endl;
            else cout<<"Nie ma takiej liczby w kopcu"<<endl;
            break;
        case 5:
            kop.nowyKop();
            cout<<"Podaj liczbe"<<endl;
            cin>>liczba1;
            kop.ile = liczba1;
            kop.random(liczba1);
            kop.wysAll("",0,false);
            break;
        case 6:
            kop.wysAll("",0,false);
            break;
        }
    }}
   // avltree tree;
    //tree.korzen = NULL;
    //tree.ile = 0;

    //tree.korzen = tree.insert(tree.korzen , tree.stworzNode(3));
    //tree.printTree();
    //tree.korzen = tree.insert(tree.korzen , tree.stworzNode(4));
   // tree.printTree();
//    tree.show(tree.korzen,1);
    //cout<<tree.wysTree(tree.korzen)<<endl;
	return 0;
}
