#include <iostream>

using namespace std;

class Tablica{
public:

    int* wsk;
    int ile;

    bool wczytajTab(string pliczek);
    void delTab(int ind);
    void delAll();
    void dodajTab(int ind,int num);
    bool znajdzTab(int liba);
    void randomTab();
    void wysTab();
};
