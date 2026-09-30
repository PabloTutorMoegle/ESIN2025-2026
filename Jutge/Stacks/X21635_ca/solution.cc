#include <cstdlib>
#include <iostream>

using namespace std;

typedef unsigned int nat;

template <typename T>
class Abin {
    public:
        Abin(): _arrel (NULL) {};
        // Pre: cert
        // Post: el resultat  ́es un arbre sense cap element
        Abin(Abin<T> &ae, const T &x, Abin<T> &ad);
        // Pre: cert
        // Post: el resultat  ́es un arbre amb un element i dos subarbres
        // Les tres grans
        Abin(const Abin<T> &a);
        ~Abin();
        Abin<T>& operator=(const Abin<T>& a);
        // operador ¡¡ d’escriptura
        template <class U> friend std::ostream& operator<<(std::ostream&, const Abin<U> &a);
        // operador ¿¿ de lectura
        template <class U> friend std::istream& operator>>(std::istream&, Abin<U> &a);
        bool compleix_suma_fills () const;
        // Pre: true
        // Post: retorna si compleix la propietat ’Suma dels fills’:
        // Per tot node el seu valor  ́es igual a la suma dels valors
        // dels nodes (arrels) del fill esquerre i del fill dret.
    private:
        struct node {
            node* f_esq ;
            node* f_dret ;
            T info ;
        };
        node* _arrel ;
        static node* copia_nodes (node* m);
        static void esborra_nodes (node* m);
    static void print_nodes (node* m, ostream &os, string d1);
    // Aqu ́ı va l’especificaci ́o dels m`etodes privats addicionals
    bool compleix_suma_fills(node* _arrel) const;
};
// Aqui va la implementaci ́o del m`etode compleix suma fills i dels privats addicionals

template <typename T>
bool Abin<T>::compleix_suma_fills(node* _arrel) const
{
    if (_arrel == nullptr) return true;

    // If leaf, property holds trivially
    if (_arrel->f_esq == nullptr && _arrel->f_dret == nullptr) return true;

    int left = _arrel->f_esq ? _arrel->f_esq->info : 0;
    int right = _arrel->f_dret ? _arrel->f_dret->info : 0;

    if (_arrel->info != left + right) return false;

    // Check recursively both subtrees
    return compleix_suma_fills(_arrel->f_esq) && compleix_suma_fills(_arrel->f_dret);
}

template <typename T>
bool Abin<T>::compleix_suma_fills () const 
{
    if (_arrel == nullptr) 
        return true;

    if (_arrel->f_esq == nullptr && _arrel->f_dret == nullptr)
        return true;

    node* temp = _arrel;
    bool r = compleix_suma_fills(temp);
    return r;
}
