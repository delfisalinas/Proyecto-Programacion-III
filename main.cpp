#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "./Estructuras/HashMap/Lista.h"
#include "string.h"
#include "./Estructuras/Arbolbinario.h"
#include "./Estructuras/HashMap/HashMapList.h"
#include <time.h>
#include <vector>
using namespace std;

/**
 * @brief Calcula y muestra la cantidad total de articulos diferentes listados en el archivo CSV.
 *
 * Esta funcion abre un archivo CSV llamado "Inventariado-Fisico.csv", lee todas las lineas del archivo
 * y cuenta cuantas lineas hay, asumiendo que cada linea representa un articulo diferente.
 * La primera linea, que se espera que sean los encabezados de las columnas, no se cuenta como articulo.
 *
 * @note Se asume que la primera linea del archivo CSV no es un articulo, por lo que el contador comienza en -1.
 */
void total_art_dif(){
    // Creacion de un objeto de archivo de flujo de entrada/salida llamado archivo.
    fstream archivo;

    // Abre el archivo CSV en modo de lectura (ios::in).
    archivo.open("./Inventariado-Fisico.csv",ios::in);

    // Declara una variable string llamada line para almacenar las lineas que se leen del archivo
    string line;

    // Inicializa un contador de articulos diferentes como -1
    // Se inicializa en -1 para compensar la primera linea que contiene encabezados de columna
    int total_art_dif=-1;

    // Ciclo while que se ejecuta hasta que no hayan mas lineas que leer en el archivo
    while(getline(archivo,line)){
        // Incrementa el contador total_art_dif por cada linea leida.
        total_art_dif++;
    }
    // Imprime el total de articulos diferentes en la consola.
    cout<<"Total de articulos diferentes: "<<total_art_dif<<endl;
}

/**
 * @brief Cuenta el numero de columnas en un archivo CSV.
 *
 * Abre y lee la primera linea no vacia del archivo CSV "Inventariado-Fisico.csv".
 * Utiliza esa linea para contar el numero de columnas en el archivo, asumiendo que las columnas
 * estan separadas por comas.
 *
 * @return int El numero de columnas en la primera linea no vacia del archivo CSV.
 * @note Esta funcion solo lee la primera linea no vacia del archivo y cuenta las columnas en esa linea.
 */
int numColumnas(){
    // Creacion de un objeto de flujo de archivo para leer datos.
    fstream archivo;
    // Abre el archivo CSV en modo lectura.
    archivo.open("./Inventariado-Fisico.csv",ios::in);

    // Variables para almacenar las lineas leidas del archivo y el contenido temporal de la columna.
    string line, c;
    // Variable para contar el numero de columnas.
    int columna;

    // Lee la primera linea no vacia del archivo para determinar el numero de columnas.
    getline(archivo, line);

    // Continua leyendo el archivo linea por linea.
    while(getline(archivo, line)){
        // Utiliza stringstream para dividir la linea en columnas basadas en comas.
        stringstream s(line);
        // Inicializa el contador de columnas para la linea actual a 0.
        columna = 0;

        // Lee cada columna de la linea basada en la coma como delimitador.
        while(getline(s, c, ',')){
            // Incrementa el contador de columnas por cada columna encontrada.
            columna++;
        }
    }
    // Retorna el numero total de columnas encontradas.
    return columna;
}

/**
 * @brief Calcula y muestra el total de articulos en stock.
 *
 * Abre el archivo CSV 'Inventariado-Fisico.csv' para leer los datos del inventario.
 * Ignora la primera linea que es el encabezado del archivo. Luego, para cada linea
 * (que representa un articulo), se extraen los valores de stock por deposito y se
 * suman para obtener el total de articulos en stock. Finalmente, muestra el total en consola.
 */
