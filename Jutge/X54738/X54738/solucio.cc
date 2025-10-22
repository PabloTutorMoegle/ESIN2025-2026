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
 
   static const int ArbreInvalid = 400;
 
   // Comprova que el contingut de cada node coincideix amb el seu grau
   bool es_arbre_compta_graus();
 
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
 
   // Aquí va l’especificació dels mètodes privats addicionals
   bool es_arbre_compta_graus(node* p);
 };
 
 // Aquí va la implementació del mètode es_arbre_compta_graus

template <typename T>
 bool Arbre<T>::es_arbre_compta_graus(node* p) {
 	bool t= true; 
 	if(p != nullptr){
	 	int cont= 0; 
	 	node* fill= p->primf;
	 	
	 	while(fill != nullptr and t) {
	 		t= es_arbre_compta_graus(fill);
	 		cont++;
	 		fill= fill->seggerm; 
 		}
 		if(p->info != cont) t= false;
 	} 
 	return t;
 }


template <typename T>
 bool Arbre<T>::es_arbre_compta_graus() {
 	bool t= es_arbre_compta_graus(_arrel);
 	return t;
 }
