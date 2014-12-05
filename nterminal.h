#ifndef NTERMINAL_H
#define NTERMINAL_H

#include "simbolo.h"

#include "terminal.h"

#include <vector>
using std::vector;

#include <algorithm>

#include <set>
using std::set;

/*! \brief Uma FormaSentencial é definida como vector<Simbolo*>
 *
 */
typedef vector<Simbolo*> FormaSentencial;

class NTerminal : public Simbolo{
    set<FormaSentencial> _producoes;
    Simbolos _first_NT, _follow;
    using Simbolo::first;

public:
    using Simbolo::get_first;
    using Simbolo::ehNTerminal;

    /*! \brief Construtor padrão
     *
     */
    NTerminal();

    /*! \brief Construtor padrão
     *
     * \param string nome
     *
     */
    NTerminal(string nome);

    /*! \brief Adiciona f ao conjunto de produções e retorna um ponteiro para f
     *
     * \param FormaSentencial f
     *
     */
    FormaSentencial * addProducao(FormaSentencial f);
    /*! \brief Retorna ponteiro para o conjunto de produções
     *
     */
    set<FormaSentencial> * producoes();
    /*! \brief Seta *S como sendo conjunto _follow união com S
     *
     * \param Simbolos *S
     *
     */
    void set_follow(Simbolos *S);

    /*! \brief Retorna ponteiro para conjunto _follow
     *
     */
    Simbolos* get_follow();

    /*! \brief Método que calcula o first do símbolo
     *
     * \param Simbolos *X, Simbolos* Ne
     *
     */
    Simbolos first(Simbolos *X, Simbolos* Ne) override;

    /*! \brief Método que calcula o first-NT do símbolo
     *
     * \param Simbolos* Ne
     *
     */
    void first_NT(Simbolos *Ne);

    /*! \brief Retorna conjunto first-NT
     *
     * \param Simbolos* Ne
     *
     */
    Simbolos get_first_NT(Simbolos *Ne);

    /*! \brief Retorna true se o simbolo é recursivo à esquerda
     *
     * \param Simbolos* Ne
     *
     */
    bool ehRE(Simbolos * Ne);
    
    /*! \brief Retorna true se o simbolo deriva epsiln diretamente
     *
     */
    bool derivaEpsilonDiretamente();

    /*! \brief Retorna true se o conjunto s contém epsilon
     *
     * \param Simbolos s
     *
     */
    static bool contemEpsilon(Simbolos s);
    /*! \brief Remove epsilon do conjunto s
     *
     * \param Simbolos *s
     *
     */
    static void removerEpsilon(Simbolos *s);

    /*! \brief Verifica se s pertence à simbolos e retorna um ponteiro para s
     *
     * \param set<NTerminal*> simbolos, NTerminal s
     *
     */
    static Simbolo * contem(set<NTerminal*> simbolos, NTerminal s);

    /*! \brief Retorna true se fs constar somente de terminais
     *
     * \param FormaSentencial fs
     *
     */
    static bool somenteTerminais(FormaSentencial fs);

    /*! \brief Retorna true se fs constar somente de não terminais
     *
     * \param FormaSentencial fs
     *
     */
    static bool somenteNTerminais(FormaSentencial fs);
};

#endif // NTERMINAL_H
