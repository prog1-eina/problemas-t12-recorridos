/********************************************************************************\
 * Curso de Programación 1. Tema 12 (Algoritmos con vectores)
 * Autores: Miguel Ángel Latre
 * Última revisión: 27 de noviembre de 2019
 * Resumen: Soluciones a los problemas de Programación 1 planteados en la clase
 *          de problemas del recorrido de vectores
 * Codificación de caracteres original de este fichero: UTF-8 con BOM
\********************************************************************************/

#include "permiso.h"

/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Ha devuelto el número de permisos de conducir de las primeras «n»
 *       componentes del vector «v» con una cantidad de puntos negativa o igual a 0.
 */
int contarSinPuntos(const Permiso v[], const int n) {
    // Esquema de recorrido del vector, contando permisos sin puntos
    int cuenta = 0;
    for (int i = 0; i < n; i++) {
        if (puntos(v[i]) <= 0) {
            cuenta++;
        }
    }
    return cuenta;
}


/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Ha devuelto el permiso de conducir de entre las primeras «n» componentes del
 *       vector «v» que tiene el menor saldo de puntos.
 */
Permiso peorConductor(const Permiso v[], const int n) {
    // Esquema de búsqueda de un mínimo en el vector, buscando un mínimo
    int indPeor = 0;
    int puntosPeor = puntos(v[0]);
    for (int i = 1; i < n; i++) {
        int puntosI = puntos(v[i]);
        if (puntosI < puntosPeor) {
            indPeor = i;
            puntosPeor = puntosI;
        }
    }
    return v[indPeor];
}


/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Ha devuelto un índice de una componente de entre las primeras «n»
 *       componentes del vector «v» que contiene un permiso con un «puntosBuscados»
 *       puntos, o un valor negativo si no existe ninguno en el vector.
 */
int buscarPorPuntos(const Permiso v[], const int n, const int puntosBuscados) {
    // Esquema de búsqueda sin garantía de éxito
    bool encontrado = false;
    int i = 0;
    while (!encontrado && i < n) {
        if (puntos(v[i]) == puntosBuscados) {
            encontrado = true;
        }
        else {
            i++;
        }
    }
    // Se cumple: encontrado || i >= n

    // Determinación del éxito de la búsqueda y devolución de resultado
    if (encontrado) {
        return i;
    }
    else {
        return -1;
    }
}


/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Ha recorrido las primeras «n» componentes el vector «v» y ha aumentado la
 *       antigüedad de todos los permisos en un mes.
 */
void actualizarMes(Permiso v[], const int n) {
    for (int i = 0; i < n; i++) {
        v[i].antiguedadMeses++;
    }
}


/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Ha recorrido las primeras «n» componentes el vector «v» y, cuando ha
 *       encontrado permisos en ellas correspondientes a conductores que han dejado
 *       de ser noveles (conductores con exactamente 12 meses de antigüedad), les ha
 *       bonificado con 4 puntos.
 *       Ha devuelto el número de permisos de conductores a los que se ha
 *       bonificado por dejar de ser noveles.
 */
int bonificarPorDejarDeSerNovel(Permiso v[], const int n) {
    int cuenta = 0;

    // Recorrido del vector buscando conductores con exactamente 24 meses de
    // antigüedad, bonificándolos con 4 puntos y contándolos.
    for (int i = 0; i < n; i++) {
        if (v[i].antiguedadMeses == MESES_NOVEL) {
            registrarBonificacion(v[i], 4);
            cuenta++;
        }
    }
    return cuenta;
}


/*
 * Pre:  «v» tiene al menos «nV» componentes y el vector «resultado», al menos «nV»
 *       componentes.
 * Post: El vector «resultado» contiene, en sus primeras «nR»
 *       componentes, únicamente aquellos permisos de las primeras «nV» componentes
 *       del vector «v» que tienen un saldo de puntos estrictamente positivo.
 */
void purgar(const Permiso v[], const int nV, Permiso resultado[], int& nR) {
    nR = 0; // Cuenta el número de permisos con puntos positivos y va a servir
            // como cursor para indexar el vector «resultado».

    // Recorrido del vector «v», copiando los permisos con puntos
    // positivos a el vector «resultado».
    for (int i = 0; i < nV; i++) {
        if (puntos(v[i]) > 0) {
            resultado[nR] = v[i];
            nR++;
        }
    }
}


/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Ha devuelto «true» si y solo si las primeras «n» componentes del vector «v»
 *       están ordenadas de forma que los permisos de sus componentes tienen
 *       valores de puntos no decrecientes.
 */
bool estaOrdenadaPorPuntos(const Permiso v[], const int n) {
    /*
     * Resolución del problema como la búsqueda de un par de componentes
     * consecutivas en las que la primera corresponde a un conductor con
     * más puntos que el de la componente siguiente. Si se encuentra tal
     * par, no esta ordenada. En caso contrario, sí está ordenada
     */
    int i = 0;
    int puntosActual = puntos(v[0]);
    bool ordenada = true;
    while (ordenada && i < n - 1) {
        int puntosSiguiente = puntos(v[i + 1]);
        ordenada = puntosActual <= puntosSiguiente;
        i++;
        puntosActual = puntosSiguiente;
    }
    // i >= n-1 || !ordenada
    return ordenada;
}


