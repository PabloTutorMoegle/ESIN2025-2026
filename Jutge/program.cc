#include <iostream>
#include <cstdlib>

using namespace std;

typedef unsigned int nat;
template <typename T>

class Abin {
    public:
        Abin (): _arrel (NULL) {};
        // Pre: cert
        // Post: el resultat  ́es un arbre sense cap element
        Abin(Abin<T> &ae, const T &x, Abin<T> &ad);
        // Pre: cert
        // Post: el resultat  ́es un arbre amb un element i dos subarbres
        // Les tres grans
        Abin(const Abin<T> &a);
        ~Abin ();
        Abin<T>& operator=(const Abin<T>& a);
        // Escriu una l ́ınia amb els elements del nivell i-`essim, d’esquerra
        // a dreta. Cada element ha de sortir precedit d’un espai.
        void nivell (nat i ) const;
    private:
        struct node {
        node* f_esq ;
        node* f_dret ;
        T info ;
        };
        node* _arrel ;
        static node* copia_nodes (node* m);
        static void esborra_nodes (node* m);
        // Aqu ́ı va l’especificaci ́o dels m`etodes privats addicionals
        static void nivell_node(const node* n, nat i);
};
template <typename T>
void Abin<T>::nivell(nat i) const 
{
    nivell_node(_arrel, i);
}

template <typename T>
void Abin<T>::nivell_node(const typename Abin<T>::node* n, nat i) {
    if (n == NULL) return;
    if (i == 0) {
        cout << " " << n->info;
    } else {
        nivell_node(n->f_esq, i - 1);
        nivell_node(n->f_dret, i - 1);
    }
}
