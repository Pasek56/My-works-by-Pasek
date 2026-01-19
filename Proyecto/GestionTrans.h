#ifndef GESTIONTRANS_H
#define GESTIONTRANS_H
#include <fstream>
#include <cstdio>
#include <fstream>
#include <iostream>
#include "Transporte.h"
#include "Clientes.h"
using namespace std;

class GestionTrans
{
	private:
		const char* ArchivoDB;
	public:
		GestionTrans(const char* archivo ){
			ArchivoDB = archivo;
		}
		void agregarUnidad(){
			ofstream Archivo(ArchivoDB, ios::binary|ios::app);
			if(!Archivo){
				cout<<"Archivo corrupto o no existente"<<endl;
			}
			Transporte Trans;
			Trans.CaptureData();
			Archivo.write(reinterpret_cast<char*>(&Trans), sizeof(Transporte));
			Archivo.close();
			cout<<"Unidad Registrada!!"<<endl;
		}
		void ListaTransporte(){
			ifstream Archi(ArchivoDB, ios::binary);
			if(!Archi){
				cout<<"Archivo corrupto o inexistente";
			}
			Transporte Porte;
			cout<<"--------LISTA--------";
			while(Archi.read(reinterpret_cast<char*>(&Porte), sizeof(Transporte))){
				Porte.Mostrar();
			}
			Archi.close();
		}
		bool Existe(const char* placa){
			ifstream Archi(ArchivoDB, ios::binary);
			Transporte transporte;
			while(Archi.read(reinterpret_cast<char*>(&transporte), sizeof(Transporte))){
				if(strcmp(transporte.getplaca(), placa)==0){
					Archi.close();
					return true;
				}
			}
			return false;
		}
		void Modificacion(const char* placa){
			fstream Archive(ArchivoDB, ios::binary | ios::in|ios::out);
			if(!Archive){
				cout<<"Error en lectura"<<endl;
			}
			Transporte T;
			bool Findid = false;
			
			while(Archive.read(reinterpret_cast<char*>(&T),sizeof(Transporte))){
				if(strcmp(T.getplaca(),placa)==0){
					T.Mostrar();
					cout<<"-------------Modificar Datos--------------";
					T.edicionTrans();
					
					Archive.seekp(-static_cast<int>(sizeof(Transporte)), ios::cur);
                	Archive.write(reinterpret_cast<char*>(&T), sizeof(Transporte));
                	Findid = true;
                	
                	cout<<">>Unidad Modificada"<<endl;
                	break;
				}
			}
			Archive.close();
			if(!Findid){
				cout<<"Placa no encontrada"<<endl;
			}
		}
		void BorrarTransporte(const char* placa){
			ifstream ArchiveIn(ArchivoDB, ios::binary);
			ofstream ArchiveOut("TempD.dat", ios::binary);
			if(!ArchiveIn) return;
			
			Transporte Tra;
			bool Elimininated = false;
			while(ArchiveIn.read(reinterpret_cast<char*>(&Tra), sizeof(Transporte))){
				if(strcmp(Tra.getplaca(),placa)==0){
					cout<<">>Eliminando unidad: "<<Tra.getplaca()<<endl;
					Elimininated = true;
				}else{
					ArchiveOut.write(reinterpret_cast<char*>(&Tra),sizeof(Transporte));
				}
			}
			ArchiveIn.close();
			ArchiveOut.close();
			
			if(Elimininated){
				remove(ArchivoDB);
				rename("TempD.dat",ArchivoDB);
				cout<<">>Unidad eliminada";
			}else{
				remove("TempD.dat");
				cout<<">>No se encontro la placa";
			}
		}
		void Asignacion(){
			fstream Arc(ArchivoDB, ios::binary|ios::in|ios::out); 
			if(!Arc){
				cout<<"Error de edicion";
				return;
			}
			char PlacaS[20];
			int newIDZone;
			cout<<"\\ Actualizacion De Ubicacion //";
			cout<<"Ingrese la placa: ";
			cin.ignore();
			cin.getline(PlacaS,20);
			Transporte TR;
			bool Finded = false;
			
			while(Arc.read(reinterpret_cast<char*>(&TR),sizeof(Transporte))){
				if(strcmp(TR.getplaca(),PlacaS) == 0){
					cout<<"Actualizando Data---------------"<<endl;
					cout<<"Placa: "<<TR.getplaca();
					cout<<"Zona Actual: "<<TR.getzonaActual()<<endl;
					cout<<"Ingrese la nueva zona del transporte: "; cin>>newIDZone;
					TR.setzonaActual(newIDZone);
					Arc.seekp(-static_cast<int>(sizeof(Transporte)), ios::cur);
					Arc.write(reinterpret_cast<char*>(&TR),sizeof(Transporte));
					cout<<"Unidad Movil Actualizada....."<<endl;
					Finded = true;
					break;
				}
			}
			if(!Finded){
				cout<<">>Error placa inexistente"<<endl;
			}
			Arc.close();
		}
		void Solicitud(){
			fstream Arc4(ArchivoDB, ios::binary|ios::in|ios::out);
			if(!Arc4){
				cout<<"Error de edicion";
				return;
			}
			char CedulaCliente[50];
			int zonaOri;
			int Opc2;
			char Requerimento[20];
			
			cout << "\n--- SOLICITUD DE SERVICIO VETERINARIO ---\n";
	        cout << "Ingrese Cedula del Cliente: "; cin >> CedulaCliente;
	        cout << "ID de Zona donde esta el cliente: "; cin >> zonaOri;
	        cout << "Especialidad requerida:\n";
	        cout << "1. Emergencia\n2. Chequeo\n3. General\nOpcion: ";
	        cin >> Opc2;
	        
	        if(Opc2 == 1) strcpy(Requerimento, "Emergencias");
	        else if(Opc2 == 2) strcpy(Requerimento,"Chequeo");
	        else if(Opc2 == 3) strcpy(Requerimento,"General");
	        else {
	        	cout<<"Ingrese una opcion valida.";
	        	return;
			}
	        
	        Transporte Tr;
	        bool En = false;
	        
	        while(Arc4.read(reinterpret_cast<char*>(&Tr),sizeof(Transporte))){
	        	if(!Tr.getocupado()&&Tr.getzonaActual()==
				zonaOri&&strcmp(Tr.getespecialidadVet(),Requerimento)==0){
					
					ofstream Bitacora("Historial.txt",ios::app);
					Bitacora<<Tr.getplaca()<<" "<< CedulaCliente<<endl;
					
					Bitacora.close();
	        		cout<<"Unidad Disponible Asignada!"<<endl;
	        		cout<<"-----Placa: "<<Tr.getplaca()<<endl;
	        		cout<<"Veterinario: "<<Tr.getespecialidadVet();
	        		cout<<">>>>>Data Guardada en Bitacora<<<<<<"<<endl;
	        		
	        		Tr.setocupado(true);
	        		
	        		Arc4.seekp(-static_cast<int>(sizeof(Transporte)), ios::cur);
	        		
	        		Arc4.write(reinterpret_cast<char*>(&Tr),sizeof(Transporte));
	        		
	        		En=true;
	        		break;
				}
			}
			Arc4.close();
			if (!En) {
	            cout << "\n[SERVICIO DENEGADO]\n";
	            cout << "No hay unidades disponibles de '" << Requerimento<< "' en la Zona " << zonaOri << ".\n";
	            cout << "Por favor intente nuevamente mas tarde.\n";
        	}
		}
		void FinalizarEncargo(){
			fstream Archive(ArchivoDB, ios::binary| ios::in|ios::out);
			if(!Archive) return;
			
			char Plac[10];
			cout<<"¡Finalizacion de Servicio!"<<endl;
			cout<<"Ingrese la placa: "<<endl;
			cin.getline(Plac,10);
			
			Transporte Tr;
			bool Encontrado = false;
			
			while(Archive.read(reinterpret_cast<char*>(&Tr),sizeof(Transporte))){
				if(strcmp(Tr.getplaca(), Plac)==0){
					if(!Tr.getocupado()){
						cout<<"La Unidad ya esta Libre"<<endl;
					}else{
						Tr.setocupado(false);
						Archive.seekp(-static_cast<int>(sizeof(Transporte)),ios::cur);
						Archive.write(reinterpret_cast<char*>(&Tr),sizeof(Transporte));
						cout << ">> Unidad " << Plac << " ahora esta DISPONIBLE"<<endl;
					}
					Encontrado=true;
					break;
				}
			}
			if(!Encontrado) cout << ">> No se encontro la unidad"<<endl;
        	Archive.close();
		}
};
#endif