/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Ha devuelto true si y solo si las primeras «n» componentes del vector «v»
 *       están clasificadas de forma tal que todos los permisos correspondientes a
 *       conductores noveles aparecen primero (en las componentes de índices más
 *       bajos) y todos los correspondientes a conductores experimentados, después
 *       (en las componentes de índices más altos).
 */
bool estaOrdenadaPorNovel(const Permiso v[], const int n) {
    /*
     * Resolución del problema como la búsqueda de un par de componentes
     * consecutivas en las que la primera corresponde a un conductor
     * experimentado y la siguiente a un conductor novel. Si se
     * encuentra tal par, no esta ordenada. En caso contrario, sí está
     * ordenada
     */
    int i = 0;
    bool ordenada = true;
    while (ordenada && i < n - 1) {
        ordenada = !(!esNovel(v[i]) && esNovel(v[i + 1]));
        i++;
    }
    // i >= n-1 || !ordenada
    return ordenada;
}


/*
 * Pre:  uno = A y otro = B
 * Post: uno = B y otro = A
 */
void permutar(Permiso& uno, Permiso& otro) {
    Permiso aux = uno;
    uno = otro;
    otro = aux;
}


/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Las primeras «n» componentes del vector «v» son una permutación de los
 *       permisos que había inicialmente en esas mismas primeras «n» componentes del
 *       vector «v» y están clasificadas de forma que todos los permisos
 *       correspondientes a conductores noveles aparecen primero (en las
 *       componentes de índices más bajos) y todos los correspondientes a
 *       conductores experimentados, después (en las componentes de índices más
 *       altos).
 */
void clasificararPorNovel(Permiso v[], const int n) {
    /*
     * INV1: Todas las componentes de índice menor que «inferior» corresponden a
     *       conductores noveles.
     */
    int inferior = 0;

    /*
     * INV2: Todas las componentes de índice mayor que «superior» corresponden a
     *       conductores experimentados.
     */
    int superior = n - 1;

    /*
     * INV3: Las componentes de índices en el intervalo [inferior, superior]
     *       pueden tener permisos noveles o experimentados.
     */
    while (inferior < superior) {
        // Se cumplen INV1, INV2 e INV3.

        if (esNovel(v[inferior])) {
            /*
             * Como v[inferior] corresponde a un conductor novel, se puede
             * incrementar en 1 el valor de «inferior» y se seguirá cumpliendo
             * INV1.
             */
            inferior++;
        } else if (!esNovel(v[superior])) {
            /*
             * Como v[superior] corresponde a un conductor experimentado, se puede
             * decrementar en 1 el valor de «superior» y se seguirá cumpliendo
             * INV2.
             */
            superior--;
        } else {
            /*
             * Se cumple !esNovel(v[inferior]) && esNovel(v[superior])
             *
             * En la componente de índice «inferior» hay un experimentado y en la
             * de índice «superior» hay un novel. Podemos intercambiarlos,
             * incrementar «inferior», decrementar «superior» y se seguirá
             * cumpliendo INV1 e INV2.
             */
            permutar(v[inferior], v[superior]);
            inferior++;
            superior--;
        }
    }
    /*
     * Al acabar el bucle, se siguen cumpliendo INV1, INV2, INV3.
     * Además, inferior >= superior, con lo que el intervalo [inferior, superior]
     * que se menciona en INV3 se refiere a uno o ningún índice: "Todas las
     * componentes de índice menor que «inferior» corresponden a conductores
     * noveles; todas las componentes de índice mayor que «superior» corresponden
     * a conductores experimentados y en v[inferior] hay un conductor novel o
     * experimentado".
     *
     * Esto quiere decir que se cumple la postcondición: "Todos los permisos
     * correspondientes a conductores noveles aparecen primero (en las componentes
     * de índices más bajas) y todos los correspondientes a conductores
     * experimentados, después (en las componentes de índices más altas)".
     */
}

/*
 * Pre:  «v» tiene al menos «n» componentes.
 * Post: Las primeras «n» componentes del vector «v» son una permutación de los
 *       permisos que había inicialmente en esas mismas primeras «n» componentes del
 *       vector «v» y están ordenadas de forma que tienen valores de puntos no
 *       decrecientes.
 */
void ordenarPorPuntos(Permiso v[], const int n) {
    // Aplica el método de ordenación interna de vectores por selección directa.
    for (int i = 0; i < n - 1; i++) {
        // Determina el índice «iMenor» del menor de los datos almacenados en el
        // subvector v[i, n - 1].
        int iMenor = i;
        for (int j = i + 1; j < n; j++) {
            if (puntos(v[j]) < puntos(v[iMenor])) {
                iMenor = j;
            }
        }

        // Permuta los valores de v[i] y v[iMenor]
        permutar(v[i], v[iMenor]);
    }
}

/*
 * Función main para que el proyecto compile sin errores. Puede utilizarse para
 * escribir un programa de prueba de las funciones anteriores.
 */
int main() {
    return 0;
}