#include "mainwindow.h"
#include <QApplication>

#include "terminal.h"

#include <set>
using namespace std;

#include <vector>

#include "leitorgramatica.h"

int main(int argc, char *argv[])
{
    //    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();

    //    return a.exec();
    LeitorGramatica l;
    string s;
    //    s = "E -> E + T | E - T | T\n"
    //               "T -> T * F | T / F | F\n"
    //               "F -> ( E ) | id";

    //    l.ler(s);

    s =
            "S -> a A B | B | A\n"
            "A -> C | B\n"
            "B -> a | b | E\n"
            "D -> a | b | F\n"
            "C -> A | E\n"
            "E -> F\n"
            "F -> E";
    Gramatica g = l.ler(s);
    g.eliminarInalcancaveis();
    string teste1 =
            "S(inicial) -> a A B | A | B \n"
            "A -> B | C \n"
            "B -> a | b | E \n"
            "C -> A | E \n"
            "E -> F \n"
            "F -> E \n";
    if(g.print().compare(teste1) == 0)
        cout << "Eliminar inalcançaveis OK!" << endl;
    else
        cout << "Eliminar inalcançaveis falhou!" << endl;

        g.eliminarInferteis();
        string teste2 = "S(inicial) -> a A B | A | B \n"
                "A -> B | C \n"
                "B -> a | b \n"
                "C -> A \n";
        if(g.print().compare(teste2) == 0)
            cout << "Eliminar inférteis OK!" << endl;
        else
            cout << "Eliminar inférteis falhou!" << endl;

        s =
                "S -> a A B | B | A\n"
                "A -> C | B\n"
                "B -> a | b | E\n"
                "D -> a | b | F\n"
                "C -> A | E\n"
                "E -> F\n"
                "F -> E";
        teste2 =
                "S(inicial) -> a A B | A | B \n"
                "A -> B | C \n"
                "B -> a | b \n"
                "C -> A \n";
        g = l.ler(s);
        g.eliminarInuteis();
        if(g.print().compare(teste2) == 0)
            cout << "Eliminar inúteis OK!" << endl;
        else
            cout << "Eliminar inúteis falhou!" << endl;

        s =
                "S -> A C\n"
                "A -> E F B\n"
                "B -> a B | &\n"
                "C -> b A C D | D\n"
                "D -> e D | &\n"
                "E -> c D | &\n"
                "F -> d F | &";
       g = l.ler(s);
       cout << "=============TESTE FIRST NT============="<<endl;
       unordered_map<Simbolo*,Simbolos> teste = g.first_NT();
       for(auto it = teste.begin(); it != teste.end(); it++){
           Simbolo *A = it->first;
           string name = A->nome();
           cout<<"First NT de : " <<name<< endl;
           for(auto it2 = (it->second).begin();it2 !=(it->second).end(); it2++){
               Simbolo * b = *it2;
               cout << b->nome() << " , ";
           }
           cout << endl;
       }
       cout << "===================================="<<endl;
        s = "S -> B A a | b\n"
            "B -> a a | & | A\n"
            "A -> S b b | B";
        g = l.ler(s);
        vector<bool> testeB = {false, true, true};
        int i = 0;
        for(auto A = g.nTerminais()->begin(); A != g.nTerminais()->end();A++){
            NTerminal * s = *A;

            if(g.derivaEpsilon(s) == testeB.at(i))
                cout << "Deriva epsilon ok!" << endl;
            else
                cout << "Deriva epsilon fail!" << endl;
            i++;
        }

        s = "S -> B A a | b | B A\n"
            "B -> a a | & | A | D\n"
            "A -> S b b | B\n"
            "D -> S A | S a";
        g = l.ler(s);
        vector<bool> testeC = {true, true, true, true};
        i = 0;
        for(auto A = g.nTerminais()->begin(); A != g.nTerminais()->end();A++){
            NTerminal * s = *A;

            if(g.derivaEpsilon(s) == testeC.at(i))
                cout << "Deriva epsilon ok!" << endl;
            else
                cout << "Deriva epsilon fail!" << endl;
            i++;
        }

        s = "S -> B A a | b | A B\n"
            "B -> a a | & | A\n"
            "A -> S b b | B";
        g = l.ler(s);
        vector<bool> testeD = {true, true, true};
        i = 0;
        for(auto A = g.nTerminais()->begin(); A != g.nTerminais()->end();A++){
            NTerminal * s = *A;

            if(g.derivaEpsilon(s) == testeD.at(i))
                cout << "Deriva epsilon ok!" << endl;
            else
                cout << "Deriva epsilon fail!" << endl;
            i++;
        }

        s = "S -> B A a | b | B A\n"
            "B -> a a | & | A | D\n"
            "A -> S b b | B\n"
            "D -> S A | S a";
        g = l.ler(s);
        cout << "Detectar NT RE da gramática: " << endl << endl << g.print();
        for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
            NTerminal * nt = *it;
            if(nt->ehRE(g.Ne()))
                cout << nt->nome() << " é RE" << endl;
            else
                cout << nt->nome() << "não é RE" << endl;
        }

        s = "S -> A a | & | d\n"
            "B -> c\n"
            "A -> S B b | b";
        g = l.ler(s);
        cout << "Detectar NT RE da gramática: " << endl << endl << g.print();
        for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
            NTerminal * nt = *it;
            if(nt->ehRE(g.Ne()))
                cout << nt->nome() << " é RE" << endl;
            else
                cout << nt->nome() << " não é RE" << endl;
        }

        s = "S -> A a | & | d\n"
            "B -> c\n"
            "A -> S B b | b";
        g = l.ler(s);
        cout << "Calcular first da gramática: " << endl << endl << g.print();
        g.calculaFirst();
        for(auto it = g.nTerminais()->begin(); it != g.nTerminais()->end(); it++){
            NTerminal * nt = *it;
            cout << "NT: " << nt->nome() << endl;
            for(auto it = nt->getFirst()->begin(); it != nt->getFirst()->end(); it++){
                NTerminal * nt2 = *it;
                cout << nt2->nome() << " ";
            }
            cout << endl;
        }
}
