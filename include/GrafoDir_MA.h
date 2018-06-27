#ifndef GRAFODIR_MA_H
#define GRAFODIR_MA_H
#include <string>

using namespace std;

template <class A>
class GrafoDir_MA
{
    public:
        GrafoDir_MA();
        virtual ~GrafoDir_MA();
        A MatAris[][];
        string ListaEtiquetas[];
        int UltimoLleno;

        void Iniciar();
        void Destruir();
        void vaciar();
        bool vacio();
        void AgregVert(string);
        void ElimVert(int);
        void AgregArist(A);
        void ElimArist(int, int);
        string Etiqueta(int);
        A Peso(int, int);
        void ModifEtiq(int, A);
        void ModifPeso(int, int, A);
        int PrimerVert();
        int SteVert(int);
        int PrimerVertAdy(int);
        int SteVertAdy(int, int);
        int NumVert();
        bool ExisteArista(int, int);

    protected:

    private:
};

#endif // GRAFODIR_MA_H
