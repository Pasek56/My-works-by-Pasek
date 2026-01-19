#ifndef CLIENTES_H
#define CLIENTES_H
#include <iomanip>
#include <cstring>
using namespace std;
class Clientes
{
	private: 
		char cedula[13];
		char Nombre[15];
		char tlf[20];
		
		char MascotaName[10];
		char edadMascota[20];
		char raza[19];
	public:
		Clientes(){
			strcpy(edadMascota, "0");
            strcpy(cedula, "");
            strcpy(Nombre, "");
            strcpy(tlf, "");
            strcpy(MascotaName, "");
            strcpy(raza, "");
		}
		const char* getcedula() const {return cedula;}
		const char* getNombre() const{return Nombre;}
		void CapturaData(){
			cin.ignore();
			
			cout<<"Ingrese su cedula: ";cin.getline(cedula,15);
			cout<<"Ingrese su nombre: ";cin.getline(Nombre,50);
			cout<<"Ingrese su numero: ";cin.getline(tlf,30);
			cout<<"Ingrese el nombre de su mascota: ";cin.getline(MascotaName, 10);
			cout<<"Edad del perro: ";cin.getline(edadMascota,10);
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
        }
        
		void DataEdit() {
			cout << "Editando... " << Nombre << endl;
            char Buff[50];
            cout << "Nuevo Nombre (Enter para mantener actual): ";
            cin.getline(Buff, 50);
            if(strlen(Buff) > 0) {
                strcpy(Nombre, Buff);
            }
            cout << "Nuevo Telefono (Enter para mantener actual): ";
            cin.getline(Buff, 20);
            if(strlen(Buff) > 0) {
                strcpy(tlf, Buff);
            }
            
            cout << "Actualizacion exitosa!!" << endl;
		}
};
#endif