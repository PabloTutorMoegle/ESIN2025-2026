#include "terminal.hpp"

/* Constructora.
    Pre: n, m, h > 0, h <= HMAX, st pertany a {FIRST_FIT, LLIURE}.
    Post: Crea una terminal buida amb les dimensions i l'estratègia indicades.
    Cost: O(N*M*H) per la inicialització de la matriu 3D. */
terminal::terminal(nat n, nat m, nat h, estrategia st) : 
    _n(n), _m(m), _h(h), _st(st), _on(n*m*h), _conts(n*m*h), _ops_grua(0) {
    
    if (n == 0) throw esin::error(NumFileresIncorr);
    if (m == 0) throw esin::error(NumPlacesIncorr);
    if (h == 0 || h > HMAX) throw esin::error(AlcadaMaxIncorr);

    _graella = new string**[_n];
    for (nat i = 0; i < _n; ++i) {
        _graella[i] = new string*[_m];
        for (nat j = 0; j < _m; ++j) {
            _graella[i][j] = new string[_h];
            for (nat k = 0; k < _h; ++k) _graella[i][j][k] = ""; 
        }
    }
}

/* Destructora.
    Pre: Cert.
    Post: Allibera la memòria dinàmica de la graella 3D.
   Cost: O(N*M). */
terminal::~terminal() noexcept {
    for (nat i = 0; i < _n; ++i) {
        for (nat j = 0; j < _m; ++j) delete[] _graella[i][j];
        delete[] _graella[i];
    }
    delete[] _graella;
}

/* insereix_contenidor.
    Pre: Cert.
    Post: Insereix c al magatzem o a l'espera segons l'estratègia.
   Cost: O(N*M*H + E*N*M*H) en el pitjor cas. */
void terminal::insereix_contenidor(const contenidor &c) {
    if (_conts.existeix(c.matricula())) throw esin::error(MatriculaDuplicada);

    ubicacio u(-1, -1, -1);
    if (buscar_lloc(c, u)) {
        col_locar_al_moll(c, u);
        gestionar_espera();
    } else {
        _espera.push_back(c.matricula());
        _conts.assig(c.matricula(), c);
        _on.assig(c.matricula(), ubicacio(-1, 0, 0));
    }
}

/* retira_contenidor.
    Pre: Cert.
    Post: Elimina m de la terminal. Gestiona el moviment de contenidors superiors a l'espera.
   Cost: O(H + E*N*M*H). */
void terminal::retira_contenidor(const string &m) {
    if (!_conts.existeix(m)) throw esin::error(MatriculaInexistent);

    ubicacio u = _on[m];
    if (u.filera() == -1) {
        _espera.remove(m);
        _conts.elimina(m);
        _on.elimina(m);
    } else {
        nat fil = u.filera();
        nat pla = u.placa();
        nat n_places = _conts[m].longitud() / 10;

        for (nat k = u.pis() + 1; k < _h; ++k) {
            for (nat j = 0; j < n_places; ++j) {
                string m_sobre = _graella[fil][pla + j][k];
                if (m_sobre != "") {
                    ubicacio u_sobre = _on[m_sobre];
                    contenidor c_sobre = _conts[m_sobre];
                    esborrar_del_moll(m_sobre);
                    _espera.push_back(m_sobre);
                    _conts.assig(m_sobre, c_sobre);
                    _on.assig(m_sobre, ubicacio(-1, 0, 0));
                }
            }
        }
        esborrar_del_moll(m);
        gestionar_espera();
    }
}

/* on.
    Pre: Cert.
    Post: Retorna la ubicació de m.
   Cost: O(1) mitjà. */
ubicacio terminal::on(const string &m) const noexcept {
    if (!_conts.existeix(m)) return ubicacio(-1, -1, -1);
    return _on[m];
}

/* longitud.
    Pre: Cert.
    Post: Retorna la longitud de m.
   Cost: O(1) mitjà. */
