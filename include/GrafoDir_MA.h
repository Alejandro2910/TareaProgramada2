#ifndef GRAFODIR_MA_H
#define GRAFODIR_MA_H
#include <string>
#include <iostream>

using namespace std;
static int VerticeNulo = -1;
static int AristaNula = -1;

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
            UltimoLleno=VerticeNulo;
        }

        void Destruir(){
            UltimoLleno=VerticeNulo;
        }

        void vaciar(){
            UltimoLleno=VerticeNulo;
        }

        bool vacio(){
            if(UltimoLleno == VerticeNulo){
                return true;
            }else{
                return false;
            }
        }

        void AgregVert(string etiq){
            UltimoLleno++;
            ListaEtiquetas[UltimoLleno] = etiq;
            for(int x=0;x<maximo;x++){
                MatAris[x][UltimoLleno]=AristaNula;
                MatAris[UltimoLleno][x]=AristaNula;
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

        void AgregArist(int v1, int v2, A peso){
            MatAris[v1][v2]=peso;
        }

        void ElimArist(int v1, int v2){
            MatAris[v1][v2]=AristaNula;
        }

        string Etiqueta(int vert){
            return ListaEtiquetas[vert];
        }

        int Vert(string etiq){
            for(int x = 0;x <= UltimoLleno;++x){
                if(ListaEtiquetas[x] == etiq){
                    return x;
                }
            }
            return VerticeNulo;
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
            if (UltimoLleno != VerticeNulo)
            {
                return 0;
            }
            return VerticeNulo;
        }

        int SteVert(int vert){
            if ((UltimoLleno + 1) != (vert + 1))
            {
                return (vert + 1);
            }
            return VerticeNulo;
        }

        int PrimerVertAdy(int vert){
            for(int x=0;x<=UltimoLleno;x++){
                if(MatAris[vert][x] != AristaNula){
                    return x;
                }
            }
            return VerticeNulo;
        }

        int SteVertAdy(int v1, int v2){
            for(int x=v2 + 1;x<=UltimoLleno;x++){
                if(MatAris[v1][x] != AristaNula){
                    return x;
                }
            }
            return VerticeNulo;
        }

        int NumVert(){
            return UltimoLleno + 1 ;
        }

        bool ExisteArista(int v1, int v2){
            if(MatAris[v1][v2] != AristaNula){
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
