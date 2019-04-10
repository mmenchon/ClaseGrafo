#include <iostream>
#include <list>
#include <queue>
#include "grafo.h"
#include "algoritmo.h"
#include <time.h>
using namespace std;
const string pipa = "pipa";
void implemetacion_dijkstra(Grafo<int,int> *g, int destino)
{
    /****************************** aplicar Dijsktra al grafo reverso ******************************/
    cout<<"Dijsktra al grafo reverso"<< endl;
    int distancia[g->getCantVertices()+1];
    int padre[g->getCantVertices()+1];
    int origen = destino;
    unsigned int t1_inicio = clock();
    Grafo<int,int> *reverse = new Grafo<int,int>;
    g->getReversGrafo(*reverse);
    dijktra(reverse, origen, distancia, padre);
    cout<< "padre"<<endl;
    for(int i=1; i<g->getCantVertices()+1; i++)
        cout << padre[i] << " ";
    cout<<endl;
    cout<< "Distancia"<<endl;
    for(int i=1; i<g->getCantVertices()+1; i++)
        cout << distancia[i] << " ";
    cout<<endl;
    cout<<"el camino  del vertice 2 al vertice "<<destino<<endl;
    int i=2; // vertice elejido arbitrariamente
    while (i != origen  && distancia[i]!=INT_MAX) {
        cout << i<< " ";
        i=padre[i];
    }
    cout << i<<endl;
    unsigned int t1_fin= clock();
    double time= (double(t1_fin-t1_inicio)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;
    /****************************** por cada vertice aplicar Dijsktra ******************************/
    cout<<endl;
    cout<< "algoritmo de Dijkstra por cada vertice"<<endl;
    t1_inicio = clock();
    for(origen=1;origen <=g->getCantVertices();origen++)
    {
    cout<<"origen: "<< origen << endl;
    dijktra2(g, origen, destino, distancia, padre);
    cout<<"distancia "<<distancia[destino] <<endl;
    cout<<"camino al vertice"<<endl;
    i=destino;
    while (i != origen && distancia[i] !=INT_MAX ) {
        cout << i<< " ";
        i=padre[i];
    }
    cout << i<<endl;
    }
    t1_fin= clock();
    time= (double(t1_fin-t1_inicio)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;
}

bool poda(vector<int> solucion, unsigned int indice, int valor, Grafo<int,int> *g)
{
    for(unsigned int i=0; i<indice; i++)
    {
        if(solucion[i]==valor)
            return true;
    }
    list<arista<int,int>> ady;
    g->getListArcos(indice, ady);
    typename list<arista<int,int>>::const_iterator it;
    for(it=ady.begin();it!=ady.end();it++)
    {
        if(solucion[(*it).getDestino()]==valor+1 || solucion[(*it).getDestino()]==valor-1)
            return true;
    }
    return false;
}

void imprimir(vector<int> solucion)
{
    cout<<"peron2"<<endl;
    for(unsigned int i=0;i<solucion.size(); i++)
    {
        cout<<"nodo "<<i<<" "<<solucion[i]<<endl;;
    }
    cout<<endl;
}

void back(vector<int> solucion, unsigned int indice, Grafo<int,int> *g)
{
    if (indice == solucion.size()){
        imprimir(solucion);
        cout<<"pipa1"<<endl;
    }
    else {
        //cout<<indice<<endl;
        for(int valor=0;valor<solucion.size(); valor++)
        {
            solucion[indice]=valor;
            if (!poda(solucion,indice, valor, g))
                back(solucion, indice+1, g);
        }
    }
}



int main()
{
    Grafo<int,int>* g = new Grafo<int,int>();
    Grafo<int,int>* grafo=new Grafo<int,int>();
    vector<int> solucion(8,-2);
    grafo->addVertice(2);
    grafo->addVertice(3);
    grafo->addVertice(4);
    grafo->addVertice(5);
    grafo->addVertice(6);
    grafo->addVertice(7);
    grafo->addVertice(1);
    grafo->addVertice(0);
    grafo->addArco(0,1,0);
    grafo->addArco(0,3,0);
    grafo->addArco(0,6,0);
    grafo->addArco(1,0,0);
    grafo->addArco(1,2,0);
    grafo->addArco(1,3,0);
    grafo->addArco(1,4,0);
    grafo->addArco(2,1,0);
    grafo->addArco(2,3,0);
    grafo->addArco(2,4,0);
    grafo->addArco(2,5,0);
    grafo->addArco(3,0,0);
    grafo->addArco(3,1,0);
    grafo->addArco(3,2,0);
    grafo->addArco(3,4,0);
    grafo->addArco(3,7,0);
    grafo->addArco(3,6,0);
    grafo->addArco(4,1,0);
    grafo->addArco(4,2,0);
    grafo->addArco(4,3,0);
    grafo->addArco(4,5,0);
    grafo->addArco(4,6,0);
    grafo->addArco(4,7,0);
    grafo->addArco(5,2,0);
    grafo->addArco(5,4,0);
    grafo->addArco(5,7,0);
    grafo->addArco(6,0,0);
    grafo->addArco(6,3,0);
    grafo->addArco(6,4,0);
    grafo->addArco(6,7,0);
    grafo->addArco(7,3,0);
    grafo->addArco(7,4,0);
    grafo->addArco(7,5,0);
    grafo->addArco(7,6,0);
    back(solucion,0,grafo);
    //imprimir(solucion);
    //solucion = {6,2,4,0,7,1,3,-1};
    //imprimir(solucion);
    //if (!poda(solucion,7, 5 ,grafo))
      //  cout<<"peron"<<endl;

    /**grafo conexo **/
    g->addVertice(1);
    g->addVertice(2);
    g->addVertice(3);
    g->addVertice(4);
    g->addVertice(5);
    g->addVertice(6);
    cout<<pipa<<endl;
    g->addArco(1,3,1);
    g->addArco(3,1,1);
    g->addArco(1,4,5);
    g->addArco(4,1,5);
    g->addArco(1,2,6);
    g->addArco(2,1,6);
    g->addArco(2,3,5);
    g->addArco(3,2,5);
    g->addArco(2,5,3);
    g->addArco(5,2,3);
    g->addArco(3,5,6);
    g->addArco(5,3,6);
    g->addArco(3,6,4);
    g->addArco(6,3,4);
    g->addArco(3,4,5);
    g->addArco(4,3,5);
    g->addArco(4,6,2);
    g->addArco(6,4,2);
    g->addArco(5,6,6);
    g->addArco(6,5,6);
    cout<<"pipa2"<<endl;
    /** grafo no conexo **/
    /*g->addVertice(1);
    g->addVertice(2);
    g->addVertice(3);
    g->addVertice(4);
    g->addVertice(5);
    g->addVertice(6);

    g->addArco(1,2,4);
    g->addArco(1,3,7);
    g->addArco(1,6,3);
    g->addArco(2,3,3);
    g->addArco(2,5,1);
    g->addArco(3,4,1);
    g->addArco(3,5,1);
    g->addArco(5,4,4);
    g->addArco(6,5,3);*/
    //int n;
    //cout << "ingrese el vertice destino (1 a 5)"<<endl;
    //cin >> n;
    //implemetacion_dijkstra(g, n);
    //prim(g);
    cout<<pipa<<endl;
    return 0;
}
