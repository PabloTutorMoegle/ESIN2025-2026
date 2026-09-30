#include <cstdlib>
#include <iostream>
using namespace std;
typedef unsigned int nat;
template <typename T>
class Abin {
    public:
    Abin():_arrel (NULL) {};
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
    // Modifica el contingut de l’arbre per tal de guardar a cada node la suma dels
    // nodes del seu subarbre.
    void arbre_sumes ();
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
    static void arbre_sumes_nodes(node* m);
    // Aqu ́ı va la implementaci ́o del m`etode arbre sumes
};

template <typename T>
void Abin<T>::arbre_sumes()
{
    // Deleguem en la funció estàtica que treballa sobre node*
    arbre_sumes_nodes(_arrel);
}

template <typename T>
void Abin<T>::arbre_sumes_nodes(node* m)
{
    if (m == nullptr) return;

    if (m->f_esq == nullptr && m->f_dret == nullptr) {
        // És una fulla, no cal canviar res
        return;
    }
    
    // Repetir per als fills
    arbre_sumes_nodes(m->f_esq);
    arbre_sumes_nodes(m->f_dret);

    // Calcular la suma dels fills
    T suma_fills = m->info;
    if (m->f_esq) suma_fills += m->f_esq->info;
    if (m->f_dret) suma_fills += m->f_dret->info;
    
    // Actualitzar el node actual
    m->info = suma_fills;
}

