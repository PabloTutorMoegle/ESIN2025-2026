
/* Constructora.
    Pre: Cert.
    Post: Crea un catàleg buit amb mida inicial numelems (mínim 1).
   Cost: O(M), on M és numelems. */
template <typename Valor>
cataleg<Valor>::cataleg(nat numelems) {
    _M = (numelems > 0) ? numelems : 1;
    _taula = new node*[_M];
    for (nat i = 0; i < _M; ++i) _taula[i] = nullptr;
    _quants = 0;
}

template <typename Valor>
cataleg<Valor>::cataleg(const cataleg& c) {
    copia(c);
}

template <typename Valor>
cataleg<Valor>& cataleg<Valor>::operator=(const cataleg& c) {
    if (this != &c) {
        for (nat i = 0; i < _M; ++i) esborra_nodes(_taula[i]);
        delete[] _taula;
        copia(c);
    }
    return *this;
}

template <typename Valor>
cataleg<Valor>::~cataleg() noexcept {
    if (_taula != nullptr) {
        for (nat i = 0; i < _M; ++i) esborra_nodes(_taula[i]);
        delete[] _taula;
    }
}

/* assig: Insereix o actualitza un parell clau-valor.
    Pre: Cert.
    Post: Si la clau k existia, s'actualitza el valor. Si no, s'insereix. 
    Llença ClauStringBuit si k és buit.
   Cost: Mitjà O(L + α), on L és la longitud de k i α el factor de càrrega. */
template <typename Valor>
void cataleg<Valor>::assig(const string &k, const Valor &v) {
    if (k.empty()) throw esin::error(ClauStringBuit);

    long index = h(k) % _M; 
    node* p = _taula[index];
    bool trobat = false;
    
    while (p != nullptr && !trobat) {
        if (p->_k == k) {
            p->_v = v; 
            trobat = true;
        }
        p = p->_seg;
    }

    if (!trobat) {
        node* nou = new node{k, v, _taula[index]};
        _taula[index] = nou;
        _quants++;
        
        if (factor_de_carrega() > 0.8) redispersio();
    }
}

/* elimina: Esborra una clau.
   Cost: Mitjà O(L + α). */
template <typename Valor>
void cataleg<Valor>::elimina(const string &k) {
    long index = h(k) % _M;
    node* act = _taula[index];
    node* ant = nullptr;

    while (act != nullptr && act->_k != k) {
        ant = act;
        act = act->_seg;
    }

    if (act == nullptr) throw esin::error(ClauInexistent);

    if (ant == nullptr) _taula[index] = act->_seg;
    else ant->_seg = act->_seg;

    delete act;
    _quants--;
}

/* existeix: Comprova si la clau és al catàleg.
   Cost: Mitjà O(L + α). */
template <typename Valor>
bool cataleg<Valor>::existeix(const string &k) const noexcept {
    if (k.empty()) return false;
    long index = h(k) % _M;
    node* act = _taula[index];
    while (act != nullptr) {
        if (act->_k == k) return true;
        act = act->_seg;
    }
    return false;
}

/* operator[]: Retorna el valor associat a la clau.
    Cost: Mitjà O(L + α).*/ 
template <typename Valor>
Valor cataleg<Valor>::operator[](const string &k) const {
    if (k.empty()) throw esin::error(ClauInexistent);
    long index = h(k) % _M;
    node* act = _taula[index];
    while (act != nullptr) {
        if (act->_k == k) return act->_v;
        act = act->_seg;
    }
    throw esin::error(ClauInexistent);
}

template <typename Valor>
nat cataleg<Valor>::quants() const noexcept {
    return _quants; 
}

/* Funció de dispersió (Hash function).
   Cost: O(L), on L és la longitud de la clau k. */
template <typename Valor>
long cataleg<Valor>::h(const string &k) const {
    long suma = 0;
    for (nat i = 0; i < k.length(); ++i) {
        suma = (suma * 31) + k[i];
    }
    return (suma < 0) ? -suma : suma;
}

/* Mètodes privats auxiliars. */

template <typename Valor>
void cataleg<Valor>::copia(const cataleg &c) {
    _M = c._M;
    _quants = c._quants;
    _taula = new node*[_M];
    for (nat i = 0; i < _M; ++i) {
        if (c._taula[i] == nullptr) _taula[i] = nullptr;
        else {
            node* act_c = c._taula[i];
            _taula[i] = new node{act_c->_k, act_c->_v, nullptr};
            node* ultim_meu = _taula[i];
            act_c = act_c->_seg;
            while (act_c != nullptr) {
                ultim_meu->_seg = new node{act_c->_k, act_c->_v, nullptr};
                ultim_meu = ultim_meu->_seg;
                act_c = act_c->_seg;
            }
        }
    }
}

template <typename Valor>
void cataleg<Valor>::esborra_nodes(node *p) {
    if (p != nullptr) {
        esborra_nodes(p->_seg);
        delete p;
    }
}

/* redispersio: Augmenta la mida de la taula quan el factor de càrrega és alt.
   Cost: O(M_nova + N). */
template <typename Valor>
void cataleg<Valor>::redispersio() {
    node** taula_antiga = _taula;
    nat mida_antiga = _M;

    nat n = 2 * mida_antiga + 1;
    bool trobat = false;
    while (!trobat) {
        trobat = true;
        for (nat i = 2; i * i <= n; ++i) {
            if (n % i == 0) { trobat = false; break; }
        }
        if (!trobat) n++;
    }
    _M = n;

    _quants = 0;
    _taula = new node*[_M];
    for (nat i = 0; i < _M; ++i) _taula[i] = nullptr;

    for (nat i = 0; i < mida_antiga; ++i) {
        node* act = taula_antiga[i];
        while (act != nullptr) {
            assig(act->_k, act->_v);
            act = act->_seg;
        }
        esborra_nodes(taula_antiga[i]);
    }
    delete[] taula_antiga;
}

template <typename Valor>
float cataleg<Valor>::factor_de_carrega() const {
    return float(_quants) / _M;
}
