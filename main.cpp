#include <iostream>
#include "GrafoDir_MA.h"
#include "Relacion_LSE.h"
#include <map>
#include "Diccionario.h"

typedef int Vertice;
typedef int Peso;

using namespace std;

Diccionario<int> D;
Relacion_LSE <int, int> R;
GrafoDir_MA<int> G;
map<string, Peso> Distancia;
map<string, string> Caminos;
map<string, Peso>::iterator it;
map<string, string>::iterator itCaminos;

void Algoritmo_Dijkstra(Vertice v){
    Distancia.clear();
    Caminos.clear();
    Diccionario <Vertice> VerticesRevisados;
    VerticesRevisados.Crear();
    Vertice actual = G.PrimerVert();
    Vertice pivote = 0;
    Vertice AdyacentePivote = 0;
    int menor = 0;
    while (actual != VerticeNulo)
    {
        if (G.ExisteArista(v, actual))
        {
            Distancia.insert(make_pair(G.Etiqueta(actual),G.Peso(v, actual)));
            Caminos.insert(make_pair(G.Etiqueta(actual),G.Etiqueta(v)+"-> "+G.Etiqueta(actual)));
        }
        else if (v == actual)
        {
            Distancia.insert(make_pair(G.Etiqueta(actual),0));
            Caminos.insert(make_pair(G.Etiqueta(actual),""));
        }
        else
        {
            Distancia.insert(make_pair(G.Etiqueta(actual),-1));
            Caminos.insert(make_pair(G.Etiqueta(actual),""));
        }
        actual = G.SteVert(actual);
    }
    VerticesRevisados.Agregar(v);
    while (G.NumVert() != VerticesRevisados.NumElem())
    {
        menor = -1;
        for (it = Distancia.begin(); it != Distancia.end(); ++it) //Busca el menor camino que no esté listo.
        {
            if (!VerticesRevisados.Pertenece(G.Vert(it->first)))
            {
                if (((it ->second < menor && it ->second >= 0) || menor < 0) && G.Vert(it ->first) != v )
                {
                    menor = it ->second;
                    pivote = G.Vert(it ->first);
                }
            }
        }
        VerticesRevisados.Agregar(pivote);
        AdyacentePivote = G.PrimerVertAdy(pivote);
        while (AdyacentePivote != VerticeNulo)
        {
            it = Distancia.find(G.Etiqueta(AdyacentePivote));
            if (!VerticesRevisados.Pertenece(AdyacentePivote) && (it ->second > (Distancia.find(G.Etiqueta(pivote))-> second) + G.Peso(pivote, AdyacentePivote) || it ->second < 0))
            {
                it ->second = Distancia.find(G.Etiqueta(pivote))-> second + G.Peso(pivote, AdyacentePivote);
                itCaminos = Caminos.find(G.Etiqueta(AdyacentePivote));
                itCaminos ->second = Caminos.find(G.Etiqueta(pivote))-> second + "-> " + G.Etiqueta(AdyacentePivote);
            }
            AdyacentePivote = G.SteVertAdy(pivote, AdyacentePivote);
        }
    }
    for (itCaminos = Caminos.begin(); itCaminos != Caminos.end(); ++itCaminos)
    {
        cout << "El camino mas corto de " << G.Etiqueta(v) << " a " << itCaminos ->first << ": " << itCaminos ->second;
        cout << ". Su costo es de: " << Distancia.find(itCaminos->first)->second << endl;
    }
}

void Algoritmo_Floyd(){

}

int main()
{
    G.Iniciar();
    G.AgregVert("A");
    G.AgregVert("B");
    G.AgregVert("C");
    G.AgregVert("D");
    G.AgregVert("E");
    G.AgregVert("F");
    G.AgregVert("G");
    G.AgregArist(G.Vert("A"), G.Vert("G"), 4);
    G.AgregArist(G.Vert("G"), G.Vert("F"), 1);
    G.AgregArist(G.Vert("A"), G.Vert("F"), 8);
    G.AgregArist(G.Vert("B"), G.Vert("A"), 3);
    G.AgregArist(G.Vert("B"), G.Vert("D"), 13);
    G.AgregArist(G.Vert("C"), G.Vert("B"), 2);
    G.AgregArist(G.Vert("D"), G.Vert("C"), 3);
    G.AgregArist(G.Vert("C"), G.Vert("E"), 15);
    G.AgregArist(G.Vert("D"), G.Vert("E"), 1);
    G.AgregArist(G.Vert("F"), G.Vert("E"), 4);
    G.AgregArist(G.Vert("F"), G.Vert("D"), 2);

    R.Crear();
    R.AgregarRelacion(G.Vert("A"), G.Vert("G"));
    R.AgregarRelacion(G.Vert("G"), G.Vert("F"));
    R.AgregarRelacion(G.Vert("A"), G.Vert("F"));
    R.AgregarRelacion(G.Vert("B"), G.Vert("A"));
    R.AgregarRelacion(G.Vert("B"), G.Vert("D"));
    R.AgregarRelacion(G.Vert("C"), G.Vert("B"));
    R.AgregarRelacion(G.Vert("D"), G.Vert("C"));
    R.AgregarRelacion(G.Vert("C"), G.Vert("E"));
    R.AgregarRelacion(G.Vert("D"), G.Vert("E"));
    R.AgregarRelacion(G.Vert("F"), G.Vert("E"));
    R.AgregarRelacion(G.Vert("F"), G.Vert("D"));
    R.MuestreDatos();

    Algoritmo_Dijkstra(2); //REVISAR
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
