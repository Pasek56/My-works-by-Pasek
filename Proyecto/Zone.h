#ifndef ZONE_H
#define ZONE_H
#include <iostream>
#include <cstring>
using namespace std;
class Zone
{
	private:
		int id = 0;
		char ZonaName[40] = {0};
	public:
		Zone(){
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
			
			cout<<"Ingrese el nombre de la zona con este id"; cin.getline(ZonaName,sizeof(ZonaName));
		}
		void Mostrar(){
			cout<<"Zona: "<<ZonaName<<endl;
			cout<<"ID De zona: "<<id<<endl;
			cout<<"-------------------------"<<endl;
		}
		void setZonaName(const char* n){
			strncpy(ZonaName,n,39);
			ZonaName[39] = '\0';
		}
};

#endif