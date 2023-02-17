#include <iostream>

using namespace std;

class Graf{

	public:
	int ile_wierz;
    int ile_kraw;
    int poczatek;
    
    char** A;
    struct Node ** head;

    bool wczytajGraf(string pliczek, int a);
    void los(int gesc);
    void gPrimeLis(int pocz);
    void gPrimeMac(int pocz);
    void gKruskalLis();
    void gKruskalMac();

    void gDieskryLis();
    void gDieskryMac();
    void gFordLis();
    void gFordMac();

    void usunGraf();
};