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
        void afegir fill (Arbre<T> &a);
        static const int ArbreInvalid = 400;
        // Comprova que el contingut de cada node coincideix amb el seu grau
        bool es_arbre_compta_graus ();
    private:
        Arbre (): arrel (NULL) {};
        struct node {
            T info ;
            node* primf ;
            node* seggerm;
        };
        node* arrel ;
        static node* copia arbre (node* p );
        static void destrueix arbre (node* p) throw();
        bool es_arbre_compta_graus (node* p);
};
// Aquí va la implementació del m`etode es arbre compta graus

template <typename T>
bool Arbre<T>::es_arbre_compta_graus (node* p)
{
    if (p->primf == nullptr)
    {
        return true;
    }

    int grau = 0;
    node* current = p->primf->seggerm;

    while(current != nullptr)
    {
        es_arbre_compta_graus(current);
        grau++;
        current = current->seggerm;
    }
    
    return p->primf == grau;
}

template <typename T>
bool Arbre<T>::es_arbre_compta_graus () 
{
    if (arrel == nullptr) return true;
    else return es_arbre_compta_graus (arrel);
}