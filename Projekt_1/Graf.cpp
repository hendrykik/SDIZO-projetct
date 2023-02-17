#include <iostream>
#include "Graf.h"
#include <fstream>
#include <cstdlib>
#include "Kopiec.h"
#include <stdlib.h>
#include <cstdio>

using namespace std;

struct Node{
	   int liczba;
       int waga;
	   struct Node* next;
};

struct Edge{
    int start;
    int koniec;
	int waga;
};

bool Graf::wczytajGraf(string pliczek, int a){

    ifstream plik;
    int val1, val2, meh;
    Node * p, *d;

    plik.open( pliczek.c_str() );//otwieranie pliku
    if( !plik.good() )
    {
         return false;
    }

    plik >> ile_kraw;
    plik >> ile_wierz;
    if(a==1){
        plik >> poczatek;
    }

    A = new char * [ ile_wierz ];  // Tworzymy tablicę wskaźników
    head = new Node * [ ile_wierz ]; //Tworzymy tablice list sasiedzctwa

    for( int i = 0; i < ile_wierz; i++ ) 
        head [ i ] = NULL; //na poczatku zerorujemy listy

    for( int i = 0; i < ile_wierz; i++ )
        A [ i ] = new char [ ile_wierz ]; // Tworzymy wiersze

    for( int i = 0; i < ile_wierz; i++ )
        for( int j = 0; j < ile_wierz; j++ ) A [ i ][ j ] = 0;

    for( int i = 0; i < ile_kraw; i++ )
    { 
        plik >> val1;//wierzcholek 1
        plik >> val2;//wierzcholek 2
        plik >> meh;//wartosc krawedzi

        p = new Node;    // Tworzymy pierwszy element
        d = new Node;    // Tworzymy drugi element


        p->liczba = val2;          //przypisujemy wartosc
        p->next = head [ val1 ]; // nastepny element ot poprzedni pierszy
        p->waga = meh; //przypisanie wagi krawedzi
        head [ val1 ] = p; //dajemy go na poczatek listy
        A [ val1 ][ val2 ] = meh; // Krawędź v1->v2 obecna

        if(a==0){
        d->liczba = val1;          //przypisujemy wartosc
        d->next = head [ val2 ]; // nastepny element ot poprzedni pierszy
        d->waga = meh; //przypisanie wagi krawedzi
        head [ val2 ] = d; //dajemy go na poczatek listy
        A [ val2 ][ val1 ] = meh;
        }
    }
	plik.close();

    return true;
}

