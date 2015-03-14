//Dijkstra's algorithm

#include<stdio.h>
#include<iostream>
#include<vector>
#define INT_MAX 10000009
using namespace std;

struct Edge
{
    int dest;
    int cost;
};
vector<vector<Edge> > graph;
bool exists[1000];
int minDist(int dis[], bool vis[],int v)
{
    int min = INT_MAX;
    int pos;
    for(int i=1; i<=v; i++)
    {
        if(vis[i]==false && dis[i] <= min)
        {
            pos=i;
            min=dis[i];
        }
    }
    return pos;
}
void dijkstra(int n, int v)
{
    int dis[100];
    bool vis[100];

    for(int i=1; i<=v; i++)
    {
        dis[i]=INT_MAX;
        vis[i]=false;
    }
    dis[n]=0;

    for(int j=1; j<v; j++)
    {
        int x = minDist(dis, vis, v);
        vis[x]=true;
        if(exists[x])
        {
       for(int i=0; i<graph[x].size(); i++)
        {
            if(vis[graph[x][i].dest]==false && dis[x]+graph[x][i].cost < dis[graph[x][i].dest] && dis[x]!=INT_MAX)
             {
                dis[graph[x][i].dest] = dis[x] + graph[x][i].cost;
            }
        }
        }
    }

    for(int i=1; i<=v; i++)
    {
        if(i!=n)
            cout<<"Distance of "<<i<<" : "<<dis[i]<<endl;
    }
}
int main()
{
    int V, E;
    cout<<"Enter number of vertices and edges\n";
    cin>>V>>E;

    vector<Edge> dummy;

    cout<<"Enter src, dest, weight\n";
    for(int i=0; i<E; i++)
    {
        graph.push_back(dummy);
    }

    for(int i=0; i<E; i++)
    {
        int src, dest, weight;
        cin>>src>>dest>>weight;

        Edge e;
        e.dest=dest;
        e.cost=weight;

        graph[src].push_back(e);
        exists[src]=true;
    }
    int start;
    cout<<"Choose start\n";
    cin>>start;

    dijkstra(start, V);
}
