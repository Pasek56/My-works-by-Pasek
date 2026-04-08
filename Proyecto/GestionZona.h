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
			cout<<"Zona registrada exitosamente\n";
			
			char opc;
			cout << "¿Desea conectar esta zona con otra existente? (s/n): "; cin >> opc;
			if(tolower(opc) == 's'){
				ConectarZonas("Grafo.txt", z.getid());
			}
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
			cin.ignore(1000, '\n');
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
		
	bool ExisteZona(int idBuscado) {
			ifstream arc(DataBase.c_str(), ios::binary);
			if(!arc) return false;
			Zone Z;
			while(arc.read(reinterpret_cast<char*>(&Z), sizeof(Zone))) {
				if(Z.getid() == idBuscado) {
					arc.close();
					return true;
				}
			}
			arc.close();
			return false;
		}
		
		void ConectarZonas(const char* archivoGrafo, int idBase = -1) {
			int idOri, idDest, dist;
			cout << "\n=== CONEXION DE ZONAS ===" << endl;
			
			if (idBase != -1) {
				idOri = idBase;
				cout << "Zona de origen fijada a: " << idOri << endl;
			} else {
				cout << "Ingrese el ID de la primera zona (Origen): "; cin >> idOri;
			}
			
			if (!ExisteZona(idOri)) {
				cout << "[!] Error: La zona " << idOri << " no existe en la base de datos." << endl;
				return;
			}
			
			cout << "Ingrese el ID de la segunda zona (Destino): "; cin >> idDest;
			if (!ExisteZona(idDest)) {
				cout << "[!] Error: La zona " << idDest << " no existe en la base de datos." << endl;
				return;
			}
			
			if(idOri == idDest) {
				cout << "[!] Error: No puedes conectar una zona consigo misma." << endl;
				return;
			}
			
			cout << "Ingrese la distancia entre ambas zonas (km): "; cin >> dist;
			if (dist <= 0) {
				cout << "[!] Error: La distancia debe ser mayor a 0." << endl;
				return;
			}
			
			ofstream fileG(archivoGrafo, ios::app);
			if(!fileG) {
				cout << "Error abriendo el archivo de grafos." << endl;
				return;
			}
			
			fileG << idOri << "," << idDest << "," << dist << "\n";
			fileG.close();
			cout << ">> Conexion registrada exitosamente (" << idOri << " <--> " << idDest << " : " << dist << " km)\n";
		}
		
};
#endif