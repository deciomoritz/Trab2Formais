#include "terminal.h"

Terminal::Terminal()
{
}

Terminal::Terminal(string nome){
    _nome = nome;
}

void Terminal::first(){
    _first.insert(this);
}
