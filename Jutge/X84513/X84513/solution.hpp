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
   static void arbre_max_fills(node* p);
 };
 
 // Aquí va la implementació del mètode arbre_max_fills i privats addicionals

 template <typename T>
void Arbre<T>::arbre_max_fills(node* p) {
	
	if(p->primf == nullptr) arbre_max_fill(p->info);
	
	while(p->primf != nullptr) {
		while(p->seggerm != nullptr) {
			arbre_max_fills(p->primf);
			arbre_max_fills(p->seggerm);
			int maxim= max(p->primf->info, p->seggerm->info); 
		}
		p->info= maxim; 
	}
	
}

 template <typename T>
void Arbre<T>::arbre_max_fills() {
	arbre_max_fills(_arrel); 
}





