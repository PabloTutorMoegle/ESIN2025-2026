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
        max_grau ++;
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
#include <iostream>
#include <stack>

template <typename T>				
typename Arbre<T>::node* Arbre<T>::copia_arbre(node* p) { 
  node* aux = NULL;
  if (p != NULL) {
    aux = new node;
    try {
      aux -> info = p -> info;
      aux -> primf = aux -> seggerm = NULL;
      aux -> primf = copia_arbre(p -> primf);
      aux -> seggerm = copia_arbre(p -> seggerm);
    }
    catch (...) {
      destrueix_arbre(aux);
    }
  }
  return aux;
}

template <typename T>	
void Arbre<T>::destrueix_arbre(node* p) throw() { 
  if (p != NULL) {
    destrueix_arbre(p -> primf);
    destrueix_arbre(p -> seggerm);
    delete p;
  }
}

template <typename T>	
Arbre<T>::Arbre(const T &x) {
  _arrel = new node; 
  try {
    _arrel -> info = x;
    _arrel -> seggerm = NULL;
    _arrel -> primf = NULL;
  } 
  catch (...) {
    delete _arrel;
    throw;
  }
}

template <typename T>	
Arbre<T>::Arbre(const Arbre<T> &a) { 
  _arrel = copia_arbre(a._arrel);
}

template <typename T>	
Arbre<T>&  Arbre<T>::operator=(const Arbre<T> &a) { 
  Arbre<T> tmp(a);
  node* aux = _arrel;
  _arrel = tmp._arrel;
  tmp._arrel = aux;
  return *this;
}

template <typename T>	
Arbre<T>::~Arbre() throw() { 
  destrueix_arbre(_arrel);
}

template <typename T>	
void Arbre<T>::afegir_fill(Arbre<T> &a) { 
  if (_arrel == NULL or a._arrel == NULL or 
    a._arrel -> seggerm != NULL) {
    throw ArbreInvalid;
  }
  a._arrel -> seggerm = _arrel -> primf;
  _arrel -> primf = a._arrel;
  a._arrel = NULL;
}

// Llegeix un arbre general des de cin i el retorna.
Arbre<int> arbre() {
  int valor, nf;
  cin >> valor >> nf;
  Arbre<int> a(valor);
  stack<Arbre<int> > pa;
  while (nf>0) {
    pa.push(arbre());
    nf--;
  }
  while (not pa.empty()) {
    a.afegir_fill(pa.top());
    pa.pop();
  }
  return a;
}

int main() {
  Arbre<int> a(arbre());
  cout << a.grau_max() << endl;
  return 0;
}
