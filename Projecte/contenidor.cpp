#include "contenidor.hpp"

// Constructora. Crea un contenidor amb matrícula m i longitud l. Es produeix un error
// amb codi MatriculaIncorrecta si m no és una seqüència de un o més caràcters,
// formada exclusivament per lletres majúscules i dígits. Es produeix un error amb codi
// LongitudIncorrecta si l no pertany a 10, 20, 30.
contenidor(const string &m, nat l)
{
    if(m.empty()) throw error(MatriculaIncorrecta);
    for(char c : m) {
        if(!((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
            throw error(MatriculaIncorrecta);
        }
    }
    if(l != 10 && l != 20 && l != 30) {
        throw error(LongitudIncorrecta);
    }
    this.m = m;
    this.l = l;
}
// Constructora per còpia, assignació i destructora.
contenidor(const contenidor &u)
{
    m = u.m;
    l = u.l;
}
contenidor& operator=(const contenidor &u)
{
    if(this != &u) {
        m = u.m;
        l = u.l;
    }
    return *this;
}
~contenidor() noexcept
{

}
// Consultors. Retornen respectivament la longitud i la matrícula del contenidor.
nat longitud() const noexcept
{
    return l;
}
string matricula() const noexcept
{
    return m;
}
// Operadors de comparació. L’operador d’igualtat retorna cert si i només si els dos
// contenidors contenen la mateixa matrícula i longitud. L’operador menor retorna cert
// si i només si la matrícula del paràmetre implícit és més petit en ordre alfabètic que
// la de c o si les dues matrícules són iguals i la longitud del paràmetre implícit és més
// petita que la de c. La resta d’operadors es defineixen consistentment respecte a <.
bool operator==(const contenidor &c) const noexcept
{
    return (m == c.m) && (l == c.l);
}
bool operator!=(const contenidor &c) const noexcept
{
    return !(*this == c);
}
bool operator<(const contenidor &c) const noexcept
{
    if(m < c.m) return true;
    if(m == c.m && l < c.l) return true;
    return false;
}
bool operator<=(const contenidor &c) const noexcept
{
    return (*this < c) || (*this == c);
}
bool operator>(const contenidor &c) const noexcept
{
    return !(*this <= c);
}
bool operator>=(const contenidor &c) const noexcept
{
    return !(*this < c);
}
