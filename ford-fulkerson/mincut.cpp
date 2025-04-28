#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_V 100
#define INF INT_MAX

int V; // Número de vértices

// Estructura para representar una arista con capacidad y costo
struct Edge {
    int to;         // Nodo destino
    int capacity;   // Capacidad de la arista
    int cost;       // Costo por unidad de flujo
    int flow;       // Flujo actual
};

// Estructura para representar una ruta
struct Route {
    vector<int> path;
    int flow;
    int cost;
};

// Grafo representado como listas de adyacencia
vector<Edge> graph[MAX_V];
vector<Route> routes;

// Función para agregar una arista al grafo
void addEdge(int from, int to, int capacity, int cost) {
    // Arista directa
    graph[from].push_back({to, capacity, cost, 0});
    // Arista inversa (para el grafo residual)
    graph[to].push_back({from, 0, -cost, 0});
}

// Algoritmo de camino más corto (Bellman-Ford)
bool findShortestPath(int source, int sink, vector<int>& dist, vector<int>& parent, vector<int>& edge) {
    fill(dist.begin(), dist.end(), INF);
    fill(parent.begin(), parent.end(), -1);
    fill(edge.begin(), edge.end(), -1);
    
    dist[source] = 0;
    bool updated;
    
    // Relaxación de aristas
    for (int i = 0; i < V - 1; i++) {
        updated = false;
        for (int u = 0; u < V; u++) {
            if (dist[u] == INF) continue;
            
            for (int j = 0; j < graph[u].size(); j++) {
                Edge& e = graph[u][j];
                if (e.capacity > e.flow && dist[e.to] > dist[u] + e.cost) {
                    dist[e.to] = dist[u] + e.cost;
                    parent[e.to] = u;
                    edge[e.to] = j;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }
    
    return dist[sink] != INF;
}

// Algoritmo de flujo máximo con costo mínimo
void minCostMaxFlow(int source, int sink) {
    vector<int> dist(V), parent(V), edge(V);
    int maxFlow = 0;
    int minCost = 0;
    
    // Mientras exista un camino de aumento
    while (findShortestPath(source, sink, dist, parent, edge)) {
        // Encontrar el flujo máximo que se puede enviar por este camino
        int pathFlow = INF;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            int j = edge[v];
            pathFlow = min(pathFlow, graph[u][j].capacity - graph[u][j].flow);
        }
        
        // Crear una nueva ruta
        Route newRoute;
        vector<int> path;
        for (int v = sink; v != source; v = parent[v]) {
            path.push_back(v);
        }
        path.push_back(source);
        reverse(path.begin(), path.end());
        newRoute.path = path;
        newRoute.flow = pathFlow;
        
        // Calcular el costo de la ruta
        int routeCost = 0;
        
        // Aumentar el flujo a lo largo del camino
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            int j = edge[v];
            graph[u][j].flow += pathFlow;
            
            // Encontrar la arista inversa
            int reverseEdgeIndex = -1;
            for (int k = 0; k < graph[v].size(); k++) {
                if (graph[v][k].to == u) {
                    reverseEdgeIndex = k;
                    break;
                }
            }
            
            graph[v][reverseEdgeIndex].flow -= pathFlow;
            routeCost += pathFlow * graph[u][j].cost;
        }
        
        newRoute.cost = routeCost;
        routes.push_back(newRoute);
        
        maxFlow += pathFlow;
        minCost += routeCost;
    }
    
    // Mostrar resultados
    cout << "\n--- RESULTADOS ---\n";
    cout << "Flujo máximo: " << maxFlow << endl;
    cout << "Costo mínimo: " << minCost << endl;
    
    cout << "\n--- RUTAS UTILIZADAS ---\n";
    for (int i = 0; i < routes.size(); i++) {
        cout << "Ruta " << i+1 << ": ";
        for (int j = 0; j < routes[i].path.size(); j++) {
            cout << routes[i].path[j];
            if (j < routes[i].path.size() - 1) cout << " -> ";
        }
        cout << " | Flujo: " << routes[i].flow;
        cout << " | Costo: " << routes[i].cost << endl;
    }
}

int main()
{
     cout << "Ingrese el número de vértices: ";
     cin >> V; // Lee el número de vértices

     int E;
     cout << "Ingrese el número de aristas: ";
     cin >> E; // Lee el número de aristas

     cout << "Ingrese las aristas en el formato 'u v capacidad costo':" << endl;
     for (int i = 0; i < E; i++) // Lee todas las aristas
     {
          int u, v, capacity, cost;
          cin >> u >> v >> capacity >> cost; // Lee el nodo origen, nodo destino, capacidad y costo
          addEdge(u, v, capacity, cost); // Agrega la arista al grafo
     }

     int s, t;
     cout << "Ingrese el nodo fuente: ";
     cin >> s; // Lee el nodo fuente
     cout << "Ingrese el nodo sumidero: ";
     cin >> t; // Lee el nodo sumidero

     minCostMaxFlow(s, t); // Llama a la función minCostMaxFlow

     return 0;
}