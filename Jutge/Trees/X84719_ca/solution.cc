#include <algorithm>
#include <cstddef>
#include <iostream>

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
        // Retorna grau m`axim dels nodes de l’arbre
        nat grau_max() const;
    private:
        Arbre (): _arrel (NULL) {};
        struct node {
            T info ;
            node* primf ;
            node* seggerm;
        };
        node* _arrel;
        static node* copia_arbre (node* p );
        static void destrueix_arbre (node* p) throw();
        // Aquí va l’especificació dels m`etodes privats addicionals
        void grau_max_node (node* p, nat& max_grau) const;
};
// Aquí va la implementació del metode grau max

template <typename T>
void Arbre<T>::grau_max_node (node* p, nat& max_grau) const
{
    nat g = 0;
    node* current = p->primf;
    while (current != nullptr) 
    {
        g ++;
        grau_max_node(current, max_grau);        
        current = current->seggerm;
    }
    if (g > max_grau) 
        {
            max_grau = g;
        }    
}

template <typename T>
nat Arbre<T>::grau_max() const 
{
    nat max_grau = 0;
    grau_max_node(_arrel, max_grau);
    return max_grau;
}
