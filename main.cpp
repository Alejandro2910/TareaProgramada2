/** Tarea programada 2.
*   En esta tarea se trabajaron los modelos matematicos: Grafo Dirigido, Grafo No Dirigido, Diccionario y Relaciones 1:1
*   junto con sus respectivos algoritmos y operadores basicos.
*   @author Alejandro Benavides B61015, Andres Mesen B64390
*   @version V5
**/

#include <iostream>
#include "GrafoDir_MA.h"
#include "GrafoDir_LA.h"
#include "Relacion_LSE.h"
#include "GrafoNoDir_MA.h"
#include <map>
#include "Diccionario.h"

typedef int Vertice;
typedef int Peso;

using namespace std;
NodoL<int, string>* iterSol;
Relacion_LSE <string, int> Dist;
Relacion_LSE <string, string> Cam;
Relacion_LSE <int, string> SolAct;
Relacion_LSE <int, string>SolFact;
Relacion_LSE <int, int> Aristas;
Diccionario <Vertice> VerticesVisitados;
NodoL<string, string>* iterCam;
NodoL<string, int>* iter;
GrafoDir_MA<int> G;
GrafoDir_MA<int> G2;
GrafoNoDir_MA<int> GN;
Vertice actual;
Vertice pivote = 0;
Vertice AdyacentePivote = 0;
int menor;
int ContSol;
int CostoAct;
int MejorCosto;

/** @brief Este algoritmo de el grado dirigido calcula el camino mas corto desde el vertice v, a todos los demas.
*   @param Vertice v.
**/
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
    VerticesVisitados.Agregar(v);
    while (G.NumVert() != VerticesVisitados.NumElem())
    {
        menor = -1;
        iter = Dist.Primero();
        while(iter != nullptr)
        {
            if (!VerticesVisitados.Pertenece(G.Vert(iter->elem.first)))
            {
                if (((iter->elem.second < menor && iter->elem.second >= 0) || menor < 0) && G.Vert(iter->elem.first) != v )
                {
                    menor = iter->elem.second;
                    pivote = G.Vert(iter->elem.first);
                }
            }
            iter = iter ->ptrSig;
        }
        VerticesVisitados.Agregar(pivote);
        AdyacentePivote = G.PrimerVertAdy(pivote);
        while (AdyacentePivote != VerticeNulo)
        {
            iter = Dist.Encuentre(G.Etiqueta(AdyacentePivote));
            if (!VerticesVisitados.Pertenece(AdyacentePivote) && (iter->elem.second > (Dist.Encuentre(G.Etiqueta(pivote))->elem.second) + G.Peso(pivote, AdyacentePivote) || iter->elem.second < 0))
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

/** @brief Este algoritmo de el grado dirigido calcula el camino mas corto entre cada par de vertices del grafo.
*   @param No recibe parametros.
**/
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

/** @brief Este algoritmo lista los vertices del grafo por medio del recorrido de profundidad primero, siendo llamado por el sig algoritmo.
*   @param Vertice v.
**/
void Prof_Primero_R(Vertice v){
    cout<<G.Etiqueta(v)<<" ";
    VerticesVisitados.Agregar(v);
    Vertice va = G.PrimerVertAdy(v);
    while(va != VerticeNulo){
        if(!VerticesVisitados.Pertenece(va)){
            Prof_Primero_R(va);
        }
        va = G.SteVertAdy(v, va);
    }
}

/** @brief Este algoritmo llama al algoritmo que lista los vertices por medio de profundidad primero cuando esta seguro que el grafo no esta vacio.
*   @param No recibe parametros.
**/
void Prof_Primero(){
    cout<<"Listado de elementos por profundidad primero: ";
    if(!G.vacio()){
        VerticesVisitados.Vaciar();
        Vertice v = G.PrimerVert();
        while(v != VerticeNulo){
            if(!VerticesVisitados.Pertenece(v)){
                Prof_Primero_R(v);
            }
            v = G.SteVert(v);
        }
    }
}

/** @brief Este algoritmo permite eliminar un vertice el cual no se encuentre aislado, siempre y cuando este no se encuentre vacio.
*   @param Vertice elim
**/
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
        G.ElimVert(elim);
    }

}

