#include <iostream>

using namespace std;

class Kopiec{
public:

    int ile;
    int tab[110001];

    int rodzic(int i);
    int l(int i);
    int r(int i);

    void nowyKop();
    bool wczytajKopiec(string pliczek);
    void dodajKop(int num);
    bool usunKop(int ind);
    void naprawUp(int i);
    void naprawDown(int i);
    void wysLin();
    void sprawdz(int ind);
    bool znajdz(int ind);
    void random(int ind);

    void wysKop(const std::string& prefix, int i, bool isLeft);
    void wysAll(const std::string& prefix, int i, bool isLeft);

};
