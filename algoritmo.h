#ifndef ALGORITMO_H
#define ALGORITMO_H
#include "grafo.h"
#include <list>
#include <queue>
#include <iostream>
#include <set>
#include "minheap.h"
#include "union-find.h"
using namespace std;
const int NO_VISITADO=-1;
const int DESCUBIERTO=0;
const int VISITADO=1;

void dfs(Grafo<int,int>* g, int v, int* marca, int* padre, int* finalizado, int* descubierto, int&tiempo, list<int>* sortTopologico);
void dfs_Forest(Grafo<int,int>* g);

void testAciclicidad(Grafo<int,int>* g, int v, int* marca, int* padre, int* finalizado, int* descubierto, int&tiempo);
void dfs_Forest_aciclididad(Grafo<int,int>* g);

void bfs(Grafo<int,int>* g, int s);

void calcularBajo(int* descubierto, int* padre, int* bajo, int v, int min_back, int size);
void puntoArticulacion_dfs(Grafo<int,int>* g, int v, int* marca, int* padre, int* finalizado, int* descubierto, int&tiempo, int* bajo);
void dfs_Forest_PA(Grafo<int,int>* g);

void dijktra(Grafo<int,int>* g, int origen, int *d, int *padre);

void dijktra2(Grafo<int,int>* g, int origen, int destino, int *d, int *padre);

void kruskal(Grafo<int,int>* g);

void prim(Grafo<int,int>* g);

#endif // ALGORITMO_H