void total_art(){
    fstream archivo; // Variable para manejar el archivo.

    // Abrir el archivo CSV en modo de lectura.
    archivo.open("./Inventariado-Fisico.csv", std::ios::in);

    // Variables para almacenar los datos de cada linea del archivo.
    string line, grupo, codigo_barras, articulo, stock_por_deposito;
    int numDepositos = numColumnas() - 3; // Calcula el numero de depositos leyendo el numero de columnas del archivo y restando las columnas de grupo, codigo de barras y articulo.
    int cantidad = 0; // Variable para acumular la cantidad total de articulos.

    // Leer y descartar la primera linea del archivo que contiene los encabezados.
    getline(archivo, line);

    // Leer el archivo linea por linea.
    while(getline(archivo, line)){
        stringstream s(line); // Usar stringstream para separar los datos por comas.

        // Obtener los valores de grupo, codigo de barras y articulo de la linea actual.
        getline(s, grupo, ',');
        getline(s, codigo_barras, ',');
        getline(s, articulo, ',');

        // Iterar sobre el numero de depositos para obtener el stock por deposito.
        for(int i = 0; i < numDepositos; i++){
            getline(s, stock_por_deposito, ','); // Obtener el stock del deposito actual.

            // Verificar si el stock esta vacio y ajustar en caso de estarlo.
            if(!stock_por_deposito.substr(1, stock_por_deposito.size() - 2).empty()){
                stock_por_deposito = stock_por_deposito.substr(1, stock_por_deposito.size() - 2);
            }else{
                stock_por_deposito = "0"; // Si esta vacio, establecer el stock a 0.
            }

            // Sumar el stock del deposito actual a la cantidad total.
            cantidad += stoi(stock_por_deposito);
        }
    }
    // Mostrar en consola la cantidad total de articulos en stock.
    cout << "Total de articulos: " << cantidad << endl;
}

 /**
 * @brief Estructura de Articulo con operadores sobrecargados.
 *
 * Esta estructura representa un Articulo y tiene operadores sobrecargados
 * para facilitar su manejo dentro de un árbol binario de búsqueda u otras
 * estructuras que requieran comparación y visualización.
 *
 * Es util unicamente en el caso que se usen los arboles para las funciones de min y max stock.
 */
 /*
// Estructura Articulo: Utilizada para manejar artículos dentro de un árbol de búsqueda binario.
struct Articulo {
    string nombre; // Variable para almacenar el nombre del artículo.
    int cantotales; // Variable para almacenar la cantidad total de los artículos.

    // Sobrecarga del operador << para imprimir el nombre del artículo en el flujo de salida.
    friend std::ostream& operator<<(std::ostream& os, const Articulo& objeto) {
        os << ">  " <<  objeto.nombre << endl;
        return os;
    }

    // Sobrecarga del operador < para comparar artículos por cantidad total.
    bool operator<(const Articulo& otro) const {
        return cantotales < otro.cantotales;
    }

    // Sobrecarga del operador <= para comparar si la cantidad total de un artículo es menor o igual a la de otro.
    bool operator<=(const Articulo& otro) const {
        return cantotales <= otro.cantotales;
    }

    // Sobrecarga del operador > para comparar artículos por cantidad total.
    bool operator>(const Articulo& otro) const {
        return cantotales > otro.cantotales;
    }

    // Sobrecarga del operador >= para comparar si la cantidad total de un artículo es mayor o igual a la de otro.
    bool operator>=(const Articulo& otro) const {
        return cantotales >= otro.cantotales;
    }
};
*/

/**
 * @brief Listado de articulos con cantidad n o menos de stock.
 *
 * Esta función analiza el inventario de articulos desde un archivo CSV,
 * crea una lista en donde se almacenan los articulos que tienen una cantidad
 * de stock menor o igual a un valor n especificado y luego imprime la lista.
 *
 * @param n El valor maximo de stock para los articulos a listar.
 */
void min_stock(int n) {
    if (n < 0) {
        // Muestra un mensaje de error si 'n' es negativo y finaliza la función.
        cout << "Número de stock mínimo incorrecto" << endl;
        return;
    }

    // Abre el archivo "Inventariado-Fisico.csv" para lectura.
    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv", ios::in);

    // Declara variables para almacenar valores de cada línea del archivo.
    string line, grupo, codigo_barras, articulo, stock_por_deposito;

    // Calcula el número de depósitos en función del número de columnas en el archivo.
    int numDepositos = numColumnas() - 3;

    // Crea una lista llamada 'minStock' para almacenar los artículos que cumplen con el stock mínimo.
    Lista<string> minStock;

    // Lee la primera linea del archivo que contiene los encabezados y la descarta.
    getline(archivo, line);

    // Lee cada linea del archivo.
    while (getline(archivo, line)) {
        int stock_por_articulo = 0;
        stringstream s(line);

        // Parsea cada elemento de la linea separado por comas.
        getline(s, grupo, ',');
        getline(s, codigo_barras, ',');
        getline(s, articulo, ',');
        articulo = articulo.substr(1, articulo.size() - 2);

        // Itera a traves de los depositos y calcula el stock total por articulo.
        for (int i = 0; i < numDepositos; i++) {
            getline(s, stock_por_deposito, ',');
            if (!stock_por_deposito.substr(1, stock_por_deposito.size() - 2).empty()) {
                stock_por_deposito = stock_por_deposito.substr(1, stock_por_deposito.size() - 2);
            } else {
                stock_por_deposito = "0";
            }
            stock_por_articulo += stoi(stock_por_deposito);
        }
        // Si el stock total por artículo es menor o igual a 'n', agrega el artículo a 'minStock'.
        if (stock_por_articulo <= n) {
            minStock.insertarUltimo(articulo);
        }
    }
    // Muestra los artículos cuyo stock total es menor o igual a 'n'.
    cout << "*ARTICULOS*" << endl;
    minStock.printAbajo();
}


