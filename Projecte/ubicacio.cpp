#include "ubicacio.hpp"

/* Constructora. Crea la ubicació <i, j, k>. 
    Pre: Cert.
    Post: Crea una ubicació amb filera i, plaça j i piso k. 
    Llença error UbicacioIncorrecta si les coordenades no són vàlides.
   Cost: O(1) */
ubicacio::ubicacio(int i, int j, int k) {
    bool coords_positives = (i >= 0 && j >= 0 && k >= 0);
    bool cas_espera = (i == -1 && j == 0 && k == 0); // [cite: 219]
    bool cas_inexistent = (i == -1 && j == -1 && k == -1); // [cite: 219]

    if (!(coords_positives || cas_espera || cas_inexistent)) {
        throw esin::error(UbicacioIncorrecta); // [cite: 231]
    }
    
    fil = i;
    plaza = j;
    piso = k;
}

/* Constructora per còpia.
    Cost: O(1)*/
ubicacio::ubicacio(const ubicacio& u) {
    fil = u.fil;
    plaza = u.plaza;
    piso = u.piso;
}

/* Operador d'assignació.
   Cost: O(1) */
ubicacio& ubicacio::operator=(const ubicacio& u) {
    if (this != &u) {
        fil = u.fil;
        plaza = u.plaza;
        piso = u.piso;
    }
    return *this;
}

/* Destructora.
    Cost: O(1)*/
ubicacio::~ubicacio() noexcept {}

/* Consultors.
   Cost: O(1) */
int ubicacio::filera() const noexcept { return fil; }
int ubicacio::placa() const noexcept { return plaza; }
int ubicacio::pis() const noexcept { return piso; }

/* Operador d'igualtat.
    Post: Cert si tenen mateixa filera, plaça i piso.
   Cost: O(1) */
bool ubicacio::operator==(const ubicacio &u) const noexcept {
    return (fil == u.fil && plaza == u.plaza && piso == u.piso);
}

bool ubicacio::operator!=(const ubicacio &u) const noexcept {
    return !(*this == u);
}

/* Operador menor.
    Post: Cert si la ubicació és menor segons l'ordre: filera, plaça, piso.
   Cost: O(1) */
bool ubicacio::operator<(const ubicacio &u) const noexcept {
    if (fil != u.fil) return fil < u.fil;
    if (plaza != u.plaza) return plaza < u.plaza;
    return piso < u.piso;
}

bool ubicacio::operator<=(const ubicacio &u) const noexcept {
    return (*this < u) || (*this == u);
}

bool ubicacio::operator>(const ubicacio &u) const noexcept {
    return !(*this <= u);
}

bool ubicacio::operator>=(const ubicacio &u) const noexcept {
    return !(*this < u);
}
