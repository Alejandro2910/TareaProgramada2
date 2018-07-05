#ifndef NODOD_H
#define NODOD_H

template<class A>
class NodoD
{
    public:
        A Dato;
        NodoD* PtrSig;
        NodoD(){

        }
        NodoD(A Elemento){
           Dato = Elemento;
           PtrSig = nullptr;
        }
        virtual ~NodoD(){

        }

    protected:

    private:
};

#endif // NODOD_H
