#ifndef GRAFO_H
#define GRAFO_H
#include <map>
#include <list>
#include <assert.h>
#include <iostream>
using namespace std;

template <typename V, typename C>
class arista
{
public:
    arista(){origen=0;destino=0;costo=0;}
    arista(const arista<V,C>& other)
    {
        origen=other.origen;
        destino=other.destino;
        costo=other.costo;
    }
    arista(V origen, V destino, C costo)
    {
        this->origen=origen;
        this->destino=destino;
        this->costo=costo;
    }
    V getOrigen() const{return origen;}
    V getDestino() const{return destino;}
    C getCosto() const{return costo;}
    void setOrigen(V origen){this->origen=origen;}
    void setDestino(V destino){this->destino=destino;}
    void setCosto(C costo){this->costo=costo;}
    bool operator <(const arista<V,C>& other) const{
        return (costo<other.costo);
    }
    bool operator >(const arista<V,C>& other) const{
        return(costo>other.costo);
    }
    arista<V,C>& operator =(const arista<V,C>& other){
        this->origen=other.origen;
        this->destino=other.destino;
        this->costo=other.costo;
        return *this;
    }

private:
    V origen, destino;
    C costo;
};


template <typename V, typename C>
class Grafo
{
public:

    Grafo(){
        cantArcos=0;
        cantVertices=0;
    }

    void addVertice(const V & vertice){
        if(isVertice(vertice) == false)
        {
            grafo[vertice]=arcos;
            cantVertices++;
        }
    }
    void delVertice(const V & vertice){
        assert(isVertice(vertice));
        //map< int, map <int, C> >::iterator itGrafos =grafo.find(vertice);
        //grafo.erase(itGrafos);
        grafo.erase(vertice);
        cantVertices--;
    }
    bool isVertice(const V & vertice) const{
        typename map<V, map<V, C> >::const_iterator it;
        it=grafo.find(vertice);
        if(it != grafo.end())
            return true;
        else
            return false;
    }

    void addArco(const V & origen, const V & destino, const C & costo){
        assert(isVertice(origen) && isVertice(destino));
        if (isArco(origen, destino) == false){
            //arcos[destino]=costo;
            //grafo[origen]=arcos;
            typename map<V, map<V,C>>::iterator it;
            it=grafo.find(origen);
            it->second[destino]=costo;
            cantArcos++;
            arista<V,C> nuevo(origen, destino, costo);
            aristas.push_back(nuevo);
        }
    }
    void delArco(const V & origen, const V & destino){
        assert(isVertice(origen) && isVertice(destino) && isArco(origen, destino));
        typename map< V, map<V, C> >::iterator itGrafo;
        itGrafo=grafo.find(origen);
        itGrafo->second.erase(destino);
    }
    bool isArco(const V & origen, const V & destino) const{
        typename map< V, map<V, C> >::const_iterator itGrafo;
        itGrafo=grafo.find(origen);
        if (itGrafo !=grafo.end()){
            typename map<V,C>::const_iterator itArco;
            itArco=itGrafo->second.find(destino);
            if (itArco != itGrafo->second.end())
                return true;
            else
                return false;
        }
        else {
            return false;
        }
    }
    C GetCostArco(const V & origen, const V & destino) const{
        assert(isArco(origen, destino));
        typename map< V, map<V, C> >::const_iterator itGrafo;
        itGrafo=grafo.find(origen);
        typename map<V,C>::const_iterator itArco;
        itArco=itGrafo->second.find(destino);
        return itArco->second;
    }

    void getListVertices(list<V>& listaVertice){
        typename map<V, map<V, C>>::iterator itGrafo=grafo.begin();
        while(itGrafo != grafo.end()){
            listaVertice.push_back(itGrafo->first);
            itGrafo++;
        }
    }
    void getListArcos(const V & origen, list<arista<V,C>> & listArcos){
        assert(isVertice(origen));
        typename map<V, map<V, C>>::iterator itGrafo=grafo.find(origen);
        typename map<V,C>::iterator itArco=itGrafo->second.begin();
        while(itArco !=itGrafo->second.end())
        {
            arista<V,C> nuevo;
            nuevo.setOrigen(origen);
            nuevo.setDestino(itArco->first);
            nuevo.setCosto(itArco->second);
            listArcos.push_back(nuevo);
            itArco++;
        }
    }
    void getReversGrafo(Grafo<V,C> & otherGrafo){
        list<V> lvertices;
        getListVertices(lvertices);
        typename list<V>::iterator itV;
        for(itV=lvertices.begin(); itV!=lvertices.end(); itV++)
        {
            otherGrafo.addVertice(*itV);
        }
        list<arista<V,C>> lAristas;
        getAristas(lAristas);
        typename list<arista<V,C>>::const_iterator itAristas;
        for(itAristas=lAristas.begin(); itAristas!=lAristas.end(); itAristas++)
        {
            otherGrafo.addArco(itAristas->getDestino(), itAristas->getOrigen(), itAristas->getCosto());
        }
    }
    void getAristas(list<arista<V,C>> &lAristas)
    {
        typename list<arista<V,C>>::iterator it;
        for(it=aristas.begin(); it!=aristas.end(); it++)
        {
            arista<V,C> nuevo(it->getOrigen(), it->getDestino(), it->getCosto());
            lAristas.push_back(nuevo);
        }
    }

    int getCantVertices() const {return cantVertices;}
    int getCantArcos() const {return cantArcos;}

private:

    int cantVertices, cantArcos;
    list<arista<V,C>> aristas;
    map< V,C > arcos;
    map< V, map <V, C> > grafo;

};

#endif // GRAFO_H
