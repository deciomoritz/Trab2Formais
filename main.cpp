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

}
