#ifndef RELACION_LSE_H
#define RELACION_LSE_H
#include "NodoL.h"
#include <iostream>

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
            delete PrimerElem;
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

        void AgregarRelacion(A PreImg, B Img)
        {
            if(PrimerElem == nullptr){
                PrimerElem = new NodoL<A, B>(PreImg, Img);
            }else{
                NodoL<A, B> *Nuevo = new NodoL<A, B>(PreImg, Img);
                NodoL<A, B> *iter = PrimerElem;
                while(iter->ptrSig != nullptr){
                    iter=iter->ptrSig;
                }
                iter->ptrSig = Nuevo;
            }
        }

        void EliminarRelacion(A pre, B img){
            if(PrimerElem->elem.first == pre && PrimerElem->elem.second == img){
                NodoL<A, B>* Temp = PrimerElem;
                PrimerElem = PrimerElem->ptrSig;
                delete Temp;
            }else{
                NodoL<A, B>* iterador = PrimerElem;
                NodoL<A, B>* iteradorAtrasado = PrimerElem;
                while(iterador->elem.first != pre && iterador->elem.second != img){
                        iterador = iterador->ptrSig;
                        if(iterador->elem.first == pre && iterador->elem.second == img){
                            iteradorAtrasado->ptrSig = iterador->ptrSig;
                            delete iterador;
                            break;
                        }
                    iteradorAtrasado = iteradorAtrasado->ptrSig;
                }
            }
        }

        void ModificarImagen(A PreImgElem, B NuevImgElem){
            NodoL<A, B>* iter = PrimerElem;
            while(iter!=nullptr){
                if(iter->elem.first == PreImgElem){
                    iter->elem.second = NuevImgElem;
                    break;
                }
                iter = iter->ptrSig;
            }
        }

        void ModificarPreImagen(B ImgElem, A NuevPreImgElem){
            NodoL<A, B>* iter = PrimerElem;
            while(iter != nullptr){
                if(iter->elem.second == ImgElem){
                    iter->elem.first = NuevPreImgElem;
                    break;
                }
                iter = iter->ptrSig;
            }
        }

        bool ExisteRel(B Img, A PreImg){
            NodoL<A, B>* iter = PrimerElem;
            while(iter != nullptr){
                if(iter->elem.first == PreImg && iter->elem.second == Img){
                    return true;
                }
                iter = iter->ptrSig;
            }
            return false;
        }

        B Imagen(A PreImg){
            NodoL<A, B>* iter = PrimerElem;
            while(iter != nullptr){
                if(iter->elem.first == PreImg){
                    return iter->elem.second;
                }
                iter = iter->ptrSig;
            }
        }

        A PreImagen(B Img){
            NodoL<A, B>* iter = PrimerElem;
            while(iter != nullptr){
                if(iter->elem.second == Img){
                    return iter->elem.first;
                }
                iter = iter->ptrSig;
            }
        }

        bool EstaEnDominio(A PreImg){
            NodoL<A, B>* iter = PrimerElem;
            while(iter != nullptr){
                if(iter->elem.first == PreImg){
                    return true;
                }
                iter = iter->ptrSig;
            }
            return false;
        }

        bool EstaEnCodominio(B Img){
            NodoL<A, B>* iter = PrimerElem;
            while(iter != nullptr){
                if(iter->elem.second == Img){
                    return true;
                }
                iter = iter->ptrSig;
            }
            return false;
        }

        int NumRel(){
            int cont = 0;
            NodoL<A, B>* iter = PrimerElem;
            while(iter != nullptr){
                cont++;
                iter = iter->ptrSig;
            }
            return cont;
        }

        void MuestreDatos(){
            cout<<"Lista de Relaciones: "<<endl;
            NodoL<A, B>* iter = PrimerElem;
            while(iter != nullptr){
                cout<<"1. "<<iter->elem.first<<" 2. "<<iter->elem.second<<endl;
                iter=iter->ptrSig;
            }
        }

    protected:

    private:
};

#endif // RELACION_LSE_H
