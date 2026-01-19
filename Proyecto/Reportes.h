#ifndef REPORTES_H
#define REPORTES_H
#include "GestionTrans.h"
#include <fstream>
#include <string>
#include <iostream>
#include <map>
using namespace std;
class Reportes
{
	public:
		void finalizarJornada(){
			cout<<"Procesando cierre"<<endl;
			ifstream Historial("Historial.txt");
			if(!Historial){
				cout<<"No Hay historial"<<endl;
				return;
			}
			map<string, int> ContPlacas;
			map<string, int> ContClientes;
			
			string placaLeida, cedulaLeida;
			
			while(Historial >> placaLeida >> cedulaLeida){
				ContPlacas[placaLeida]++;
				ContClientes[cedulaLeida]++;
			}
			Historial.close();
			
			string PlTop = "N/A";
			
			int maxPla = 0;
			for(auto const& pair : ContPlacas){
			    if (pair.second > maxPla) {
			        maxPla = pair.second;
			        PlTop = pair.first;
				}
			}
			string ClienteTop = "N/A";
			int MaxClient = 0;
			for(auto const& pair : ContClientes){
			    if (pair.second > MaxClient) {
			        MaxClient = pair.second;
			        ClienteTop = pair.first;
			    }
			}
			ofstream Report("Reporte.txt");
			Report << "=== REPORTE FINAL DEL DIA ===\n";
			Report<<"Unidad Mas solicitudes: "<<PlTop<<"( "<<maxPla<<" Servicios )"<<endl;
			Report<<"Cliente mas frecuente: "<<ClienteTop<<"( "<<MaxClient<<" Servicios )"<<endl;
			cout << ">> Reporte generado en 'reporte_estadistico.txt'"<<endl;
			cout << ">> Limpiando historial temporal...\n";
			ofstream Limpieza("Historial.txt",ios::trunc);
			Limpieza.close();
			cout<<"Hasta pronto........"<<endl;
		}
};

#endif