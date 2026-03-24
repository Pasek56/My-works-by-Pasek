#ifndef GESTIONTRANS_H
#define GESTIONTRANS_H
#include <fstream>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Transporte.h"
#include "Clientes.h"
#include "Colas.h"
#include "Gestor.h"
using namespace std;

class GestionTrans
{
	private:
		const char* ArchivoDB;
		Colas Cool;
	public:
		GestionTrans(const char* archivo ){
			ArchivoDB = archivo;
		}
		void agregarUnidad(){
			ofstream Archivo(ArchivoDB, ios::binary|ios::app);
			Transporte Trans;
			if(!Archivo){
				cout<<"Archivo corrupto o no existente"<<endl;
			}
			cout << "--- Registro de Nueva Unidad ---" << endl;
			Trans.CaptureData();
			Archivo.write(reinterpret_cast<char*>(&Trans), sizeof(Transporte));
			if (Archivo.good()) {
		        cout << ">> Unidad Registrada Exitosamente!!" << endl;
		    } else {
		        cout << "[!] Error critico al escribir en el disco." << endl;
		    }
		    Archivo.close();
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
			fstream Archive(ArchivoDB, ios::binary|ios::in|ios::out);
			if(!Archive){
				cout<<"Error en lectura"<<endl;
			}
			Transporte T;
			bool Findid = false;
			
			while(Archive.read(reinterpret_cast<char*>(&T),sizeof(Transporte))){
				if(strcmp(T.getplaca(),placa)==0){
					T.Mostrar(); // Muestra datos actuales
		            cout << "-------------Modificar Datos--------------\n";
		            T.edicionTrans(); // Llama a la edición interna del objeto
		            
		            // Reposicionar el puntero de escritura y actualizar el registro
		            Archive.seekp(-static_cast<int>(sizeof(Transporte)), ios::cur);
		            Archive.write(reinterpret_cast<char*>(&T), sizeof(Transporte));
		            
		            Find = true;
		            cout << ">> Unidad Modificada con éxito" << endl;
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
			int newIDZone, NuevaHora;
			cout<<"\\ Asignacion de inicio //";
			cout<<"Ingrese la placa: ";
			cin.getline(PlacaS,20);
			Transporte TR;
			bool Finded = false;
			
			while(Arc.read(reinterpret_cast<char*>(&TR),sizeof(Transporte))){
				if(strcmp(TR.getplaca(),PlacaS) == 0){
					cout << "Asignando unidad " << TR.getplaca() << " a nueva zona fija." << endl;
		            cout << "Nueva Zona: "; cin >> newIDZone;
					do{
						cout<<"Ingrese la hora de llegada: "; cin>>NuevaHora;
						if(NuevaHora >= 0 && NuevaHora <= 2359 && (NuevaHora % 100) <= 59){
							break;
						}
						cout<<"[!] Hora invalida."<<endl;
					}while(true);
					TR.setzonaActual(newIDZone);
					TR.setHora(NuevaHora);
					
					Arc.seekp(-static_cast<int>(sizeof(Transporte)), ios::cur);
					Arc.write(reinterpret_cast<char*>(&TR),sizeof(Transporte));
					cout << ">> Unidad posicionada exitosamente." << endl;
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
			ifstream ArcIn(ArchivoDB, ios::binary);
    		if (!ArcIn) return;
    		
			char CedulaCliente[50];
			int zonaOri, Opc2;
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
	        vector<Transporte> Candidatos;
	        
	        while(ArcIn.read(reinterpret_cast<char*>(&Tr),sizeof(Transporte))){
	        	if(!Tr.getocupado()&&Tr.getzonaActual()==
				zonaOri&&strcmp(Tr.getespecialidadVet(),Requerimento)==0){
					Candidatos.push_back(Tr);
				}
			}
			ArcIn.close();
			if(Candidatos.empty()){
				cout<<"Servicio denegado, no hay Unidades disponibles";
				ArcIn.close();
				return;
			}
			sort(Candidatos.begin(), Candidatos.end(), [](const Transporte& a, Transporte& b){
				return a.getHora() > b.getHora();	
			});
			
			cout << "\nUnidades disponibles en su zona (Ordenadas por llegada):" << endl;
		    for (int i = 0; i < Candidatos.size(); i++) {
		        cout << i + 1 << ". Placa: " << Candidatos[i].getplaca() 
		             << " | Especialidad: " << Candidatos[i].getespecialidadVet()
		             << " | Hora de llegada: " << Candidatos[i].getHora() << " hrs" << endl;
		    }

    		int sel; cin >> sel;
		    if (sel < 1 || sel > Candidatos.size()) {
		        cout << "Seleccion invalida." << endl;
		        ArcIn.close();
		        return;
		    }else if(sel >= 1 && sel <= Candidatos.size()){
		    	AsignarServicio(Candidatos[sel-1].getplaca(),CedulaCliente, zonaOri);
			}
		}
		void AsignarServicio(const char* placa, const char* cedula, int zona) {
		    fstream Arc(ArchivoDB, ios::binary | ios::in | ios::out);
		    Transporte Tr;
		    bool exito = false;
		    while (Arc.read(reinterpret_cast<char*>(&Tr), sizeof(Transporte))) {
		        if (strcmp(Tr.getplaca(), placa) == 0) {
		            Tr.setocupado(true);
		            Arc.seekp(-static_cast<int>(sizeof(Transporte)), ios::cur);
		            Arc.write(reinterpret_cast<char*>(&Tr), sizeof(Transporte));
		            exito = true;
		            break;
		        }
		    }
		    Arc.close();
		    if (exito) {
		        ofstream Bitacora("Historial.txt", ios::app);
		        Bitacora << "Unidad: " << placa << " | Cliente: " << cedula << " | Zona: " << zona << endl;
		        Bitacora.close();
		        cout << "\n[SISTEMA] Unidad " << placa << " vinculada al cliente " << cedula << endl;
		    }
		}
		void FinalizarEncargo(Gestor& Gest){
			fstream Archive(ArchivoDB, ios::binary| ios::in|ios::out);
			if(!Archive) {
				return;
			}
			char Plac[10];
			cout<<"¡Finalizacion de Servicio!"<<endl;
			cout<<"Ingrese la placa: "<<endl;
			cin.getline(Plac,10);
			
			Transporte Tr;
			bool Encontrado = false;
			
			while(Archive.read(reinterpret_cast<char*>(&Tr),sizeof(Transporte))){
				if(strcmp(Tr.getplaca(), Plac)==0){
					Encontrado = true;
					
					if(!Tr.getocupado()){
						cout<<"La Unidad ya esta Libre En: "<<Tr.getzonaActual()<<endl;
					}else{
						int zoneservice = Tr.getzonaActual();						
						Colas& Controller = Gest.getControladorColas();
						Clientes* Next = Controller.NextQue(zoneservice);
						
						if(Next != nullptr){
							cout<<"\n[!] ATENCIÓN: Hay clientes esperando en la zona "<<zoneservice<<endl;
							char respuesta;
							cout<<"El cliente aun necesita el servicio? (S/N): ";cin>>respuesta;
							if(toupper(respuesta) == 'S'){
								Tr.setocupado(true);
								Controller.DeleteofQue(zoneservice);
								cout << ">> Servicio asignado: " << Next->getNombre() << endl;
							}else if(toupper(respuesta)=='N'){
								cout<<"[INFO] No hay clientes en espera en la zona"<<endl;
								liberarUnidad(Tr);
							}
						}
						Archive.seekp(-static_cast<int>(sizeof(Transporte)),ios::cur);
						Archive.write(reinterpret_cast<char*>(&Tr),sizeof(Transporte));
						Archive.flush();
					}                                                               
					break;
				}
			}
			if(!Encontrado) cout << ">> No se encontro la unidad"<<endl;
        	Archive.close();
		}
		void liberarUnidad(Transporte& T) {
		    int NewZone, NewHora;
		    cout << "Procediendo a reubicacion de disponibilidad." << endl;
		    cout << "Ingrese nueva zona de destino: "; cin >> NewZone;
		    
		    do {
		        cout << "Ingrese hora de llegada (HHMM): "; cin >> NewHora;
		        if (NewHora >= 0 && NewHora <= 2359 && (NewHora % 100) <= 59) break;
		        cout << "[!] Hora invalida." << endl;
		    } while (true);
		
		    T.setocupado(false);
		    T.setzonaActual(NewZone);
		    T.setHora(NewHora);
		    cout << ">> Unidad liberada y posicionada en zona " << NewZone << endl;
		}
};
#endif