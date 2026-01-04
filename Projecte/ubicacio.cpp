#include "ubicacio.hpp"
#include "ubicacio.rep"

// Constructora. Crea la ubicació <i, j, k>. Genera un error amb codi UbicacioIncorrecta si < i, j, k > no pertany a {< u, v, w > |u ≥ 0 ∨ v ≥ 0 ∨ w ≥ 0} o a
// {< −1, 0, 0 >, < −1, −1, −1 >}.
ubicacio::ubicacio(int i, int j, int k)
{
    if (!((i >= 0) || (j >= 0) || (k >= 0) || ( (i == -1) && (j == 0) && (k == 0) ) || ( (i == -1) && (j == -1) && (k == -1) )))
        esin::error(UbicacioIncorrecta);
    fil = i;
    plaza = j;
    piso = k;
}
// Constructora per còpia, assignació i destructora.
ubicacio::ubicacio(const ubicacio& u)
{
    fil = u.fil;
    plaza = u.plaza;
    piso = u.piso;
}
ubicacio& ubicacio::operator=(const ubicacio& u)
{
    if (this != &u) {
        fil = u.fil;
        plaza = u.plaza;
        piso = u.piso;
    }
    return *this;
}
ubicacio::~ubicacio() noexcept
{

}
// Consultors. Retornen respectivament el primer, segon i tercer component de la ubicació.
int ubicacio::filera() const noexcept
{
    return fil;
}
int ubicacio::placa() const noexcept
{
    return plaza;
}
int ubicacio::pis() const noexcept
{
    return piso;
}
// Operadors de comparació. L’operador d’igualtat retorna cert si i només si les dues
// ubicacions tenen la mateixa filera, plaça i piso. L’operador menor retorna cert si i
// només si la filera del paràmetre implícit és més petit que la d’u, o si les dues fileres
// són iguals i la plaça del paràmetre implícit és més petita que la d’u, o si les fileres i
// les places coincideixen i el piso del paràmetre implícit és més petit que el d’u. La resta
// d’operadors es defineixen consistentment respecte <.
bool ubicacio::operator==(const ubicacio &u) const noexcept
{
    if ( (fil == u.fil) && (plaza == u.plaza) && (piso == u.piso) )
        return true;
    return false;
}
bool ubicacio::operator!=(const ubicacio &u) const noexcept
{
    return !(*this == u);
}
bool ubicacio::operator<(const ubicacio &u) const noexcept
{
    if (fil < u.fil)
        return true;
    else if (fil == u.fil) {
        if (plaza < u.plaza)
            return true;
        else if (plaza == u.plaza) {
            if (piso < u.piso)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
    
    return false;
}
bool ubicacio::operator<=(const ubicacio &u) const noexcept
{
    return (*this < u) || (*this == u);
}
bool ubicacio::operator>(const ubicacio &u) const noexcept
{
    return !(*this <= u);
}
bool ubicacio::operator>=(const ubicacio &u) const noexcept
{
    return !(*this < u);
}
