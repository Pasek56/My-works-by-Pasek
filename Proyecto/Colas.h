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
		map<int, queue<Clientes>> Colas;
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
				Colas[zone].push(Cli);
				cout<<">>>>>>>Zona Sin unidades<<<<<<<"<<endl;
				cout<<"Cliente "<<Cli.getNombre()<<endl;
				cout<<"Registrado en la cola de espera de "<<zone<<endl;
				cout<<"Cantidad de clientes en cola de esta zona: "<<Colas[zone].size();
			}else{
				cout<<"Ya existe unidad en esta zona pero se encuentra libre"<<endl;
			}
		}
		void VerCola(int Cola){
			if(Colas.count(Cola)>0){
				cout<<"La zona Contiene: "<<Colas[Cola].size()<<" Clientes en espera"<<endl;
			}
		}
		Clientes* NextQue(int Postal){
			if(Colas.count(Postal) > 0 && !Colas[Postal].empty()){
				return &Colas[Postal].front();
			}
			return nullptr;
		}
		void DeleteofQue(int Postal){
			if(Colas.count(Postal) > 0 && !Colas[Postal].empty()){
				Colas[Postal].pop();
			}
		}
};
#endif