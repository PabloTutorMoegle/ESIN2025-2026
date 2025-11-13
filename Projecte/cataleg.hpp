#ifndef _CATALEG_HPP
#define _CATALEG_HPP

#include <string>
#include <esin/error>
#include <esin/util>

using std::string;
using util::nat;

template <typename Valor>
class cataleg {

    public:
        // Constructora. Crea un catàleg buit on numelems és el nombre aproximat d’elements
        // que com a màxim s’inseriran al catàleg.
        explicit cataleg(nat numelems);
        // Constructora per còpia, assignació i destructora.
        cataleg(const cataleg& c);
        cataleg& operator=(const cataleg& c);
        ~cataleg() noexcept;
        // Mètode modificador. Insereix el parell < clau, valor > indicat. En cas que la clau
        // k ja existeixi en el catàleg actualitza el valor associat. Genera un error amb codi
        // ClauStringBuit en cas que la clau sigui l’string buit.
        void assig(const string &k, const Valor &v);
        // Elimina del catàleg el parell que té com a clau k. En cas que la clau k no existeixi en
        // el catàleg genera un error amb codi ClauInexistent.
        void elimina(const string &k);
        // Retorna cert si i només si la clau k existeix dins del catàleg; fals en cas contrari.
        bool existeix(const string &k) const noexcept;
        // Retorna el valor associat a la clau k; si no existeix cap parell amb clau k llavors genera
        // un error amb codi ClauInexistent. Exemple:
            // cataleg<int> ct(91);
            // ...
            // int n = ct["dia"];
        Valor operator[](const string &k) const;
        // Retorna el nombre d’elements que s’han inserit en el catàleg fins aquest moment.
        nat quants() const noexcept;
        // Gestió d’errors
        static constexpr int ClauStringBuit = 30;
        static constexpr int ClauInexistent = 31;
    private:
        #include "cataleg.rep"
};
#include "cataleg.t"
#endif