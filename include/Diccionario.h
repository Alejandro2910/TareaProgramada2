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

/**
* @brief Operador basico que inicializa el modelo diccionario.
* @param No recibe parámetros.
*/
template<typename A> void Diccionario<A>::Crear(){
    PrimerElem = nullptr;
}

/**
* @brief Operador basico que destruye el diccionario.
* @param No recibe parámetros.
*/
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

/**
* @brief Operador basico que vacia el diccionario.
* @param No recibe parámetros.
*/
template<typename A> void Diccionario<A>::Vaciar(){
    NodoD<A>* Sig;
    while(PrimerElem!=nullptr)
    {
        Sig=PrimerElem->PtrSig;
        delete &PrimerElem;
        PrimerElem=Sig;
    }
}

/**
* @brief Operador basico que revisa si el diccionario esta vacio.
* @param No recibe parámetros.
* @return Retorna true en caso de que este vacio, false en el contrario.
*/
template<typename A> bool Diccionario<A>::Vacio(){
    if(PrimerElem==nullptr)
    {
        return true;
    }
    return false;
}

/**
* @brief Operador basico que agrega elementos al dicciomario.
* @param A elem.
*/
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

/**
* @brief Operador basico que elimina el elemento enviado como parametro.
* @param A elem.
*/
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

/**
* @brief Operador basico que verifica que el elemento enviado como parametro pertenece al diccionario.
* @param A elem.
* @return True si el elemento pertenece, False de lo contrario.
*/
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

/**
* @brief Operador basico que retorna la cantidad de elementos del diccionario.
* @param No recibe parametros.
* @return Int con la cantidad de elementos del diccionario.
*/
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
