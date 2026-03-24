#ifndef TRANSPORTE_H
#define TRANSPORTE_H
#include <string>
using namespace std;
class Transporte
{
	private:
		char placa[30];
		char modelo[30];
		char VeterinarioName[20];
		char especialidadVet[20];
		int zonaActual;
		bool ocupado;
		int Hora;
	public:
		Transporte(){
			strcpy(placa, "Pendiente");
			strcpy(modelo, "Sin Modelo");
			strcpy(VeterinarioName, "Sin Asignar");
			strcpy(especialidadVet, "Ninguna");
			zonaActual = 0;
			ocupado = false;
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
			cout<<"Modelo del vehiculo: "; cin.getline(modelo, 20);
			cout<<"Placa del vehiculo: "; cin.getline(placa, 20);
			cout<<"Nombre del veterinario: "; cin.getline(VeterinarioName, 30);
			cout<<"Especialidad: ";
			int opc;
			cout<<"1) Emergencia"<<endl;
			cout<<"2) Chequeo"<<endl;
			cout<<"3) General"<<endl;
			cin>>opc;
			
			cin.ignore();
			if(opc == 1){strcpy(especialidadVet,"Emergencias");}
			if(opc == 2){strcpy(especialidadVet,"Chequeo");}
			if(opc == 3){strcpy(especialidadVet,"Medico General");}
			if(opc > 4){cout<<"Ingrese una opcion valida";}
			zonaActual = 0;
			ocupado = false;
		}
		void Mostrar() const{
			cout<<"----------------------------------"<<endl;
			cout<<"[Unidad: "<<placa<<" Modelo: "<<modelo<<"]"<<endl;
			cout<<"[Veterinario: "<<VeterinarioName<<" Especialidad: "<<especialidadVet<<"]"<<endl;
			cout<<"Edo: "<<(ocupado ? "En servicio":"Disponible");
			cout<<"Zona Asignada: "<<(zonaActual == 0 ? "Sin aignar":to_string(zonaActual))<<endl;
			cout<<"Placa: "<<placa<<endl;
		}
		void edicionTrans(){
			cout<<"Editando Aignacion, Unidad: "<<placa<<endl;
			char buffer[50];
			cout<<"Veterinario Actual: "<<VeterinarioName<<endl;
			cout<<"Nuevo Veterinario: ";
			cin.getline(buffer,50);
			if(strlen(buffer) > 0){
				strncpy(VeterinarioName, buffer, 49);
				VeterinarioName[49] = '\0';
			}
			cout<<"Datos Actualizados"<<endl;
		}
};

#endif