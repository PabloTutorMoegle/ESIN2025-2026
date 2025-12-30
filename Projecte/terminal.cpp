#include "terminal.hpp"

// Constructora. Crea una terminal buida amb n fileres de m places cadascuna, i una
// alçada màxima d’apilament h; a més fixa l’estratègia d’inserció i retirada dels contenidors respecte el paràmetre st. Genera un error amb codi NumFileresIncorr,
// NumPlacesIncorr o AlcadaMaxIncorr si n = 0, m = 0, h = 0, h > HMAX o un
// error amb codi EstrategiaIncorr si st no pertany a {FIRST_FIT, LLIURE}.
terminal(nat n, nat m, nat h, estrategia st)
{
    if(n == 0) throw error(NumFileresIncorr);
    if(m == 0) throw error(NumPlacesIncorr);
    if(h == 0 || h > HMAX) throw error(AlcadaMaxIncorr);
    if(st != estrategia::FIRST_FIT && st != estrategia::LLIURE) {
        throw error(EstrategiaIncorr);
    }
    this.n = n;
    this.m = m;
    this.h = h;
    this.st = st;
}
// Constructora per còpia, assignació i destructora.
terminal(const terminal& b)
{
    this.n = b.n;
    this.m = b.m;
    this.h = b.h;
    this.st = b.st;
}
terminal& operator=(const terminal& b)
{
    if(this != &b) {
        this.n = b.n;
        this.m = b.m;
        this.h = b.h;
        this.st = b.st;
    }
    return *this;
}
~terminal() noexcept
{

}
// Col·loca el contenidor c en l’àrea d’emmagatzematge de la terminal o en l’àrea d’espera si no troba lloc en l’àrea d’emmagatzematge usant l’estratègia prefixada en el
// moment de crear la terminal. Si elcontenidor c es col·loca en l’àrea d’emmagatzematge pot succeir que un o més contenidors de l’àrea d’espera puguin ser moguts a
// l’àrea d’emmagatzematge. En aquest cas es mouran els contenidors de l’àrea d’espera a l’àrea d’emmagatzematge seguint l’ordre que indiqui l’estratègia que s’està
// usant. Finalment, genera un error amb codi MatriculaDuplicada si ja existís a la
// terminal un contenidor amb una matrícula idèntica que la del contenidor c.
void insereix_contenidor(const contenidor &c)
{

}
// Retira de la terminal el contenidor c la matrícula del qual és igual a m. Aquest contenidor pot estar a l’àrea d’emmagatzematge o a l’àrea d’espera. Si el contenidor
// estigués a l’àrea d’emmagatzematge llavors s’hauran de moure a l’àrea d’espera tots
// els contenidors que siguin necessaris per netejar la part superior de c, s’hauran de
// retirar possiblement diversos contenidors, començant pel contenidor sense cap altre
// a sobre amb el número de plaça més baix (més a l’esquerra) i així successivament
// (veure exemple amb detall a la subsecció 2.1). Un cop s’hagi eliminat el contenidor
// indicat, s’intenta moure contenidors de l’àrea d’espera a l’àrea d’emmagatzematge,
// seguint l’ordre que indiqui l’estratègia que s’està usant. Genera un error amb codi
// MatriculaInexistent si a la terminal no hi ha cap contenidor la matrícula del qual
// sigui igual a m.
void retira_contenidor(const string &m)
{

}
// Retorna la ubicació <i, j, k> del contenidor la matrícula del qual és igual a m si el
// contenidor està a l’àrea d’emmagatzematge de la terminal. Si el contenidor està
// a l’àrea d’espera retorna la ubicació <-1, 0, 0>. Si no existeix cap contenidor que
// tingui una matrícula igual a m retorna la ubicació <-1, -1, -1>. Cal recordar que si
// un contenidor té més de 10 peus, la seva ubicació correspon a la plaça que tingui el
// número de plaça més petit.
ubicacio on(const string &m) const noexcept
{

}
// Retorna la longitud del contenidor la matrícula del qual és igual a m. Genera un error
// amb codi MatriculaInexistent si no existeix un contenidor a la terminal la matrícula
// del qual sigui igual a m.
nat longitud(const string &m) const
{

}
// Retorna la matrícula del contenidor que ocupa la ubicació u =< i, j, k > o la cadena
// buida si la ubicació està buida. Genera un error amb codi UbicacioNoMagatzem si
// i < 0, i >= n, j < 0, j >= m, k < 0 o k >= h, o sigui si < i, j, k > no identifica
// una ubicació vàlida de l’àrea d’emmagatzematge. Cal observar que si m, obtinguda
// amb t.contenidor_ocupa(u, m), és una matrícula (no la cadena buida) pot succeir que u != t.on(m), ja que un contenidor pot ocupar diverses places i la seva
// ubicació es correspon amb la de la plaça ocupada amb número de plaça més baix.
void contenidor_ocupa(const ubicacio &u, string &m) const
{

}
// Retorna el nombre de places de la terminal que en aquest instant només hi cabrien
// un contenidor de 10 peus, però no un de més llarg. Per exemple, la filera de la figura
// 1 de l’enunciat contribuirà amb 7 unitats a la fragmentació total (corresponen a les
// ubicacions <f, 0, 1>, <f, 1, 2>, <f, 2, 1>, <f, 7, 1>, <f, 8, 0>, <f, 9, 1> i <f, 10, 0>).
nat fragmentacio() const noexcept
{

}
// Retorna el número d’operacions de grua realitzades des del moment de creació de la
// terminal. Es requereix d’una operació de grua per moure un contenidor des de l’àrea
// d’espera a l’àrea d’emmagatzematge o viceversa. També es requereix d’una operació
// de grua per inserir o retirar directament un contenidor de l’àrea d’emmagatzematge.
// En canvi no requereix cap operació de grua inserir o retirar directament un contenidor
// de l’àrea d’espera.
nat ops_grua() const noexcept
{

}
// Retorna la llista de les matrícules de tots els contenidors de l’àrea d’espera de la
// terminal, en ordre alfabètic creixent.
void area_espera(list<string> &l) const noexcept
{

}
// Retorna el número de fileres de la terminal.
nat num_fileres() const noexcept
{

}
// Retorna el número de places per filera de la terminal.
nat num_places() const noexcept
{

}
// Retorna l’alçada màxima d’apilament de la terminal.
nat num_pisos() const noexcept
{

}
// Retorna l’estratègia d’inserció i retirada de contenidors de la terminal.
estrategia quina_estrategia() const noexcept
{

}