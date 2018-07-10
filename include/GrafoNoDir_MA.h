#ifndef GRAFONODIR_MA_H
#define GRAFONODIR_MA_H
#include "GrafoDir_MA.h"
#include <string>
#include <iostream>

using namespace std;


template <class A>
class GrafoNoDir_MA
{
    public:
        GrafoNoDir_MA(){}
        virtual ~GrafoNoDir_MA(){}
        int maximo=100;
        int MatAris[100][100];
        string ListaEtiquetas[100];
        int UltimoLleno;

        /**
        * @brief Operador basico que inicializa el grafo.
        * @param No recibe parámetros.
        */
        void Iniciar(){
            UltimoLleno=VerticeNulo;
        }

        /**
        * @brief Operador basico que "destruye" el grafo.
        * @param No recibe parámetros.
        */
        void Destruir(){
            UltimoLleno=VerticeNulo;
        }

        /**
        * @brief Operador basico que "vacia" el grafo.
        * @param No recibe parámetros.
        */
        void vaciar(){
            UltimoLleno=VerticeNulo;
        }

        /**
        * @brief Operador basico que revisa si el grafo en cuestion se encuentra vacio o no.
        * @param No recibe parámetros.
        * @return true en caso de que ultimo lleno sea igual a -1, false de lo contrario
        */
        bool vacio(){
            if(UltimoLleno == VerticeNulo){
                return true;
            }else{
                return false;
            }
        }

        /**
        * @brief Operador basico que agrega vertices al grafo mientras que este tenga espacio.
        * @param String Etiq.
        */
        void AgregVert(string etiq){
            UltimoLleno++;
            ListaEtiquetas[UltimoLleno] = etiq;
            for(int x=0;x<maximo;x++){
                MatAris[x][UltimoLleno]=AristaNula;
                MatAris[UltimoLleno][x]=AristaNula;
            }
        }

        /**
        * @brief Operador basico que elimina vertices del grafo mientras hayan.
        * @param Int vert.
        */
        void ElimVert(int vert){
            for(int x=vert;x<UltimoLleno;x++){ //por terminar
                ListaEtiquetas[x]=ListaEtiquetas[x+1];
            }
            for (int i = vert; i < UltimoLleno; ++i)
            {
                for (int j = 0; j < UltimoLleno; ++j)
                {
                    if(i == j){
                        MatAris[i][j] = 0;
                    }
                    MatAris[i][j]=MatAris[i+1][j];
                    MatAris[j][i]=MatAris[j][i+1];
                }
            }
            UltimoLleno--;
        }

        /**
        * @brief Operador basico que agrega una arista conectanto el vertice v1 y al vertice v2 con el valor de su peso.
        * @param Int v1, Int v2, A Peso.
        */
        void AgregArist(int v1, int v2, A peso){
            MatAris[v1][v2]=peso;
            MatAris[v2][v1]=peso;
        }

        /**
        * @brief Operador basico que: Logicamente borra la arista que conecta ambos vertices bidireccionalmente
        * pero fisicamente elimina ambas aristas por separado.
        * @param Int v1, Int v2.
        */
        void ElimArist(int v1, int v2){
            MatAris[v1][v2]=AristaNula;
            MatAris[v2][v1]=AristaNula;
        }

        /**
        * @brief Operador basico que retorna la etiqueta del vertice solicitado.
        * @param Int vert.
        * @return String etiqueta en el elemento vert de la ListaEtiquetas.
        */
        string Etiqueta(int vert){
            return ListaEtiquetas[vert];
        }

        /**
        * @brief Operador basico que retorna el vertice al que la etiqueta etiq pertenece.
        * @param String etiq.
        * @return int x con el valor del vertice, verticenulo en caso de que no lo encuentre.
        */
        int Vert(string etiq){
            for(int x = 0;x <= UltimoLleno;++x){
                if(ListaEtiquetas[x] == etiq){
                    return x;
                }
            }
            return VerticeNulo;
        }