void Graf::los(int gesc){
    int val1, val2, meh, pentla=0, TabWag[ile_kraw];
    Node * p, *d;

    poczatek = 0;

    for( int i = 0; i < ile_kraw; i++ ) 
        TabWag [ i ] = -1; //na poczatku zerorujemy listy

    A = new char * [ ile_wierz ];  // Tworzymy tablicę wskaźników
    head = new Node * [ ile_wierz ]; //Tworzymy tablice list sasiedzctwa

    for( int i = 0; i < ile_wierz; i++ ) 
        head [ i ] = NULL; //na poczatku zerorujemy listy

    for( int i = 0; i < ile_wierz; i++ )
        A [ i ] = new char [ ile_wierz ]; // Tworzymy wiersze
    
    for( int i = 0; i < ile_wierz; i++ )
        for( int j = 0; j < ile_wierz; j++ ) A [ i ][ j ] = 0;
    

    for( int i = 0; i < ile_kraw; i++ )
    { 
        pentla = 0;
        if(i<ile_wierz){
            val1 = i;//wierzcholek 1
            while(pentla==0){
                    val2 = rand()%ile_wierz;//wierzcholek 2
                    if(val2 != val1 && A [ val1 ][ val2 ]==0) pentla=1;
            }
        }
        else{
            while(pentla==0){
                    val1 = rand()%ile_wierz;//wierzcholek 1
                    val2 = rand()%ile_wierz;//wierzcholek 2
                    if(val2 != val1 && A [ val1 ][ val2 ]==0) pentla=1;
            }
        }

        meh = rand()%30 + 1;//wartosc krawedzi.

        p = new Node;    // Tworzymy pierwszy element
        d = new Node;    // Tworzymy drugi element

        p->liczba = val2;          //przypisujemy wartosc
        p->next = head [ val1 ]; // nastepny element ot poprzedni pierszy
        p->waga = meh; //przypisanie wagi krawedzi
        head [ val1 ] = p; //dajemy go na poczatek listy

        d->liczba = val1;          //przypisujemy wartosc
        d->next = head [ val2 ]; // nastepny element ot poprzedni pierszy
        d->waga = meh; //przypisanie wagi krawedzi
        head [ val2 ] = d; //dajemy go na poczatek listy

        A [ val1 ][ val2 ] = meh; // zapisujemy wartosc krawedzi
        A [ val2 ][ val1 ] = meh;
    }

    if(gesc == 99){//usuwanie 1% krawedzi
        float usun;
        usun = 0.01*ile_kraw;
        for(float i=0; i<usun;){
            val1 = rand()%ile_wierz;//wierzcholek 1
            val2 = rand()%ile_wierz;//wierzcholek 2
            if(val2 != val1 && A [ val1 ][ val2 ]!=0){ 
                i++;
                A [ val1 ][ val2 ]=0;
                A [ val2 ][ val1 ]=0;
                p = head[val1];
                d=p;
                pentla = 0;
                while(p && pentla==0){
                    if(p->liczba == val2){
                        if(head[val1] == p){head[val1] = p->next;}
                        if(p->next) {d->next = p->next; }
                        pentla=1;
                    }
                    else{
                    d=p;
                    p = p->next;}
                }
                p = head[val2];
                d=p;
                pentla = 0;
                while(p && pentla==0){
                    if(p->liczba == val1){
                        if(head[val2] == p){head[val2] = p->next;}
                        if(p->next) {d->next = p->next;}
                        pentla=1;
                    }
                    d=p;
                    p = p->next;
                }
                }
        }
    }
}

void Graf::gPrimeLis(int pocz){

    int min, nast=-1, pent1=0, pent2=0,pent3 = 0, kolejny, poprzedni, start, koniec;
    bool Tab[ile_wierz];
    Kopiec kopiec;
    struct Node ** nowy;

    kopiec.ile=0;
    Node *p, *d, *r, *a, *b;
    p = new Node; d = new Node;  r = new Node;  a = new Node; b = new Node; 

    nowy = new Node * [ ile_wierz ]; //Tworzymy tablice list sasiedzctwa

    for( int i = 0; i < ile_wierz; i++ ) 
        nowy [ i ] = NULL; //na poczatku zerorujemy listy

    for(int i=0; i<ile_wierz;i++) Tab[i] = false;
    
    int iter=0;

    for(int w=0; w<ile_wierz-1; w++){
        Tab[pocz] = true;

        p = head [ pocz ];
        while( p ){
            kopiec.ile++;
            if(kopiec.ile==1) {kopiec.wsk = new Edge[kopiec.ile];}
            else {kopiec.wsk=(Edge*)realloc(kopiec.wsk,(kopiec.ile)*sizeof(Edge));}//zmieniennie wielkosci tablicy dla kopca
            kopiec.wsk[kopiec.ile-1].waga = p->waga; //pyrzpisanie wartosci wagi krawedzi w kopcu
            kopiec.wsk[kopiec.ile-1].start = pocz;
            kopiec.wsk[kopiec.ile-1].koniec = p->liczba;
            kopiec.dodajKop();//uporzadkowanie kopca
            p = p->next;//przejscie do nastepnej krawedzi
        }
        pent1=0; 
        pent2=0;
        pent3=0;

        while(pent1==0 && kopiec.wsk[0].waga){

            min = kopiec.wsk[ 0 ].waga;
            start = kopiec.wsk[ 0 ].start;
            koniec = kopiec.wsk[ 0 ].koniec;
            
            kopiec.extracMin(); 
            pent3 = 0;

            p = head[ start ];

            while(p && pent3==0){
                if( p->waga == min  ){
                    r = p;

                    if(Tab[p->liczba] == false){
                        pent3 = -1;
                        pent1 = -1;
                    }
                }
                p = p->next;
            }   

            if(pent3 ==0 ) p = head[ koniec ];
            
            while(p && pent3==0){
                if( p->waga == min  ){
                    r = p;
                    
                    if(Tab[start] == false){
                        pent3 = -1;
                        pent1 = -1;
                        pent2 = -1;
                    }
                }
                p = p->next;
            }     
        }

        if (pent2 != -1) p = head[ start ];
        if (pent2 == -1) p = head[ koniec ];

        //dodawanie wartosci do nowej struktury
        
        a = new Node;
        b = new Node;

        a->liczba = r->liczba;          //przypisujemy wartosc
        a->next = nowy [ pocz ]; // nastepny element ot poprzedni pierszy
        a->waga = r->waga; //przypisanie wagi krawedzi
        nowy [ pocz ] = a; //dajemy go na poczatek listy


        b->liczba = pocz;          //przypisujemy wartosc
        b->next = nowy [ r->liczba ]; // nastepny element to poprzedni pierszy
        b->waga = r->waga; //przypisanie wagi krawedzi
        nowy [ r->liczba ] = b; //dajemy go na poczatek listy

        //pocz = koniec;
        if (pent2 != -1) pocz = koniec;
        if (pent2 == -1) pocz = start;
    } 

    delete[] head;

    head = nowy;
    
    kopiec.usunKop();
}

