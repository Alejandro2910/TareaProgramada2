#include <iostream>
#include <GrafoDir_MA.h>

using namespace std;

int main()
{
    GrafoDir_MA<int> G;
    G.Iniciar();
    G.AgregVert("A");
    G.AgregVert("B");
    G.AgregVert("C");
    G.AgregVert("D");
    G.AgregVert("E");
    G.AgregVert("F");
    G.AgregVert("G");
    G.AgregArist(4, 0, 6);
    G.AgregArist(1, 6, 5);
    G.AgregArist(8, 0, 5);
    G.AgregArist(3, 1, 0);
    G.AgregArist(13, 1, 3);
    G.AgregArist(2, 2, 1);
    G.AgregArist(3, 3, 2);
    G.AgregArist(15, 2, 4);
    G.AgregArist(1, 3, 4);
    G.AgregArist(4, 5, 4);
    G.AgregArist(2, 5, 3);
    G.MuestreDatos();
    G.ElimArist(2, 1);
    G.ElimArist(2, 4);
    G.ElimArist(3, 2);
    G.ElimVert(2);
    G.MuestreDatos();
    return 0;
}