/**
 * @brief Listado de articulos con cantidad n o menos de stock.
 *
 * Esta función analiza el inventario de articulos desde un archivo CSV y
 * crea un arbol binario para organizar los articulos que tienen una cantidad
 * de stock menor o igual a un valor n especificado.
 *
 * @param n El valor maximo de stock para los articulos a listar.
 */
/*
void min_stock(int n) {

    if(n<0){
        cout<<"Numero de stock minimo incorrecto"<<endl;
        return;
    }

    // Creacion del arbol binario para almacenar articulos.
    ArbolBinario<Articulo> arbol;
    Articulo raiz;

    // Configuracion del nodo raiz con el valor minimo de stock y su insercion en el arbol.
    raiz.nombre = "Raiz";
    raiz.cantotales = n;
    arbol.putMin_Stock(raiz);

    // Apertura del archivo CSV para lectura de datos de inventario.
    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv", ios::in);
    string line, grupo, codigo_barras, articulo, stock_por_deposito;

    // Determinacion de la cantidad de depositos a partir del archivo.
    int numDepositos = numColumnas() - 3;
    getline(archivo, line); // Lectura de la linea de encabezado.

    // Procesamiento de cada linea del archivo CSV.
    while (getline(archivo, line)) {
        Articulo art;
        int stock_por_articulo = 0;
        stringstream s(line);

        // Extraccion de los datos de cada articulo.
        getline(s, grupo, ',');
        getline(s, codigo_barras, ',');
        getline(s, articulo, ',');

        // Limpieza y asignacion del nombre del articulo.
        articulo = articulo.substr(1, articulo.size() - 2);
        art.nombre = articulo;

        // Cálculo del stock total por articulo sumando los stocks por deposito.
        for (int i = 0; i < numDepositos; i++) {
            getline(s, stock_por_deposito, ',');
            if (!stock_por_deposito.substr(1, stock_por_deposito.size() - 2).empty()) {
                stock_por_deposito = stock_por_deposito.substr(1, stock_por_deposito.size() - 2);
            } else {
                stock_por_deposito = "0";
            }
            stock_por_articulo += stoi(stock_por_deposito);
        }

        // Actualizacion del total de stock del articulo y su insercion en el arbol.
        art.cantotales = stock_por_articulo;
        arbol.putMin_Stock(art);
    }

    // Impresion del listado de articulos con stock minimo.
    cout << "*ARTICULOS*" << endl;
    arbol.inorderizq();
}
*/
/**
 * @brief Funcion que lista los articulos con cantidad n o menos de stock segun un deposito.
 *
 * La funcion abre un archivo CSV en modo lectura y recorre sus lineas para encontrar
 * aquellos articulos cuyo stock en el deposito indicado es menor o igual al valor n.
 * Almacena los articulos encontrados en una lista e imprime la lista.
 *
 * @param n El numero maximo de unidades en stock para considerar un articulo con stock minimo.
 * @param deposito El indice del deposito a revisar (basado en 1).
 */
