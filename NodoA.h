#ifndef NODOA_H
#define NODOA_H
#include "NodoV.h"

class NodoA
{
    public:
        int label;
        NodoA *NextAdy;
        NodoV *NextVert;

        NodoA();
        virtual ~NodoA();

    protected:

    private:
};

#endif // NODOA_H
