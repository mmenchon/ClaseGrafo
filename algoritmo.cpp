#include "algoritmo.h"
void dfs(Grafo<int,int>* g, int v, int* marca, int* padre, int* finalizado, int* descubierto, int&tiempo, list<int>* sortTopologico)
{
    marca[v]=DESCUBIERTO;
    tiempo=tiempo+1;
    descubierto[v]=tiempo;
    list<arista<int,int>> arcos;
    g->getListArcos(v, arcos);
    list<arista<int,int>>::const_iterator it;
    for(it=arcos.begin(); it!=arcos.end(); it++)
    {
        if (marca[(*it).getDestino()]==NO_VISITADO){
            padre[(*it).getDestino()]=v;
            dfs(g, (*it).getDestino(), marca, padre, finalizado, descubierto, tiempo, sortTopologico);
        }
    }
    marca[v]=VISITADO;
    tiempo=tiempo+1;
    finalizado[v]=tiempo;
    sortTopologico->push_back(v);
}

void dfs_Forest(Grafo<int,int>* g)
{
    int marca[g->getCantVertices()+1];
    int padre[g->getCantVertices()+1];
    int finalizado[g->getCantVertices()+1];
    int descubierto[g->getCantVertices()+1];

    list<int> vertices;
    g->getListVertices(vertices);
    list<int>::const_iterator it;
    for(it=vertices.begin(); it!=vertices.end(); it++)
    {
        marca[*it]=NO_VISITADO;
        padre[*it]=0;
        finalizado[*it]=0;
        descubierto[*it]=0;
    }
    int tiempo=0;
    list<int> *sortTopologico = new list<int>;
    for(it=vertices.begin(); it!=vertices.end(); it++)
    {
        if (marca[*it]==NO_VISITADO)
            dfs(g, *it, marca, padre, finalizado, descubierto, tiempo, sortTopologico);
    }

    cout<<"descubierto"<<endl;
    for(int i=1; i<g->getCantVertices()+1; i++)
        cout << descubierto[i] << " ";
    cout<<endl;
    cout<<"finalizado"<<endl;
    for(int i=1; i<g->getCantVertices()+1; i++)
        cout << finalizado[i] << " ";
    cout << endl;
    cout << "orden Topologico"<<endl;
    list<int>::const_iterator itTopo;
    for(itTopo=sortTopologico->begin(); itTopo!=sortTopologico->end(); itTopo++)
        cout << *itTopo<< " ";
    cout << endl;
}

void testAciclicidad(Grafo<int,int>* g, int v, int* marca, int* padre, int* finalizado, int* descubierto, int&tiempo)
{
    marca[v]=DESCUBIERTO;
    tiempo=tiempo+1;
    descubierto[v]=tiempo;
    list<arista<int,int>> arcos;
    g->getListArcos(v, arcos);
    list<arista<int,int>>::const_iterator it;
    for(it=arcos.begin(); it!=arcos.end(); it++)
    {
        if (marca[(*it).getDestino()]==NO_VISITADO){
            padre[(*it).getDestino()]=v;
            testAciclicidad(g, (*it).getDestino(), marca, padre, finalizado, descubierto, tiempo);
        }
        else
        {
            if( (descubierto[(*it).getDestino()]<descubierto[v]) && (marca[it->getDestino()]==DESCUBIERTO))
             cout<< "hay un ciclo  en el arco ("<<v<<","<< it->getDestino()<< ")"<<endl;
        }
    }
    marca[v]=VISITADO;
    tiempo=tiempo+1;
    finalizado[v]=tiempo;
}

void dfs_Forest_aciclididad(Grafo<int,int>* g)
{
    int marca[g->getCantVertices()+1];
    int padre[g->getCantVertices()+1];
    int finalizado[g->getCantVertices()+1];
    int descubierto[g->getCantVertices()+1];

    list<int> vertices;
    g->getListVertices(vertices);
    list<int>::const_iterator it;
    for(it=vertices.begin(); it!=vertices.end(); it++)
    {
        marca[*it]=NO_VISITADO;
        padre[*it]=0;
        finalizado[*it]=0;
        descubierto[*it]=0;
    }
    int tiempo=0;
    for(it=vertices.begin(); it!=vertices.end(); it++)
    {
        if (marca[*it]==NO_VISITADO)
            testAciclicidad(g, *it, marca, padre, finalizado, descubierto, tiempo);
    }
}

