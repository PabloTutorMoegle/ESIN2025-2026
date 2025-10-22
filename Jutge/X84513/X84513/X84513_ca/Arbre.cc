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
        // // Col·loca l’Arbre donat com a primer fill de l’arrel de l’arbre sobre el que s’aplica el
        // m`etode i l’arbre a queda invalidat; despr ́es de fer b.afegir fill(a), a no  ́es un arbre v`alid.
        void afegir fill (Arbre<T> &a);
        // Imprimeix la informaci ́o dels nodes en preodre, cada element en una nova l ́ınia i
        // precedit per espais segons el nivell on est`a situat.
        void preordre () const;
        static const int ArbreInvalid = 400;
        // Modifica el contingut dels nodes per tal de guardar a cada node el valor m`axim entre
        // els valors dels nodes que s ́on els seus fills. Els nodes fulla (els de grau 0) no es
        // modifiquen.
        void arbre_max_fills ();
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
        static void preordre (node *p, string pre );
        // Aqu ́ı va l’especificaci ́o dels m`etodes privats addicionals
        static void arbre_max_fills(node *p);
};
// Aqu ́ı va la implementaci ́o del m`etode arbre max fills i privats addicionals

template <typename T>
void Arbre<T>::arbre_max_fills(node *p)
{
    // Si el puntero es nulo no hay nada que procesar
    if (p != nullptr)
    {
        // Si el primer hijo existe entonces hay al menos un hijo
        if (p->primf != nullptr)
        {
            // Inicializa el máximo con la información del primer hijo
            T max_value = p->primf->info;

            // Recorre los hermanos a partir del segundo (seggerm del primer hijo)
            node* current = p->primf->seggerm;
            while (current != nullptr)
            {
                // Si el valor del nodo actual es mayor que el máximo actual,
                // actualiza el máximo.
                // Nota: esto asume que `T` tiene definido el operador '>'
                if (current->info > max_value)
                {
                    max_value = current->info;
                }
                // Avanza al siguiente hermano
                current = current->seggerm;
            }

            // Asigna al nodo p el máximo de sus hijos
            p->info = max_value;
        }
        // Si p->primf == nullptr: p no tiene hijos y la función no modifica p->info
    }
}

template <typename T>
void Arbre<T>::arbre_max_fills () 
{
    if (arrel != nullptr)
    {
        arbre_max_fills(arrel);
    }
}
