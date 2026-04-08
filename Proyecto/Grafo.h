#ifndef GRAFO_H
#define GRAFO_H

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Grafo {
private:
    int** matriz;
    int max_nodos;
    const int INF = 999999;

public:
    Grafo(const char* archivoC) {
        max_nodos = 51; // Asumimos un limite maximo para dinamismo seguro.
        matriz = new int*[max_nodos];
        for (int i = 0; i < max_nodos; ++i) {
            matriz[i] = new int[max_nodos];
            for (int j = 0; j < max_nodos; ++j) {
                if (i == j) matriz[i][j] = 0;
                else matriz[i][j] = INF;
            }
        }
        
        ifstream archivo(archivoC);
        if (!archivo) {
            cout << "Nota: Archivo de grafo (" << archivoC << ") no encontrado o vacio. Las rutas seran inalcanzables." << endl;
            return;
        }
        
        string linea;
        while (getline(archivo, linea)) {
            // Reemplazar comas por espacios para facilitar lectura
            for (size_t i = 0; i < linea.length(); ++i) {
                if (linea[i] == ',') linea[i] = ' ';
            }
            stringstream ss(linea);
            int origen, destino, distancia;
            if (ss >> origen >> destino >> distancia) {
                if (origen >= 0 && origen < max_nodos && destino >= 0 && destino < max_nodos) {
                    matriz[origen][destino] = distancia;
                    matriz[destino][origen] = distancia; // no dirigido
                }
            }
        }
        archivo.close();
    }

    ~Grafo() {
        if (matriz != nullptr) {
            for (int i = 0; i < max_nodos; ++i) {
                delete[] matriz[i];
            }
            delete[] matriz;
            matriz = nullptr;
        }
    }

    bool aplicarDijkstra(int origen, int destino, int& totalDistancia, vector<int>& rutaFinal) {
        if (origen < 0 || origen >= max_nodos || destino < 0 || destino >= max_nodos) {
            return false;
        }
        
        vector<int> dist(max_nodos, INF);
        vector<int> prev(max_nodos, -1);
        vector<bool> visitado(max_nodos, false);
        
        dist[origen] = 0;
        
        for (int i = 0; i < max_nodos - 1; ++i) {
            int u = -1;
            int minDist = INF;
            
            for (int j = 0; j < max_nodos; ++j) {
                if (!visitado[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    u = j;
                }
            }
            
            if (u == -1 || dist[u] == INF) break;
            
            visitado[u] = true;
            
            for (int v = 0; v < max_nodos; ++v) {
                if (!visitado[v] && matriz[u][v] != INF) {
                    int alt = dist[u] + matriz[u][v];
                    if (alt < dist[v]) {
                        dist[v] = alt;
                        prev[v] = u;
                    }
                }
            }
        }
        
        if (dist[destino] == INF) {
            return false; // inalcanzable
        }
        
        totalDistancia = dist[destino];
        
        // Tracing backwards
        int curr = destino;
        while (curr != -1) {
            rutaFinal.push_back(curr);
            curr = prev[curr];
        }
        reverse(rutaFinal.begin(), rutaFinal.end());
        return true;
    }
};

#endif
