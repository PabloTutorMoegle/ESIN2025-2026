#include "ubicacio.hpp"

// Constructora. Crea la ubicació <i, j, k>. Genera un error amb codi UbicacioIncorrecta si < i, j, k > no pertany a {< u, v, w > |u ≥ 0 ∨ v ≥ 0 ∨ w ≥ 0} o a
// {< −1, 0, 0 >, < −1, −1, −1 >}.
ubicacio(int i, int j, int k)
{

}
// Constructora per còpia, assignació i destructora.
ubicacio(const ubicacio& u)
{

}
ubicacio& operator=(const ubicacio& u)
{

}
~ubicacio() noexcept
{

}
// Consultors. Retornen respectivament el primer, segon i tercer component de la ubicació.
int filera() const noexcept
{

}
int placa() const noexcept
{

}
int pis() const noexcept
{

}
// Operadors de comparació. L’operador d’igualtat retorna cert si i només si les dues
// ubicacions tenen la mateixa filera, plaça i pis. L’operador menor retorna cert si i
// només si la filera del paràmetre implícit és més petit que la d’u, o si les dues fileres
// són iguals i la plaça del paràmetre implícit és més petita que la d’u, o si les fileres i
// les places coincideixen i el pis del paràmetre implícit és més petit que el d’u. La resta
// d’operadors es defineixen consistentment respecte <.
bool operator==(const ubicacio &u) const noexcept
{

}
bool operator!=(const ubicacio &u) const noexcept
{

}
bool operator<(const ubicacio &u) const noexcept
{

}
bool operator<=(const ubicacio &u) const noexcept
{

}
bool operator>(const ubicacio &u) const noexcept
{

}
bool operator>=(const ubicacio &u) const noexcept
{

}