void Graf::gPrimeMac(int pocz){

    int min, pent1=0, pent2=0, kolejny, poprzedni, uniq, start, koniec;
    bool Tab[ile_wierz];
    Kopiec kopiec;
    char** nowy;

    nowy = new char * [ ile_wierz ]; 
    
    kopiec.ile=0;

    for( int i = 0; i < ile_wierz; i++ )
        nowy [ i ] = new char [ ile_wierz ]; // Tworzymy wiersze

    for( int i = 0; i < ile_wierz; i++ )
        for( int j = 0; j < ile_wierz; j++ ) nowy [ i ][ j ] = 0;

    for(int i=0; i<ile_wierz;i++) Tab[i] = false;

    for(int w=0; w<ile_wierz-1; w++){  
        Tab[pocz] = true;
        for(int i=0; i<ile_wierz; i++){
            if(A[pocz][i] != 0 && nowy[pocz][i]==0){
            kopiec.ile++;
            if(kopiec.ile==1) kopiec.wsk = new Edge[kopiec.ile];
            else kopiec.wsk=(Edge*)realloc(kopiec.wsk,(kopiec.ile)*sizeof(Edge));//zmieniennie wielkosci tablicy dla kopca
            kopiec.wsk[kopiec.ile-1].waga = (int)A[pocz][i]; //pyrzpisanie wartosci wagi krawedzi w kopcu
            kopiec.wsk[kopiec.ile-1].start = pocz;
            kopiec.wsk[kopiec.ile-1].koniec = i;
            kopiec.dodajKop();//uporzadkowanie kopca
            }
        }
        pent1=0; 
        pent2=0;

        while(pent1==0 && kopiec.wsk[0].waga){
            min = kopiec.wsk[ 0 ].waga;
            start = kopiec.wsk[ 0 ].start;
            koniec = kopiec.wsk[ 0 ].koniec;

            kopiec.extracMin(); 
            
            if((int)A[start][koniec]==min && Tab[koniec]==false){
                kolejny = start;
                poprzedni = koniec;
                pent1=1;
            }
            else if((int)A[koniec][start]==min && Tab[start]==false){
                kolejny = koniec;
                poprzedni = start;
                pent1=1;
            }
        }
        nowy [kolejny][poprzedni] = A [kolejny][poprzedni];
        nowy [poprzedni][kolejny] = A [kolejny][poprzedni];

        pocz = poprzedni;
    }

    delete[] A;
    A = nowy;
}

class Parent{
    public:
        int ranga;
        Parent* rodzic;
};

