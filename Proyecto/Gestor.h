#ifndef GESTOR_H
#define GESTOR_H
#include "Clientes.h"
#include "Colas.h"
#include "Zone.h"
#include <fstream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
#include <string>
using namespace std;
class Gestor
{
	private:
		string Archivo;
		Colas Co;
	public:
		Gestor(const string& archivo){
			Archivo = archivo;
		}
		Colas& getControladorColas() {
        	return Co;
    	}
		void Registro(){
			Clientes Clien;
			Clien.CapturaData();
			ofstream archivo(Archivo.c_str(), ios::binary | ios::app);
			if(!archivo){
				cerr<<"Archivo corrupto o inexistente"<<endl;
				return;
			}
			archivo.write(reinterpret_cast<const char*>(&Clien), sizeof(Clientes));
			archivo.close();
			
			Co.ColaCliente(Clien);
		}
		void Lista(){                      
			ifstream archivo(Archivo.c_str(),ios::in | ios::binary);
			if(!archivo){
				cerr<<"NO hay clientes......."<<endl;
				return;
			}
			Clientes temp;
			bool Date = false;
			
			temp.printHeader();
			while(archivo.read(reinterpret_cast<char*>(&temp), sizeof(Clientes))){
				temp.showDataRow();
				Date = true;
			}
			
			if(!Date){
				cout<<"El archivo esta vacio"<<endl;
			} else {
				cout << "=======================================================================================================\n";
			}
			
			archivo.close();
			cout << "\n=== ESTADO ACTUAL DE COLAS POR ZONA ===" << endl;
		    int cp;
		    cout << "Ingrese el CP para ver detalle de espera (o 0 para omiter): ";
		    cin >> cp;
		    cin.ignore(1000, '\n');
		    if (cp != 0) {
		        Co.VerCola(cp);
		    }
			//Agregar verificacion si la zona existe o no
			//En caso de no existir, llamar al registro de zonas, usando la varaible
		}
		void Modificar(const char* Search){
			fstream archivo(Archivo.c_str(), ios::binary | ios::in | ios::out);
			if(!archivo) { cout << "Error de archivo.\n"; return; }
			Clientes Cli;
			bool Find = false;
			streampos pos = archivo.tellg();
			while(archivo.read(reinterpret_cast<char*>(&Cli),sizeof(Clientes))){
				
				if(strcmp(Cli.getcedula(), Search) == 0){
					Cli.showData();
					Cli.DataEdit();
					archivo.seekp(pos);
					archivo.write(reinterpret_cast<char*>(&Cli),sizeof(Clientes));
					Find = true;
					break;
				}
			}
			archivo.close();
			if(!Find) cout<<"Cliente no encontrado, verifique datos"<<endl;
		}
		void Delete(const char* Cola){
			ifstream archiveIn(Archivo.c_str(), ios::binary);
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
				remove(Archivo.c_str());
				rename("temp.dat",Archivo.c_str());
				cout<<"Eliminacion completa";
			}else{
				cout<<"Cedula no encontrada"<<endl;
				remove("temp.dat");
			}
		}
};
#endif