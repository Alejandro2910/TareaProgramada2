#include <iostream>
#include "GrafoDir_MA.h"
#include "GrafoDir_LA.h"
#include "Relacion_LSE.h"
#include <map>
#include "Diccionario.h"

typedef int Vertice;
typedef int Peso;

using namespace std;

Relacion_LSE <string, int> Dist;
Relacion_LSE <string, string> Cam;
Relacion_LSE <int, int> Aristas;
Diccionario <Vertice> VerticesRevisados;
NodoL<string, string>* iterCam;
NodoL<string, int>* iter;
GrafoDir_MA<int> G;
GrafoDir_MA<int> G2;
Vertice actual;
Vertice pivote = 0;
Vertice AdyacentePivote = 0;
int menor = 0;

void Algoritmo_Dijkstra(Vertice v){
    actual = G.PrimerVert();
    while (actual != VerticeNulo)
    {
        if (G.ExisteArista(v, actual))
        {
            Dist.AgregarRelacion(G.Etiqueta(actual),G.Peso(v, actual));
            Cam.AgregarRelacion(G.Etiqueta(actual),G.Etiqueta(v)+"-> "+G.Etiqueta(actual));
        }
        else if (v == actual)
        {
            Dist.AgregarRelacion(G.Etiqueta(actual),0);
            Cam.AgregarRelacion(G.Etiqueta(actual),"");
        }
        else
        {
            Dist.AgregarRelacion(G.Etiqueta(actual),-1);
            Cam.AgregarRelacion(G.Etiqueta(actual),"");
        }
        actual = G.SteVert(actual);
    }
    VerticesRevisados.Agregar(v);
    while (G.NumVert() != VerticesRevisados.NumElem())
    {
        menor = -1;
        iter = Dist.Primero();
        while(iter != nullptr)
        {
            if (!VerticesRevisados.Pertenece(G.Vert(iter->elem.first)))
            {
                if (((iter->elem.second < menor && iter->elem.second >= 0) || menor < 0) && G.Vert(iter->elem.first) != v )
                {
                    menor = iter->elem.second;
                    pivote = G.Vert(iter->elem.first);
                }
            }
            iter = iter ->ptrSig;
        }
        VerticesRevisados.Agregar(pivote);
        AdyacentePivote = G.PrimerVertAdy(pivote);
        while (AdyacentePivote != VerticeNulo)
        {
            iter = Dist.Encuentre(G.Etiqueta(AdyacentePivote));
            if (!VerticesRevisados.Pertenece(AdyacentePivote) && (iter->elem.second > (Dist.Encuentre(G.Etiqueta(pivote))->elem.second) + G.Peso(pivote, AdyacentePivote) || iter->elem.second < 0))
            {
                iter->elem.second = Dist.Encuentre(G.Etiqueta(pivote))->elem.second + G.Peso(pivote, AdyacentePivote);
                iterCam = Cam.Encuentre(G.Etiqueta(AdyacentePivote));
                iterCam->elem.second = Cam.Encuentre(G.Etiqueta(pivote))->elem.second + "-> " + G.Etiqueta(AdyacentePivote);
            }
            AdyacentePivote = G.SteVertAdy(pivote, AdyacentePivote);
        }
    }
    iterCam = Cam.Primero();
    while(iterCam != nullptr)
    {
        cout << "El camino mas corto de " << G.Etiqueta(v) << " a " << iterCam->elem.first << ": " << iterCam->elem.second;
        cout << ". Su costo es de: " << Dist.Encuentre(iterCam->elem.first)->elem.second << endl;
        iterCam = iterCam->ptrSig;
    }
}