void min_stock(int n, int deposito) {
    //Comprobaciones para ver si la cantidad de stock minimo y el deposito ingresado son validos
    if(deposito <=0 || (numColumnas()-3)<deposito){
        cout<<"Deposito inexistente"<<endl;
        return;
    }
    if(n<0){
        cout<<"Numero de stock minimo incorrecto. Pruebe ingresando un numero positivo o 0."<<endl;
        return;
    }

    // Inicializar el archivo para leer los datos del inventario
    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv", ios::in);

    // Declaracion de variables para almacenar la informacion de cada linea del archivo CSV
    string line, grupo, codigo_barras, articulo, stock_por_deposito;

    // Lista para almacenar los articulos con stock minimo
    Lista<string> minStock;

    // Leer la primera linea del archivo CSV que generalmente contiene los encabezados
    getline(archivo, line);

    // Leer cada linea del archivo CSV
    while(getline(archivo, line)) {
        // Usar stringstream para separar los campos por comas
        stringstream s(line);

        // Leer y almacenar cada campo del archivo CSV
        getline(s, grupo, ',');
        getline(s, codigo_barras, ',');
        getline(s, articulo, ',');

        // Se le sacan las comillas al nombre del articulo solamente
        articulo = articulo.substr(1, articulo.size() - 2);

        // Variable para llevar la cuenta del stock actual del articulo
        int stock_actual = 0;

        // Recorrer hasta antes del deposito de interes
        for(int i = 0; i < deposito-1; i++) {
            getline(s, stock_por_deposito, ',');
        }

        // Esta sería la lectura del deposito de interes
        getline(s, stock_por_deposito, ',');

        // Sacar comillas y verificar que no este vacio
        if(!stock_por_deposito.substr(1, stock_por_deposito.size() - 2).empty()){
                    stock_por_deposito = stock_por_deposito.substr(1, stock_por_deposito.size() - 2);
        } else {
            stock_por_deposito = "0";
        }

        // Convertir el stock a entero
        stock_actual = stoi(stock_por_deposito);

        // Verificar si el stock actual es menor o igual a 'n'
        if(stock_actual <= n) {
            //Insertar el articulo en la lista de stock minimo
             minStock.insertarUltimo(articulo);
        }
    }

    // Imprimir toda la lista de stock minimo
    cout << "*ARTICULOS*" << endl;
    minStock.printAbajo();
}


/**
 * @brief Listado de artículos con cantidad n o menos de stock según un depósito.
 *
 * Esta funcion construye un arbol binario de articulos, cada uno con su stock actualizado,
 * de acuerdo con la informacion de un archivo CSV que contiene el inventario fisico.
 * Se asume que la columna de stock de interes se especifica con el parametro 'deposito'.
 *
 * @param n La cantidad total de articulos que representara el nodo raiz del arbol.
 * @param deposito El indice del deposito del cual se quiere obtener el stock, comenzando en 1.
 */
/*
void min_stock(int n, int deposito) {

    //Comprobaciones para ver si la cantidad de stock minimo y el deposito ingresado son validos
    if(deposito <=0 || (numColumnas()-3)<deposito){
        cout<<"Deposito inexistente"<<endl;
        return;
    }

    if(n<0){
        cout<<"Numero de stock minimo incorrecto. Pruebe ingresando un numero positivo o 0."<<endl;
        return;
    }

    // Inicializa el arbol binario para almacenar los articulos.
    ArbolBinario<Articulo> arbol;
    Articulo raiz;
    raiz.nombre = "Raiz";
    raiz.cantotales = n;
    arbol.putMin_Stock(raiz);

    // Abre el archivo CSV para leer los datos del inventario.
    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv", ios::in);
    string line, grupo, codigo_barras, articulo, stock_por_deposito;

    // Calcula el numero de depositos basado en el numero de columnas del archivo.
    int numDepositos = numColumnas() - 3;
    // No cuenta la primera linea del archivo (cabecera).
    getline(archivo, line);

    // Procesa cada linea del archivo CSV.
    while (getline(archivo, line)) {
        Articulo art;
        stringstream s(line);
        // Lee y almacena los datos de cada columna.
        getline(s, grupo, ',');
        getline(s, codigo_barras, ',');
        getline(s, articulo, ',');
        articulo = articulo.substr(1, articulo.size() - 2);
        art.nombre = articulo;
        int stock_actual = 0;

        // Itera sobre el stock de cada deposito para encontrar el stock del deposito deseado.
        for (int i = 0; i < numDepositos; i++) {
            getline(s, stock_por_deposito, ',');
            // Encuentra el stock correspondiente al deposito especificado.
            if (i == (deposito - 1)) {  // Asume que deposito empieza en 1
                // Limpia los datos de stock si no estan vacíos.
                if (!stock_por_deposito.substr(1, stock_por_deposito.size() - 2).empty()) {
                    stock_por_deposito = stock_por_deposito.substr(1, stock_por_deposito.size() - 2);
                } else {
                    stock_por_deposito = "0";
                }
                stock_actual = stoi(stock_por_deposito);
                break;  // Salir despues de obtener el stock del deposito interesado.
            }
        }
        // Actualiza el stock total del articulo y lo inserta en el arbol.
        art.cantotales = stock_actual;
        arbol.putMin_Stock(art);
    }
    // Imprime los articulos en orden.
    cout << "*ARTICULOS*" << endl;
    arbol.inorderizq();
}
*/

