#ifndef CLIENTES_H
#define CLIENTES_H
#include <iomanip>
#include <cstring>
#include <limits>
#include <iostream>
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
			cout << "Editando... " << Nombre << endl;
	        char Buff[50];
	        cout << "Nuevo Telefono (Enter para mantener actual): ";
	        cin.getline(Buff, sizeof(Buff));
	        if (Buff[0] != '\0') {
				strncpy(tlf, Buff, sizeof(tlf) - 1);
				tlf[sizeof(tlf) - 1] = '\0';
			}
	        cout << "Actualizacion exitosa!!" << endl;
		}
};
#endif