void Graf::gKruskalLis(){
    int min, pent0=-1, pent1=-1, val1, val2, ilosc=0, gd1=0, gd2=0, start, koniec, pent2, k;
    bool Tab[ile_wierz];
    Kopiec kopiec;
    struct Node ** nowy;

    Parent** par = new Parent* [ile_wierz];
    Parent* ro= new Parent;
    Parent* md= new Parent;

    kopiec.ile=0;

    Node *p, *d, *r, *a, *b;
    p = new Node; d = new Node;  r = new Node;  a = new Node; b = new Node; 
    nowy = new Node * [ ile_wierz ]; //Tworzymy tablice list sasiedzctwa

    for( int i = 0; i < ile_wierz; i++ ) 
        {
            ro = new Parent;
            nowy [ i ] = NULL; //na poczatku zerorujemy listy
            ro->ranga = 0;
            ro->rodzic = ro;
            par[i]=ro;
        }
    for(int i=0; i<ile_wierz;i++) Tab[i] = false;
    for( int i = 0; i < ile_wierz-1; i++ )
    {
        p = head [ i ];
        Tab[i] = true;
        while( p ){
            pent0=-1;
            if(Tab[p->liczba]==false){
                kopiec.ile++;
                if(kopiec.ile==1) kopiec.wsk = new Edge[kopiec.ile];
                else kopiec.wsk=(Edge*)realloc(kopiec.wsk,(kopiec.ile)*sizeof(Edge));//zmieniennie wielkosci tablicy dla kopca
                kopiec.wsk[kopiec.ile-1].waga = p->waga; //pyrzpisanie wartosci wagi krawedzi w kopcu
                kopiec.wsk[kopiec.ile-1].start = i;
                kopiec.wsk[kopiec.ile-1].koniec = p->liczba;
                kopiec.dodajKop();//uporzadkowanie kopca
            }
            p = p->next;//przejscie do nastepnej krawedzi
        }
    }
    
    for(int i=0; i<ile_wierz;i++) Tab[i] = false;//wyzerowanie talbicy
    //ilosc<ile_wierz-1


    for(int i=0; ilosc<ile_wierz-1 && kopiec.ile!=1; i++){
        min = kopiec.wsk[ 0 ].waga;//wziecie najmniejesz liczby z kopca
        start = kopiec.wsk[ 0 ].start;
        koniec = kopiec.wsk[ 0 ].koniec;
        kopiec.extracMin(); //usuniecie jest z kopca
        pent1=-1;//warunek fukcji
        pent2=0;
        for(int l=0; l<2 && pent1==-1; l++){
            if(l==0){p = head[start]; k=start;}
            if(l==1){p = head[koniec]; k=koniec;}
            //p = head[k];//pierwszy element tabeli sadziedztwa dla i
            while(p && pent1==-1){
                if(p->waga == min){
                        ro= par[k];
                        md= par[p->liczba];
                        while(ro->rodzic!=ro){
                            ro = ro->rodzic;
                        }
                        while(md->rodzic!=md){
                            md = md->rodzic;
                        }
                        if(ro != md){
                            if(ro->ranga < md->ranga){
                                md = par[p->liczba];
                                for(int l=0; l<ile_wierz;l++){if(par[l]==ro) gd1=l;}

                                ro->rodzic = md;
                                par[gd1] = ro;
                            }
                            else if(ro->ranga==md->ranga){
                                md->rodzic = ro;
                                ro->ranga++;

                                for(int l=0; l<ile_wierz;l++){if(par[l]==ro) gd1=l;}
                                for(int l=0; l<ile_wierz;l++){if(par[l]==md) gd2=l;}
                                par[gd2] = md;
                                par[gd1] = ro;
                            }
                            else{
                                ro= par[k];

                                for(int l=0; l<ile_wierz;l++){if(par[l]==md) gd1=l;}
                                md->rodzic = ro;
                                par[gd1] = md;
                            }
                            val1 = p->liczba;
                            val2 = k;
                            pent1=0;
                            Tab[ilosc] = true;
                        }
                }
                p = p->next;//przejscie od nastepnego elementu
            }
            
        }
        if(pent1 == 0){
            ilosc++;

            a = new Node;
            b = new Node;
            a->liczba = val1;          //przypisujemy wartosc
            a->next = nowy [ val2 ]; // nastepny element ot poprzedni pierszy
            a->waga = min; //przypisanie wagi krawedzi
            nowy [ val2 ] = a; //dajemy go na poczatek listy

            b->liczba = val2;          //przypisujemy wartosc
            b->next = nowy [ val1 ]; // nastepny element ot poprzedni pierszy
            b->waga = min; //przypisanie wagi krawedzi
            nowy [ val1 ] = b; //dajemy go na poczatek listy
        }
    }
    delete[] par;
    delete[] head;
    head = nowy;
    kopiec.usunKop();

}

