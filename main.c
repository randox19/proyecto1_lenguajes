#include "script.h"
#include "registro_aviones.c"
#include "estado_vuelo.c"
#include "estadisticas.c"
#include "cargar_usuarios.c"
#include "reservacion_def.c"

void quitar_Char(char *str, char basura) {

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != basura) dst++;
    }
    *dst = '\0';
}


int main () {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    char usuario[40];
    char contrasenna[40];
    char ptr[200];
    char ptr2[200];
    char comilla[2]="'";
    int bandera;
    bandera=0;


    

    char *server = "localhost"; 
    char *database = "sys";
    char *user="root";
    char *password="root";

    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    FILE *flujo = fopen("usuarios_reporte.txt", "w");
    if (flujo==NULL){
        perror("Error en la creacion del archivo \n\n");
    
    }
    else
    {
        fprintf(flujo,"");
    }
    do{
    printf("\n\t\t ************************************\n");
	printf("\n\t\t             Bienvenido  \n");
	printf("\n\t\t ************************************\n");
    printf("\nIntroduzca su nombre de usuario: "); 
    fgets(usuario,40,stdin );
    printf("\nIntroduzca su contraseña: "); 
    fgets(contrasenna,40,stdin );
    quitar_Char(contrasenna, '\n');
    quitar_Char(usuario, '\n');


    strcpy(ptr,"Select MD5 ('");
    strcpy(ptr2,contrasenna);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr,strcat(ptr,comilla));
    strcpy(ptr2,");");
    strcpy(ptr,strcat(ptr,ptr2));  


    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "\nUsuario o Contraseña incorrectos "); 
        bandera=1;

    }
    else
    {
         
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row==NULL){
            bandera=1;
            fflush(stdout);
            fprintf(stdout, "\nUsuario o Contraseña incorrectos ");       
           
        }
        else
        {
            strcpy(contrasenna,row[0]);
            bandera=0;
            
            
            
        }
   
    mysql_free_result(res);
    }

    strcpy(ptr,"Select * from aerolinea where nombre_usuario ='");
    strcpy(ptr2,usuario);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr,strcat(ptr,comilla));
    strcpy(ptr2," and contrasenna='");
    strcpy(ptr,strcat(ptr,ptr2));  
    strcpy(ptr2,contrasenna);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr,strcat(ptr,comilla));
    strcpy(ptr2,";");
    strcpy(ptr,strcat(ptr,ptr2));  


    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "\nUsuario o Contraseña incorrectos  "); 
        bandera=1;

    }
    else
    {
         
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row==NULL){
            bandera=1;
            fflush(stdout);
            fprintf(stdout, "\nUsuario o Contraseña incorrectos ");       
           
        }
        else
        {
           bandera=0;
        
            
            
        }
    }
    
    
    }while (bandera==1);
    
    mysql_free_result(res);
    mysql_close(conn);
    menu_principal();
    
    
    return 0;
}


void menu_principal(){
	
    int opcion;
    char temp[40];
   
    do{
    printf("\n\t\t ************************************\n");
	printf("\n\t\t            Menu Principal  \n");
	printf("\n\t\t ************************************\n");
    printf ("\n 1.Opciones Generales");
    printf ("\n 2.Opciones Operativas");
    printf ("\n 3.Salir\n");
    printf("\nIntroduzca su opcion del 1 al 3: "); 
    fflush(stdin);
    fgets(temp,40,stdin);
    opcion=atoi(temp);


    switch (opcion)
        {
        case 1: 
            menu_general();
            break;
        case 2: 
            menu_operativo();
            break;
        case 3: 
            break;
        default:
            printf("\nSeleccione una opción del 1-3\n");
            break;
            }
    }while (opcion != 3 );
}
void menu_operativo(){
	
    int opcion;
    char temp[40];
    do{
    printf("\n\t\t ************************************\n");
	printf("\n\t\t            Menu Operativo  \n");
	printf("\n\t\t ************************************\n");
    printf ("\n 1.Registro de Aviones");
    printf ("\n 2.Carga de usuarios");
    printf ("\n 3.Estado de vuelo");
    printf ("\n 4.Estadísticas");
    printf ("\n 5.Volver al menu principal\n");
    printf("\nIntroduzca su opcion del 1 al 5: "); 
    fflush(stdin);
    fgets(temp,40,stdin);
    opcion=atoi(temp);

    switch (opcion)
    {
    case 1: 
        registro_usuarios();
        break;
    case 2: 
        cargar_usuarios();
        break;
    case 3: 
        estado_vuelo();
        break;
    case 4: 
        estadisticas();
        break;
    default:
        break;
    }
    }while (opcion != 5);
    
    

}

void menu_general(){
    int opcion;
    char temp[40];
    do{
    printf("\n\t\t ************************************\n");
	printf("\n\t\t            Menu General  \n");
	printf("\n\t\t ************************************\n");
    printf ("\n 1.Reservación de vuelo");
    printf ("\n 2.Información de reserva");
    printf ("\n 3.Volver al menu principal\n");
    printf("\nIntroduzca su opcion del 1 al 3: "); 
    fflush(stdin);
    fgets(temp,40,stdin);
    opcion=atoi(temp);

    
    switch (opcion)
    {
    case 1: 
        reserv_def();
        break;
    case 2: 
        estado_reserv();
        break;
    default:
        printf("\n Seleccione una opción del 1-3");
        break;
    }
    }while (opcion != 3);
    

}