void bfs(Grafo<int,int>* g, int s)
{
    int estado[g->getCantVertices()+1];
    int padre[g->getCantVertices()+1];
    queue<int> Q;
    list<int> vertices;
    g->getListVertices(vertices);
    list<int>::const_iterator it;
    for(it=vertices.begin(); it!=vertices.end();it++){
        estado[*it]=NO_VISITADO;
        padre[*it]=0;
    }
    padre[s]=0;
    estado[s]=VISITADO;
    Q.push(s);
    while (Q.empty() == false)
    {
        int u=Q.front();
        Q.pop();
        list<arista<int,int>> arcos;
        g->getListArcos(u, arcos);
        list<arista<int,int>>::const_iterator itAdy;
        for(itAdy=arcos.begin(); itAdy!=arcos.end();itAdy++)
        {
            if(estado[(*itAdy).getDestino()]==NO_VISITADO){
                estado[(*itAdy).getDestino()]=VISITADO;
                Q.push((*itAdy).getDestino());
                padre[itAdy->getDestino()]=u;
            }
        }
    }
    cout<< "padre"<<endl;
    for(int i=1; i<=g->getCantVertices(); i++)
        cout << padre[i] << " ";
}

void calcularBajo(int* descubierto, int* padre, int* bajo, int v, int min_back, int size)
{
    //int hijo=v;
    int min_hijo=INT_MAX;
    for(int i=1;i<=size;i++)
    {
        if (padre[i]==v)
            min_hijo=min(min_hijo, bajo[i]);
    }
    if (descubierto[v] <= min_back && descubierto[v] <= min_hijo)
        bajo[v]=descubierto[v];
    else
        if(min_back <= min_hijo)
            bajo[v]=min_back;
        else {
            bajo[v]=min_hijo;
        }
    //bajo[v]=min(descubierto[v], min_back,min_hijo);
}

void puntoArticulacion_dfs(Grafo<int,int>* g, int v, int* marca, int* padre, int* finalizado, int* descubierto, int&tiempo, int* bajo)
{
    marca[v]=DESCUBIERTO;
    tiempo=tiempo+1;
    descubierto[v]=tiempo;
    int min_back=INT_MAX;
    list<arista<int,int>> arcos;
    g->getListArcos(v, arcos);
    list<arista<int,int>>::const_iterator it;
    for(it=arcos.begin(); it!=arcos.end(); it++)
    {
        if (marca[(*it).getDestino()]==NO_VISITADO){
            padre[(*it).getDestino()]=v;
            puntoArticulacion_dfs(g, (*it).getDestino(), marca, padre, finalizado, descubierto, tiempo, bajo);
        }
        else
            if((descubierto[(*it).getDestino()]<descubierto[v]) && (marca[it->getDestino()]==DESCUBIERTO))
            {
                min_back=min(min_back,descubierto[(*it).getDestino()]);
            }
    }
    marca[v]=VISITADO;
    tiempo=tiempo+1;
    finalizado[v]=tiempo;
    calcularBajo(descubierto, padre, bajo, v, min_back, g->getCantVertices()+1);
}

