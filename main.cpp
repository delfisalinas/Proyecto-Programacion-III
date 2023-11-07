#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "./Estructuras/HashMap/Lista.h"
#include "./Estructuras/Cola.h"
#include "./Estructuras/Pila.h"
#include "string.h"
#include "./Estructuras/Arbolbinario.h"
#include "./Estructuras/HashMap/HashMapList.h"
#include <time.h>
#include <vector>
using namespace std;

//Cantidad total de articulos diferentes
void total_art_dif(){
    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv",ios::in);

    string line;
    int total_art_dif=-1;

    while(getline(archivo,line)){
        total_art_dif++;
    }

    cout<<"Total de articulos diferentes: "<<total_art_dif<<endl;
}

//Contador de columnas en el archivo CSV
int numColumnas(){
    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv",ios::in);
    string line,c;
    int columna;
    getline(archivo,line);

    while(getline(archivo,line)){
        stringstream s(line);
        columna=0;
        while(getline(s,c,',')){
            columna++;
        }
    }
    return columna;
}

//Cantidad total de articulos (Stock total)
void total_art(){
    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv",ios::in);
    string line,grupo,codigo_barras,articulo,stock_por_deposito;
    int numDepositos=numColumnas()-3, cantidad=0;
    getline(archivo,line);

    while(getline(archivo,line)){
        stringstream s(line);
        getline(s,grupo,',');
        getline(s,codigo_barras,',');
        getline(s,articulo,',');

        for(int i=0;i<numDepositos;i++){
            getline(s,stock_por_deposito,',');
            if(!stock_por_deposito.substr(1,stock_por_deposito.size()-2).empty()){
                stock_por_deposito=stock_por_deposito.substr(1,stock_por_deposito.size()-2);
            }else{
                stock_por_deposito="0";
            }
            cantidad+=stoi(stock_por_deposito);
        }

    }

    cout<<"Total de articulos: "<<cantidad<<endl;
}

//Struct de Articulos con operadores sobrecargados para la utilizacion del arbol
struct Articulo {
    string nombre;
    int cantotales;

    friend std::ostream& operator<<(std::ostream& os, const Articulo& objeto) {
        os << ">  " <<  objeto.nombre << endl;
        return os;
    }

    bool operator<(const Articulo& otro) const {
        if (cantotales < otro.cantotales) {
            return true;
        }  else {
            return false;
        }
    }

    bool operator<=(const Articulo& otro) const {
        if (cantotales <= otro.cantotales) {
            return true;
        }  else {
            return false;
        }
    }

    bool operator>(const Articulo& otro) const {
        if (cantotales > otro.cantotales) {
            return true;
        } else {
            return false;
        }
    }

    bool operator>=(const Articulo& otro) const {
        if (cantotales >= otro.cantotales) {
            return true;
        }  else {
            return false;
        }
    }
};


//Listado de articulos con cantidad n o menos de stock
void min_stock(int n){

    ArbolBinario<Articulo> arbol;
    Articulo raiz;
    raiz.nombre="Raiz";
    raiz.cantotales=n;
    arbol.putMin_Stock(raiz);

    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv",ios::in);
    string line,grupo,codigo_barras,articulo,stock_por_deposito;
    int numDepositos=numColumnas()-3;
    getline(archivo,line);

    while(getline(archivo,line)){
        Articulo art;
        int stock_por_articulo=0;
        stringstream s(line);
        getline(s,grupo,',');
        getline(s,codigo_barras,',');
        getline(s,articulo,',');
        articulo=articulo.substr(1,articulo.size()-2);
        art.nombre=articulo;

        for(int i=0;i<numDepositos;i++){
            getline(s,stock_por_deposito,',');
            if(!stock_por_deposito.substr(1,stock_por_deposito.size()-2).empty()){
                stock_por_deposito=stock_por_deposito.substr(1,stock_por_deposito.size()-2);
            }else{
                stock_por_deposito="0";
            }
            stock_por_articulo+=stoi(stock_por_deposito);
        }
        art.cantotales=stock_por_articulo;
        arbol.putMin_Stock(art);
    }
    cout<<"*ARTICULOS*"<<endl;
    arbol.inorderizq();
}