void Algoritmo_Floyd(){
    int A[G.NumVert()][G.NumVert()];
    string P[G.NumVert()][G.NumVert()];
    int i, j, k;

    for(i = 0; i < G.NumVert(); ++i){
        for(j = 0; j < G.NumVert(); j++){
            if(i == j){
                A[i][j] = 0;
                P[i][j] = '-';
            }else{
                A[i][j] = G.Peso(i, j);
                P[i][j] = "";
            }

        }
    }

    for(k = 0; k < G.NumVert(); ++k)
    {
        for(i = 0; i < G.NumVert(); ++i)
        {
            for(j = 0; j < G.NumVert(); ++j)
            {
                if (A[i][k] != -1 && A[k][j] != -1)
                {
                    if((A[i][k]+A[k][j]) < A[i][j] || A[i][j] == -1)
                    {
                        A[i][j] = A[i][k]+A[k][j];
                        P[i][j] = G.Etiqueta(k);
                    }
                }
            }
        }
    }
    cout<<"Matriz de Pesos: "<<endl;
    for(i = 0;i < G.NumVert();i++){
        for(j = 0;j < G.NumVert();j++){
            cout<<A[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"\nMatriz de caminos: "<<endl;
    for(i = 0;i < G.NumVert();i++){
        for(j = 0;j < G.NumVert();j++){
            cout<<P[i][j]<<"\t";
        }
        cout<<endl;
    }

}


void Prof_Primero_R(Vertice v){
    cout<<G.Etiqueta(v)<<" ";
    VerticesRevisados.Agregar(v);
    Vertice va = G.PrimerVertAdy(v);
    while(va != VerticeNulo){
        if(!VerticesRevisados.Pertenece(va)){
            Prof_Primero_R(va);
        }
        va = G.SteVertAdy(v, va);
    }
}

void Prof_Primero(){
    cout<<"Listado de elementos por profundidad primero: ";
    if(!G.vacio()){
        VerticesRevisados.Vaciar();
        Vertice v = G.PrimerVert();
        while(v != VerticeNulo){
            if(!VerticesRevisados.Pertenece(v)){
                Prof_Primero_R(v);
            }
            v = G.SteVert(v);
        }
        VerticesRevisados.Destruir();
    }
}

void Elimine_Vertice_NoAis(Vertice elim){
    if(G.vacio()){
        cout<<"Imposible eliminar vertice de grafo vacio"<<endl;
    }else{
        Vertice v = G.PrimerVert();
        while(v != VerticeNulo){
            if(G.ExisteArista(v, elim)){
                G.ElimArist(v, elim);
            }else if(v == elim){
                Vertice va = G.PrimerVertAdy(elim);
                Vertice vaAdel;
                while(vaAdel != VerticeNulo){
                    vaAdel = G.SteVertAdy(elim, va);
                    G.ElimArist(elim, va);
                    va = vaAdel;
                }
            }
            v = G.SteVert(v);
        }
    }
    G.ElimVert(elim);
}

GrafoDir_MA<int> Copie_Grafo(GrafoDir_MA<int> G1, GrafoDir_MA<int> G2){
    if(G1.vacio()){
        G2.vaciar();
        return G2;
    }else{
        if(!G2.vacio()){
            G2.vaciar();
        }
        Vertice v = G1.PrimerVert();
        while(v != VerticeNulo){
            G2.AgregVert(G.Etiqueta(v));
            v = G1.SteVert(v);
        }
        v = G.PrimerVert();
        while(v != VerticeNulo){
            Vertice va = G.PrimerVertAdy(v);
            while(va != VerticeNulo){
                    if(G.ExisteArista(v, va)){
                        G2.AgregArist(v, va, G.Peso(v, va));
                    }
                va = G.SteVertAdy(v, va);
            }
            v = G.SteVert(v);
        }

    }
    return G2;
}

int main()
{
    Dist.Crear();
    Cam.Crear();
    VerticesRevisados.Crear();
    Aristas.Crear();
    G.Iniciar();
    G2.Iniciar();
    G.AgregVert("A");
    G.AgregVert("B");
    G.AgregVert("C");
    G.AgregVert("D");
    G.AgregVert("E");
    G.AgregVert("F");
    G.AgregArist(G.Vert("A"), G.Vert("B"), 2);
    G.AgregArist(G.Vert("A"), G.Vert("E"), 3);
    G.AgregArist(G.Vert("A"), G.Vert("F"), 2);
    G.AgregArist(G.Vert("B"), G.Vert("A"), 3);
    G.AgregArist(G.Vert("B"), G.Vert("C"), 3);
    G.AgregArist(G.Vert("B"), G.Vert("D"), 2);
    G.AgregArist(G.Vert("B"), G.Vert("E"), 8);
    G.AgregArist(G.Vert("B"), G.Vert("F"), 8);
    G.AgregArist(G.Vert("C"), G.Vert("D"), 5);
    G.AgregArist(G.Vert("D"), G.Vert("F"), 30);
    G.AgregArist(G.Vert("E"), G.Vert("B"), 1);
    G.AgregArist(G.Vert("E"), G.Vert("C"), 10);
    G.AgregArist(G.Vert("E"), G.Vert("D"), 20);
    G.AgregArist(G.Vert("F"), G.Vert("E"), 8);

    Algoritmo_Dijkstra(2);
    cout<<endl;
    Algoritmo_Floyd();
    cout<<endl;
    Prof_Primero();
    cout<<endl;
    Elimine_Vertice_NoAis(G.Vert("A"));
    G.MuestreDatos();
    cout<<endl;
    return 0;
}
