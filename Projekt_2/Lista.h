#include <iostream>

using namespace std;

class Lista{

	public:
	struct Node * head;
	int ile;
    struct Node * ogon;

    bool wczytajListe(string pliczek);
    bool szukaj(int &ind, int lib);
    void delListafront();
	void delListamid(int ind);
	void delListaback();
	void delAll();
	void addListafront(int num);
	void addListamid(int num, int ind);
	void addListaback(int num);
	void random();
	void wyswietlListe();
};