// Listado de artículos con cantidad n o menos de stock según un depósito
void min_stock(int n, int deposito) {
    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv", ios::in);
    string line, grupo, codigo_barras, articulo, stock_por_deposito;
    int numDepositos = numColumnas() - 3;
    Lista<string> minStock;
    getline(archivo, line);

    while(getline(archivo, line)) {
        stringstream s(line);
        getline(s, grupo, ',');
        getline(s, codigo_barras, ',');
        getline(s, articulo, ',');
        articulo = articulo.substr(1, articulo.size() - 2);

        int stock_actual=0;

        for(int i = 0; i < numDepositos; i++) {
            getline(s, stock_por_deposito, ',');
            if(i == (deposito - 1)) {  // Asume que deposito empieza en 1
                if(!stock_por_deposito.substr(1, stock_por_deposito.size() - 2).empty()){
                    stock_por_deposito = stock_por_deposito.substr(1, stock_por_deposito.size() - 2);
                } else {
                    stock_por_deposito = "0";
                }
                stock_actual = stoi(stock_por_deposito);
                break;  // Salir después de obtener el stock del depósito interesado
            }
        }

        if(stock_actual <= n) {
            // minStock.insertarUltimo(articulo);
            cout << "----------------------------------" << endl;
            cout << articulo << endl;
        }
    }

    // Si se necesita imprimir la lista completa descomentar la siguiente línea
    // minStock.printAbajo();
}

unsigned int hashFunc(string clave) {
    unsigned int divisor = 97;
    unsigned int hash = 0;

    for (char i : clave) {
        hash = (hash * 31) + static_cast<unsigned int>(i);
    }

    return hash % divisor;
}

//El stock del articulo en un deposito
void stock(string nombre_articulo,int deposito){

    HashMapList<string,vector<int>> hashMap(100000,hashFunc);

    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv",ios::in);

    string line,stock_por_deposito,nombre,grupo,codigoBarras;
    int numDepositos=numColumnas()-3;
    getline(archivo,line);

    while(getline(archivo,line)){
        stringstream s(line);

        getline(s, grupo, ',');
        getline(s, codigoBarras, ',');
        getline(s, nombre, ',');
        nombre=nombre.substr(1,nombre.size()-2);

        vector<int> stock(numDepositos, 0);

        for(int i=0;i<numDepositos;i++){
            getline(s,stock_por_deposito,',');
            if(!stock_por_deposito.substr(1,stock_por_deposito.size()-2).empty()){
                stock[i]=stoi(stock_por_deposito.substr(1,stock_por_deposito.size()-2));
            }else{
                stock[i]=0;
            }
        }
        hashMap.put(nombre, stock);
    }

    archivo.close();

    Lista<HashEntry<string,vector<int>>>* lista=hashMap.get(nombre_articulo);

    if(lista!=nullptr){
        Nodo<HashEntry<string,vector<int>>>* nodo=lista->getInicio();
        while (nodo!=nullptr) {
            if (nodo->getDato().getClave()==nombre_articulo) {
                vector<int> stock=nodo->getDato().getValor();
                if(deposito<=numDepositos && deposito>0){
                    cout<<"Stock en el deposito"<<deposito<<": "<<stock[deposito-1]<<endl;
                }else if(deposito>numDepositos){
                    cout<<"Deposito "<<deposito<<" no encontrado. Recuerde que hay "<<numDepositos<<" depositos"<<endl;
                }else{
                    cout<<"Deposito "<<deposito<<" no encontrado. No existe tal deposito."<<endl;
                }
                break;
            }
            nodo=nodo->getSiguiente();
        }

        if(nodo==nullptr){
            cout<<"Articulo "<<nombre_articulo<<" no encontrado"<<endl;
        }

    }else {
        cout<<"Articulo "<<nombre_articulo<<" no encontrado"<<endl;
    }
}