/** @brief Este algoritmo copia crea una copia de g1 en g2.
*   @param GrafoDir_MA<int> G1, GrafoDir_MA<int> G2.
**/
void Copie_Grafo(GrafoDir_MA<int> G1, GrafoDir_MA<int> &G2){
    if(G1.vacio()){
        G2.vaciar();
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
}

/**
* @brief Este algoritmo realiza el metodo de usqueda exhaustiva pura para buscar la solucion optima.
* @param No recibe parámetros.
*/
void Problema_del_vendedor_R(Vertice i){//Para que funcione con GrafoDir cambiar el tipo vertice a NodoV* y los -1 en este algoritmo por GN.Anterior();
    Vertice va = GN.PrimerVertAdy(GN.Vert(SolAct.Imagen(i - 1)));
    while(va != VerticeNulo){
        if(!VerticesVisitados.Pertenece(va)){
            VerticesVisitados.Agregar(va);
            SolAct.AgregarRelacion(i, GN.Etiqueta(va));
            CostoAct += GN.Peso(GN.Vert(SolAct.Imagen(i - 1)), va);
            if(i == GN.NumVert()){
                if(GN.ExisteArista(GN.Vert(SolAct.Imagen(i - 1)), GN.Vert(SolAct.Imagen(1)))){
                        CostoAct += GN.Peso(GN.Vert(SolAct.Imagen(i - 1)), GN.Vert(SolAct.Imagen(1)));
                        ++ContSol;
                        if(CostoAct<MejorCosto || MejorCosto == -1){
                            MejorCosto = CostoAct;
                            iterSol = SolAct.Primero();
                            while(iterSol != nullptr){
                                SolFact.AgregarRelacion(iterSol->elem.first, iterSol->elem.second);
                                iterSol = iterSol->ptrSig;
                            }
                        }
                        CostoAct -= GN.Peso(GN.Vert(SolAct.Imagen(i - 1)), GN.Vert(SolAct.Imagen(1)));
                }
            }else{
                Problema_del_vendedor_R(i + 1);
            }
            CostoAct -= GN.Peso(GN.Vert(SolAct.Imagen(i - 1)), va);
            SolAct.EliminarRelacion(i, GN.Etiqueta(va));
            VerticesVisitados.Eliminar(va);
        }
        va = GN.SteVertAdy(i - 1, va);
    }
}

/**
* @brief Este algoritmo verifica que el grafo no este vacio para llamar a su metodo recursivo.
* @param No recibe parámetros.
* @return void.
*/
void Problema_del_vendedor(){
    if(!GN.vacio()){
        VerticesVisitados.Vaciar();
        SolAct.Vaciar();
        SolFact.Vaciar();
        ContSol = 0;
        CostoAct = 0;
        MejorCosto = -1;

        SolAct.AgregarRelacion(1, GN.Etiqueta(GN.PrimerVert()));
        VerticesVisitados.Agregar(GN.PrimerVert());
        Problema_del_vendedor_R(2);

        cout << "Se obtuvieron " << ContSol << " soluciones factibles.\nLa solucion de menor costo obtenida fue: ";
        for (int i = 1; i <= GN.NumVert(); ++i)
        {
            cout << SolFact.Imagen(i) << ", ";
        }
        cout << "con un costo de: " << MejorCosto << "." << endl;
    }

}

int main()
{
    Dist.Crear();
    Cam.Crear();
    VerticesVisitados.Crear();
    Aristas.Crear();
    G.Iniciar();
    G2.Iniciar();
    GN.Iniciar();
    int resp = 0;
    string etiq="";
    string nuevEtiq="";
    string v1="";
    string v2="";
    int PoA=0;

    GN.AgregVert("A");
    GN.AgregVert("B");
    GN.AgregVert("C");
    GN.AgregVert("D");
    GN.AgregVert("E");
    GN.AgregArist(GN.Vert("A"), GN.Vert("B"), 3);
    GN.AgregArist(GN.Vert("A"), GN.Vert("C"), 4);
    GN.AgregArist(GN.Vert("A"), GN.Vert("D"), 2);
    GN.AgregArist(GN.Vert("A"), GN.Vert("E"), 7);
    GN.AgregArist(GN.Vert("B"), GN.Vert("C"), 4);
    GN.AgregArist(GN.Vert("B"), GN.Vert("D"), 6);
    GN.AgregArist(GN.Vert("B"), GN.Vert("E"), 3);
    GN.AgregArist(GN.Vert("C"), GN.Vert("D"), 5);
    GN.AgregArist(GN.Vert("C"), GN.Vert("E"), 8);
    GN.AgregArist(GN.Vert("D"), GN.Vert("E"), 6);

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

    cout<<"Bienvenido a la tarea programada, los grafos dirigido y no dirigido se crearon automaticamente. Para conocer sus\nelementos consulte el manual de usuario."<<endl;
    while(resp != -1){
        cout<<"\nQue modelo desea utilizar:\n1. Grafo Dirigido.\n2. Grafo No Dirigido.\n3. Salir"<<endl;
        cin>>resp;
        if(resp == 1){
            cout<<"\nQue desea hacer:\n1. Usar operadores basicos.\n2. Usar los algoritmos.\n3. Salir"<<endl;
            cin>>resp;
            switch(resp){
            case 1:
                cout<<"\nQue operador basico desea usar:\n1. Destruir.\n2. Vaciar.\n3. Agregar Vertice.\n4. Eliminar Vertice.\n5. Agregar Arista.\n6. Eliminar Arista.\n7. Modificar Etiqueta.\n8. Modificar Peso"<<endl;
                cin>>resp;
                etiq = "";
                v1 = "";
                v2 = "";
                PoA = 0;
                nuevEtiq = "";
                switch(resp){
                case 1:
                    G.Destruir();
                    break;
                case 2:
                    G.vaciar();
                    G.MuestreDatos();
                    break;
                case 3:
                    cout<<"Digite la etiqueta que llevara el vertice: ";
                    cin>>etiq;
                    G.AgregVert(etiq);
                    G.MuestreDatos();
                    break;
                case 4:
                    cout<<"Digite la etiqueta del vertice que desea eliminar(recuerde que obligatoriamente debe pertenecer al grafo): ";
                    cin>>etiq;
                    G.ElimVert(G.Vert(etiq));
                    G.MuestreDatos();
                    break;
                case 5:
                    cout<<"Digite la etiqueta del vertice de salida: ";
                    cin>>v1;
                    cout<<"\nDigite la etiqueta del vertice de llegada: ";
                    cin>>v2;
                    cout<<"\nDigite valor del peso de la arista: ";
                    cin>>PoA;
                    G.AgregArist(G.Vert(v1), G.Vert(v2), PoA);
                    G.MuestreDatos();
                    break;
                case 6:
                    cout<<"Digite la etiqueta del vertice de salida: ";
                    cin>>v1;
                    cout<<"\nDigite la etiqueta del vertice de llegada: ";
                    cin>>v2;
                    G.ElimArist(G.Vert(v1), G.Vert(v2));
                    G.MuestreDatos();
                    break;
                case 7:
                    cout<<"Digite la etiqueta del vertice a modificar: ";
                    cin>>etiq;
                    cout<<"\nDigite la nueva etiqueta: ";
                    cin>>nuevEtiq;
                    G.ModifEtiq(G.Vert(etiq), nuevEtiq);
                    G.MuestreDatos();
                    break;
                case 8:
                    cout<<"Digite la etiqueta del vertice de salida: ";
                    cin>>v1;
                    cout<<"\nDigite la etiqueta del vertice de llegada: ";
                    cin>>v2;
                    cout<<"\nDigite el nuevo peso: ";
                    cin>>PoA;
                    G.ModifPeso(G.Vert(v1), G.Vert(v2), PoA);
                    G.MuestreDatos();
                    break;
                default:
                    cout<<"OPCION INVALIDA"<<endl;
                    break;
                }
                resp = 0;
                break;
            case 2:
                cout<<"\nQue algoritmo desea ejecutar:\n1. Dijkstra.\n2. Floyd.\n3. Listado por Profundidad Primero.\n4. Eliminar vertice no aisaldo.\n5. Copiar grafo."<<endl;
                cin>>resp;
                v1 = "";
                switch(resp){
                case 1:
                    cout<<"Digite la etiqueta del vertice que desea saber el menor camino: ";
                    cin>>v1;
                    Algoritmo_Dijkstra(G.Vert(v1));
                    break;
                case 2:
                    Algoritmo_Floyd();
                    break;
                case 3:
                    Prof_Primero();
                    break;
                case 4:
                    cout<<"Digite la etiqueta del vertice que desea eliminar: ";
                    cin>>v1;
                    Elimine_Vertice_NoAis(G.Vert(v1));
                    G.MuestreDatos();
                    break;
                case 5:
                    Copie_Grafo(G, G2);
                    cout<<"Grafo 1: "<<endl;
                    G.MuestreDatos();
                    cout<<"Grafo 2: "<<endl;
                    G2.MuestreDatos();
                    break;
                default:
                    cout<<"OPCION INVALIDA"<<endl;
                    break;
                }
                resp = 0;
                break;
            case 3:
                resp = -1;
                break;
            default:
                cout<<"OPCION INVALIDA"<<endl;
                break;
            }
        }else if(resp == 2){
            cout<<"Que desea hacer:\n1. Usar operadores basicos.\n2. Usar los algoritmos.\n3. Salir"<<endl;
            cin>>resp;
            switch(resp){
            case 1:
                cout<<"\nQue operador basico desea usar:\n1. Destruir.\n2. Vaciar.\n3. Agregar Vertice.\n4. Eliminar Vertice.\n5. Agregar Arista.\n6. Eliminar Arista.\n7. Modificar Etiqueta.\n8. Modificar Peso"<<endl;
                cin>>resp;
                etiq = "";
                v1 = "";
                v2 = "";
                PoA = 0;
                nuevEtiq = "";
                switch(resp){
                case 1:
                    GN.Destruir();
                    break;
                case 2:
                    GN.vaciar();
                    GN.MuestreDatos();
                    break;
                case 3:
                    cout<<"Digite la etiqueta que llevara el vertice: ";
                    cin>>etiq;
                    GN.AgregVert(etiq);
                    GN.MuestreDatos();
                    break;
                case 4:
                    cout<<"Digite la etiqueta del vertice que desea eliminar(recuerde que obligatoriamente debe pertenecer al grafo): ";
                    cin>>etiq;
                    GN.ElimVert(G.Vert(etiq));
                    GN.MuestreDatos();
                    break;
                case 5:
                    cout<<"Digite la etiqueta del vertice de salida: ";
                    cin>>v1;
                    cout<<"\nDigite la etiqueta del vertice de llegada: ";
                    cin>>v2;
                    cout<<"\nDigite valor del peso de la arista: ";
                    cin>>PoA;
                    GN.AgregArist(G.Vert(v1), G.Vert(v2), PoA);
                    GN.MuestreDatos();
                    break;
                case 6:
                    cout<<"Digite la etiqueta del vertice de salida: ";
                    cin>>v1;
                    cout<<"\nDigite la etiqueta del vertice de llegada: ";
                    cin>>v2;
                    GN.ElimArist(G.Vert(v1), G.Vert(v2));
                    GN.MuestreDatos();
                    break;
                case 7:
                    cout<<"Digite la etiqueta del vertice a modificar: ";
                    cin>>etiq;
                    cout<<"\nDigite la nueva etiqueta: ";
                    cin>>nuevEtiq;
                    GN.ModifEtiq(G.Vert(etiq), nuevEtiq);
                    GN.MuestreDatos();
                    break;
                case 8:
                    cout<<"Digite la etiqueta del vertice de salida: ";
                    cin>>v1;
                    cout<<"\nDigite la etiqueta del vertice de llegada: ";
                    cin>>v2;
                    cout<<"\nDigite el nuevo peso: ";
                    cin>>PoA;
                    GN.ModifPeso(G.Vert(v1), G.Vert(v2), PoA);
                    GN.MuestreDatos();
                    break;
                default:
                    cout<<"OPCION INVALIDA"<<endl;
                    break;
                }
                resp = 0;
                break;
            case 2:
                cout<<"\nQue algoritmo desea ejecutar:\n1. Problema Vendedor"<<endl;
                cin>>resp;
                if(resp == 1){
                    Problema_del_vendedor();
                }else{
                    cout<<"OPCION INVALIDA"<<endl;
                }
                resp = 0;
                break;
            case 3:
                resp = -1;
                break;
            default:
                cout<<"OPCION INVALIDA"<<endl;
                break;
            }
        }else if(resp == 3){
            resp = -1;
        }else{
            cout<<"OPCION INVALIDA"<<endl;
        }
    }
    return 0;
}
