#include "ubicacio.hpp"

/* Constructora. Crea la ubicació <i, j, k>. 
   Pre: Cert.
   Post: Crea una ubicació amb filera i, plaça j i pis k. 
   Llença error UbicacioIncorrecta si les coordenades no són vàlides.
   Cost: O(1) */
ubicacio::ubicacio(int i, int j, int k) {
    bool coords_positives = (i >= 0 && j >= 0 && k >= 0);
    bool cas_espera = (i == -1 && j == 0 && k == 0); [cite: 219]
    bool cas_inexistent = (i == -1 && j == -1 && k == -1); [cite: 219]

    if (!(coords_positives || cas_espera || cas_inexistent)) {
        throw esin::error(UbicacioIncorrecta); [cite: 231]
    }
    
    fil = i;
    placa = j;
    pis = k;
}

/* Constructora per còpia.
   Cost: O(1)*/
ubicacio::ubicacio(const ubicacio& u) {
    fil = u.fil;
    placa = u.placa;
    pis = u.pis;
}

/* Operador d'assignació.
   Cost: O(1) */
ubicacio& ubicacio::operator=(const ubicacio& u) {
    if (this != &u) {
        fil = u.fil;
        placa = u.placa;
        pis = u.pis;
    }
    return *this;
}

/* Destructora.
   Cost: O(1)*/
ubicacio::~ubicacio() noexcept {}

/* Consultors.
   Cost: O(1) */
int ubicacio::filera() const noexcept { return fil; }
int ubicacio::placa() const noexcept { return placa; }
int ubicacio::pis() const noexcept { return pis; }

/* Operador d'igualtat.
   Post: Cert si tenen mateixa filera, plaça i pis.
   Cost: O(1) */
bool ubicacio::operator==(const ubicacio &u) const noexcept {
    return (fil == u.fil && placa == u.placa && pis == u.pis);
}

bool ubicacio::operator!=(const ubicacio &u) const noexcept {
    return !(*this == u);
}

/* Operador menor.
   Post: Cert si la ubicació és menor segons l'ordre: filera, plaça, pis.
   Cost: O(1) */
bool ubicacio::operator<(const ubicacio &u) const noexcept {
    if (fil != u.fil) return fil < u.fil;
    if (placa != u.placa) return placa < u.placa;
    return pis < u.pis;
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
