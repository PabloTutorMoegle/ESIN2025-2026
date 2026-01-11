#include "contenidor.hpp"
#include <esin/error>
#include <esin/util>

namespace esin {
    using ::error;
}

/* Constructora. 
    Pre: Cert.
    Post: Crea un contenidor amb matrícula m i longitud l.
    Llença MatriculaIncorrecta si m és buida o conté caràcters no alfanumèrics (A-Z, 0-9).
    Llença LongitudIncorrecta si l no és 10, 20 o 30.
   Cost: O(M) on M és la longitud de la matrícula (pel recorregut de validació). */
contenidor::contenidor(const string &m, nat l) {
    if (m.empty()) {
        throw esin::error(MatriculaIncorrecta);
    }
    
    for (char c : m) {
        if (!((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
            throw esin::error(MatriculaIncorrecta);
        }
    }
    
    if (l != 10 && l != 20 && l != 30) {
        throw esin::error(LongitudIncorrecta);
    }
    
    _matr = m;
    _long = l;
}

/* Constructora per còpia.
   Cost: O(M) per la còpia de l'string. */
contenidor::contenidor(const contenidor &u) {
    _matr = u._matr;
    _long = u._long;
}

/* Operador d'assignació.
   Cost: O(M) per la còpia de l'string. */
contenidor& contenidor::operator=(const contenidor &u) {
    if (this != &u) {
        _matr = u._matr;
        _long = u._long;
    }
    return *this;
}

/* Destructora.
   Cost: O(1) (l'string s'allibera automàticament). */
contenidor::~contenidor() noexcept {}

/* Consultors.
   Cost: O(1) (el retorn de l'string per valor pot ser O(M), però molts compiladors 
   apliquen optimitzacions de moviment). */
nat contenidor::longitud() const noexcept {
    return _long;
}

string contenidor::matricula() const noexcept {
    return _matr;
}

/* Operadors de comparació.
   Igualtat: Cert si matrícula i longitud coincideixen.
   Cost: O(M). */
bool contenidor::operator==(const contenidor &c) const noexcept {
    return (_matr == c._matr) && (_long == c._long);
}

bool contenidor::operator!=(const contenidor &c) const noexcept {
    return !(*this == c);
}

/* Menor: Ordre alfabètic de matrícula, i en cas d'empat, per longitud.
   Cost: O(M). */
bool contenidor::operator<(const contenidor &c) const noexcept {
    if (_matr != c._matr) {
        return _matr < c._matr;
    }
    return _long < c._long;
}

bool contenidor::operator<=(const contenidor &c) const noexcept {
    return !(c < *this);
}

bool contenidor::operator>(const contenidor &c) const noexcept {
    return c < *this;
}

bool contenidor::operator>=(const contenidor &c) const noexcept {
    return !(*this < c);
}