nat terminal::longitud(const string &m) const {
    if (!_conts.existeix(m)) throw esin::error(MatriculaInexistent);
    return _conts[m].longitud();
}

/* fragmentacio.
    Pre: Cert.
    Post: Retorna el comptador de fragmentació segons la definició de l'enunciat.
   Cost: O(N*M*H). */
nat terminal::fragmentacio() const noexcept {
    nat frag = 0;
    for (nat i = 0; i < _n; ++i) {
        for (nat j = 0; j < _m; ++j) {
            for (nat k = 0; k < _h; ++k) {
                if (_graella[i][j][k] == "") {
                    bool lloc_20 = false;
                    if (j + 1 < _m && _graella[i][j+1][k] == "" && 
                        (k == 0 || (_graella[i][j][k-1] != "" && _graella[i][j+1][k-1] != ""))) {
                        lloc_20 = true;
                    }
                    if (!lloc_20) frag++;
                }
            }
        }
    }
    return frag;
}

/* area_espera.
    Pre: Cert.
    Post: Llista matrícules d'espera ordenades alfabèticament.
   Cost: O(E log E). */
void terminal::area_espera(std::list<string> &l) const noexcept {
    l = _espera;
    l.sort();
}

/* --- MÈTODES PRIVATS --- */

bool terminal::es_pot_posar(nat f, nat p, nat k, nat ll) const {
    nat n_places = ll / 10;
    if (p + n_places > _m) return false;
    for (nat j = 0; j < n_places; ++j) {
        if (_graella[f][p + j][k] != "") return false; 
        if (k > 0 && _graella[f][p + j][k - 1] == "") return false; 
    }
    return true;
}

bool terminal::buscar_lloc(const contenidor &c, ubicacio &u) const {
    nat ll = c.longitud();
    if (_st == estrategia::FIRST_FIT) {
        for (nat i = 0; i < _n; ++i)
            for (nat j = 0; j <= _m - (ll/10); ++j)
                for (nat k = 0; k < _h; ++k)
                    if (es_pot_posar(i, j, k, ll)) { u = ubicacio(i, j, k); return true; }
    } else {
        for (int i = _n - 1; i >= 0; --i)
            for (nat j = 0; j <= _m - (ll/10); ++j)
                for (nat k = 0; k < _h; ++k)
                    if (es_pot_posar((nat)i, (nat)j, k, ll)) { u = ubicacio((nat)i, (nat)j, k); return true; }
    }
    return false;
}

void terminal::gestionar_espera() {
    bool canvi = true;
    while (canvi) {
        canvi = false;
        auto it = _espera.end();
        while (it != _espera.begin()) {
            --it;
            string m = *it;
            contenidor c = _conts[m];
            ubicacio u(-1, -1, -1);
            if (buscar_lloc(c, u)) {
                col_locar_al_moll(c, u);
                it = _espera.erase(it);
                canvi = true;
                break; 
            }
        }
    }
}

void terminal::col_locar_al_moll(const contenidor &c, const ubicacio &u) {
    for (nat j = 0; j < c.longitud()/10; ++j) 
        _graella[u.filera()][u.placa() + j][u.pis()] = c.matricula();
    _on.assig(c.matricula(), u);
    _conts.assig(c.matricula(), c);
    _ops_grua++; 
}

void terminal::esborrar_del_moll(const string &m) {
    ubicacio u = _on[m];
    nat n_places = _conts[m].longitud() / 10;
    for (nat j = 0; j < n_places; ++j)
        _graella[u.filera()][u.placa() + j][u.pis()] = "";
    _on.elimina(m);
    _conts.elimina(m);
    _ops_grua++;
}

nat terminal::ops_grua() const noexcept { return _ops_grua; }
nat terminal::num_fileres() const noexcept { return _n; }
nat terminal::num_places() const noexcept { return _m; }
nat terminal::num_pisos() const noexcept { return _h; }
terminal::estrategia terminal::quina_estrategia() const noexcept { return _st; }
