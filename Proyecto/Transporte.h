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
			cout<<"3) General"<<endl;
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
			cout<<"Editando Aignacion, Unidad: "<<placa<<endl;
			char buffer[sizeof(VeterinarioName)];
			cout<<"Veterinario Asignado: "<<VeterinarioName<<endl;
			cout<<"Nuevo Veterinario: ";
			cin.getline(buffer,sizeof(VeterinarioName));
			if(buffer[0] != '\0'){
				strncpy(VeterinarioName, buffer, sizeof(VeterinarioName)-1);
				VeterinarioName[sizeof(VeterinarioName)-1] = '\0';
			}
			cout<<"Datos Actualizados";
		}
};

#endif