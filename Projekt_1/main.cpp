#include <iostream>
#include "Graf.h"
#include "Kopiec.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>



using namespace std;

struct Node{
	   int liczba;
       int waga;
	   struct Node* next;
};



void menu(){
    cout<<"Co chcesz zrobic?"<<endl;
        cout<<"1 - Wczytaj z pliku"<<endl;
        cout<<"2 - Losowy graf"<<endl;
        cout<<"3 - Wyswietl graf"<<endl;
        cout<<"4 - Algorytm 1 Prima"<<endl;
        cout<<"5 - Algorytm 2 Kruskala"<<endl;
}

void menuGlowne(){
    cout<<"1 - wyznaczanie najkrótszej ścieżki w grafie"<<endl;
    cout<<"2 - wyznaczanie minimalnego drzewa rozpinającego"<<endl;
}

void menuMST(){
    cout<<"Co chcesz zrobic?"<<endl;
        cout<<"1 - Wczytaj z pliku"<<endl;
        cout<<"2 - Losowy graf"<<endl;
        cout<<"3 - Wyswietl graf"<<endl;
        cout<<"4 - Algorytm 1 Dijkstry"<<endl;
        cout<<"5 - Algorytm 2 Forda-Bellmana"<<endl;
}

void wysListe(Graf graf){
    cout<<endl;
    Node *p;
    int suma=0;
    for( int i = 0; i < graf.ile_wierz; i++ )
    {
        p = graf.head [ i ];
        cout<<"Tab["<<i<<"]";
        while( p ){
            cout <<"   {"<< p->liczba <<" ,"<< p->waga<<"}  ";
            suma+=p->waga;
            p = p->next;
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"suma to  "<<suma/2<<endl;
    cout<<endl;
}

void wysMac(Graf graf){
    cout << "    ";
    int suma=0;
    for( int i = 0; i < graf.ile_wierz; i++ ) cout << setw ( 3 ) << i;
    cout << endl << endl;
    for( int i = 0; i < graf.ile_wierz; i++ )
    {
        cout << setw ( 3 ) << i<<" ";
        for( int j = 0; j < graf.ile_wierz; j++ ){
            cout << setw ( 3 ) << (int) graf.A [ i ][ j ];
            suma+=(int)graf.A [ i ][ j ];
        }
        cout << endl;
    }

    cout << endl;
    cout<<"suma to  "<<suma/2<<endl;
    cout<<endl;
}

int main(){
    string nazwaP, plik1, plik2;
    Graf graf;
    int Jak=0,a=0, gestosc, wierz=0;
    Kopiec kopiec;
    kopiec.ile=0;

    //nazwaP = "/Users/janzemlo/projekt_sdizo2/dane_mst2.txt";
    ///plik1= "/Users/janzemlo/projekt_sdizo2/";
    graf.A = NULL;

    menuGlowne();
    cin>>Jak;
    if(Jak==1){
        while(true){
            menuMST();
            cin>>Jak;
            if(Jak == 1){
                cout<<"Podaj nazwe pliku z rozszezeniem"<<endl;
                cin>>plik2;
                nazwaP = plik1+plik2;
                graf.wczytajGraf(nazwaP,1);
                wysListe(graf);
                wysMac(graf);
            }
            if(Jak == 2){
                cout<<"Podaj ilosc wierzchokkow"<<endl;
                cin>>graf.ile_wierz;
                cout<<"Podaj gestosc grafu (ponad 50 to bedzie spojny)"<<endl;
                cin>>gestosc;
                double licz;
                licz = ((double(gestosc)/100)*double(graf.ile_wierz)*(double(graf.ile_wierz) - 1))/2;
                graf.ile_kraw = (int) ceil( licz );
                graf.los(gestosc);
                wysListe(graf);
                wysMac(graf);
            }
            if(Jak == 3){
                wysListe(graf);
                wysMac(graf);
            }
            if(Jak == 4){
                if(graf.A!=NULL && graf.ile_kraw>=graf.ile_wierz-1){
                    //cout<<"Od jakiego wierzcholka zaczynamy od 0 do"<<graf.ile_wierz-1<<endl;
                    //cin>>wierz;
                    graf.gDieskryLis();
                    cout<<endl;
                    graf.gDieskryMac();
                }
            }
            if(Jak == 5){
                if(graf.A!=NULL && graf.ile_kraw>=graf.ile_wierz-1){
                    //cout<<"Od jakiego wierzcholka zaczynamy od 0 do"<<graf.ile_wierz-1<<endl;
                    //cin>>wierz;
                    graf.gFordLis();
                    cout<<endl;
                    graf.gFordMac();
                }
            }
            if(Jak == 0){
                cout<<endl<<"koniec programu"<<endl;
                break;
            }
        }
    }
    else if(Jak==2){
    while(true){
        menu();
        cin>>Jak;
        if(Jak == 1){
            cout<<"Podaj nazwe pliku z rozszezeniem"<<endl;
            cin>>plik2;
            nazwaP = plik1+plik2;
            graf.wczytajGraf(nazwaP,0);
            wysListe(graf);
            wysMac(graf);
        }
        if(Jak == 2){
            cout<<"Podaj ilosc wierzchokkow"<<endl;
            cin>>graf.ile_wierz;
            cout<<"Podaj gestosc grafu (ponad 50 to bedzie spojny)"<<endl;
            cin>>gestosc;
            double licz;
            licz = ((double(gestosc)/100)*double(graf.ile_wierz)*(double(graf.ile_wierz) - 1))/2;
            graf.ile_kraw = (int) ceil( licz );
            graf.los(gestosc);
            wysListe(graf);
            wysMac(graf);
        }
        if(Jak == 3){
            wysListe(graf);
            wysMac(graf);
        }
        if(Jak == 4){//&& graf.ile_kraw>=graf.ile_wierz-1
            if(graf.A!=NULL ){
                //cout<<"Od jakiego wierzcholka zaczynamy od 0 do"<<graf.ile_wierz-1<<endl;
                //cin>>wierz;
                graf.gPrimeLis(0);
                graf.gPrimeMac(0);
                wysListe(graf);
                wysMac(graf);
                }
        }
        if(Jak == 5){//&& graf.ile_kraw>=graf.ile_wierz-1
            if(graf.A!=NULL ){
                graf.gKruskalLis();
                graf.gKruskalMac();
                wysListe(graf);
                wysMac(graf);
            }
        }
        graf.poczatek = 0;
        if(Jak == 6){

            double sum = 0;
            double add = 1;

            // Start measuring time
            struct timeval begin, end;
            long seconds =0;
            long microseconds=0;

            
            graf.ile_wierz = 50;
                
            gestosc = 20;
            cout<<"podaj wuerz"<<endl;
            cin>>graf.ile_wierz;
            cout<<"podaj gestosc"<<endl;
            cin>>gestosc;

            for(int i=0; i<50; i++){
                
                double licz;
                licz = ((double(gestosc)/100)*double(graf.ile_wierz)*(double(graf.ile_wierz) - 1))/2;
                graf.ile_kraw = (int) ceil( licz );
                graf.los(gestosc);


                gettimeofday(&begin, 0);
                //graf.gPrimeLis(0);
                //graf.gPrimeMac(0);
                //graf.gKruskalLis();
                //graf.gKruskalMac();

                //graf.gDieskryLis();
                //graf.gDieskryMac();

                //graf.gFordLis();
                //graf.gFordMac();

                gettimeofday(&end, 0);

                seconds += end.tv_sec - begin.tv_sec;
                microseconds += end.tv_usec - begin.tv_usec;
            }

            // Stop measuring time and calculate the elapsed time
            double elapsed = (seconds + microseconds*1e-6)/50;
            
            cout<<endl;
            printf("Time measured: %.0f seconds.\n", elapsed*1000000);
            //cout<<"mikrosendy   "<<microseconds/50<<endl;
            cout<<endl;
            
        }
        if(Jak == 0){
            cout<<endl<<"koniec programu"<<endl;
            break;
        }
    }
    }

    return 0;
}