void dfs_Forest_PA(Grafo<int,int>* g)
{
    int marca[g->getCantVertices()+1];
    int padre[g->getCantVertices()+1];
    int finalizado[g->getCantVertices()+1];
    int descubierto[g->getCantVertices()+1];
    int bajo[g->getCantVertices()+1];

    list<int> vertices;
    g->getListVertices(vertices);
    list<int>::const_iterator it;
    for(it=vertices.begin(); it!=vertices.end(); it++)
    {
        marca[*it]=NO_VISITADO;
        padre[*it]=0;
        finalizado[*it]=0;
        descubierto[*it]=0;
        bajo[*it]=INT_MAX;
    }
    int tiempo=0;
    for(it=vertices.begin(); it!=vertices.end(); it++)
    {
        if (marca[*it]==NO_VISITADO)
            puntoArticulacion_dfs(g, *it, marca, padre, finalizado, descubierto, tiempo, bajo);
    }

    for(int i=1; i<g->getCantVertices()+1; i++)
        cout << i << " ";
    cout<<endl;
    cout<< "A B C D E F G"<<endl;
    int hijos=0, raiz=0;
    int i=1;
    while (i<=g->getCantVertices()+1) //busco cual es la raiz del arbol
    {
        if (padre[i]==0)
            raiz=i;
        break;
        i++;
    }
    for(i=1;i<=g->getCantVertices()+1; i++) //cuanto la cantidad de hijos
    {
        if (padre[i]==raiz)
            hijos++;
    }
    if (hijos>=2)
        cout << raiz <<" es PA" <<endl;
    for(i=1;i<=g->getCantVertices(); i++)
    {
        if(i!=raiz)
        {
            int hijo=INT_MIN, j=1;
            bool termino=true;
            while(termino && j<=g->getCantVertices()+1)
            {
                if (padre[j]==i)
                {
                    hijo=j;
                    termino=false;
                }
                else bajo[hijo]=INT_MIN;
                j++;
            }
            //cout <<i<<": "<<bajo[hijo]<<" Bajo de "<<hijo<<" "<<endl;
            if(bajo[hijo]>=descubierto[i])
               cout << i <<" es PA" <<endl;
        }
    }
}

void dijktra(Grafo<int,int>* g, int origen, int *d, int *padre)
{
    list<int> vertices;
    g->getListVertices(vertices);
    list<int>::const_iterator it;
    MinHeap<arista<int,int>> heap;
    set<int> s;
    s.insert(origen);
    for(it=vertices.begin(); it!=vertices.end(); it++)
    {
        d[*it]=INT_MAX;
        padre[*it]=0;
    }
    d[origen]=0;
    arista<int,int> nodo;
    nodo.setOrigen(origen);nodo.setCosto(0);
    heap.insert(nodo);
    while (heap.empty() == false)
    {
        arista<int,int> vertice = heap.extractMin();
        list<arista<int,int>> ady;
        s.insert(vertice.getOrigen());
        g->getListArcos(vertice.getOrigen(), ady);
        typename list<arista<int,int>>::iterator itAdy=ady.begin();
        while (itAdy != ady.end())
        {
            if (s.find((*itAdy).getDestino()) == s.end())
            {
                int dt=d[vertice.getOrigen()] + g->GetCostArco(vertice.getOrigen(), (*itAdy).getDestino());
                if(d[(*itAdy).getDestino()] > dt)
                {
                    d[(*itAdy).getDestino()]= dt;
                    padre[(*itAdy).getDestino()]=vertice.getOrigen();
                    arista<int,int> nuevo;
                    nuevo.setOrigen((*itAdy).getDestino());
                    nuevo.setCosto(d[(*itAdy).getDestino()]);
                    heap.insert(nuevo);
                }
            }
            itAdy++;
        }
    }
}

void dijktra2(Grafo<int,int>* g, int origen, int destino, int *d, int *padre)
{
    list<int> vertices;
    g->getListVertices(vertices);
    list<int>::const_iterator it;
    MinHeap<arista<int,int>> heap;
    set<int> s;
    s.insert(origen);
    for(it=vertices.begin(); it!=vertices.end(); it++)
    {
        d[*it]=INT_MAX;
        padre[*it]=0;
    }
    d[origen]=0;
    arista<int,int> nodo;
    nodo.setOrigen(origen);nodo.setCosto(0);
    heap.insert(nodo);
    while ((heap.empty() == false) && (s.find(destino) == s.end()))
    {
        arista<int,int> vertice = heap.extractMin();
        list<arista<int,int>> ady;
        s.insert(vertice.getOrigen());
        g->getListArcos(vertice.getOrigen(), ady);
        typename list<arista<int,int>>::iterator itAdy=ady.begin();
        while (itAdy != ady.end())
        {
            if (s.find((*itAdy).getDestino()) == s.end())
            {
                int dt=d[vertice.getOrigen()] + g->GetCostArco(vertice.getOrigen(), (*itAdy).getDestino());
                if(d[(*itAdy).getDestino()] > dt)
                {
                    d[(*itAdy).getDestino()]= dt;
                    padre[(*itAdy).getDestino()]=vertice.getOrigen();
                    arista<int,int> nuevo;
                    nuevo.setOrigen((*itAdy).getDestino());
                    nuevo.setCosto(d[(*itAdy).getDestino()]);
                    heap.insert(nuevo);
                }
            }
            itAdy++;
        }
    }
}

