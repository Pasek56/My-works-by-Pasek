#ifndef GESTOR_H
#define GESTOR_H
#include "Clientes.h"
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std;
class Gestor
{
	private:
		const char* Archivo;
	public:
		Gestor(const char* archivo){
			Archivo = archivo;
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
			cout<<"Cliente Registrado"<<endl;
		}
		void Lista(){
			ifstream archivo(Archivo, ios::binary);
			if(!archivo){
				cerr<<"NO hay clientes......."<<endl;
				return;
			}
			Clientes temp;
			while(archivo.read(reinterpret_cast<char*>(&temp), sizeof(Clientes))){
				temp.showData();
			}
			archivo.close();
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
			if(!archiveIn) cout<<"No hay archivo para salida"; return;
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
			remove(Archivo);
			rename("temp.dat",Archivo);
			if(eliminado){
				if(remove(Archivo) != 0){
					cout<<"Error"<<endl;
				}
				if(rename("temp.dat",Archivo) != 0) cout<<"Error"<<endl;
				cout<<"Eliminacion completa";
			}else{
				cout<<"Cedula no encontrada"<<endl;
				remove("temp.dat");
			}
		}
};
#endif