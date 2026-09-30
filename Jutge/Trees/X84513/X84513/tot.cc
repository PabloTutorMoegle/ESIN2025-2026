 #include <cstdlib>
 #include <string>
 using namespace std;
 typedef unsigned int nat;
 
 template <typename T>
 class Arbre {
 
 public:
   // Construeix un Arbre format per un únic node que conté a x.
   Arbre(const T &x);

   // Tres grans.
   Arbre(const Arbre<T> &a);
   Arbre& operator=(const Arbre<T> &a);
   ~Arbre() throw();
 
   // Col·loca l’Arbre donat com a primer fill de l’arrel de l’arbre sobre el que s’aplica el mètode i l’arbre a queda invalidat; després de fer b.afegir_fill(a), a no és un arbre vàlid.
   void afegir_fill(Arbre<T> &a);
 
   // Imprimeix la informació dels nodes en preodre, cada element en una nova línia i
   // precedit per espais segons el nivell on està situat.
   void preordre() const;
 
   static const int ArbreInvalid = 400;
 
   // Modifica el contingut dels nodes per tal de guardar a cada node el valor màxim entre
   // els valors dels nodes que són els seus fills. Els nodes fulla (els de grau 0) no es
   // modifiquen.
   void arbre_max_fills();
 
 private:
   Arbre(): _arrel(NULL) {};
   struct node {
     T info;
     node* primf;
     node* seggerm;
   };
   node* _arrel;
   static node* copia_arbre(node* p);
   static void destrueix_arbre(node* p) throw();
   static void preordre(node *p, string pre);
 
   // Aquí va l’especificació dels mètodes privats addicionals
   static void arbre_max_fills(node* p/*, int maxim*/);
 };
 
 // Aquí va la implementació del mètode arbre_max_fills i privats addicionals

template <typename T>
void Arbre<T>::arbre_max_fills(node* p/*, int maxim*/) {
	
	/*
	if(p->primf == nullptr) arbre_max_fills(p,p->info);
	
	while(p->primf != nullptr) {
		arbre_max_fills(p->primf,maxim);
		arbre_max_fills(p->seggerm,maxim);
		if(p->seggerm != nullptr) maxim= max(p->primf->info, p->seggerm->info); 
		p->info= maxim; 
	}
	*/

    	if(p != nullptr) {
	int maxim= p->info; 
   	node *fill= p->primf; 
   	bool t= true; 
   	while(fill != nullptr) {
   		arbre_max_fills(fill);
   		if(t) {
   			maxim= fill->info; 
   			t= false; 
   		}
   		else if(maxim<fill->info) maxim= fill->info;
   		fill= fill->seggerm; 
   	} 
   	p->info= maxim; 
   	}
}

 template <typename T>
void Arbre<T>::arbre_max_fills() {
	arbre_max_fills(_arrel); 
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

template <typename T>
void Arbre<T>::preordre(node *p, string pre) {
  if (p != NULL) {
    cout << pre << p->info << endl;
    preordre(p->primf, pre + "  ");
    preordre(p->seggerm, pre);
  }
}

template <typename T>
void Arbre<T>::preordre() const {
  preordre(_arrel, "");
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
  a.arbre_max_fills();
  a.preordre();
  return 0;
}
