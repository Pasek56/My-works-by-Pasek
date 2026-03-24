#ifndef GESTOR_H
#define GESTOR_H
#include "Clientes.h"
#include "Colas.h"
#include <fstream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
using namespace std;
class Gestor
{
	private:
		const char* Archivo;
		Colas Co;
	public:
		Gestor(const char* archivo){
			Archivo = archivo;
		}
		Colas& getControladorColas() {
        	return Co;
    	}
		void Registro(){
			ofstream archivo(Archivo, ios::binary | ios::app);
			if(!archivo){
				cerr<<"Archivo corrupto o inexistente"<<endl;
				return;
			}
			Clientes Clien;
			Clien.CapturaData();
			archivo.write(reinterpret_cast<char*>(&Clien), sizeof(Clientes));
			archivo.close();
			
			Co.ColaCliente(Clien);
		}
		void Lista(){                      
			ifstream archivo(Archivo,ios::in | ios::binary);
			if(!archivo){
				cerr<<"NO hay clientes......."<<endl;
				return;
			}
			Clientes temp;
			bool Date = false;
			while(archivo.read(reinterpret_cast<char*>(&temp), sizeof(Clientes))){
				temp.showData();
				Date = true;
			}
			if(!Date){
				cout<<"El archivo esta vacio";
			}
			archivo.close();
			cout << "\n=== ESTADO ACTUAL DE COLAS POR ZONA ===" << endl;
		    int cp;
		    cout << "Ingrese el CP para ver detalle de espera (o 0 para omiter): ";
		    cin >> cp;
		    if (cp != 0) {
		        Co.VerCola(cp);
		    }
		}
		void Modificar(const char* Search){
			fstream archivo(Archivo, ios::binary | ios::in | ios::out);
			if(!archivo) { cout << "Error de archivo.\n"; return; }
			
			Clientes Cli;
			bool Find = false;
			
			while(archivo.read(reinterpret_cast<char*>(&Cli),sizeof(Clientes))){
				
				if(strcmp(Cli.getcedula(), Search) == 0){
					Cli.showData();
					Cli.DataEdit();
					archivo.seekp(-static_cast<int>(sizeof(Clientes)),ios::cur);
					archivo.write(reinterpret_cast<char*>(&Cli),sizeof(Clientes));
					Find = true;
					break;
				}
			}
			archivo.close();
			if(!Find) cout<<"Cliente no encontrado, verifique datos"<<endl;
		}
		void Delete(const char* Cola){
			ifstream archiveIn(Archivo, ios::binary);
			ofstream archiveOut("temp.dat", ios::binary);
			if(!archiveIn || !archiveOut){
				cout<<"No hay archivo para salida"; 
				return;
			}
			Clientes TEP;
			bool eliminado=false;
			while(archiveIn.read(reinterpret_cast<char*>(&TEP), sizeof(Clientes))){
				if(strcmp(TEP.getcedula(),Cola)==0){
					cout<<"Eliminando a.... ->"<<TEP.getNombre()<<endl;
					eliminado = true;
				}else{
					archiveOut.write(reinterpret_cast<char*>(&TEP), sizeof(Clientes));
				}
			}
			archiveIn.close();
			archiveOut.close();
			
			if(eliminado){
				remove(Archivo);
				rename("temp.dat",Archivo);
				cout<<"Eliminacion completa";
			}else{
				cout<<"Cedula no encontrada"<<endl;
				remove("temp.dat");
			}
		}
};
#endif