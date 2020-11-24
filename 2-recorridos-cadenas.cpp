/******************************************************************************\
 * Curso de Programación 1. Tema 12
 * Autores: Miguel Ángel Latre
 * Última revisión: 24 de noviembre de 2020
 * Resumen: Soluciones a los problemas de Programación 1 planteados en la 
 *          sección «Recorridos de vectores de datos de tipos simples» de
 *          la clase de problemas del tema 12 (recorridos de vectores),
 *          planteados anteriormente en la colección de problemas del tema 10
 *          (cadenas de caracteres).
 * Nota: Este fichero contiene un programa completo que realiza pruebas de las
 *       funciones solicitadas. Este fichero puede compilarse y ejecutarse con
 *       la extensión Run Code de Visual Studio Code, tal y como se hacía en las
 *       prácticas 1 y 2. 
\******************************************************************************/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;


/********************************** Problema 1 ********************************/
/*
 * Pre:  ---
 * Post: Ha devuelto el número de caracteres de la cadena «cad» cuyo valor es el 
 *       de una letra mayúscula o minúscula del alfabeto inglés.
 */
unsigned int contarLetras(const string cad) {
    unsigned int cuenta = 0;
    for (unsigned int i = 0; i < cad.length(); i++) {
        if (isalpha(cad.at(i))) {
            cuenta++;
        }
     }
    return cuenta;
}


/********************************** Problema 2 ********************************/
/*
 * Pre:  Todos los caracteres de «cadena» son letras del alfabeto inglés.
 * Post: Ha devuelto el número de palabras individuales que forman «cadena»
 */
unsigned int numeroPalabrasEnCamelCase(string cadena) {
    if (cadena.length() == 0) {
        return 0;
    }
    else {
        unsigned int numPalabras = 1;
        for (unsigned int i = 0; i < cadena.length() - 1; i++) {
            if (islower(cadena.at(i)) && isupper(cadena.at(i + 1))) {
                numPalabras++;
            }
        }
        return numPalabras;
    }
}


/******************************* Pruebas **************************************/
/*
 * Pre:  ---
 * Post: Ha probado la función contarLetras. Debería escribir 6 veces «true» en 
 *       la pantalla
 */
int pruebaContarLetras() {
    cout << boolalpha;
    cout << (contarLetras("") == 0) << endl;
    cout << (contarLetras("1230--$456") == 0) << endl;
    cout << (contarLetras("A0000") == 1) << endl;
    cout << (contarLetras("1234A") == 1) << endl;
    cout << (contarLetras("   AB   ") == 2) << endl;
    cout << (contarLetras("TodoLetras") == 10) << endl;
    return 0;
}


/*
 * Pre:  ---
 * Post: Ha probado la función contarLetras. Debería escribir 7 veces «true» en 
 *       la pantalla
 */
int pruebaNumeroPalabrasEnCamelCase() {
    cout << boolalpha;
    cout << (numeroPalabrasEnCamelCase("") == 0) << endl;
    cout << (numeroPalabrasEnCamelCase("a") == 1) << endl;
    cout << (numeroPalabrasEnCamelCase("EINA") == 1) << endl;
    cout << (numeroPalabrasEnCamelCase("camelCase") == 2) << endl;
    cout << (numeroPalabrasEnCamelCase("iPad") == 2) << endl;
    cout << (numeroPalabrasEnCamelCase("ArrayIndexOutOfBoundsException") == 6) 
         << endl;
    cout << (numeroPalabrasEnCamelCase("numeroPalabrasEnCamelCase") == 5) 
         << endl;
    return 0;
}


/*
 * Programa que prueba las funciones «contarLetras» y
 * «numeroPalabrasEnCamelCase»
 */
int main() {
    pruebaContarLetras();
    pruebaNumeroPalabrasEnCamelCase();
    return 0;
}