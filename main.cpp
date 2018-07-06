#include <iostream>
#include "GrafoDir_MA.h"
#include "Relacion_LSE.h"
#include <map>
#include "Diccionario.h"

typedef int Vertice;
typedef int Peso;

using namespace std;

GrafoDir_MA<int> G;
Diccionario<int> D;
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
    Vertice pivote;
    Vertice AdyacentePivote;
    int menor;
    int n = G.NumVert();
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
    while (n != VerticesRevisados.NumElem())
    {
        menor = -1;
        for (it = Distancia.begin(); it != Distancia.end(); ++it) //Busca el menor camino que no esté listo.
        {
            if ((it ->second < menor && it ->second >= 0) || menor < 0)
            {
                if (!VerticesRevisados.Pertenece(G.Vert(it->first)))
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
    G.AgregArist(0, 6, 4);
    G.AgregArist(6, 5,1);
    G.AgregArist(0, 5, 8);
    G.AgregArist(1, 0, 3);
    G.AgregArist(1, 3, 13);
    G.AgregArist(2, 1, 2);
    G.AgregArist(3, 2, 3);
    G.AgregArist(2, 4, 15);
    G.AgregArist(3, 4, 1);
    G.AgregArist(5, 4, 4);
    G.AgregArist(5, 3, 2);
    G.MuestreDatos();
    Algoritmo_Dijkstra(2); //REVISAR
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