void Graf::gKruskalMac(){
    int min, pent0=-1, pent1=-1, val1, val2, ilosc=0, gd1=0, gd2=0,k,j, start, koniec;
    bool Tab[ile_wierz];
    Kopiec kopiec;
    char** nowy;
    Parent** par = new Parent* [ile_wierz];
    Parent* ro= new Parent;
    Parent* md= new Parent;

    kopiec.ile=0;

    nowy = new char * [ ile_wierz ]; 
    
    for( int i = 0; i < ile_wierz; i++ ) 
    {
        ro = new Parent;
        ro->ranga = 0;
        ro->rodzic = ro;
        par[i]=ro;
    }
    
    kopiec.ile=0;

    for( int i = 0; i < ile_wierz; i++ )
        nowy [ i ] = new char [ ile_wierz ]; // Tworzymy wiersze

    for( int i = 0; i < ile_wierz; i++ )
        for( int j = 0; j < ile_wierz; j++ ) nowy [ i ][ j ] = 0;

    for(int i=0; i<ile_wierz;i++) Tab[i] = false;

    
    for( int i = 0; i < ile_wierz; i++ )
    {
        Tab[i] = true;
        for( int k=0; k<ile_wierz; k++){
            if(Tab[k]==false && (int)A[i][k]!=0){
            kopiec.ile++;
            if(kopiec.ile==1) kopiec.wsk = new Edge[kopiec.ile];
            else kopiec.wsk=(Edge*)realloc(kopiec.wsk,(kopiec.ile)*sizeof(Edge));//zmieniennie wielkosci tablicy dla kopca
            kopiec.wsk[kopiec.ile-1].waga = (int)A[i][k]; //pyrzpisanie wartosci wagi krawedzi w kopcu
            kopiec.wsk[kopiec.ile-1].start = i;
            kopiec.wsk[kopiec.ile-1].koniec = k;
            kopiec.dodajKop();//uporzadkowanie kopca
            }
        }
    }

    for(int i=0; i<ile_wierz;i++) Tab[i] = false;//wyzerowanie talbicy

    
    for(int i=0; ilosc<ile_wierz-1 && kopiec.wsk[0].waga;){
        min = kopiec.wsk[ 0 ].waga;//wziecie najmniejesz liczby z kopca
        start = kopiec.wsk[ 0 ].start;
        koniec = kopiec.wsk[ 0 ].koniec;
        kopiec.extracMin(); //usuniecie jest z kopca
        pent1=-1;//warunek fukcji
        
            for(int l=0; l<2 && pent1==-1; l++){
                if(l==0) {k = start; j=koniec;}
                if(l==1) {k = koniec; j=start;}

                if((int)A[k][j] == min){
                        ro= par[j];//k
                        md= par[k];//p liczba
                        while(ro->rodzic!=ro){
                            ro = ro->rodzic;
                        }
                        while(md->rodzic!=md){
                            md = md->rodzic;
                        }
                        if(ro != md){
                            if(ro->ranga < md->ranga){
                                md = par[k];
                                for(int l=0; l<ile_wierz;l++){if(par[l]==ro) gd1=l;}

                                ro->rodzic = md;
                                par[gd1] = ro;
                            }
                            else if(ro->ranga==md->ranga){
                                md->rodzic = ro;
                                ro->ranga++;

                                for(int l=0; l<ile_wierz;l++){if(par[l]==ro) gd1=l;}
                                for(int l=0; l<ile_wierz;l++){if(par[l]==md) gd2=l;}
                                par[gd2] = md;
                                par[gd1] = ro;
                            }
                            else{
                                ro= par[j];

                                for(int l=0; l<ile_wierz;l++){if(par[l]==md) gd1=l;}
                                md->rodzic = ro;
                                par[gd1] = md;
                            }
                            val1 = k;
                            val2 = j;
                            pent1=0;
                            Tab[ilosc]=true;
                        }   
                }
            }
        
       
        if(pent1 == 0){
            ilosc++;
            nowy[val1][val2]=min;
            nowy[val2][val1]=min;
        }
    }

    delete[] par;
    delete[] A;
    A = nowy;

}

