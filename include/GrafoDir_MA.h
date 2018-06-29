#ifndef GRAFODIR_MA_H
#define GRAFODIR_MA_H
#include <string>
#include <iostream>

using namespace std;

template <class A>
class GrafoDir_MA
{
    public:
        GrafoDir_MA(){}
        virtual ~GrafoDir_MA(){}
        int maximo=100;
        int MatAris[100][100];
        string ListaEtiquetas[100];
        int UltimoLleno;

        void Iniciar(){
            UltimoLleno=-1;
        }

        void Destruir(){
            UltimoLleno=-1;
        }

        void vaciar(){
            UltimoLleno=-1;
        }

        bool vacio(){
            if(UltimoLleno==-1){
                return true;
            }else{
                return false;
            }
        }

        void AgregVert(string etiq){
            if(UltimoLleno<maximo){
                UltimoLleno++;
                ListaEtiquetas[UltimoLleno] = etiq;
                for(int x=0;x<maximo;x++){
                    MatAris[x][UltimoLleno]=-1;
                    MatAris[UltimoLleno][x]=-1;
                }
            }else{
                cout<<"No hay más campo en el Grafo para agregar Vértices"<<endl;
            }
        }

        void ElimVert(int vert){
            for(int x=vert;x<UltimoLleno;x++){ //por terminar
                ListaEtiquetas[x]=ListaEtiquetas[x+1];
            }
            for (int i = vert; i < UltimoLleno; ++i)
            {
                for (int j = 0; j < UltimoLleno; ++j)
                {
                    MatAris[i][j]=MatAris[i+1][j];
                    MatAris[j][i]=MatAris[j][i+1];
                }
            }
            UltimoLleno--;
        }

        void AgregArist(A peso, int v1, int v2){
            MatAris[v1][v2]=peso;
        }

        void ElimArist(int v1, int v2){
            MatAris[v1][v2]=-1;
        }

        string Etiqueta(int vert){
            return ListaEtiquetas[vert];
        }

        A Peso(int v1, int v2){
            return MatAris[v1][v2];
        }

        void ModifEtiq(int vert, string nuevEtiq ){
            ListaEtiquetas[vert]=nuevEtiq;
        }
        void ModifPeso(int v1, int v2, A p){
            MatAris[v1][v2]=p;
        }

        int PrimerVert(){
            return 0;
        }

        int SteVert(int vert){
            return vert + 1;
        }

        int PrimerVertAdy(int vert){
            for(int x=0;x<=UltimoLleno;x++){
                if(MatAris[vert][x] != -1){
                    return x;
                }
            }
            return -1;
        }

        int SteVertAdy(int v1, int v2){
            for(int x=v2;x<=UltimoLleno;x++){
                if(MatAris[v1][x] != -1){
                    return x;
                }
            }
            return -1;
        }

        int NumVert(){
            return UltimoLleno + 1 ;
        }

        bool ExisteArista(int v1, int v2){
            if(MatAris[v1][v2] != 0){
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
