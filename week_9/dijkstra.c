#include <stdlib.h> 
#include <stdio.h> 
   
#define V 9
#define INT_MAX 100000 

int minDistance(int dist[], int sptSet[]) 
{  
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < V; v++) 
        if (sptSet[v] == 0 && dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
} 

void printSolution(int dist[]) 
{ 
    printf("Vertex \t\t Distance from Source\n"); 
    for (int i = 0; i < V; i++) 
        printf("%d \t\t %d\n", i, dist[i]); 
} 
  
void dijkstra(int graph[V][V], int src) 
{ 
    int dist[V]; // dist[i] : distance from src to i 
  
    int sptSet[V]; // sptSet[i] will be 1 if vertex i is included in shortest  
  
    // Initialize all distances as INFINITE and stpSet[] as 0 
    for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX, sptSet[i] = 0; 
  
    // Distance of source vertex from itself is always 0 
    dist[src] = 0; 
  
    // Find shortest path for all vertices 
    for (int count = 0; count < V - 1; count++) {  
        int u = minDistance(dist, sptSet); 
   
        sptSet[u] = 1; 
  
        // Update dist value of the adjacent vertices of the picked vertex. 
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v]) { 
                dist[v] = dist[u] + graph[u][v];
	    }
	} 
    } 
   
    printSolution(dist); 
} 
  
int main() 
{ 
    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 }, 
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 }, 
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 }, 
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 }, 
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 }, 
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 }, 
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 }, 
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 }, 
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } }; 
  
    printf("src : 0\n");
    dijkstra(graph, 0); 
  
    return 0; 
} 
