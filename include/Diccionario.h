#ifndef DICCIONARIO_H
#define DICCIONARIO_H
#include <NodoD.h>

template<class A>
class Diccionario
{
    public:
        NodoD<A>* PrimerElem;
        Diccionario();
        virtual ~Diccionario();
        void Crear();
        void Destruir();
        void Vaciar();
        bool Vacio();
        void Agregar(A);
        void Eliminar(A);
        bool Pertenece(A);
        int NumElem();

    protected:

    private:
};

template<typename A>Diccionario<A>::Diccionario(){

}

template<typename A>Diccionario<A>::~Diccionario(){

}

template<typename A> void Diccionario<A>::Crear(){
    PrimerElem = nullptr;
}

template<typename A> void Diccionario<A>::Destruir(){
    NodoD<A>* Sig;
    while(PrimerElem!=nullptr)
    {
        Sig=PrimerElem->PtrSig;
        delete &PrimerElem;
        PrimerElem=Sig;
    }
    delete PrimerElem;
}

template<typename A> void Diccionario<A>::Vaciar(){
    NodoD<A>* Sig;
    while(PrimerElem!=nullptr)
    {
        Sig=PrimerElem->PtrSig;
        delete &PrimerElem;
        PrimerElem=Sig;
    }
}

template<typename A> bool Diccionario<A>::Vacio(){
    if(PrimerElem!=nullptr)
    {
        return true;
    }
    return false;
}

template<typename A> void Diccionario<A>::Agregar(A elem){
    if(PrimerElem == nullptr){
        PrimerElem = new NodoD<A>(elem);
    }else{
        NodoD<A>* iter =PrimerElem;
        while(iter->PtrSig != nullptr){
            iter=iter->PtrSig;
        }
        iter->PtrSig = new NodoD<A>(elem);
    }
}

template<typename A> void Diccionario<A>::Eliminar(A elem){
    if(PrimerElem->Dato == elem){
        NodoD<A>* Temp = PrimerElem;
        PrimerElem = PrimerElem->PtrSig;
        delete Temp;
    }else{
        NodoD<A>* iter = PrimerElem;
        NodoD<A>* iterAtras = PrimerElem;
        while(iter->Dato != elem){
            iter = iter->PtrSig;
            if(iter->Dato == elem){
                iterAtras->PtrSig = iter->PtrSig;
                delete iter;
                break;
            }
            iterAtras = iterAtras->PtrSig;
        }
        iter->PtrSig = new NodoD<A>(elem);
    }
}

template<typename A>bool Diccionario<A>::Pertenece(A elem){
    NodoD<A>*iter = PrimerElem;
    while(iter != nullptr){
        if(iter->Dato == elem){
            return true;
        }
        iter = iter->PtrSig;
    }
    return false;
}

template<typename A>int Diccionario<A>::NumElem(){
    int cont = 0;
    NodoD<A>*iter = PrimerElem;
    while(iter != nullptr){
        ++cont;
        iter = iter->PtrSig;
    }
    return cont;
}


#endif // DICCIONARIO_H