/**
 * @brief Funcion de hash que utiliza el metodo de multiplicacion.
 *
 * Esta funcion de hash recorre cada caracter de la cadena dada,
 * utiliza un factor de multiplicacion de 131 y luego suma el valor ASCII
 * del caracter actual al hash acumulado. Finalmente, realiza una operacion
 * modulo con un divisor para obtener el hash final.
 *
 * @param clave La cadena de texto a la cual se le aplicara la funcion de hash.
 * @return El valor de hash resultante como un entero sin signo.
 */
unsigned int hashFunc(string clave) {
    unsigned int hash = 0;

    // Iteramos sobre cada caracter de la cadena 'clave'.
    for (char i : clave) {
        // Calculamos el hash multiplicando el hash actual por 131
        // y luego sumamos el valor ASCII del caracter actual.
        hash = (hash * 131) + static_cast<unsigned int>(i);
    }
//La elección de 131 y el uso de un numero primo son estrategias comunes en la construccion de funciones hash para distribuir
// bien los valores hash y evitar colisiones (cuando dos cadenas diferentes producen el mismo valor hash).
    return hash;
}

/**
 * Obtiene el stock de un articulo en un deposito especifico.
 *
 * @param nombre_articulo El nombre del articulo a buscar.
 * @param deposito El indice del deposito donde buscar el stock.
 */
void stock(string nombre_articulo, int deposito) {
    // Inicializa el hashmap con una capacidad y funcion de hash especifica.
    HashMapList<string,vector<int>> hashMap(100000, hashFunc);

    fstream archivo;
    // Abre el archivo de inventario en modo de lectura.
    archivo.open("./Inventariado-Fisico.csv", std::ios::in);

    string line, stock_por_deposito, nombre, grupo, codigoBarras;
    // Calcula el numero de depositos basado en la cantidad de columnas del archivo.
    int numDepositos = numColumnas() - 3;
    // No se cuenta la primera linea del archivo.
    getline(archivo, line);

    // Procesa el archivo linea por linea.
    while(getline(archivo, line)) {
        stringstream s(line);

        // Lee los datos del producto del archivo CSV.
        getline(s, grupo, ',');
        getline(s, codigoBarras, ',');
        getline(s, nombre, ',');
        nombre = nombre.substr(1, nombre.size() - 2);

        // Inicializa el vector de stock para el articulo.
        vector<int> stock(numDepositos, 0);

        // Llena el vector con el stock por deposito.
        for (int i = 0; i < numDepositos; i++) {
            getline(s, stock_por_deposito, ',');
            if (!stock_por_deposito.substr(1, stock_por_deposito.size() - 2).empty()) {
                stock[i] = stoi(stock_por_deposito.substr(1, stock_por_deposito.size() - 2));
            } else {
                stock[i] = 0;
            }
        }
        // Agrega el articulo al hashmap.
        hashMap.put(nombre, stock);
    }

    // Cierra el archivo de inventario.
    archivo.close();

    // Busca el articulo en el hashmap.
    Lista<HashEntry<string,vector<int>>>* lista = hashMap.get(nombre_articulo);

    if (lista != nullptr) {
        Nodo<HashEntry<string,vector<int>>>* nodo = lista->getInicio();
        while (nodo != nullptr) {
            if (nodo->getDato().getClave() == nombre_articulo) {
                vector<int> stock = nodo->getDato().getValor();
                // Muestra el stock en el deposito si es valido.
                if (deposito <= numDepositos && deposito > 0) {
                    cout << "Stock en el deposito " << deposito << ": " << stock[deposito - 1] << endl;
                } else if (deposito > numDepositos) {
                    cout << "Deposito " << deposito << " no encontrado. Recuerde que hay " << numDepositos << " depositos" << endl;
                } else {
                    cout << "Deposito " << deposito << " no encontrado. No existe tal deposito." <<endl;
                }
                break;
            }
            nodo = nodo->getSiguiente();
        }

        if (nodo == nullptr) {
            cout << "Articulo " << nombre_articulo << " no encontrado" << endl;
        }

    } else {
        cout << "Articulo " << nombre_articulo << " no encontrado" << endl;
    }
}
/**
 * @brief Muestra el stock total de un artículo especifico.
 *
 * Esta función procesa un archivo CSV de inventario y calcula el stock total
 * para un artículo dado. Utiliza una tabla hash para almacenar y acceder
 * a los datos del inventario por nombre de artículo.
 *
 * @param nombre_articulo Nombre del artículo a buscar en el inventario.
 */
