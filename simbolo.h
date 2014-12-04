#ifndef SIMBOLO_H
#define SIMBOLO_H

#include <set>
using std::set;

#include <string>
using std::string;

class Simbolo;

typedef set<Simbolo*> Simbolos;

class Simbolo
{

protected:
    Simbolos _first;
    string _nome;

public:
    Simbolo();

    virtual Simbolos first(Simbolos *X, Simbolos* Ne);

    bool operator== (const Simbolo &s) const{
        return _nome.compare(s._nome) == 0;
    }

    bool ehNTerminal();
    Simbolos get_first(Simbolos* Ne);
    string nome();
};

#endif // SIMBOLO_H
