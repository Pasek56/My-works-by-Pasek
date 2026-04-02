#ifndef GESTIONZONA_H
#define GESTIONZONA_H
#include "Zone.h"
#include <iostream>
#include <fstream>
using namespace std;
class GestionZona
{
	private:
		string DataBase;
	public:
		GestionZona(const string archivo){
			DataBase = archivo;
		}
		void registro(){
			Zone z;
			z.Ingreso();

			ofstream Arc(DataBase.c_str(), ios::binary|ios::app);
			if(!Arc){
				cout<<"Problemas con el archivo";
				return;
			}
			Arc.write(reinterpret_cast<char*>(&z),sizeof(Zone));
			Arc.close();
			cout<<"Zona registrada exitosamente";
		}
		void ListaZonas(){
			ifstream Arc2(DataBase.c_str(), ios::binary); 
			if(!Arc2) { 
				cout<<"No hay zonas Registradas>>>>";
				return;
			}
			Zone A;
			while(Arc2.read(reinterpret_cast<char*>(&A),sizeof(Zone))){
				A.Mostrar();
			}
			Arc2.close();
		}
		void Modificar(){
			fstream Arc3(DataBase.c_str(), ios::binary|ios::in|ios::out); 
			if(!Arc3){
				cout<<"Error de archivo";
				return;
			}
			int idS;
			cout<<"Ingrese el id de la zona: "; cin>>idS;
			cin.ignore();
			Zone B;
			bool Find = false;
			
			while(Arc3.read(reinterpret_cast<char*>(&B),sizeof(Zone))){
				if(B.getid() == idS){
					cout<<"Zona Actual: "<<B.getZonaName()<<endl;
					char Buffer[40];
					cout<<"Ingrese el nuevo nombre (Enter para omitir): "; cin.getline(Buffer, sizeof(Buffer));
					if(Buffer[0] != '\0'){
						B.setZonaName(Buffer);
					}
					Arc3.seekp(-static_cast<int>(sizeof(Zone)), ios::cur);
					
					Arc3.write(reinterpret_cast<char*>(&B), sizeof(Zone));
					cout<<"------------[Zona Actualizada]------------";
					Find = true;
					break;
				}
			}
			Arc3.close();
			if(!Find){
				cout<<"Zona no encontrada";
			}
		}
		
};
#endif