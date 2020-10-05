//Bibliotecas usadas a lo largo del programa
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <mysql/mysql.h>
#include <stdlib.h>
#define len_char 40

void menu_principal();
/*
Entradas:Ninguna
Salidas: Ninguna
Función: Imprime por medio de caracteres el menu principal.
*/

void menu_general();
/*
Entradas:Ninguna
Salidas: Ninguna
Función: Imprime por medio de caracteres el menu general.
*/
void menu_operativo();
/*
Entradas:Ninguna
Salidas: Ninguna
Función: Imprime por medio de caracteres el menu operativo.
*/
int cargar_usuarios();
/*
Entradas:Ninguna
Salidas: Un entero
Función: Lee el archivo usuarios.txt lo extrae los datos por medios de comas y los modifica para que después se realice el ingreso.
*/
void insertar_usuario();
/*
Entradas:Ninguna
Salidas: Ninguna
Función: Una vez extraido los datos esta función se encarga de ingresarlos a la base de datos
*/
void registro_usuarios();
/*
Entradas:Ninguna
Salidas: Ninguna
Función: Imprime por medio de caracteres el menu para las consultas de el registro de aviones.
*/
void quitar_Char(char *str, char basura);
/*
Entradas:Ninguna
Salidas: Ninguna
Función: Quita un caracter específico a una cadena.
*/
void agregar_avion ();
/*
Entradas:Ninguna
Salidas: Ninguna
Función: Agrega un avión con los datos necesarios para el mismo, valida que no sea un avión repetido o existente.
*/
void eliminar_avion();
/*
Entradas:Ninguna
Salidas: Ninguna
Función: Elimina un avión en específico, valida que no tenga un vuelo asociado.
*/
void filtrar_aviones();
/*
Entradas:Ninguna
Salidas: Ninguna
Función: Filtra los aviones por medio de marca, dando como resultado una tabla con todos los modelos y especificaciones de esa marca.
*/
void estado_vuelo();
/*
Entradas:Ninguna
Salidas: Ninguna
Función: Imprime el estado del vuelo graficamente y muestra especificaciones del mismo vuelo junto con que pasajeros cuenta.
*/
void estadisticas();
/*
Entradas:Ninguna
Salidas: Ninguna
Función: Imprime las 2 estadisticas, una con el top 3 de los vuelos que más dinero han recaudado y otra con los vuelos por la cantidad de pasajeros.
*/
void reserv_def();
/*
Entradas:Ninguna
Salidas: Ninguna
Función: Crea un formato para la introdución de la reserva, además valida que el formato y especificaciones estén acordes para que seguidamente se le ingrese
los datos captados a la base de datos, también genera un informe de la reserva por medio de un nombre que se le brinda.
*/

void estado_reserv();
/*
Entradas:Ninguna
Salidas: Ninguna
Función: Imprime el último informe de la última reserva realizada
*/
