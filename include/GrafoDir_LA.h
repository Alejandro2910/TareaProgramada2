#ifndef GRAFODIR_LA_H
#define GRAFODIR_LA_H
#include "NodoA.h"
#include "NodoV.h"

typedef string T;
typedef int P;
static NodoV VerticeNulo = nullptr;
class GrafoDir_LA
{
    public:
        GrafoDir_LA();
        virtual ~GrafoDir_LA();
        NodoV* g;

        void Iniciar();
        void Destruir();
        void Vaciar();
        bool Vacio();
        void AgVer(T);
        void ElimVert(NodoV);
        void AgArista(NodoV, NodoV);
        void ElimArista(NodoV, NodoV);
        T Etiqueta(NodoV);
        P Peso(NodoV, NodoV);
        void ModifEtiqueta(NodoV, T);
        void ModifPeso(NodoV, NodoV, P);
        NodoV* PrimerVert();
        NodoV* SteVert();
        NodoV* PrimerVertAdy(NodoV);
        NodoV* SteVertAdy(NodoV, NodoV);
        int NumVert();
        bool ExisteArista(NodoV, NodoV);

    protected:

    private:
};

void GrafoDir_LA::Iniciar()
{
    g=nullptr;
}

void GrafoDir_LA::Destruir()
{
    NodoV* tempV;
    NodoA* tempA;
    NodoA* tempA2;
    while(g!=nullptr)
    {
        tempV=g;
        g=g->NextVert;
        tempA2=tempV->NextAdy;
        while(tempA!=nullptr)
        {
            tempA2=tempA;
            tempA=tempA->NextAdy;
            delete tempA2;
        }
        delete tempV;
    }
    delete g;

}
void GrafoDir_LA::Vaciar()
{
    NodoV* tempV;
    NodoA* tempA;
    NodoA* tempA2;
    while(g!=nullptr)
    {
        tempV=g;
        g=g->NextVert;
        tempA2=tempV->NextAdy;
        while(tempA!=nullptr)
        {
            tempA2=tempA;
            tempA=tempA->NextAdy;
            delete tempA2;
        }
        delete tempV;
    }
}

bool GrafoDir_LA::Vacio()
{
    if(g)
        return true;
    return false;
}

void GrafoDir_LA::AgVer(T label)
{
    if(!g)
    {
        NodoV* n=new NodoV();
        n->label=label;
        g=n;
    }
    else
    {

    }
}

void GrafoDir_LA::ElimVert(NodoV){}
void GrafoDir_LA::AgArista(NodoV, NodoV){}
void GrafoDir_LA::ElimArista(NodoV, NodoV){}
T GrafoDir_LA::Etiqueta(NodoV){}
P GrafoDir_LA::Peso(NodoV, NodoV){}
void GrafoDir_LA::ModifEtiqueta(NodoV, T){}
void GrafoDir_LA::ModifPeso(NodoV, NodoV, P){}
NodoV* GrafoDir_LA::PrimerVert(){}
NodoV* GrafoDir_LA::SteVert(){}
NodoV* GrafoDir_LA::PrimerVertAdy(NodoV){}
NodoV* GrafoDir_LA::SteVertAdy(NodoV, NodoV){}
int GrafoDir_LA::NumVert(){}
bool GrafoDir_LA::ExisteArista(NodoV, NodoV){}




#endif // GRAFODIR_LA_H
