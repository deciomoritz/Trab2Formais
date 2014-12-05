#ifndef ANALISADORSINTATICO_H
#define ANALISADORSINTATICO_H

#include<stack>
using std::stack;

#include "leitorgramatica.h"

const char invalido = 'î';

class AnalisadorSintatico
{
public:
    /*! \brief Construtor padrão
     *
     */
    AnalisadorSintatico();

    /*! \brief Analisa a sentença, retorna true caso a sentença pertença à Gramática g
     *
     * \param string sentenca, Gramatica & g
     *
     */
    static bool analisar(string sentenca, Gramatica & g);

    /*! \brief Lê a string e transforma em uma Sentenca da Gramática g. Caso contenha símbolos que não pertençam ao alfabeto
     * de L(G), retorna uma Sentenca contendo o carácter inválido, definido como î
     *
     * \param string s, Gramatica g
     *
     */
    static Sentenca lerSentenca(string s, Gramatica g);
};

#endif // ANALISADORSINTATICO_H
