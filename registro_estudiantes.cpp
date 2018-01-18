// 21 de julio del 2017
// Desarrollado por Jhonathan Salas Segura
// CENDITEL Nodo Mérida
// TDA Persona
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;
// Variables Menu
void Agregar();
void Eliminar();
void Buscar();
void Consultar();
void Modificar();
void Salir();
void Menu();
// Variables Globales
char nombre[30], apellido[30];
int cedula=0, auxCedula=0;
bool encontrado=false;
char auxGrupo[10];

int main(){
    Menu();
    return 0;
    system("PAUSE");
}
void Menu(){
    int opcion=0;
    do{ // Inicio ciclo panel opciones
        cout << "Panel de Opciones" << endl;
        cout << "1.- Agregar" << endl;
        cout << "2.- Eliminar" << endl;
        cout << "3.- Consultar" << endl;
        cout << "4.- Buscar" << endl;
        cout << "5.- Modificar" << endl;
        cout << "6.- Salir" << endl;
        cout << "Que deseas hacer?" << endl;
        cin >> opcion;
        switch(opcion){
        case 1:
            Agregar();
        break;
        case 2:
            Eliminar();
        break;
        case 3:
            Consultar();
        break;
        case 4:
            Buscar();
        break;
        case 5:
            Modificar();
        break;
        case 6:
            Salir();
        break;
        default:
            cout << "Opcion Invalida!" << endl;
        }
    }while(opcion!=6);
    } // Fin do
void Agregar(){
    ofstream escritura;
    ifstream consulta;
    bool repetido=false;
    escritura.open("personas.txt", ios::out|ios::app);
    consulta.open("personas.txt", ios::out|ios::in);
    if(escritura.is_open() && consulta.is_open())
    {
        cout << "Ingresa la cedula del alumno: " << endl;
        cin >> auxCedula;
        consulta >> cedula; // Lectura adelantada
        while(!consulta.eof()){
            consulta >> nombre >> apellido;
            if(cedula==auxCedula){
                cout << "Ya existe un registro con esta Cedula" << endl;
                repetido=true;
                break;
            }
            consulta >> cedula; // Lectura adelantada
        }
        if(repetido==false){
            cout << "Abierto y Agregando Correctamente" << endl;
            cout << "Ingresar nombre: ";
            cin >> nombre;
            cout << "Ingresar apellido: ";
            cin >> apellido;

            escritura << auxCedula <<" "<< nombre <<" "<< apellido <<endl;
            cout << "Registro Agregado" << endl; // Confirmar elaboracion de la accion
        }

    }
    else
    {
        cout << "Error, No se pudo abrir ni crear el archivo" << endl;
    }

    escritura.close();
    consulta.close();
} //Fin Funcion Agregar

void Consultar(){
    ifstream lectura;

    lectura.open("personas.txt", ios::out | ios::in);

    if(lectura.is_open()){

        cout << "Registros del Archivo personas.txt" << endl;
        cout << "_________________________________" << endl;
        lectura >> cedula; // Lectura adelantada
        while(!lectura.eof()){
            lectura >> nombre >> apellido;
            cout << "Cedula: " << cedula << endl;
            cout << "Nombre: " << nombre << endl;
            cout << "Apellido: " << apellido << endl;
            lectura >> cedula; // Lectura adelantada
            cout << "_________________________________" << endl;
        }
    }else{
        cout << "Error, No se pudo abrir ni escribir el archivo" << endl;
    }
    lectura.close();
} //Fin Funcion Consultas

