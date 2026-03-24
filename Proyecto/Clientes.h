#ifndef CLIENTES_H
#define CLIENTES_H
#include <iomanip>
#include <cstring>
#include <limits>
#include <iostream>
class Clientes
{
	private: 
		char cedula[13];
		char Nombre[15];
		char tlf[20];
		int zonaClien;
		char MascotaName[20];
		char edadMascota[20];
		char raza[19];
	public:
		Clientes(){
			memset(cedula, 0, sizeof(cedula));
	        memset(Nombre, 0, sizeof(Nombre));
	        memset(tlf, 0, sizeof(tlf));
	        zonaClien = 0;
	        memset(MascotaName, 0, sizeof(MascotaName));
	        memset(edadMascota, 0, sizeof(edadMascota));
	        memset(raza, 0, sizeof(raza));
		}
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
		}
		void showData() const{
			cout << "--------------------------------------------------" << endl;
        cout << left << setw(15) << "Cedula" 
             << setw(20) << "Nombre" 
             << setw(20) << "Mascota" 
             << setw(20) << "Raza" << endl;
        cout << left << setw(15) << cedula 
             << setw(20) << Nombre 
             << setw(20) << MascotaName 
             << setw(20) << raza << endl;
        cout << "Telefono: " << tlf << endl;
        cout << "Zona Actual: " << zonaClien << endl;
        }
        
		void DataEdit() {
			cout << "Editando... " << Nombre << endl;
	        char Buff[50];
	        cout << "Nuevo Nombre (Enter para mantener actual): ";
	        cin.getline(Buff, 50);
	        if (strlen(Buff) > 0) {
	            strncpy(Nombre, Buff, 14);
	            Nombre[14] = '\0'; 
	        }
	        cout << "Nuevo Telefono (Enter para mantener actual): ";
	        cin.getline(Buff, 20);
	        if (strlen(Buff) > 0) {
	            strncpy(tlf, Buff, 19);
	            tlf[19] = '\0';
	        }
	        cout << "Actualizacion exitosa!!" << endl;
		}
};
#endif