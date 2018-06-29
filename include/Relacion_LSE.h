#ifndef RELACION_LSE_H
#define RELACION_LSE_H
#include "NodoL.h"

using namespace std;

template<class A, class B>
class Relacion_LSE
{
    public:
        NodoL<A, B> *PrimerElem;

        Relacion_LSE(){}
        virtual ~Relacion_LSE(){}

        void Crear(){
            PrimerElem = nullptr;
        }

        void Destruir()
        {
            NodoL<A, B>* sig;
            while(PrimerElem!=nullptr)
            {
                sig=PrimerElem->ptrSig;
                delete &PrimerElem;
                PrimerElem=sig;
            }
            delete this;
        }

        void Vaciar()
        {
            NodoL<A, B>* sig;
            while(PrimerElem!=nullptr)
            {
                sig=PrimerElem->ptrSig;
                delete &PrimerElem;
                PrimerElem=sig;
            }
        }

        bool vacia(){
            if(PrimerElem!=nullptr)
            {
                return true;
            }
            return false;
        }

        void AgregarRelacion(A dat1, B dat2)
        {

        }
    protected:

    private:
};

#endif // RELACION_LSE_H
