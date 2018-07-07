#ifndef GRAFODIR_LA_H
#define GRAFODIR_LA_H
#include "NodoA.h"
#include "NodoV.h"

NodoV* NodoNulo = nullptr ;
NodoA* NodoNulo = nullptr ;
typedef string T;
typedef int P;
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
        void ElimVert(NodoV*);
        void AgArista(P, NodoV*, NodoV*);
        void ElimArista(NodoV*, NodoV*);
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
        NodoV* n=new NodoV(label);
        //n->label=label;
        g=n;
    }
    else
    {
        NodoV* n=new NodoV(label);
        n->NextVert=g;
        g=n;
    }
}

void GrafoDir_LA::ElimVert(NodoV* n)
{
    NodoV* nIter=g;
    while(nIter!=NodoNulo)
    {
        if(nIter->NextVert == n)
        {
            nIter->NextVert=n->NextVert;
            delete n;
            break;
        }
        nIter=nIter->NextVert;
    }
}

void GrafoDir_LA::AgArista(P peso, NodoV* v1, NodoV* v2)
{
    //Se puede hacer mas eficiente
    NodoA *a1= new NodoA(peso, v1);
    NodoA *a2= new NodoA(peso, v2);
    NodoV* nIter=g;
    bool enco1, enco2 = false;
    while(nIter!=NodoNulo  && !(enco1&&enco2))
    {
        if(nIter->NextVert == v2)
        {
            a1->NextAdy=nIter->NextAdy;
            nIter->NextAdy=a1;
            enco2=true;
        }
        else
        {
            if(nIter->NextVert == v1)
            {
                a2->NextAdy=nIter->NextAdy;
                nIter->NextAdy=a2;
                enco1=true;
            }
        }
        nIter=nIter->NextVert;
    }
}

void GrafoDir_LA::ElimArista(NodoV* v1, NodoV* v2)
{
    NodoV* nIter=g;
    bool enco1, enco2 = false;

    while(nIter!=NodoNulo  && !(enco1&&enco2))
    {
        if(nIter->NextVert == v2 )
        {
            NodoA* aiter=nIter->NextAdy;
            while( aiter!=nullptr)
            {
                if(aiter->NextAdy!=nullptr)
                {
                    if(aiter->NextAdy->NextVert==v1)
                    {
                        NodoA* tmp=aiter;
//                        aiter->NextAdy->NextVert=aiter->NextAdy->NextAdy;
//                        delete
                    }
                }
            }
            a1->NextAdy=nIter->NextAdy;
            nIter->NextAdy=a1;
            enco2=true;
        }
        else
        {
            if(nIter->NextVert == v1)
            {
                a2->NextAdy=nIter->NextAdy;
                nIter->NextAdy=a2;
                enco1=true;
            }
        }
        nIter=nIter->NextVert;
    }
}

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
