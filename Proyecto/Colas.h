#ifndef COLAS_H
#define COLAS_H
#include "Clientes.h"
#include "Transporte.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <cstring>
#include <map>

using namespace std;
class Colas{
	private:
		map<int, queue<Clientes>> colas;
	public:
		bool BusquedaUnidad(int zonaBus){
			ifstream Lista("transporte.dat", ios::binary);
			if(!Lista){
				cout<<"Error de Archivo"<<endl;
				return false;
			}
			Transporte Tras;
			
			while(Lista.read(reinterpret_cast<char*>(&Tras), sizeof(Transporte))){
				if(Tras.getzonaActual()==zonaBus && !Tras.getocupado()){
					Lista.close();
					return true;
				}
			}
			Lista.close();
			return false;
		}
		
		void ColaCliente(Clientes Cli){
			int zone = Cli.getzonaClien();
			
			if(!BusquedaUnidad(zone)){
				colas[zone].push(Cli);
				cout<<">>>>>>>Zona Sin unidades<<<<<<<"<<endl;
				cout<<"Cliente "<<Cli.getNombre()<<endl;
				cout<<"Registrado en la cola de espera de "<<zone<<endl;
				cout<<"Cantidad de clientes en cola de esta zona: "<<colas[zone].size();
			}else{
				cout<<"Ya existe unidad en esta zona pero se encuentra libre"<<endl;
			}
		}
		void VerCola(int Cola){
			if(colas.count(Cola)>0){
				cout<<"La zona Contiene: "<<colas[Cola].size()<<" Clientes en espera"<<endl;
			}
		}
		bool NextQue(int Postal, Clientes& clienteEncontrado){
			if(colas.count(Postal) > 0 && !colas[Postal].empty()){
				clienteEncontrado = colas[Postal].front(); 
				return true;
			}
			return false;
		}
		void DeleteofQue(int Postal){
			auto it = colas.find(Postal);
			if(it!= colas.end() && !it->second.empty()){
				it->second.pop();
				cout<<">>>Cliente eliminado de la cola<<<";
			}
		}
};
#endif