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
    /*! \brief Construtor padrão
     *
     */
    Simbolo();

    /*! \brief Método que calcula o first do símbolo
     *
     * \param Simbolos *X, Simbolos* Ne
     *
     */
    virtual Simbolos first(Simbolos *X, Simbolos* Ne);

    bool operator== (const Simbolo &s) const{
        return _nome.compare(s._nome) == 0;
    }

    /*! \brief Retorna true caso o simbolo em questão seja um Não Terminal
     *
     */
    bool ehNTerminal();

    /*! \brief Retorna o first do símbolo, dado um conjunto Ne
     *
     * \param Simbolos * Ne
     *
     */
    Simbolos get_first(Simbolos* Ne);

    /*! \brief Retorna nome do Simbolo
     *
     */
    string nome();
};

#endif // SIMBOLO_H