void Graf::gDieskryLis(){
    int Wagi[ile_wierz], kraw, waga_1, min;
    bool Tab[ile_wierz];
    struct Node ** nowy;
    
    Node *p, *d, *e, *f, *g;
    p = new Node; d = new Node; e = new Node; f = new Node; g = new Node; 

    nowy = new Node * [ ile_wierz ]; //Tworzymy tablice list sasiedzctwa

    for( int i = 0; i < ile_wierz; i++ ) 
        nowy [ i ] = NULL; //na poczatku zerorujemy listy

    for(int i=0; i<ile_wierz;i++) {Tab[i] = false; Wagi[i]=10000;}
    
    Wagi[poczatek] = 0;
    kraw = poczatek;
    for(int i=0; i<ile_wierz; i++){
        min=1000;
        for(int j=0; j<ile_wierz; j++){if( Wagi[j] < min && Tab[j]==false) {kraw = j; min=Wagi[j];}}
        Tab[kraw] = true;
        p = head [kraw];
        waga_1 = Wagi[kraw];
        while(p){
            if(Wagi[p->liczba] > p->waga + waga_1){
                Wagi[p->liczba] = p->waga + waga_1;

                e = new Node;
                d = nowy[i];
                f = e;
                while(d){
                    e->liczba = d->liczba;
                    g = new Node;
                    e->next = g;
                    e=e->next;
                    d=d->next;
                }
                e->liczba = i;
                e->waga = Wagi[p->liczba];
                nowy[p->liczba] = f;
            }
            p=p->next;
        }
        // for(int j=0; j<ile_wierz; j++){
        //     //cout<<j<<"  waga  "<<Wagi[j]<<endl;
        // }
    }

    for( int i = 0; i < ile_wierz; i++ )
    {
        p = nowy [ i ];
        cout<<"Droga["<<i<<"]";
        while( p ){
            cout <<"  "<< p->liczba <<"   ";
            p = p->next;
        }
        cout<<" waga   "<<Wagi[i];
        cout<<endl;
    }

    //cout<<endl;
}

void Graf::gDieskryMac(){
    int Wagi[ile_wierz], kraw, waga_1, min;
    bool Tab[ile_wierz];
    struct Node ** nowy;
    
    Node *p, *d, *e, *f, *g;
    p = new Node; d = new Node; e = new Node; f = new Node; g = new Node; 

    nowy = new Node * [ ile_wierz ]; //Tworzymy tablice list sasiedzctwa

    for( int i = 0; i < ile_wierz; i++ ) 
        nowy [ i ] = NULL; //na poczatku zerorujemy listy

    for(int i=0; i<ile_wierz;i++) {Tab[i] = false; Wagi[i]=10000;}

    Wagi[poczatek] = 0;
    kraw = poczatek;
    
    for(int i=0; i<ile_wierz; i++){
        min=1000;
        for(int j=0; j<ile_wierz; j++){if( Wagi[j] < min && Tab[j]==false) {kraw = j; min=Wagi[j];}}
        Tab[kraw] = true;
        waga_1 = Wagi[kraw];
        
        for(int j=0; j<ile_wierz; j++){

            if(Wagi[j] > (int)A[kraw][j] + waga_1 && (int)A[kraw][j]!=0){
                Wagi[j] = (int)A[kraw][j] + waga_1;

                e = new Node;
                d = nowy[i];
                f = e;
                while(d){
                    e->liczba = d->liczba;
                    g = new Node;
                    e->next = g;
                    e=e->next;
                    d=d->next;
                }
                e->liczba = kraw;
                e->waga = Wagi[j];
                nowy[j] = f;
            }
        }
    }


    // for(int j=0; j<ile_wierz; j++){
    //     //cout<<j<<"  waga  "<<Wagi[j]<<endl;
    // }
    
    for( int i = 0; i < ile_wierz; i++ )
    {
        p = nowy [ i ];
        cout<<"Droga["<<i<<"]";
        while( p ){
            cout <<"  "<< p->liczba <<"   ";
            p = p->next;
        }
        cout<<" waga   "<<Wagi[i];
        cout<<endl;
    }

    //cout<<endl;
}

