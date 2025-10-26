#include <cstdlib>
#include <string>

using namespace std;

typedef unsigned int nat;

template <typename T>
class Arbre {
    public:
        // Construeix un Arbre format per un  ́unic node que cont ́e a x.
        Arbre(const T &x);
        // Tres grans.
        Arbre(const Arbre<T> &a);
        Arbre& operator=(const Arbre<T> &a);
        ~Arbre () throw();
        // Col·loca l’Arbre donat com a primer fill de l’arrel de l’arbre sobre el que s’aplica el
        //m`etode i l’arbre a queda invalidat; despr ́es de fer b.afegir fill(a), a no  ́es un arbre v`alid.
        void afegir_fill (Arbre<T> &a);
        static const int ArbreInvalid = 400;
        // Comprova que el contingut de cada node coincideix amb el seu grau
        bool es_arbre_compta_graus ();
    private:
        Arbre (): _arrel (NULL) {};
        struct node {
            T info ;
            node* primf ;
            node* seggerm;
        };
        node* _arrel ;
        static node* copia_arbre (node* p );
        static void destrueix_arbre (node* p) throw();
        bool es_arbre_compta_graus (node* p);
};
// Aquí va la implementació del m`etode es arbre compta graus

template <typename T>
bool Arbre<T>::es_arbre_compta_graus (node* p)
{
    bool res = true;
    if (p == nullptr)
    {
        return res;
    }

    int grau = 0;
    node* current = p->primf;

    while(current != nullptr && res)
    {
        res = es_arbre_compta_graus(current);
        grau++;
        current = current->seggerm;
    }
    
    if (p->info != grau) res = false;
    return res;
}

template <typename T>
bool Arbre<T>::es_arbre_compta_graus () 
{
    if (_arrel == nullptr) return true;
    else return es_arbre_compta_graus (_arrel);
}
