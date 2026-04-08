#ifndef TRANSPORTE_H
#define TRANSPORTE_H
#include <string>
using namespace std;
class Transporte
{
	private:
		char placa[30] = "Pendiente";
		char modelo[30] = "Sin modelo";
		char VeterinarioName[20] = "Sin Asignar";
		char especialidadVet[20] = "Ninguna";
		int zonaActual = 0;
		bool ocupado = false;
		int Hora = 0;
	public:
		Transporte(){
		}
		const char* getespecialidadVet() const {return especialidadVet;}
		const char* getplaca() const{return placa;}
		const char* getmodelo() const{return modelo;}
		const int getzonaActual() {return zonaActual;}
		const bool getocupado() {return ocupado;}
		int getHora() const {return Hora;}
		void setHora(int hour) {Hora = hour;}
		void setzonaActual(int zona) {zonaActual = zona;}
		void setocupado(bool Ocup) {ocupado = Ocup;}
		
		void CaptureData(){
			cout<<"Modelo del vehiculo: "; cin.getline(modelo, sizeof(modelo));
			cout<<"Placa del vehiculo: "; cin.getline(placa, sizeof(placa));
			cout<<"Nombre del veterinario: "; cin.getline(VeterinarioName,sizeof(VeterinarioName));
			cout<<"Especialidad: ";
			int opc;
			cout<<"1) Emergencia"<<endl;
			cout<<"2) Chequeo"<<endl;
			cout<<"3) Medico General"<<endl;
			cin>>opc;
			switch(opc){
				case 1:
					strcpy(especialidadVet,"Emergencias");
					break;
				case 2:
					strcpy(especialidadVet,"Chequeo");
					break;
				case 3:
				strcpy(especialidadVet,"Medico General");
					break;
				default:
					cout<<"Ingrese una opcion valida"<<endl;
			}
			zonaActual = 0;
			ocupado = false;
		}
		void Mostrar() const{
			cout<<"----------------------------------"<<endl;
			cout<<"[Unidad: "<<placa<<" Modelo: "<<modelo<<"]"<<endl;
			cout<<"[Veterinario: "<<VeterinarioName<<" Especialidad: "<<especialidadVet<<"]"<<endl;
			cout<<"Edo: "<<(ocupado ? "En servicio":"Disponible")<<endl;
			cout<<"Zona Asignada: "<<(zonaActual == 0 ? "Sin asignar":to_string(zonaActual))<<endl;
		}
		void edicionTrans(){
			int opc;
			do {
				cout << "\n=== EDITANDO UNIDAD (Placa: " << placa << ") ===\n";
				cout << "1. Modificar Veterinario asigado\n";
				cout << "2. Modificar Especialidad\n";
				cout << "0. Guardar y Salir\n";
				cout << "Seleccione: "; cin >> opc;
				cin.ignore(1000, '\n');
				
				char buffer[50];
				switch(opc){
					case 1:
						cout << "Veterinario Actual: " << VeterinarioName << "\nNuevo Veterinario (Enter para omitir): ";
						cin.getline(buffer, sizeof(buffer));
						if(buffer[0] != '\0') { strncpy(VeterinarioName, buffer, sizeof(VeterinarioName)-1); VeterinarioName[sizeof(VeterinarioName)-1] = '\0'; }
						break;
					case 2:
						cout << "Especialidad Actual: " << especialidadVet << "\n";
						cout << "Nueva Especialidad:\n 1) Emergencias\n 2) Chequeo\n 3) Medico General\n (Cualquier otra para omitir): ";
						int subOpc;
						cin >> subOpc;
						cin.ignore(1000, '\n');
						if(subOpc == 1) strcpy(especialidadVet, "Emergencias");
						else if(subOpc == 2) strcpy(especialidadVet, "Chequeo");
						else if(subOpc == 3) strcpy(especialidadVet, "Medico General");
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