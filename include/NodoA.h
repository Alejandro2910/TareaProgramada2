#ifndef NODOA_H
#define NODOA_H

class NodoV;
typedef int P;
class NodoA
{
    public:

        P peso; //T peso;
        NodoA *NextAdy;
        NodoV *NextVert;

        NodoA(){}
        NodoA(P, NodoV*);
        NodoA(P, NodoA*, NodoV*);
        virtual ~NodoA();

    protected:

    private:
};

NodoA::NodoA(P peso, NodoV* v)
{
    NextVert=v;
    peso=peso;
}

NodoA::~NodoA()
{

}

#endif // NODOA_H
