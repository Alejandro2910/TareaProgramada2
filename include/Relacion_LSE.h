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

        /**
        * @brief Operador basico que inicializa el modelo 1:1.
        * @param No recibe parámetros.
        */
        void Crear(){
            PrimerElem = nullptr;
        }

        /**
        * @brief Operador basico que destruye el modelo 1:1.
        * @param No recibe parámetros.
        */
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

        /**
        * @brief Operador basico que vacia el modelo 1:1.
        * @param No recibe parámetros.
        */
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

        /**
        * @brief Operador basico que revisa si el modelo 1:1 en cuestion se encuentra vacio o no.
        * @param No recibe parámetros.
        * @return true en caso de que ultimo lleno sea igual a -1, false de lo contrario
        */
        bool vacia(){
            if(PrimerElem!=nullptr)
            {
                return true;
            }
            return false;
        }

         /**
        * @brief Operador basico que agrega los elementos PreImg e Img a un nodo de la LSE.
        * @param A PreImg, B Img.
        */
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

        /**
        * @brief Operador basico que elimina el nodo que posea ambos elementos enviados como parametros.
        * @param A PreImg, B Img.
        */
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

        /**
        * @brief Operador basico que modifica el valor Imagen del nodo cuya PreImagen coincida con la envidad como parametro.
        * @param A PreImgElem, B NuevImgElem.
        */
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

        /**
        * @brief Operador basico que modifica el valor PreImg del nodo cuya PreImagen coincida con la envidad como parametro.
        * @param A NuevPreImgElem, B ImgElem.
        */
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

        /**
        * @brief Operador basico que verifica que exista la relacion entre la PreImg y Img.
        * @param B Img, A PreImg.
        * @return Retorna true en caso de que la reacion exista, false de lo contrario.
        */
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

        /**
        * @brief Operador basico que retorna el elemento Img de la relacion cuyo PreImg coincida con el enviado como parametro.
        * @param B PreImg.
        * @return
        */
        B Imagen(A PreImg){
            NodoL<A, B>* iter = PrimerElem;
            while(iter != nullptr){
                if(iter->elem.first == PreImg){
                    return iter->elem.second;
                }
                iter = iter->ptrSig;
            }
        }

        /**
        * @brief Operador basico que retorna el elemento PreImg de la relacion cuyo Img coincida con el enviado como parametro.
        * @param B Img.
        * @return El elemento de tipo A Preimagen
        */
        A PreImagen(B Img){
            NodoL<A, B>* iter = PrimerElem;
            while(iter != nullptr){
                if(iter->elem.second == Img){
                    return iter->elem.first;
                }
                iter = iter->ptrSig;
            }
        }

        /**
        * @brief Operador basico que retorna true en caso que el elemento enviado como parametro este en el modelo.
        * @param A PreImg.
        * @return True si A PreImg esta en el modelo, false de lo contrario
        */
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

        /**
        * @brief Operador basico que retorna true en caso que el elemento enviado como parametro este en el modelo.
        * @param B Img.
        * @return True si B Img esta en el modelo, false de lo contrario
        */
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

         /**
        * @brief Operador basico que devuelve la cantidad de relaciones presentes en el modelo.
        * @param No recibe parametros.
        * @return Retorna la cantidad entera de relaciones presentes.
        */
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

        /**
        * @brief Operador basico que devuelve el primer nodo o primera relacion del modelo.
        * @param No recibe parametros.
        * @return Retorna el primer nodo en caso de que exista, de lo contrario retorna vertice nulo.
        */
        NodoL<A, B>* Primero(){
            return PrimerElem;
        }

        /**
        * @brief Operador basico que devuelve la posicion del nodo cuyo elemento del dominio es igual al que fue enviado como parametro, en caso contrario retorna un apuntador nulo.
        * @param A elemento.
        * @return Retorna un apuntador al nodo si el elemento se encuentra en el modelo, de lo contrario retorna nulo.
        */
        NodoL<A, B>* Encuentre(A elemento){
            NodoL<A, B>* it = PrimerElem;
            while(it != nullptr){
                if(it->elem.first == elemento){
                    return it;
                }
                it = it->ptrSig;
            }
            return nullptr;
        }

        void operator =(Relacion_LSE<A, B> R2){
            NodoL<A, B>* iter = this->Primero();
            while(iter != nullptr){
                R2.AgregarRelacion(iter->elem.first, iter->elem.second);
                iter = iter->ptrSig;
            }
        }


    protected:

    private:
};

#endif // RELACION_LSE_H
