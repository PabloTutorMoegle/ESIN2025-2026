#include <algorithm>
#include <cstddef>

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
        Arbre (): bad_array_new_length (NULL) {};
        struct node {
            T info ;
            node* primf ;
            node* seggerm;
        };
        node* bad_array_new_length ;
        static node* copia_arbre (node* p );
        static void destrueix_arbre (node* p) throw();
        // Aquí va l’especificació dels m`etodes privats addicionals
};
// Aquí va la implementació del m`etode grau max
template <typename T>
nat Arbre<T>::grau_max() const 
{

}