void Eliminar(){
    ofstream aux;
    ifstream lectura;
    encontrado=false;
    int auxCedula=0;
    aux.open("auxiliar.txt",ios::out);
    lectura.open("personas.txt", ios::in);
    if(aux.is_open() && lectura.is_open()){
        cout << "Ingresar la Cedula de la Persona a Eliminar: " << endl;
        cin >> auxCedula;
        lectura >> cedula;
        while(!lectura.eof()){
            lectura >> nombre >> apellido; // Leer los campos
            if(auxCedula==cedula){
                encontrado=true;

                cout << "Registro Eliminado" << endl; // Confirmar elaboracion de la accion
            }else{
               aux << cedula << " " << nombre << " " << apellido << endl;
            }
            lectura >> cedula; // Lectura adelantada
        }
    }else{
        cout << "No se pudo abrir el Archivo, aun no ha sido creado" << endl;
    }
    if (encontrado==false){
        cout << "No se encontro ningun registro con Clave" << auxCedula << endl;
    }
    aux.close();
    lectura.close();
    remove("personas.txt");
    rename("auxiliar.txt", "personas.txt");
} // Fin Funcion Eliminar

void Buscar(){
    ifstream lectura;
    lectura.open("personas.txt", ios::out | ios::in); // Abrir el archivo
    // Validar la apertura del archivo
    encontrado=false;
    if(lectura.is_open()){
        cout << "Ingrese la Cedula de la persona que deseas buscar: ";
        cin >> auxCedula;
        lectura >> cedula; // Lectura adelantada

        while(!lectura.eof()){
            lectura >> nombre >> apellido; // Leeer los campos
            // Comparar cada registro para ver si es encontrado
            if(auxCedula==cedula){
                cout << "_______________________________" << endl;
                cout << "Cedula: " << cedula << endl;
                cout << "Nombre: " << nombre << endl;
                cout << "Apellido: " << apellido << endl;
                cout << "_______________________________" << endl;
                encontrado=true;
            }
            lectura >> cedula; // Lectura adelantada
        }
        if(encontrado==false){
            cout << "No hay registros con la Cedula " << auxCedula << endl;
        }
    }else{
        cout << "No se pudo abrir el archivo, aun no ha sido creado";
    }
    lectura.close();
} // Fin Funcion Buscar

void Modificar(){
    ofstream aux;
    ifstream lectura;
    encontrado=false;
    int auxCedula=0;
    char auxNombre[30], auxApellido[30];
    aux.open("auxiliar.txt",ios::out);
    lectura.open("personas.txt", ios::in);
    if(aux.is_open() && lectura.is_open()){
        cout << "Ingresar la Cedula de la persona a modificar: " << endl;
        cin >> auxCedula;
        lectura >> cedula;
        while(!lectura.eof()){
            lectura >> nombre >> apellido; // Leer los campos
            if(auxCedula==cedula){
                encontrado=true;
                cout << "_______________________________" << endl;
                cout << "Cedula: " << cedula << endl;
                cout << "Nombre: " << nombre << endl;
                cout << "Apellido: " << apellido << endl;
                cout << "_______________________________" << endl;

                // Modificacion Nombre
                cout << "Ingresa el nuevo Nombre de la persona con la Cedula " << cedula << ": ";
                cin >> auxNombre;
                aux << cedula << " " << auxNombre << " " << apellido << endl;
                // Modificacion Apellido
                cout << "Ingresa el nuevo Apellido de la persona con la Cedula " << cedula << ": ";
                cin >> auxApellido;
                aux << cedula << " " << auxNombre << " " << auxApellido << endl;

                cout << "Registro Modificado" << endl; // Confirmar elaboracion de la accion

            }else{
               aux << cedula << " " << nombre << " " << apellido << endl;
            }
            lectura >> cedula; // Lectura adelantada
        }
    }else{
        cout << "No se pudo abrir el Archivo, aun no ha sido creado" << endl;
    }
    if (encontrado==false){
        cout << "No se encontro ningun registro con Clave" << auxCedula << endl;
    }
    aux.close();
    lectura.close();
    remove("personas.txt");
    rename("auxiliar.txt", "personas.txt");
} // Fin Funcion Modificar

void Salir(){
    cout << "Programa Finalizado" << endl;
} // Fin Funcion Salir
