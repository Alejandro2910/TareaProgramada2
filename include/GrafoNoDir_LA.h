#ifndef GRAFONODIR_LA_H
#define GRAFONODIR_LA_H
#include "GrafoDir_LA.h"
//#include "NodoA.h"
//#include "NodoV.h"

//NodoV* NodoNulo = nullptr ;
//NodoA* NodoNulo1 = nullptr ;
//typedef string T;
//typedef int P;
class GrafoNoDir_LA
{
    public:
        GrafoNoDir_LA();
        virtual ~GrafoNoDir_LA();
        NodoV* g;

        void Iniciar();
        void Destruir();
        void Vaciar();
        bool Vacio();
        void AgVer(T);
        void ElimVert(NodoV*);
        void AgArista(P, NodoV*, NodoV*);
        void ElimArista(NodoV*, NodoV*);
        T Etiqueta(NodoV*);
        P Peso(NodoV*, NodoV*);
        void ModifEtiqueta(NodoV*, T);
        void ModifPeso(NodoV*, NodoV*, P);
        NodoV* PrimerVert();
        NodoV* SteVert(NodoV*);
        NodoV* PrimerVertAdy(NodoV*);
        NodoV* SteVertAdy(NodoV*, NodoV*);
        int NumVert();
        bool ExisteArista(NodoV*, NodoV*);
        void Imprimir();


    protected:

    private:
};

GrafoNoDir_LA::GrafoNoDir_LA()
{
    //ctor
}

GrafoNoDir_LA::~GrafoNoDir_LA()
{
    //dtor
}


/**
    * @brief Operador básico que inicializa el grafo.
    * @param No recibe parámetros.
    * @return void
*/
void GrafoNoDir_LA::Iniciar()
{
    g=nullptr;
}

/**
    * @brief Operador básico que destruye el grafo, devuelve toda la memoria ocupada.
    * @param No recibe parámetros.
    * @return void
*/
void GrafoNoDir_LA::Destruir()
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
/**
    * @brief Operador básico que inicializa borra todo el grafo sin desturirlo.
    * @param No recibe parámetros.
    * @return void
*/
void GrafoNoDir_LA::Vaciar()
{
    while(g!=nullptr)
    {
        NodoV* tempV;
        NodoA* tempA;
        NodoA* tempA2;
        tempV=g;
        g=g->NextVert;
        tempA=tempV->NextAdy;
        while(tempA!=nullptr)
        {
            tempA2=tempA;
            tempA=tempA->NextAdy;
            delete tempA2;
        }
        delete tempV;
    }
}

/**
    * @brief Operador básico que indica si un grafo tiene vertices o no.
    * @param No recibe parámetros.
    * @return True si el grafo no tiene vertices y False si tiene al menos uno.
*/
bool GrafoNoDir_LA::Vacio()
{
    if(!g)
        return true;
    return false;
}

/**
    * @brief Operador básico que le agrega un nuevo vértice al grafo.
    * @param label: etiqueta de tipo T del nuevo vértice.
    * @return void
*/
void GrafoNoDir_LA::AgVer(T label)
{
    if(!g)
    {
        NodoV* n=new NodoV(label);
        g=n;
    }
    else
    {
        NodoV* n=new NodoV(label);
        n->NextVert=g;
        g=n;
    }
}

