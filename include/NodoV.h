#ifndef NODOV_H
#define NODOV_H
#include "NodoA.h"

typedef string T;
class NodoA;//<int>;
class NodoV
{
    public:
        T label;
        NodoA *NextAdy;
        NodoV *NextVert;

        NodoV();
        NodoV(T);
        virtual ~NodoV();

    protected:

    private:
};
/**
    * @brief Constructor vacío de la clase
*/
NodoV::NodoV()
{

}

/**
    * @brief Constructor de la clase
    * @param etiqueta: De tipo V contiene la etiqueta del vértice
*/
NodoV::NodoV(T etiqueta)
{
    label=etiqueta;
    NextAdy=nullptr;
    NextVert=nullptr;
}

/**
    * @brief Destructor de la clase
*/
NodoV::~NodoV()
{

}
#endif // NODOV_H