void stock(string nombre_articulo) {
    // Crea una instancia de HashMapList con el tamaño y la función hash especificados
    HashMapList<string,vector<int>> hashMap(100000, hashFunc);

    // Abre el archivo CSV en modo lectura
    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv", ios::in);

    // Variables para almacenar las líneas y las palabras del archivo, así como los datos del artículo
    string line, nombre, grupo, codigoBarras, stock_por_deposito;
    int numDepositos = numColumnas() - 3; // Calcula el número de depósitos

    // Lee la primera linea para descartar el encabezado del CSV
    getline(archivo, line);

    // Procesa el archivo linea por linea
    while (getline(archivo, line)) {
        stringstream s(line);

        // Obtiene los datos del articulo del CSV
        getline(s, grupo, ',');
        getline(s, codigoBarras, ',');
        getline(s, nombre, ',');
        nombre = nombre.substr(1, nombre.size() - 2); // Limpia las comillas

        // Vector para almacenar el stock de cada deposito
        vector<int> stock(numDepositos, 0);

        // Recorre cada depósito y almacena el stock
        for (int i = 0; i < numDepositos; i++) {
            getline(s, stock_por_deposito, ',');
            if (!stock_por_deposito.substr(1, stock_por_deposito.size() - 2).empty()) {
                stock[i] = stoi(stock_por_deposito.substr(1, stock_por_deposito.size() - 2));
            }
        }

        // Agrega el articulo y su stock al HashMapList
        hashMap.put(nombre, stock);
    }

    archivo.close(); // Cierra el archivo

    // Obtiene la lista de entradas para el articulo especificado
    Lista<HashEntry<string,vector<int>>>* lista = hashMap.get(nombre_articulo);

    // Si la lista no es nula, procesa las entradas
    if(lista != nullptr) {
        Nodo<HashEntry<string,vector<int>>>* nodo = lista->getInicio();
        int stock_total = 0; // Variable para almacenar el stock total

        // Recorre la lista y suma el stock de cada deposito
        while (nodo != nullptr) {
            if (nodo->getDato().getClave() == nombre_articulo) {
                vector<int> stock = nodo->getDato().getValor();
                for (int cantidad : stock) {
                    stock_total += cantidad;
                }

                // Muestra el stock total del articulo si el stock es mayor que 0
                cout << "Stock total del articulo " << nombre_articulo << ": " << stock_total << endl;
                break;
            }
            nodo = nodo->getSiguiente();
        }


        if (nodo == nullptr) {
            cout << "Articulo " << nombre_articulo << " no encontrado" << endl;
        }

    } else {
        // Si la lista es nula o esta vacia, significa que el articulo no se encontro
        cout << "Articulo " << nombre_articulo << " no existe" << endl;
    }
}



/**
 * @brief Encuentra y muestra los articulos con un stock total mayor o igual al valor especificado.
 *
 * Esta funcion busca y muestra los articulos cuyo stock total es igual o superior al valor 'n' especificado.
 * Lee la informacion de los articulos desde un archivo CSV llamado "Inventariado-Fisico.csv".
 *
 * @param n El stock maximo deseado.
 *
 * La funcion abre el archivo CSV, procesa las lineas de datos, calcula el stock total por artículo
 * y muestra los artículos que cumplen con el stock máximo en la consola.
 *
 * Si 'n' es un numero negativo, se mostrara un mensaje de error y la funcion terminará sin procesar el archivo.
 */