void kruskal(Grafo<int,int>* g)
{
    MinHeap<arista<int,int>> h;
    set<arista<int,int>> T;
    UF componentes(g->getCantVertices()+1);
    list<arista<int,int>> laristas;
    g->getAristas(laristas);
    typename list<arista<int,int>>::const_iterator it;
    for(it=laristas.begin(); it!=laristas.end();it++)
    {
        h.insert(*it);
    }
    while (h.empty() == false)
    {
        arista<int,int> arco = h.extractMin();
        if(componentes.find(arco.getOrigen()) != componentes.find(arco.getDestino()))
        {
            componentes._union(arco.getOrigen(), arco.getDestino());
            T.insert(arco);
        }
    }
}

void prim(Grafo<int,int>* g)
{
    list<int> vertices;
    cout<<"pipa2"<<endl;
    int* masCercano = new int[g->getCantVertices()+1];
    int* distance = new int[g->getCantVertices()+1];
    g->getListVertices(vertices);
    typename list<int>::const_iterator it=vertices.begin();
    MinHeap<arista<int,int>> heap;
    set<int> s;
    s.insert(1);
    masCercano[1]=0;
    distance[1]=0;
    it++;
    for(;it!=vertices.end();it++)
    {
        cout<<*it<<endl;
        arista<int,int> arco;
        arco.setOrigen(1);
        arco.setDestino(*it);
        if (g->isArco(1, *it))
            arco.setCosto(g->GetCostArco(1,*it));
        else
            arco.setCosto(INT_MAX);
        heap.insert(arco);
        masCercano[(*it)]=1;
        distance[(*it)]=INT_MAX;
    }
    cout << "distancia"<< endl;
    for(int i =1;i<g->getCantVertices()+1;i++)
        cout<<distance[i]<<" ";
    cout<<endl;
    while (heap.empty() == false)
    {
        arista<int,int> vertice=heap.extractMin();
        s.insert(vertice.getDestino());
        cout << "vertice destino "<<vertice.getDestino()<<endl;
        //masCercano[vertice.getDestino()]=vertice.getOrigen();
        list<arista<int,int>> adyacentes;
        g->getListArcos(vertice.getDestino(),adyacentes);
        typename list<arista<int,int>>::iterator itAdy=adyacentes.begin();
        while (itAdy != adyacentes.end())
        {
            if(s.find(itAdy->getDestino()) == s.end() && distance[(*itAdy).getDestino()] > g->GetCostArco(itAdy->getOrigen(),itAdy->getDestino()))
            {
                distance[(*itAdy).getDestino()]=g->GetCostArco(itAdy->getOrigen(),itAdy->getDestino());
                arista<int,int> arco;
                arco.setCosto(g->GetCostArco(itAdy->getOrigen(),itAdy->getDestino()));
                arco.setOrigen(itAdy->getOrigen());
                arco.setDestino(itAdy->getDestino());
                heap.insert(arco);
                masCercano[itAdy->getDestino()]=itAdy->getOrigen();
            }
            itAdy++;
        }
        cout << "distancia"<< endl;
        for(int i =1;i<g->getCantVertices()+1;i++)
            cout<<distance[i]<<" ";
        cout<<endl;
    }
    cout << "arbol de minimo costo"<< endl;
    for(int i =1;i<g->getCantVertices()+1;i++)
        cout<<masCercano[i]<<" ";
    cout<<endl;
    cout<< "1 2 3 4 5 6 "<<endl;
    delete distance;
    delete masCercano;
}
