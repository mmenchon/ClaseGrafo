#ifndef UNIONFIND_H
#define UNIONFIND_H

class UF
{
public:
    UF(int n) {
        id = new int[n];
        sz = new int[n];
        for(int i=0;i<=n;i++){
            id[i]=i;
            sz[i]=1;
        }
    }

    int find(int i)
    {
        while (i != id[i]) {
            id[i]=id[id[i]];
            i=id[i];
        }
        return i;
    }

    void _union(int p, int q)
    {
        int i=find(p), j=find(q);
        if (i != j){
            if (sz[i]<sz[j])
            {
                id[i]=j;
                sz[j]+=sz[i];
            }else
                {
                    id[j]=i;
                    sz[i]+=sz[j];
                }
        }

    }

    bool conectadas(int p, int q)
    {
        return(find(q) == find(p));
    }

private:
    int* id;
    int* sz;

};
#endif // UNIONFIND_H
