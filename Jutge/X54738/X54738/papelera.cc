/*
template <typename T>
 void Arbre<T>::es_arbre_compta_graus(node* p, int x, bool t) {
 	node* aux;
 	while(p->primf != nullptr) {
 		aux= p->primf;
 		es_arbre_compta_graus(p->primf,x,t);
 		if(p->seggerm != nullptr)es_arbre_compta_graus(p->seggerm,x+1,t);
 		if(aux->info == x) {
 			t= true;
 			x= 0;
 		} else {
 			t= false;
 			x= 0; 
 		} 
 	}
 	x=0; 
 	
 	/*
 	node* fill= p->primf; 
 	while(fill != nullptr) {
 		es_arbre_compta_graus(fill,x,t);
 		fill= fill->seggerm; 
 		x++;
 		if(fill->info != x) t= false;
 		else t= true; 
 	}
 	*/
 }
*/