/**
    * @brief Operador básico que elimina un vértice del grafo.
    * @param n: Vértice por ser eliminado
    * @return void
*/
void GrafoNoDir_LA::ElimVert(NodoV* n)
{
    NodoV* nIter=g;
    if(n==g)
    {
        g=g->NextVert;
        delete n;
    }
    else
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

/**
    * @brief Operador básico que agrega una arista entre dos vértices existentes del grafo.
    * @param peso: Contiene el peso de la arista, es del tipo P
    * @param v1: Apuntador al vértice cola
    * @param v2: Apuntador al vértice cabeza
    * @return void
*/
void GrafoNoDir_LA::AgArista(P peso, NodoV* v1, NodoV* v2)
{
    NodoA *a1= new NodoA(peso, v2);
    NodoA *a2= new NodoA(peso, v1);
    a1->NextAdy=v1->NextAdy;
    v1->NextAdy=a1;
    a2->NextAdy=v2->NextAdy;
    v2->NextAdy=a2;
}

/**
    * @brief Operador básico que elimina una arista entre dos vértices del grafo.
    * @param n: Vértice por ser eliminado
    * @param v1: Apuntador al vértice cola
    * @param v2: Apuntador al vértice cabeza
    * @return void
*/
void GrafoNoDir_LA::ElimArista(NodoV* v1, NodoV* v2)
{
    bool enco=false;
    NodoA* aiter1=v1->NextAdy;
    NodoA* aiter2=v2->NextAdy;
    if(aiter1->NextVert==v2)
    {
        v1->NextAdy=aiter1->NextAdy;
        delete aiter1;
        v2->NextAdy=aiter2->NextAdy;
        delete aiter2;
        enco=true;
    }
    else
    {
        while( aiter1!=nullptr && !(enco))
        {
            if(aiter1->NextAdy!=nullptr)
            {
                if(aiter1->NextAdy->NextVert==v2)
                {
                    NodoA* tmp=aiter1->NextAdy;
                    aiter1->NextAdy=tmp->NextAdy;
                    delete tmp;
                    enco=true;
                }
            }
            aiter1=aiter1->NextAdy;
        }
        enco=false;
        while( aiter2!=nullptr && !(enco))
        {
            if(aiter2->NextAdy!=nullptr)
            {
                if(aiter2->NextAdy->NextVert==v1)
                {
                    NodoA* tmp=aiter2->NextAdy;
                    aiter2->NextAdy=tmp->NextAdy;
                    delete tmp;
                    enco=true;
                }
            }
            aiter2=aiter2->NextAdy;
        }
    }
}

/**
    * @brief Operador básico que retorna la etiqueta de un vértice del grafo.
    * @param v: Apuntador al vértice del que se quiere conocer la etiqueta
    * @return Etiqueta de tipo T del vértice
*/
T GrafoNoDir_LA::Etiqueta(NodoV* v)
{
    return v->label;
}

/**
    * @brief Operador básico que retorna el peso de una arista del grafo.
    * @param v1: Apuntador al vértice cola
    * @param v2: Apuntador al vértice cabeza
    * @return Peso de tipo P de la arista
*/
P GrafoNoDir_LA::Peso(NodoV* v1, NodoV* v2)
{
    NodoA* aiter=v1->NextAdy;
    while(aiter!=nullptr)
    {
        if(aiter->NextVert==v2)
        {
            return aiter->peso;
        }
        aiter=aiter->NextAdy;
    }
}

/**
    * @brief Operador básico que modifica la etiqueta de un vértice del grafo.
    * @param v: Apuntador al vértice del que se requiere modificar la etiqueta
    * @param nLabel: De tipo T, tiene la nueva etiqueta
    * @return void
*/
void GrafoNoDir_LA::ModifEtiqueta(NodoV* v, T nLabel)
{
    v->label=nLabel;
}

/**
    * @brief Operador básico que actualiza el peso de una arista del grafo.
    * @param v1: Apuntador al vértice cola
    * @param v2: Apuntador al vértice cabeza
    * @param nPeso: De tipo P, tiene el nuevo peso de la arista.
    * @return void
*/
void GrafoNoDir_LA::ModifPeso(NodoV* v1, NodoV* v2, P nPeso)
{
    bool enco=false;
    NodoA* aiter=v1->NextAdy;
    while(aiter!=nullptr && !(enco))
    {
        if(aiter->NextVert==v2)
        {
            aiter->peso=nPeso;
            enco=true;
        }
        aiter=aiter->NextAdy;
    }
}

/**
    * @brief Operador básico que retorna el "primer" vértice del grafo
    * @param No recibe parámetros
    * @return Puntero al primer vértice del grafo
*/
NodoV* GrafoNoDir_LA::PrimerVert()
{
    return g;
}

/**
    * @brief Operador básico que retorna el siguiente vértice de uno dado en el grafo
    * @param v: Puntero al vértice en el que se está actualmente
    * @return Puntero al siguiente vértice a v en el grafo
*/
NodoV* GrafoNoDir_LA::SteVert(NodoV* v)
{
    return v->NextVert;
}

/**
    * @brief Operador básico que retorna el "primer" vértice adyacente a uno dado en el grafo
    * @param v: Puntero al vértice en el que se está actualmente
    * @return Puntero al "primer" vértice adyacente a v en el grafo
*/
NodoV* GrafoNoDir_LA::PrimerVertAdy(NodoV* v)
{
    return v->NextAdy->NextVert;
}

/**
    * @brief Operador básico que retorna el "siguiente" vértice adyacente de uno dado en el grafo
    * @param v1: Puntero al vértice en el que se está actualmente
    * @param v2: Puntero a un vértice adyacente de v1
    * @return Puntero a un vértice adyacente de v1 diferente de v2
*/
NodoV* GrafoNoDir_LA::SteVertAdy(NodoV* v1, NodoV* v2)
{
    NodoA* aiter=v1->NextAdy;
    while(aiter!=nullptr)
    {
        if(aiter->NextVert==v2)
        {
            if(aiter->NextAdy==nullptr)
                return nullptr;
            else
                return aiter->NextAdy->NextVert;
        }
        aiter=aiter->NextAdy;
    }
    //return v2->NextAdy;
}

/**
    * @brief Operador básico que retorna la cantidad de vértices que conforma el grafo
    * @param No recibe parámetros
    * @return Entero con la cantidad de vértices contados
*/
int GrafoNoDir_LA::NumVert()
{
    NodoV* nIter=g;
    int conta=0;
    while(nIter!=NodoNulo)
    {
        ++conta;
        nIter=nIter->NextVert;
    }
    return conta;
}

/**
    * @brief Operador básico que pregunta si un vértice apunta al otro vértice dado
    * @param v1: Apuntador al vértice cola
    * @param v2: Apuntador al vértice cabeza
    * @return True si de v1 sale una arista que apunta a v2 y false en caso contrario
*/
bool GrafoNoDir_LA::ExisteArista(NodoV* v1, NodoV* v2)
{
    NodoA* aiter=v1->NextAdy;
    while(aiter!=nullptr)
    {
        if(aiter->NextVert==v2)
        {
            return true;
        }
        aiter=aiter->NextAdy;
    }
    return false;
}

/**
    * @brief Operador básico que recorre todo el grafo e imprime las etiquetas y las aristas con su pesos
    * @param No recibe parámetros
    * @return void
*/
void GrafoNoDir_LA::Imprimir()
{
    NodoV* nIter=g;
    NodoA* aiter;
    while(nIter!=nullptr)
    {
        cout<< nIter->label<<" ";
        aiter=nIter->NextAdy;
        while(aiter!=nullptr)
        {
            cout<<" - "<<aiter->peso<<" - "<<aiter->NextVert->label;
            aiter=aiter->NextAdy;
        }
        cout<<endl;
        nIter=nIter->NextVert;
    }
}

#endif // GRAFONODIR_LA_H