void max_stock(int n) {
    // Validacion de la cantidad de stock maximo ingresado
    if (n < 0) {
        cout << "Número de stock maximo incorrecto. Pruebe ingresando un numero positivo o 0." << endl;
        return;
    }

    // Abre el archivo "Inventariado-Fisico.csv" para lectura.
    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv", ios::in);

    // Declara variables para almacenar valores de cada linea del archivo.
    string line, grupo, codigo_barras, articulo, stock_por_deposito;

    // Calcula el numero de depositos en función del numero de columnas en el archivo.
    int numDepositos = numColumnas() - 3;

    // Crea una lista llamada 'maxStock' para almacenar los articulos que cumplen con el stock maximo.
    Lista<string> maxStock;

    // Lee la primera linea del archivo que contiene los encabezados y la descarta.
    getline(archivo, line);

    // Lee cada linea del archivo.
    while (getline(archivo, line)) {
        int stock_por_articulo = 0;
        stringstream s(line);

        // Parsea cada elemento de la linea separado por comas.
        getline(s, grupo, ',');
        getline(s, codigo_barras, ',');
        getline(s, articulo, ',');

        // Elimina las comillas que rodean el nombre del articulo.
        articulo = articulo.substr(1, articulo.size() - 2);

        // Itera a traves de los depositos y calcula el stock total por articulo.
        for (int i = 0; i < numDepositos; i++) {
            getline(s, stock_por_deposito, ',');
            if (!stock_por_deposito.substr(1, stock_por_deposito.size() - 2).empty()) {
                stock_por_deposito = stock_por_deposito.substr(1, stock_por_deposito.size() - 2);
            } else {
                stock_por_deposito = "0";
            }
            stock_por_articulo += stoi(stock_por_deposito);
        }

        // Si el stock total por articulo es mayor o igual a 'n', agrega el artículo a 'maxStock'.
        if (stock_por_articulo >= n) {
            maxStock.insertarUltimo(articulo);
        }
    }

    // Muestra los articulos cuyo stock total es mayor o igual a 'n'.
    cout << "*ARTICULOS*" << endl;
    maxStock.printAbajo();
}