        /**
        * @brief Operador basico que retorna el peso de la arista que conecta a v1 con v2.
        * @param Int v1, Int v2.
        * @return A peso de la arista en la Matriz de Aristas.
        */
        A Peso(int v1, int v2){
            return MatAris[v1][v2];
        }

        /**
        * @brief Operador basico que permite modificar la etiqueta del vertice dado.
        * @param Int vert, String nuevEtiq.
        */
        void ModifEtiq(int vert, string nuevEtiq ){
            ListaEtiquetas[vert]=nuevEtiq;
        }

        /**
        * @brief Operador basico que permite modificar el peso de la arista que conecta a v1 y a v2.
        * @param Int vert, String nuevEtiq, A p.
        */
        void ModifPeso(int v1, int v2, A p){
            MatAris[v1][v2] = p;
            MatAris[v2][v1] = p;
        }

        /**
        * @brief Operador basico que devuelve el "primer vertice" del grafo.
        * @param No recibe parametros.
        * @return Retorna el primer vertice en caso de que exista, de lo contrario retorna vertice nulo.
        */
        int PrimerVert(){
            if (UltimoLleno != VerticeNulo)
            {
                return 0;
            }
            return VerticeNulo;
        }

         /**
        * @brief Operador basico que devuelve el vertice siguiente al que fue enviado como parametro..
        * @param int vert.
        * @return Retorna el siguiente vertice a vert en caso de que exista, de lo contrario retorna vertice nulo.
        */
        int SteVert(int vert){
            if ((UltimoLleno + 1) != (vert + 1))
            {
                return (vert + 1);
            }
            return VerticeNulo;
        }

        /**
        * @brief Operador basico que devuelve el primer vertice adyacente al que fue enviado como parametro..
        * @param int vert.
        * @return Retorna el primer vertice adyacente a vert en caso de que exista, de lo contrario retorna vertice nulo.
        */
        int PrimerVertAdy(int vert){
            for(int x=0;x<=UltimoLleno;x++){
                if(MatAris[vert][x] != AristaNula){
                    return x;
                }
            }
            return VerticeNulo;
        }

        /**
        * @brief Operador basico que devuelve el siguiente vertice adyacente a v1, despues de v2.
        * @param int v1, v2.
        * @return Retorna el siguiente vertice adyacente a v1 luego de v2 en caso de que exista, de lo contrario retorna vertice nulo.
        */
        int SteVertAdy(int v1, int v2){
            for(int x=v2 + 1;x<=UltimoLleno;x++){
                if(MatAris[v1][x] != AristaNula){
                    return x;
                }
            }
            return VerticeNulo;
        }

        /**
        * @brief Operador basico que devuelve la cantidad de vertices presentes en el grafo.
        * @param No recibe parametros.
        * @return Retorna la cantidad entera de vertices en el grafo.
        */
        int NumVert(){
            return UltimoLleno + 1 ;
        }

        /**
        * @brief Operador basico que verifica que exista la arista que conecta a el vertice v1 y al vertice v2.
        * @param Int v1, Int v2.
        * @return Retorna true en caso de que la arista exista, false de lo contrario.
        */
        bool ExisteArista(int v1, int v2){
            if(MatAris[v1][v2] != AristaNula && MatAris[v2][v1] != AristaNula){
                return true;
            }else{
                return false;
            }
        }

        void MuestreDatos(){
            cout<<"Lista de etiquetas: "<<endl;
            for(int x=0;x<=UltimoLleno;x++){
                cout<<ListaEtiquetas[x]<<" "<<endl;
            }
            cout<<endl;
            cout<<"Matriz de adyacencia: "<<endl;
            for(int z=0;z<=UltimoLleno;z++){
                for(int y=0;y<=UltimoLleno;y++){
                    cout<<MatAris[z][y]<<"\t";
                }
                cout<<endl;
            }
            cout<<endl;
        }

    protected:

    private:
};

#endif // GRAFODIR_MA_H
