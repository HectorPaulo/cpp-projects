#include <iostream> // Incluye la biblioteca de entrada y salida estándar
#include <limits.h> // Incluye la biblioteca para límites de tipos de datos
#include <string.h> // Incluye la biblioteca para manipulación de cadenas y memoria
#include <queue> // Incluye la biblioteca para la estructura de datos cola
#include <vector> // Incluye la biblioteca para la estructura de datos vector
using namespace std; // Utiliza el espacio de nombres estándar

// Número máximo de vértices
#define MAX_V 100

int V; // Número de vértices

/* Devuelve true si hay un camino desde la fuente 's' hasta el sumidero 't' en
    el grafo residual. También llena parent[] para almacenar el camino */
int bfs(int rGraph[MAX_V][MAX_V], int s, int t, int parent[])
{
     bool visited[MAX_V]; // Array para marcar los vértices visitados
     memset(visited, 0, sizeof(visited)); // Inicializa el array visited a false

     queue<int> q; // Cola para la búsqueda en anchura (BFS)
     q.push(s); // Añade el nodo fuente a la cola
     visited[s] = true; // Marca el nodo fuente como visitado
     parent[s] = -1; // Inicializa el nodo fuente sin padre

     while (!q.empty()) // Mientras la cola no esté vacía
     {
          int u = q.front(); // Obtiene el primer elemento de la cola
          q.pop(); // Elimina el primer elemento de la cola

          for (int v = 0; v < V; v++) // Recorre todos los vértices
          {
                if (visited[v] == false && rGraph[u][v] > 0) // Si el vértice no ha sido visitado y hay capacidad en el grafo residual
                {
                     q.push(v); // Añade el vértice a la cola
                     parent[v] = u; // Establece el padre del vértice
                     visited[v] = true; // Marca el vértice como visitado
                }
          }
     }

     return (visited[t] == true); // Devuelve true si se alcanzó el nodo sumidero
}

void dfs(int rGraph[MAX_V][MAX_V], int s, bool visited[])
{
     visited[s] = true; // Marca el nodo como visitado
     for (int i = 0; i < V; i++) // Recorre todos los vértices
         if (rGraph[s][i] && !visited[i]) // Si hay capacidad en el grafo residual y el vértice no ha sido visitado
              dfs(rGraph, i, visited); // Llama recursivamente a DFS
}

void minCut(int graph[MAX_V][MAX_V], int s, int t)
{
     int u, v;
     int rGraph[MAX_V][MAX_V]; // Grafo residual
     for (u = 0; u < V; u++) // Inicializa el grafo residual con las capacidades originales
          for (v = 0; v < V; v++)
                 rGraph[u][v] = graph[u][v];

     int parent[MAX_V]; // Array para almacenar el camino
     int max_flow = 0; // Inicializa el flujo máximo a 0

     while (bfs(rGraph, s, t, parent)) // Mientras haya un camino desde la fuente al sumidero
     {
          int path_flow = INT_MAX; // Inicializa el flujo del camino a infinito
          for (v = t; v != s; v = parent[v]) // Recorre el camino desde el sumidero a la fuente
          {
                u = parent[v];
                path_flow = min(path_flow, rGraph[u][v]); // Encuentra la capacidad mínima en el camino
          }

          for (v = t; v != s; v = parent[v]) // Actualiza las capacidades en el grafo residual
          {
                u = parent[v];
                rGraph[u][v] -= path_flow; // Reduce la capacidad en la dirección del camino
                rGraph[v][u] += path_flow; // Aumenta la capacidad en la dirección inversa
          }

          max_flow += path_flow; // Añade el flujo del camino al flujo máximo
     }

     bool visited[MAX_V]; // Array para marcar los vértices visitados
     memset(visited, false, sizeof(visited)); // Inicializa el array visited a false
     dfs(rGraph, s, visited); // Llama a DFS para encontrar los vértices alcanzables desde la fuente en el grafo residual

     cout << "Rutas por las que pasa el flujo:" << endl;
     vector<string> rutas; // Vector para almacenar las rutas
     for (int i = 0; i < V; i++) // Recorre todos los vértices
     {
         for (int j = 0; j < V; j++) // Recorre todos los vértices
         {
             if (graph[i][j] > 0 && rGraph[i][j] < graph[i][j]) // Si hay capacidad en el grafo original y se ha utilizado en el grafo residual
             {
                 cout << "Ruta: " << i << " -> " << j << " | Capacidad: " << graph[i][j] << " | Flujo: " << graph[i][j] - rGraph[i][j] << endl;
                 rutas.push_back(to_string(i) + " -> " + to_string(j)); // Añade la ruta al vector
             }
         }
     }
     cout << "Flujo máximo total: " << max_flow << endl; // Imprime el flujo máximo total

     cout << "Rutas en forma de nodos direccionados:" << endl;
     for (const auto& ruta : rutas) // Recorre todas las rutas
     {
         cout << ruta << endl; // Imprime cada ruta
     }

     return;
}

int main()
{
     cout << "Ingrese el número de vértices: ";
     cin >> V; // Lee el número de vértices

     int graph[MAX_V][MAX_V]; // Grafo original
     memset(graph, 0, sizeof(graph)); // Inicializa el grafo a 0

     int E;
     cout << "Ingrese el número de aristas: ";
     cin >> E; // Lee el número de aristas

     cout << "Ingrese las aristas en el formato 'u v capacidad':" << endl;
     for (int i = 0; i < E; i++) // Lee todas las aristas
     {
          int u, v, capacity;
          cin >> u >> v >> capacity; // Lee el nodo origen, nodo destino y capacidad
          graph[u][v] = capacity; // Establece la capacidad en el grafo
     }

     int s, t;
     cout << "Ingrese el nodo fuente: ";
     cin >> s; // Lee el nodo fuente
     cout << "Ingrese el nodo sumidero: ";
     cin >> t; // Lee el nodo sumidero

     minCut(graph, s, t); // Llama a la función minCut

     return 0;
}