void Graf::gFordLis(){
    int Wagi[ile_wierz], kraw, waga_1, min;
    bool Tab[ile_wierz];
    struct Node ** nowy;
    
    Node *p, *d, *e, *f, *g;
    p = new Node; d = new Node; e = new Node; f = new Node; g = new Node; 

    nowy = new Node * [ ile_wierz ]; //Tworzymy tablice list sasiedzctwa

    for(int i=0; i<ile_wierz;i++) {Tab[i] = false;}

    for( int i = 0; i < ile_wierz; i++ ) 
        nowy [ i ] = NULL; //na poczatku zerorujemy listy

    for(int i=0; i<ile_wierz;i++) {Tab[i] = false; Wagi[i]=10000;}
    
    Wagi[poczatek] = 0;
    kraw = poczatek;

    for(int z=0; z<ile_wierz; z++){
        for(int i=0; i<ile_wierz; i++){
            p = head[i];
            while(p){
                if(Wagi[p->liczba] > Wagi[i] + p->waga){
                    Wagi[p->liczba] = Wagi[i] + p->waga;

                    e = new Node;
                    d = nowy[i];
                    f = e;
                    while(d){
                        e->liczba = d->liczba;
                        g = new Node;
                        e->next = g;
                        e=e->next;
                        d=d->next;
                    }
                    e->liczba = i;
                    e->waga = Wagi[p->liczba];
                    nowy[p->liczba] = f;
                }
                p=p->next;
            }


        }
    }
    for( int i = 0; i < ile_wierz; i++ )
    {
        p = nowy [ i ];
        cout<<"Droga["<<i<<"]";
        while( p ){
            cout <<"  "<< p->liczba <<"   ";
            p = p->next;
        }
        cout<<" waga   "<<Wagi[i];
        cout<<endl;
    }
}

void Graf::gFordMac(){
    int Wagi[ile_wierz], kraw, waga_1, min;
    bool Tab[ile_wierz];
    struct Node ** nowy;
    
    Node *p, *d, *e, *f, *g;
    p = new Node; d = new Node; e = new Node; f = new Node; g = new Node; 

    nowy = new Node * [ ile_wierz ]; //Tworzymy tablice list sasiedzctwa

    for(int i=0; i<ile_wierz;i++) {Tab[i] = false;}

    for( int i = 0; i < ile_wierz; i++ ) 
        nowy [ i ] = NULL; //na poczatku zerorujemy listy

    for(int i=0; i<ile_wierz;i++) {Tab[i] = false; Wagi[i]=10000;}
    
    Wagi[poczatek] = 0;
    kraw = poczatek;

    for(int z=0; z<ile_wierz; z++){
        for(int i=0; i<ile_wierz; i++){
            for(int j=0; j<ile_wierz; j++){
                if(Wagi[j] > Wagi[i] + (int) A[i][j]  && (int)A[i][j]!=0){
                    Wagi[j] = Wagi[i] + (int) A[i][j];

                    e = new Node;
                    d = nowy[i];
                    f = e;
                    while(d){
                        e->liczba = d->liczba;
                        g = new Node;
                        e->next = g;
                        e=e->next;
                        d=d->next;
                    }
                    e->liczba = i;
                    e->waga = Wagi[j];
                    nowy[j] = f;
                }
            }
            
            // //cout<<endl;
            // for(int j=0; j<ile_wierz; j++){
            //     //cout<<j<<"  waga  "<<Wagi[j]<<endl;
            // }
        }
    }
    for( int i = 0; i < ile_wierz; i++ )
    {
        p = nowy [ i ];
        cout<<"Droga["<<i<<"]";
        while( p ){
            cout <<"  "<< p->liczba <<"   ";
            p = p->next;
        }
        cout<<" waga   "<<Wagi[i];
        cout<<endl;
    }
}

void Graf::usunGraf(){

    Node *wsk,*d;
    for(int i=0; i<ile_wierz;i++){
    wsk = head[i];
    do{
        d=wsk;
        wsk = wsk->next;
        free(d);
    }while(wsk->next);
    }
    delete[] head;
    delete[] A;
}