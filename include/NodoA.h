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

        NodoA(){}       //Constructor vacío de la clase
        NodoA(P, NodoV*);
        NodoA(P, NodoA*, NodoV*);
        virtual ~NodoA();

    protected:

    private:
};

/**
    * @brief Constructor de la clase
    * @param pes: De tipo P contiene el peso de la arista
    * @param v: Puntero al nodo cabeza
*/
NodoA::NodoA(P pes, NodoV* v)
{
    NextVert=v;
    peso=pes;
    NextAdy=nullptr;
}

/**
    * @brief Destructor de la clase
*/
NodoA::~NodoA()
{

}

#endif // NODOA_H
