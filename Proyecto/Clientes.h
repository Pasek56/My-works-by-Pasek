#ifndef CLIENTES_H
#define CLIENTES_H
#include <iomanip>
#include <cstring>
#include <limits>
#include <iostream>
#include "GestionZona.h"
class Clientes
{
	private: 
		char cedula[13] = {0};
		char Nombre[15] = {0};
		char tlf[20] = {0};
		int zonaClien = 0;
		char MascotaName[20] = {0};
		char edadMascota[20] = {0};
		char raza[19] = {0};
	public:
		Clientes(){}
		const char* getcedula() const {return cedula;}
		const char* getNombre() const{return Nombre;}
		int getzonaClien() const{return zonaClien;}
		void CapturaData(){
			cout << "Ingrese su nombre: "; 
		    cin.getline(Nombre, 15);
		    
		    cout << "Ingrese su cedula: "; 
		    cin.getline(cedula,13);
		    
		    cout << "Ingrese su numero: "; 
		    cin.getline(tlf, 20);
		
		    cout << "Ingrese el nombre de su mascota: "; 
		    cin.getline(MascotaName, 20);
		
		    cout << "Raza de la mascota: "; 
		    cin.getline(raza, 19);
		
		    cout << "Edad de la mascota: "; 
		    cin.getline(edadMascota, 20);
		
		    cout << "Zona Del Cliente: "; 
		    cin >> zonaClien;
		    cin.ignore(1000, '\n');
			GestionZona gz("zonas.dat");
			if (!gz.ExisteZona(zonaClien)) {
				cout << "[!] La zona " << zonaClien << " no existe. Registrando nueva zona...\n";
				gz.registro();
			}
		}
		static void printHeader() {
			cout << "=======================================================================================================\n";
			cout << left << setw(15) << "Cedula" 
				 << setw(20) << "Nombre" 
				 << setw(20) << "Mascota" 
				 << setw(15) << "Raza" 
				 << setw(10) << "Edad" 
				 << setw(15) << "Telefono"
				 << setw(10) << "Zona" << endl;
			cout << "-------------------------------------------------------------------------------------------------------\n";
		}

		void showDataRow() const {
			cout << left << setw(15) << cedula 
				 << setw(20) << Nombre 
				 << setw(20) << MascotaName 
				 << setw(15) << raza 
				 << setw(10) << edadMascota 
				 << setw(15) << tlf
				 << setw(10) << zonaClien << endl;
		}

		void showData() const{
			printHeader();
			showDataRow();
        }
        
		void DataEdit() {
			int opc;
			do {
				cout << "\n=== EDITANDO CLIENTE (CI: " << cedula << ") ===\n";
				cout << "1. Modificar Nombre\n";
				cout << "2. Modificar Telefono\n";
				cout << "3. Modificar Nombre de Mascota\n";
				cout << "0. Guardar y Salir\n";
				cout << "Seleccione: "; cin >> opc;
				cin.ignore(1000, '\n');
				
				char Buff[50];
				switch(opc) {
					case 1:
						cout << "Nombre Actual: " << Nombre << "\nNuevo Nombre (Enter para omitir): ";
						cin.getline(Buff, sizeof(Buff));
						if(Buff[0] != '\0') { strncpy(Nombre, Buff, sizeof(Nombre)-1); Nombre[sizeof(Nombre)-1] = '\0'; }
						break;
					case 2:
						cout << "Telefono Actual: " << tlf << "\nNuevo Telefono (Enter para omitir): ";
						cin.getline(Buff, sizeof(Buff));
						if(Buff[0] != '\0') { strncpy(tlf, Buff, sizeof(tlf)-1); tlf[sizeof(tlf)-1] = '\0'; }
						break;
					case 3:
						cout << "Mascota Actual: " << MascotaName << "\nNuevo Nombre (Enter para omitir): ";
						cin.getline(Buff, sizeof(Buff));
						if(Buff[0] != '\0') { strncpy(MascotaName, Buff, sizeof(MascotaName)-1); MascotaName[sizeof(MascotaName)-1] = '\0'; }
						break;
					case 0:
						cout << "Saliendo de la edicion..." << endl;
						break;
					default:
						cout << "Opcion invalida." << endl;
				}
			} while(opc != 0);
		}
};
#endif