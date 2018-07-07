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

NodoV::NodoV()
{

}

NodoV::NodoV(T label)
{
    label=label;
}

NodoV::~NodoV()
{

}
#endif // NODOV_H
