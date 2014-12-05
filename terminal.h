#ifndef TERMINAL_H
#define TERMINAL_H

#include "simbolo.h"

#include <iostream>
using namespace::std;

class Terminal : public Simbolo{

public:

    using Simbolo::get_first;
    using Simbolo::ehNTerminal;


    /*! \brief Construtor padrão
     *
     */
    Terminal();
    /*! \brief Construção padrão
     *
     * \param string nome
     *
     */
    Terminal(string nome);

    /*! \brief Método que calcula o first do símbolo
     *
     * \param Simbolos *X, Simbolos* Ne
     *
     */
    Simbolos first(Simbolos *X, Simbolos* Ne) override;

    /*! \brief Método estático retorna um ponteiro para o Terminal s, se ele estiver contido no conjunto simbolos
     *
     * \param set<Terminal*> simbolos, Terminal s
     *
     */
    static Simbolo * contem(set<Terminal*> simbolos, Terminal s);
};

#endif // TERMINAL_H