/**
* @brief Listado de aquellos articulos cuyo stock es igual o supera el numero n.
*
* Esta funcion crea un arbol binario de busqueda para almacenar articulos con
* una cantidad igual o superior al umbral definido por el parametro 'n'.
* Luego procede a abrir y leer un archivo CSV que contiene el inventario,
* procesa cada linea para calcular el stock total de cada articulo y
* lo agrega al arbol si cumple con la condicion de stock.
* Finalmente, imprime el listado de articulos en orden.
*
* @param n El umbral de stock minimo que debe tener un articulo para ser listado.
*/
 /*
void max_stock(int n) {

    //Validacion de la cantidad de stock maximo ingresado
    if(n<0){
        cout<<"Numero de stock maximo incorrecto. Pruebe ingresando un numero positivo o 0."<<endl;
        return;
    }

    // Creacion del arbol binario para almacenar articulos.
    ArbolBinario<Articulo> arbol;
    // Inicializacion de la raiz del arbol.
    Articulo raiz;
    raiz.nombre = "Raiz";
    raiz.cantotales = n;
    // Insertar la raiz en el arbol.
    arbol.putMax_Stock(raiz);

    // Apertura del archivo CSV para leer el inventario.
    fstream archivo;
    archivo.open("./Inventariado-Fisico.csv", ios::in);
    // Variables para procesar cada linea del archivo.
    string line, grupo, codigo_barras, articulo, stock_por_deposito;
    // Calcula la cantidad de depositos leyendo el numero de columnas del archivo.
    int numDepositos = numColumnas() - 3;
    // No se cuenta la primera linea que contiene los encabezados.
    getline(archivo, line);

    // Leer cada linea del archivo para procesar los articulos.
    while (getline(archivo, line)) {
        // Creacion e inicializacion del articulo a procesar.
        Articulo art;
        int stock_por_articulo = 0;
        stringstream s(line);
        // Leer y procesar cada campo del articulo en la linea.
        getline(s, grupo, ',');
        getline(s, codigo_barras, ',');
        getline(s, articulo, ',');
        // Ajuste del nombre del articulo para eliminar comillas.
        articulo = articulo.substr(1, articulo.size() - 2);
        art.nombre = articulo;

        // Procesar el stock de cada deposito.
        for (int i = 0; i < numDepositos; i++) {
            getline(s, stock_por_deposito, ',');
            // Ajustar el stock leido para eliminar comillas y comprobar si no esta vacio.
            if (!stock_por_deposito.substr(1, stock_por_deposito.size() - 2).empty()) {
                stock_por_deposito = stock_por_deposito.substr(1, stock_por_deposito.size() - 2);
            } else {
                stock_por_deposito = "0";
            }
            // Sumar el stock de este deposito al total del articulo.
            stock_por_articulo += stoi(stock_por_deposito);
        }
        // Establecer el stock total del articulo.
        art.cantotales = stock_por_articulo;
        // Insertar el articulo en el arbol si cumple con la condicion de stock.
        arbol.putMax_Stock(art);
    }
    // Imprimir el listado de articulos en orden.
    cout << "*ARTICULOS*" << endl;
    arbol.inorderizq();
}
*/

 int main(int argc, char **argv) {
     // Comienza a medir el tiempo de ejecucion del programa.
     clock_t begin;
     cout << "Comenzando a medir Tiempo\n" << endl;
     begin = clock();

     // Comprueba el primer argumento pasado al programa.
     if (strcmp(argv[1], "-total_art_dif") == 0) {
         if (argc > 2) {
             cout << "Se han agregado argumentos que no corresponden" << endl;
         } else {
             total_art_dif();
         }
     } else if (strcmp(argv[1], "-total_art") == 0) {
         if (argc > 2) {
             cout << "Se han agregado argumentos que no corresponden" << endl;
         } else {
             total_art();
         }
     } else if (strcmp(argv[1], "-min_stock") == 0) {
         // Comprueba si la opcion de linea de comandos es "-min_stock".
         // Comprueba la cantidad de argumentos pasados al programa para la opcion -min_stock.
         if (argc < 3 || argc > 4) {
             // Si hay menos de 3 o más de 4 argumentos, muestra un mensaje de error.
             cout << "ARGUMENTO NO VALIDO" << endl;
         } else if (argc == 3) {
             // Si hay 3 argumentos, se espera que el segundo sea un numero entero.
             try {
                 int num = stoi(argv[2]);
                 // Llama a la funcion min_stock con el valor entero proporcionado.
                 min_stock(num);
             } catch (const std::invalid_argument& e) {
                 // Captura una excepcion si el segundo argumento no es un numero valido.
                 cout << "Ingreso incorrecto. No es un numero valido." << endl;
             }
         } else if (argc == 4) {
             // Si hay 4 argumentos, se esperan dos numeros enteros.
             try {
                 int num = stoi(argv[2]);
                 int dep = stoi(argv[3]);
                 // Llama a la funcion min_stock con los dos valores enteros proporcionados.
                 min_stock(num, dep);
             } catch (const std::invalid_argument& e) {
                 // Captura una excepcion si alguno de los argumentos no es un numero valido.
                 cout << "Ingreso incorrecto. No es un numero valido." << endl;
             }
         }
     } else if (strcmp(argv[1], "-stock") == 0) {
         // Comprueba la cantidad de argumentos pasados al programa para la opción -stock.
         if (argc < 3 || argc > 4) {
             cout << "ARGUMENTO NO VALIDO" << endl;
         } else if (argc == 3) {
             stock(argv[2]);
         } else if (argc == 4) {
             try {
                 int dep = stoi(argv[3]);
                 stock(argv[2], dep);
             } catch (const std::invalid_argument& e) {
                 cout << "Ingreso incorrecto. No es un numero valido." << endl;
             }
         }
     } else if (strcmp(argv[1], "-max_stock") == 0) {
         // Comprueba la cantidad de argumentos pasados al programa para la opcion -max_stock.
         if (argc != 3) {
             cout << "ARGUMENTO NO VALIDO" << endl;
         } else {
             try {
                 int num = stoi(argv[2]);
                 max_stock(num);
             } catch (const std::invalid_argument& e) {
                 cout << "Ingreso incorrecto. No es un numero valido." << endl;
             }
         }
     } else {
         cout << "ARGUMENTO NO VALIDO" << endl;
     }

     cout << endl;
     clock_t end = clock();
     double elapsed_secs = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
     cout << "Tardo elapsed_secs " << elapsed_secs << "\n" << endl;

     return 0;
 }