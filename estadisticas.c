#include "script.h"

void estadisticas(){
    MYSQL *conn;
    MYSQL *conn2;
    MYSQL_RES *res;
    MYSQL_RES *res2;
    MYSQL_ROW row;
    MYSQL_ROW row2;
    
    char *server = "localhost"; 
    char *database = "sys";
    char *user="root";
    char *password="root";
    char temp;
    do{
    conn = mysql_init(NULL);
    conn2 = mysql_init(NULL);
    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    if (!mysql_real_connect(conn2, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn2));
        exit(1);
    }
    
    
    
    printf("\n\t\t ************************************\n");
	printf("\n\t\t             Estadísticas  \n");
	printf("\n\t\t ************************************\n");
    printf ("\n A.Top 3 de vuelos de mayor venta (de mayor a menor)");
    printf ("\n B.Top 3 de vuelos con mayor cantidad de personas (de mayor a menor, incluyendo infantes)");
    printf ("\n C.Volver al menu operativo\n");
    printf("\nIntroduzca su opcion de A a C: "); 
    scanf("%s",&temp);
    
    
    switch (temp)
    {
    case 'A': 
        printf("\nTOP 3 DE VUELOS CON MAYOR VENTA\n");
        if (mysql_query(conn,"CALL sh_top_venta();")){
            fprintf(stderr, "%s\n", mysql_error(conn));
        }
        else
        {
            res = mysql_use_result(conn);
        
            printf("\n ____________ _________");
            printf("\n|Código_Vuelo|Ganancias|");
            printf("\n ------------ ---------");
        
            while ((row = mysql_fetch_row(res)) != NULL){
                printf("\n|%s       |%s     |\n", row[0],row[1]);
            }
                printf("\n");
            res = mysql_use_result(conn);    
        }
        mysql_free_result(res); 
        

        break;
    case 'B': 
        printf("\nTOP 3 DE VUELOS CON MAYOR VENTA\n");
        if (mysql_query(conn2,"CALL sh_top_pasajeros();")){
            fprintf(stderr, "%s\n", mysql_error(conn2));
        }
        else
        {
             
            res2 = mysql_use_result(conn2);
    
            printf("\n ____________ _____________");
            printf("\n|Código_Vuelo|Num_Pasajeros|");
            printf("\n ------------ -------------");
    
            while ((row2 = mysql_fetch_row(res2)) != NULL){
            printf("\n|%s       |%s            |\n", row2[0],row2[1]);
            }
            printf("\n");
            res2 = mysql_use_result(conn2);     
        }
        mysql_free_result(res2); 
        
        break;
    case 'C': 
        break;
    default:
        printf("\n Seleccione una opción de A-C");
        res = mysql_use_result(conn); 
        mysql_free_result(res);
        res2 = mysql_use_result(conn); 
        mysql_free_result(res2);
        mysql_close(conn);
        mysql_close(conn2);
        break;

    }
    }while (temp!='C');
    res = mysql_use_result(conn); 
    mysql_free_result(res);
    res2 = mysql_use_result(conn); 
    mysql_free_result(res2);
    mysql_close(conn);
    mysql_close(conn2);

}