// Función para obtener el stock total del artículo ingresado como argumento
void stock(string nombre_articulo) {
    // Crea una instancia de HashMapList con el tamaño y la función hash especificados
    HashMapList<string,vector<int>> hashMap(100000, hashFunc);

    // Abre el archivo CSV en modo lectura
    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv", ios::in);

    // Variables para almacenar las líneas y las palabras del archivo, así como los datos del artículo
    string line, nombre, grupo, codigoBarras, stock_por_deposito;
    int numDepositos = numColumnas() - 3; // Calcula el número de depósitos

    // Lee la primera línea para descartar el encabezado del CSV
    getline(archivo, line);

    // Procesa el archivo línea por línea
    while (getline(archivo, line)) {
        stringstream s(line);

        // Obtiene los datos del artículo del CSV
        getline(s, grupo, ',');
        getline(s, codigoBarras, ',');
        getline(s, nombre, ',');
        nombre = nombre.substr(1, nombre.size() - 2); // Limpia las comillas

        // Vector para almacenar el stock de cada depósito
        vector<int> stock(numDepositos, 0);

        // Recorre cada depósito y almacena el stock
        for (int i = 0; i < numDepositos; i++) {
            getline(s, stock_por_deposito, ',');
            if (!stock_por_deposito.substr(1, stock_por_deposito.size() - 2).empty()) {
                stock[i] = stoi(stock_por_deposito.substr(1, stock_por_deposito.size() - 2));
            }
        }

        // Agrega el artículo y su stock al HashMapList
        hashMap.put(nombre, stock);
    }

    archivo.close(); // Cierra el archivo

    // Obtiene la lista de entradas para el artículo especificado
    Lista<HashEntry<string,vector<int>>>* lista = hashMap.get(nombre_articulo);

    // Si la lista no es nula, procesa las entradas
    if(lista != nullptr) {
        Nodo<HashEntry<string,vector<int>>>* nodo = lista->getInicio();
        int stock_total = 0; // Variable para almacenar el stock total

        // Recorre la lista y suma el stock de cada depósito
        while (nodo != nullptr) {
            if (nodo->getDato().getClave() == nombre_articulo) {
                vector<int> stock = nodo->getDato().getValor();
                for (int cantidad : stock) {
                    stock_total += cantidad;
                }
                break;
            }
            nodo = nodo->getSiguiente();
        }

        // Muestra el stock total del artículo
        cout << "Stock total del articulo " << nombre_articulo << ": " << stock_total << endl;
    } else {
        // Si la lista es nula, significa que el artículo no se encontró
        cout << "Articulo " << nombre_articulo << " no encontrado" << endl;
    }
}

//Listado de aquellos artículos cuyo stock es igual o supera el número n
void max_stock(int n) {

    ArbolBinario<Articulo> arbol;
    Articulo raiz;
    raiz.nombre="Raiz";
    raiz.cantotales=n;
    arbol.putMax_Stock(raiz);

    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv",ios::in);
    string line,grupo,codigo_barras,articulo,stock_por_deposito;
    int numDepositos=numColumnas()-3;
    getline(archivo,line);

    while(getline(archivo,line)){
        Articulo art;
        int stock_por_articulo=0;
        stringstream s(line);
        getline(s,grupo,',');
        getline(s,codigo_barras,',');
        getline(s,articulo,',');
        articulo=articulo.substr(1,articulo.size()-2);
        art.nombre=articulo;

        for(int i=0;i<numDepositos;i++){
            getline(s,stock_por_deposito,',');
            if(!stock_por_deposito.substr(1,stock_por_deposito.size()-2).empty()){
                stock_por_deposito=stock_por_deposito.substr(1,stock_por_deposito.size()-2);
            }else{
                stock_por_deposito="0";
            }
            stock_por_articulo+=stoi(stock_por_deposito);
        }
        art.cantotales=stock_por_articulo;
        arbol.putMax_Stock(art);
    }
    cout<<"*ARTICULOS*"<<endl;
    arbol.inorderizq();
}


int main(int argc, char **argv) {
    clock_t begin;
    cout << "Comenzando a medir Tiempo\n" << endl;
    begin = clock();

    int i;
    string nombreIngresado;


    if(strcmp(argv[1],"-total_art_dif") == 0){
        total_art_dif();

    }else if(strcmp(argv[1],"-total_art")==0){
        total_art();

    }else if(strcmp(argv[1],"-min_stock")==0){
        if(argc>3 && argc<=5){
            if(strcmp(argv[3],",")==0){
                min_stock(stoi(argv[2]),stoi(argv[4]));
            }
        }else{
            min_stock(stoi(argv[2]));
        }

    }else if(strcmp(argv[1],"-stock")==0){
        i=2;
        while(i<argc && strcmp(argv[i],",") != 0){
            nombreIngresado+=argv[i];
            nombreIngresado+=" ";
            i++;
        }
        cout<<nombreIngresado<<endl;
        nombreIngresado=nombreIngresado.substr(0,nombreIngresado.size()-1);
        cout<<nombreIngresado<<endl;

        if(i==argc){
            stock(nombreIngresado);
        }else{
            stock(nombreIngresado,stoi(argv[argc-1]));
        }

    }else if(strcmp(argv[1],"-max_stock")==0){
        max_stock(stoi(argv[2]));

    }else{
        cout<<"ARGUMENTO NO VALIDO"<<endl;
    }

    cout<<endl;
    clock_t end = clock();
    double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
    cout << "Tardo elapsed_secs " << elapsed_secs << "\n" << endl;

    return 0;
}