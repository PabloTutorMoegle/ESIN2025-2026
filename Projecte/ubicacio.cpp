#include "ubicacio.hpp"
#include "ubicacio.rep"

// Constructora. Crea la ubicació <i, j, k>. Genera un error amb codi UbicacioIncorrecta si < i, j, k > no pertany a {< u, v, w > |u ≥ 0 ∨ v ≥ 0 ∨ w ≥ 0} o a
// {< −1, 0, 0 >, < −1, −1, −1 >}.
ubicacio::ubicacio(int i, int j, int k)
{
    if (!((i >= 0) || (j >= 0) || (k >= 0) || ( (i == -1) && (j == 0) && (k == 0) ) || ( (i == -1) && (j == -1) && (k == -1) )))
        esin::error(UbicacioIncorrecta);
    this.fil = i;
    this.placa = j;
    this.pis = k;
}
// Constructora per còpia, assignació i destructora.
ubicacio::ubicacio(const ubicacio& u)
{
    this.fil = u.fil;
    this.placa = u.placa;
    this.pis = u.pis;
}
ubicacio& ubicacio::operator=(const ubicacio& u)
{
    if (this != &u) {
        this.fil = u.fil;
        this.placa = u.placa;
        this.pis = u.pis;
    }
    return *this;
}
ubicacio::~ubicacio() noexcept
{

}
// Consultors. Retornen respectivament el primer, segon i tercer component de la ubicació.
int ubicacio::filera() const noexcept
{
    return this.fil;
}
int ubicacio::placa() const noexcept
{
    return this.placa;
}
int ubicacio::pis() const noexcept
{
    return this.pis;
}
// Operadors de comparació. L’operador d’igualtat retorna cert si i només si les dues
// ubicacions tenen la mateixa filera, plaça i pis. L’operador menor retorna cert si i
// només si la filera del paràmetre implícit és més petit que la d’u, o si les dues fileres
// són iguals i la plaça del paràmetre implícit és més petita que la d’u, o si les fileres i
// les places coincideixen i el pis del paràmetre implícit és més petit que el d’u. La resta
// d’operadors es defineixen consistentment respecte <.
bool ubicacio::operator==(const ubicacio &u) const noexcept
{
    if ( (this.fil == u.fil) && (this.placa == u.placa) && (this.pis == u.pis) )
        return true;
    return false;
}
bool ubicacio::operator!=(const ubicacio &u) const noexcept
{
    return !(*this == u);
}
bool ubicacio::operator<(const ubicacio &u) const noexcept
{
    if (this.fil < u.fil)
        return true;
    else if (this.fil == u.fil) {
        if (this.placa < u.placa)
            return true;
        else if (this.placa == u.placa) {
            if (this.pis < u.pis)
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
