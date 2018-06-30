#ifndef NODOV_H
#define NODOV_H
#include "NodoA.h"
class NodoA;
class NodoV
{
    public:
        int label;
        NodoA *NextAdy;
        NodoV *NextVert;

        NodoV();
//        NodoV(string e);
        virtual ~NodoV();

    protected:

    private:
};

#endif // NODOV_H
