#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Reportes.h"
#include "GestionTrans.h"
#include "Gestor.h"
#include "GestionZona.h"
using namespace std;
//Participantes
//Miguel Parada V-31.420.052
void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}
void limpiar() {
    system("cls");
}
void MenuCliente(Gestor& Gest){
	int opc;
	cin.clear();
    char auxCedula[20];
    do {
        limpiar();
        cout << "=== GESTION DE CLIENTES ===\n";
        cout << "1. Registrar Nuevo Cliente\n";
        cout << "2. Listar Todos los Clientes\n";
        cout << "3. Modificar Cliente (Buscar por Cedula)\n";
        cout << "4. Eliminar Cliente\n";
        cout << "0. Volver al Menu Principal\n";
        cout << "Opcion: ";
        cin >> opc;
        cin.ignore();
        switch(opc) {
            case 1:
                limpiar();
                Gest.Registro();
                pausar();
                break;
            case 2:
                limpiar();
                Gest.Lista();
                pausar();
                break;
            case 3:
                limpiar();
                cout << "Ingrese la cedula del cliente a modificar: ";
                cin >> auxCedula;
                Gest.Modificar(auxCedula);
                pausar();
                break;
            case 4:
                limpiar();
                cout << "Ingrese la cedula del cliente a eliminar: ";
                cin >> auxCedula;
                Gest.Delete(auxCedula);
                pausar();
                break;
        }
    } while(opc != 0);
}
void MenuZone(GestionZona& Nega){
	int opc;
    do {
        limpiar();
        cout << "=== GESTION DE ZONAS ===\n";
        cout << "1. Registrar Zona\n";
        cout << "2. Listar Zonas\n";
        cout << "3. Modificar Nombre de Zona\n";
        cout << "0. Volver al Menu Principal\n";
        cout << "Opcion: ";
        cin >> opc;
        cin.ignore(1000, '\n');
        switch(opc) {
            case 1:
                limpiar();
                Nega.registro();
                pausar();
                break;
            case 2:
                limpiar();
                Nega.ListaZonas();
                pausar();
                break;
            case 3:
                limpiar();
                Nega.Modificar(); 
                pausar();
                break;
        }
    } while(opc != 0);
}
void TransMenu(GestionTrans& Tra){
	int opc;
    char auxPlaca[20];

    do {
        limpiar();
        cout << "=== GESTION DE TRANSPORTE (Unidades) ===\n";
        cout << "1. Agregar Unidad Movil\n";
        cout << "2. Listar Flota\n";
        cout << "3. Modificar Unidad (Buscar por Placa)\n";
        cout << "4. Eliminar Unidad\n";
        cout << "0. Volver al Menu Principal\n";
        cout << "Opcion: ";
        cin >> opc;
        cin.ignore();
        switch(opc) {
            case 1:
                limpiar();
                Tra.agregarUnidad();
                pausar();
                break;
            case 2:
                limpiar();
                Tra.ListaTransporte();
                pausar();
                break;
            case 3:
                limpiar();
                cout << "Ingrese la placa a modificar: ";
                cin >> auxPlaca;
                Tra.Modificacion(auxPlaca);
                pausar();
                break;
            case 4:
                limpiar();
                cout << "Ingrese la placa a eliminar: ";
                cin >> auxPlaca;
                Tra.BorrarTransporte(auxPlaca);
                pausar();
                break;
        }
    } while(opc != 0);
}
void OperationMenu(GestionTrans& Gest, Gestor& Cli){
	int opc;
    do {
        limpiar();
        cout << "=== OPERACIONES DIARIAS ===\n";
        cout << "1. Asignar Unidad a Zona\n";
        cout << "2. Solicitar Servicio Veterinario\n";
        cout << "3. Finalizar Servicio (Liberar Unidad)\n";
        cout << "0. Volver al Menu Principal\n";
        cout << "Opcion: ";
        cin >> opc;
        cin.ignore(1000, '\n');
        switch(opc) {
            case 1:
                limpiar();
                Gest.Asignacion(); 
                pausar();
                break;
            case 2:
                limpiar();
                Gest.Solicitud(); 
                pausar();
                break;
            case 3:
                limpiar();
                Gest.FinalizarEncargo(Cli);
                pausar();
                break;
        }
    } while(opc != 0);
}

int main(int argc, char** argv) {
	Gestor gClientes("clientes.dat");
    GestionZona gZonas("zonas.dat");
    GestionTrans gTransporte("transporte.dat");
    Reportes gReportes;
    int OPC;
    do {
        limpiar();
        cout << "======================================\n";
        cout << "      SISTEMA VETERINARIO PET-CODE    \n";
        cout << "======================================\n";
        cout << "1. Gestion de Clientes\n";
        cout << "2. Gestion de Zonas\n";
        cout << "3. Gestion de Transporte\n";
        cout << "4. Operaciones de Servicio\n";
        cout << "5. CERRAR JORNADA (Generar Reporte)\n";
        cout << "0. Salir (Sin procesar reporte)\n";
        cout << "======================================\n";
        cout << "Seleccione una opcion: ";
        cin >> OPC;
        cin.ignore();
        switch(OPC) {
            case 1:
                MenuCliente(gClientes);
                break;
            case 2:
                MenuZone(gZonas);
                break;
            case 3:
                TransMenu(gTransporte);
                break;
            case 4:
                OperationMenu(gTransporte,gClientes);
                break;
            case 5:
                limpiar();
                gReportes.finalizarJornada();
                pausar();
                break;
            case 0:
                cout << "\nSaliendo del sistema...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
                pausar();
        }
    } while(OPC != 0 && OPC != 5);
    return 0;
}