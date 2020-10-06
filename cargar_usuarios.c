#include "script.h"

struct usuario
{
    char primera[300];
    char fecha[10];
}usuario[2];



int cargar_usuarios(){
    int contador;
    char coma[2]=",";
    char comilla[2]="'";
    char palabra[len_char];
    char oracion[len_char];

    contador=0;
    
    FILE * flujo = fopen ("usuarios.txt","rb");
    if (flujo == NULL) {
        perror("\nError en la apertura de archivo\n");
        return 1;
    }

    char cadena[200];
    char *token;
    while (feof(flujo)==0)
    {
        fgets(cadena,200, flujo);

        token = strtok(cadena, ",");
        while( token != NULL) {
            if (contador ==7)
            {
                quitar_Char(token, '\n');
                strcpy(palabra,token);
                strcpy(oracion,usuario[0].fecha);
                strcpy(usuario[0].fecha,strcat(oracion,coma));
                strcpy(usuario[0].fecha,strcat(oracion,palabra));
                
                insertar_usuario();
                strcpy(usuario[0].primera, "");
                strcpy(usuario[0].fecha, "");
                contador =0;
            }
            
            else if (contador == 0)
            {
                strcpy(palabra,token);
                strcpy(oracion,usuario[0].primera);
                strcpy(usuario[0].primera,strcat(oracion,palabra));
                contador=contador+1;
            }
            
            else if (contador < 4)
            {
                strcpy(palabra,token);
                strcpy(oracion,usuario[0].primera);
                strcpy(usuario[0].primera,strcat(oracion,coma));
                strcpy(usuario[0].primera,strcat(oracion,comilla));
                strcpy(usuario[0].primera,strcat(oracion,palabra));
                strcpy(usuario[0].primera,strcat(oracion,comilla));
                contador=contador+1;
            }
            
            else if (contador == 4)
            {
                strcpy(palabra,token);
                strcpy(oracion,usuario[0].primera);
                strcpy(usuario[0].primera,strcat(oracion,coma));
                strcpy(usuario[0].primera,strcat(oracion,comilla));
                strcpy(usuario[0].primera,strcat(oracion,palabra));
                contador=contador+1;
            }
                        
            
            else if (contador == 5){
                strcpy(palabra,token);
                strcpy(oracion,usuario[0].fecha);    
                strcpy(usuario[0].fecha,strcat(oracion,palabra));
                contador=contador+1;
            }
            else if (contador > 5)
            {
                strcpy(palabra,token);
                strcpy(oracion,usuario[0].fecha);
                strcpy(usuario[0].fecha,strcat(oracion,coma));
                strcpy(usuario[0].fecha,strcat(oracion,palabra));
                contador=contador+1;
                
            }
                
            

            token = strtok(NULL, ",");
            
        }

    
    }
   
    
    fclose (flujo);
    printf("\nDatos Cargados\n");
    
 
    return 0;
}

void insertar_usuario(){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    FILE *flujo = fopen("usuarios_reporte.txt", "a");
    
    char ptr[200];
    char ptr2[200];
    char coma[2]=",";
    char comilla[2]="'";

    char *server = "localhost"; 
    char *database = "sys";
    char *user="root";
    char *password="root";

    conn = mysql_init(NULL);

    if (flujo==NULL){
        perror("Error en la creacion del archivo \n\n");
    
    }
    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    
    //REALIZA CONSULTAS CRUDS

    // send SQL query /

    
    strcpy(ptr,"Insert into cliente values(");
    strcpy(ptr2,usuario[0].primera);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,"'");
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr,strcat(ptr,coma));
    strcpy(ptr2,"STR_TO_DATE('");
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,usuario[0].fecha);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr,strcat(ptr,comilla));
    strcpy(ptr2,strcat(ptr2,","));
    strcpy(ptr,strcat(ptr,coma));
    strcpy(ptr2,"'%Y,%m,%d'))");
    strcpy(ptr,strcat(ptr,ptr2));
    
    if (mysql_query(conn,ptr)){
        
        fprintf(flujo, "%s in '%s'\n", mysql_error(conn), ptr);
        
    }
    else
    {
        fprintf(flujo, "Se incerto con exito %s \n",ptr);
    }
    
    fflush(flujo);
    fclose(flujo);
    

    res = mysql_use_result(conn);

    // close connection 
    strcpy(ptr,"");
    strcpy(ptr2,"");
    mysql_free_result(res);
    mysql_close(conn);
    

}