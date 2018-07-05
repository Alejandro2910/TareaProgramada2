#include <iostream>
#include "GrafoDir_MA.h"
#include "Relacion_LSE.h"
#include <map>
#include "Diccionario.h"

typedef int VerticeDest;
typedef int VerticeFuen;
typedef int Vertice;
static int VerticeNulo = -1;
typedef int Peso;

using namespace std;

    GrafoDir_MA<int> G;
    Diccionario<int> D;
    map<Vertice, Peso> Distancias;
    map<Vertice, Vertice> Caminos;
    map<VerticeFuen, Peso>::iterator iter;
    map<VerticeFuen, VerticeDest>::iterator iterC;
    int Menor;
    int ContVert = 1;

void Dijkstra(Vertice V){
    Distancias.clear();
    Caminos.clear();
    Vertice Actual = G.PrimerVert();
    Vertice Pivote;
    Vertice AdyPivot;

    while(Actual != VerticeNulo){
        if(G.ExisteArista(V, Actual)){
            Distancias.emplace(Actual, G.Peso(V, Actual));
            Caminos.emplace(V, Actual);
        }else if(Actual == V){
            Distancias.emplace(Actual, 0);
            Caminos.emplace(V, VerticeNulo);
        }else{
            Distancias.emplace(Actual, VerticeNulo);
            Distancias.emplace(V, -1);
        }
        Actual = G.SteVert(Actual);
    }
    D.Agregar(V);
    Menor = VerticeNulo;
    while(ContVert <= G.NumVert()){
        for(iter = Distancias.begin();iter!=Distancias.end();iter++){
            if((iter->second < Menor && iter->second >= 0) || Menor < 0){
                if(!D.Pertenece(iter->first)){
                    Menor = iter->second;
                    Pivote =  iter->first;
                }
            }
        }
        D.Agregar(Pivote);
        AdyPivot = G.PrimerVertAdy(Pivote);
        while(AdyPivot != VerticeNulo){
            iter = Distancias.find(AdyPivot);
            if(!D.Pertenece(AdyPivot) && (iter->second > (Distancias.find(Pivote)->second + G.Peso(Pivote, AdyPivot))|| iter->second < 0)){
                iter->second = Distancias.find(Pivote)->second + G.Peso(Pivote, AdyPivot);
                iterC = Caminos.find(AdyPivot);
                iterC->second = AdyPivot;
            }
            AdyPivot = G.SteVertAdy(Pivote, AdyPivot);
        }
        cout<<"Resultados Dijkstra:\n"<<endl;
        for (iterC = Caminos.begin(); iterC != Caminos.end(); ++iterC)
        {
            cout << "El camino mas corto de " << G.Etiqueta(V) << " a " << iterC ->first << "tiene un costo de: "<< Distancias.find(iterC->first)->second << endl;
        }
        cout<<endl;
        for (iterC = Caminos.begin(); iterC != Caminos.end(); ++iterC)
        {
           cout<<iterC->first<< " ";
        }
        cout<<endl;
        for (iterC = Caminos.begin(); iterC != Caminos.end(); ++iterC)
        {
           cout<<iterC->second<< " ";
        }
    }
}

int main()
{
    GrafoDir_MA<int> G;
    G.Iniciar();
    G.AgregVert("A");
    G.AgregVert("B");
    G.AgregVert("C");
    G.AgregVert("D");
    G.AgregVert("E");
    G.AgregVert("F");
    G.AgregVert("G");
    G.AgregArist(4, 0, 6);
    G.AgregArist(1, 6, 5);
    G.AgregArist(8, 0, 5);
    G.AgregArist(3, 1, 0);
    G.AgregArist(13, 1, 3);
    G.AgregArist(2, 2, 1);
    G.AgregArist(3, 3, 2);
    G.AgregArist(15, 2, 4);
    G.AgregArist(1, 3, 4);
    G.AgregArist(4, 5, 4);
    G.AgregArist(2, 5, 3);
    G.MuestreDatos();
    Dijkstra(2); //REVISAR
//    Relacion_LSE <int, string> R;
//    R.Crear();
//    R.AgregarRelacion(1, "A");
//    R.AgregarRelacion(2, "B");
//    R.AgregarRelacion(3, "C");
//    R.AgregarRelacion(4, "D");
//    R.AgregarRelacion(5, "E");
//    R.MuestreDatos();
//    R.EliminarRelacion(5, "E");
//    R.MuestreDatos();
//
//    Diccionario<int> D;
//    D.Crear();
//    D.Agregar(1);
//    D.Agregar(0);
//    D.Agregar(3);
//    D.Agregar(156);
//    if(D.Pertenece(1)){
//        cout<<"Si"<<endl;
//    }
//    D.Eliminar(1);

    return 0;
}
