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
		string ArchivoDB;
	public:
		GestionTrans(const string archivo ){
			ArchivoDB = archivo;
		}
		void agregarUnidad(){
			ofstream Archivo(ArchivoDB.c_str(), ios::binary|ios::app);
			Transporte Trans;
			Trans.CaptureData();
			if(!Archivo){
				cout<<"Archivo corrupto o no existente"<<endl;
			}
			cout << "--- Registro de Nueva Unidad ---" << endl;
			Archivo.write(reinterpret_cast<char*>(&Trans), sizeof(Transporte));
			if (Archivo.good()) {
		        cout << ">> Unidad Registrada Exitosamente!!" << endl;
		    } else {
		        cout << "[!] Error critico al escribir en el disco." << endl;
		    }
		    Archivo.close();
		}
		void ListaTransporte(){
			ifstream Archi(ArchivoDB.c_str(), ios::binary);
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
			ifstream Archi(ArchivoDB.c_str(), ios::binary);
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
			fstream Archive(ArchivoDB.c_str(), ios::binary|ios::in|ios::out);
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
			ifstream ArchiveIn(ArchivoDB.c_str(), ios::binary);
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
				remove(ArchivoDB.c_str());
				rename("TempD.dat",ArchivoDB.c_str());
				cout<<">>Unidad eliminada";
			}else{
				remove("TempD.dat");
				cout<<">>No se encontro la placa";
			}
		}
		void Asignacion(){
			fstream Arc(ArchivoDB.c_str(), ios::binary|ios::in|ios::out); 
			if(!Arc){
				cout<<"Error de edicion";
				return;
			}
			char PlacaS[30];
			int newIDZone, NuevaHora;
			cout<<"\\ Asignacion de inicio //";
			cout<<"Ingrese la placa: ";
			cin.ignore();
			cin.getline(PlacaS,30);
			Transporte TR;
			bool Finded = false;
			
			while(Arc.read(reinterpret_cast<char*>(&TR),sizeof(Transporte))){
				if(strcmp(TR.getplaca(),PlacaS) == 0){
					cout << "Asignando unidad " << TR.getplaca() << " a nueva zona fija." << endl;
		            cout << "Nueva Zona: "; cin >> newIDZone;
					do{
						cout<<"Ingrese la hora de llegada(HHMM): "; cin>>NuevaHora;
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
		void Solicitud(Grafo& grafo){	
			ifstream ArcIn(ArchivoDB, ios::binary);
    		if (!ArcIn) return;
    		
			char CedulaCliente[50];
			int zonaOri, zonaDestino, Opc2;
			char Requerimento[20];
			
			cout << "\n--- SOLICITUD DE SERVICIO VETERINARIO ---\n";
	        cout << "Ingrese Cedula del Cliente: "; cin >> CedulaCliente;
	        cout << "ID de Zona donde esta el cliente (Origen): "; cin >> zonaOri;
	        cout << "ID de Zona a donde se dirige (Destino): "; cin >> zonaDestino;
	        cout << "Especialidad requerida:\n";
	        cout << "1. Emergencia\n2. Chequeo\n3. General\nOpcion: ";
	        cin >> Opc2;
	        
	        if(Opc2 == 1) strcpy(Requerimento, "Emergencias");
	        else if(Opc2 == 2) strcpy(Requerimento,"Chequeo");
	        else if(Opc2 == 3) strcpy(Requerimento,"Medico General");
	        else {
	        	cout<<"Ingrese una opcion valida.";
	        	return;
			}
	        
	        Transporte Tr;
	        vector<Transporte> Candidatos;
	        
	        while(ArcIn.read(reinterpret_cast<char*>(&Tr),sizeof(Transporte))){
	        	if(!Tr.getocupado() && strcmp(Tr.getespecialidadVet(),Requerimento)==0){
					Candidatos.push_back(Tr);
				}
			}
			ArcIn.close();
			if(Candidatos.empty()){
				cout<<"Servicio denegado, no hay Unidades disponibles con esa especialidad.";
				return;
			}
			sort(Candidatos.begin(), Candidatos.end(), [](const Transporte& a, const Transporte& b){
				return a.getHora() < b.getHora();	
			});
			
			cout << "\nUnidades disponibles (Ordenadas por llegada):" << endl;
		    for (int i = 0; i < Candidatos.size(); i++) {
		        cout << i + 1 << ". Placa: " << Candidatos[i].getplaca() 
		             << " | Zona actual: " << Candidatos[i].getzonaActual()
		             << " | Hora de llegada: " << Candidatos[i].getHora() << " hrs" << endl;
		    }

    		int sel; cin >> sel;
		    if (sel < 1 || sel > Candidatos.size()) {
		        cout << "Seleccion invalida." << endl;
		        return;
		    }else {
		    	Transporte seleccionada = Candidatos[sel-1];
		    	int objZona = seleccionada.getzonaActual();
		    	vector<int> rutaBusqueda;
		    	int distBusqueda = 0;
		    	
		    	if (grafo.obtenerRutaMinima(objZona, zonaOri, rutaBusqueda, distBusqueda)) {
		    		cout << "\n--- RUTA PARA BUSCAR AL CLIENTE ---" << endl;
		    		cout << "Secuencia: ";
		    		for (int i = 0; i < rutaBusqueda.size(); i++) {
		    			cout << rutaBusqueda[i] << (i < rutaBusqueda.size() - 1 ? " -> " : "");
					}
					cout << "\nDistancia Total: " << distBusqueda << " km" << endl;
				} else {
					cout << "\n[Advertencia] No hay ruta posible desde la zona de la unidad (" << objZona << ") a la zona del cliente (" << zonaOri << ")." << endl;
				}
				
				vector<int> rutaDestino;
				int distDestino = 0;
				if (grafo.obtenerRutaMinima(zonaOri, zonaDestino, rutaDestino, distDestino)) {
		    		cout << "\n--- RUTA PARA LLEVAR AL DESTINO ---" << endl;
		    		cout << "Secuencia: ";
		    		for (int i = 0; i < rutaDestino.size(); i++) {
		    			cout << rutaDestino[i] << (i < rutaDestino.size() - 1 ? " -> " : "");
					}
					cout << "\nDistancia Total: " << distDestino << " km" << endl;
				} else {
					cout << "\n[Advertencia] No hay ruta posible desde la zona de origen (" << zonaOri << ") a la del destino (" << zonaDestino << ")." << endl;
				}

		    	AsignarServicio(seleccionada.getplaca(), CedulaCliente, zonaDestino); 
			}
		}
		void AsignarServicio(const char* placa, const char* cedula, int zona) {
		    fstream Arc(ArchivoDB, ios::binary | ios::in | ios::out);
		    Transporte Tr;
		    bool exito = false;
		    while (Arc.read(reinterpret_cast<char*>(&Tr), sizeof(Transporte))) {
		        if (strcmp(Tr.getplaca(), placa) == 0) {
		            Tr.setocupado(true);
		            Tr.setzonaActual(zona); // Actualizamos la zona a la del destino final
		            Arc.seekp(-static_cast<int>(sizeof(Transporte)), ios::cur);
		            Arc.write(reinterpret_cast<char*>(&Tr), sizeof(Transporte));
		            exito = true;
		            break;
		        }
		    }
		    Arc.close();
		    if (exito) {
		        ofstream Bitacora("Historial.txt", ios::app);
		        Bitacora << "Unidad: " << placa << " | Cliente: " << cedula << " | Destino final (Zona): " << zona << endl;
		        Bitacora.close();
		        cout << "\n[SISTEMA] Unidad " << placa << " vinculada al cliente " << cedula << ", asignada temporalmente hacia zona " << zona << endl;
		    }
		}
		void FinalizarEncargo(Gestor& Gest){
			fstream Archive(ArchivoDB, ios::binary| ios::in|ios::out);
			if(!Archive) return;
			Clientes clienteEnEspera;
			char Plac[30];
			cin.ignore();
			cout<<"¡Finalizacion de Servicio!"<<endl;
			cout<<"Ingrese la placa: "<<endl;
			cin.getline(Plac,30);
			
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
						bool Next = Controller.NextQue(zoneservice, clienteEnEspera);
						
						if(Next == true){
							cout<<"\n[!] ATENCIÓN: Hay clientes esperando en la zona "<<zoneservice<<endl;
							char respuesta;
							cout<<"El cliente aun necesita el servicio?: ";cin>>respuesta;
							if(toupper(respuesta) == 'S'){
								Tr.setocupado(true);
								Controller.DeleteofQue(zoneservice);
								cout << ">> Servicio asignado: " << clienteEnEspera.getNombre() << endl;
							} else {
								Controller.DeleteofQue(zoneservice);
								cout<<"[INFO] Cliente retirado de la cola. Procediendo a liberar unidad."<<endl;
								liberarUnidad(Tr);
							}
						} else {
							liberarUnidad(Tr);
						}	
						Archive.seekp(-static_cast<int>(sizeof(Transporte)),ios::cur);
						Archive.write(reinterpret_cast<char*>(&Tr),sizeof(Transporte));
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