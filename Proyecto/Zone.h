#ifndef ZONE_H
#define ZONE_H
#include <iostream>
#include <cstring>
using namespace std;
class Zone
{
	private:
		int id;
		char ZonaName[40];
	public:
		Zone(){
			id = 0;
			strcmp(ZonaName,"");
		}
		int getid () const {
			return id;
		}
		const char* getZonaName() const{
			return ZonaName;
		}
		void Ingreso(){
			cout<<"Ingrese el ID de la zona: "; cin>>id;
			cin.ignore();
			
			cout<<"Ingrese el nombre de la zona con este id"; cin.getline(ZonaName,30);
		}
		void Mostrar(){
			cout<<"Zona: "<<ZonaName<<endl;
		}
		void setZonaName(const char* n){
			strncpy(ZonaName,n,39);
			ZonaName[39] = '\0';
		}
};

#endif