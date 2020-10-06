#include "script.h"

void estado_vuelo(){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    int bandera;
    char temp[40];
    char ptr[200];
    char ptr2[200];
    char comilla[2]="'";

    

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
    

    do{
    printf("\nCÓDIGO DE VUELOS DISPONIBLES\n");
    if (mysql_query(conn,"select distinct codigo_vuelo from detalle_vuelo;")){
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_use_result(conn);
    
    printf("\n ____________");
    printf("\n|Código_Vuelo|");
    printf("\n ------------");
    
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s       |\n", row[0]);
    }
        printf("\n");
    res = mysql_use_result(conn);

    
    printf("\nIntroduzca la el código de vuelo a consultar(unicamente elija uno de la tabla anterior):");
    fflush(stdin);
    fgets(temp,40,stdin);
    quitar_Char(temp, '\n');
    strcpy(ptr,"Select distinct codigo_vuelo from vuelo where codigo_vuelo =");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,";");
    strcpy(ptr,strcat(ptr,ptr2));  


    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "Ese código no esta en la tabla "); 
        bandera=1;

    }
    else
    {
         
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row==NULL){
            bandera=1;
            fflush(stdout);
            fprintf(stdout, "Ese código no esta en la tabla ");       
           
        }
        else
        {
           bandera=0;
        
            
            
        }
    }
    
    mysql_free_result(res);
    }while (bandera==1);
    
    printf("\nSimbología:");
    printf("\nBL: Business libre.");
    printf("\nBO: Business ocupado."); 
    printf("\nSL: Premium Economy libre.");
    printf("\nSO: Premium Economy ocupado.");
    printf("\nEL: Economy libre.");
    printf("\nEO: Economy ocupado.");


    printf("\n _________ _____ ______ ____ ____________");
    printf("\n|DETALLE GRAFICAMENTE DEL ESTADO DE VUELO| ");
    printf("\n --------- ----- ------ ---- ------------\n");

            
    strcpy(ptr,"SELECT fila, tipo_asiento,num_asiento from detalle_vuelo where codigo_vuelo=");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," and fila='A'");
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," ORDER BY fila,num_asiento ASC ;");
    strcpy(ptr,strcat(ptr,ptr2));
    
    
    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "\n%s", mysql_error(conn));

    }

        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row==NULL){
            fflush(stdout);
            fprintf(stdout, "Ese codigo vuelo no cuenta con fila A");       
           
        }
        else
        {
            printf("\nA: ");
            printf(" %s_%s,",row[1],row[2]); 
            while ((row = mysql_fetch_row(res))!=NULL)
            {
                printf(" %s_%s,",row[1],row[2]);    
            }
            printf("\n");
            res = mysql_use_result(conn);
            
        }
    mysql_free_result(res);
    
    strcpy(ptr,"SELECT fila, tipo_asiento,num_asiento from detalle_vuelo where codigo_vuelo=");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," and fila='B'");
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," ORDER BY fila,num_asiento ASC ;");
    strcpy(ptr,strcat(ptr,ptr2));
    
    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "%s", mysql_error(conn));

    }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row==NULL){
            fflush(stdout);
            fprintf(stdout, "Ese codigo vuelo no cuenta con fila B");       
           
        }
        else
        {
            printf("\nB: ");
            printf(" %s_%s,",row[1],row[2]); 
            while ((row = mysql_fetch_row(res))!=NULL)
            {
                printf(" %s_%s,",row[1],row[2]);    
            }
            printf("\n");
            res = mysql_use_result(conn);
                
           
            
            
        }
    mysql_free_result(res);
    
    strcpy(ptr,"SELECT fila, tipo_asiento,num_asiento from detalle_vuelo where codigo_vuelo=");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," and fila='C'");
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," ORDER BY fila,num_asiento ASC ;");
    strcpy(ptr,strcat(ptr,ptr2));
    
    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "%s", mysql_error(conn));

    }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row==NULL){
            fflush(stdout);
            fprintf(stdout, "Ese codigo vuelo no cuenta con fila C");       
           
        }
        else
        {

            printf("\nC: ");
            printf(" %s_%s,",row[1],row[2]); 
            while ((row = mysql_fetch_row(res))!=NULL)
            {
                printf(" %s_%s,",row[1],row[2]);    
            }
            printf("\n");
            res = mysql_use_result(conn);

                
           
            
            
        }
    mysql_free_result(res);
    strcpy(ptr,"SELECT fila, tipo_asiento,num_asiento from detalle_vuelo where codigo_vuelo=");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," and fila='D'");
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," ORDER BY fila,num_asiento ASC ;");
    strcpy(ptr,strcat(ptr,ptr2));
    
    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "%s", mysql_error(conn));

    }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row==NULL){
            fflush(stdout);
            fprintf(stdout, "Ese codigo vuelo no cuenta con fila D");       
           
        }
        else
        {

            printf("\nD: ");
            printf(" %s_%s,",row[1],row[2]); 
            while ((row = mysql_fetch_row(res))!=NULL)
            {
                printf(" %s_%s,",row[1],row[2]);    
            }
            printf("\n");
            res = mysql_use_result(conn);
            mysql_free_result(res);
                
           
            
            
        }
    mysql_free_result(res);
    strcpy(ptr,"SELECT fila, tipo_asiento,num_asiento from detalle_vuelo where codigo_vuelo=");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," and fila='E'");
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," ORDER BY fila,num_asiento ASC ;");
    strcpy(ptr,strcat(ptr,ptr2));
    
    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "%s", mysql_error(conn));

    }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row==NULL){
            fflush(stdout);
            fprintf(stdout, "Ese codigo vuelo no cuenta con fila E");       
           
        }
        else
        {

            printf("\nE: ");
            printf(" %s_%s,",row[1],row[2]); 
            while ((row = mysql_fetch_row(res))!=NULL)
            {
                printf(" %s_%s,",row[1],row[2]);    
            }
            printf("\n");
            res = mysql_use_result(conn);
           
                
           
            
            
        }
    mysql_free_result(res);
    strcpy(ptr,"SELECT fila, tipo_asiento,num_asiento from detalle_vuelo where codigo_vuelo=");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," and fila='F'");
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," ORDER BY fila,num_asiento ASC ;");
    strcpy(ptr,strcat(ptr,ptr2));

    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "%s", mysql_error(conn));

    }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row==NULL){
            fflush(stdout);
            fprintf(stdout, "Ese codigo vuelo no cuenta con fila F");       
           
        }
        else
        {
            printf("\nF: ");
            printf(" %s_%s,",row[1],row[2]); 
            while ((row = mysql_fetch_row(res))!=NULL)
            {
                printf(" %s_%s,",row[1],row[2]);    
            }
            printf("\n");
            res = mysql_use_result(conn);
           
                
           
            
            
        }
   
    strcpy(ptr,"CALL sh_vuelo (");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,");");
    strcpy(ptr,strcat(ptr,ptr2));  


    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "Ese código no esta en la tabla "); 

    }


    res = mysql_use_result(conn);           
    printf("\nDETALLE VUELO\n");
    printf("\n _______________ ______________ ________________ _______________ ___________ _______ ________ _____ ");
    printf("\n| Ciudad_Salida | Salida_Vuelo | Ciudad_Llegada | Llegada_Vuelo | Matricula | Marca | Modelo | Año |");
    printf("\n --------------- -------------- ---------------- --------------- ----------- ------- -------- -----\n");
                
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s|%s|%s|%s|%s|%s|%s|%s|\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7]);
    }
        printf("\n");
    mysql_next_result(conn);
    res = mysql_use_result(conn);
    mysql_next_result(conn);
                
          
    

    strcpy(ptr,"CALL sh_precio_asiento (");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,");");
    strcpy(ptr,strcat(ptr,ptr2));  


    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "Ese código no esta en la tabla "); 

    }


    res = mysql_use_result(conn);             
    printf("\nCATEGORIAS ASIENTOS\n");
    printf("\n _______________ ______________ _______________ ");
    printf("\n| Rango_Asiento | Edad_Rango   | Precio_Asiento| ");
    printf("\n --------------- -------------- --------------- ");
                
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s             |%s             |%s           |\n", row[0], row[1], row[2]);
    }
    printf("\n");
    mysql_next_result(conn);
    res = mysql_use_result(conn);  

    mysql_next_result(conn);
    
    strcpy(ptr,"CALL sh_detalle_reserv_personas (");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,");");
    strcpy(ptr,strcat(ptr,ptr2));  


    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "Ese código no esta en la tabla "); 

    }

    
    res = mysql_use_result(conn);             
    printf("\nDETALLE PERSONA RESERVADO\n");
    printf("\n _______________ _________________ ___________________ _____________ _____________ _____________ ___________________ ");
    printf("\n|id_Reservación |Pasaporte_Cliente| Nombre_Cliente    |Prim_Apellido| Seg_Apellido| Fila_Reserva|Num_Asiento_Reserva|");
    printf("\n --------------- ----------------- ------------------- ------------- ------------- ------------- -------------------\n ");
                
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s              |%s            |%s|%s|%s|%s|%s|\n", row[0], row[1], row[2], row[3],row[4],row[5],row[6]);
    }
    printf("\n");
    mysql_next_result(conn);
    res = mysql_use_result(conn);    


    mysql_next_result(conn);
    strcpy(ptr,"CALL sh_detalle_reserv (");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,");");
    strcpy(ptr,strcat(ptr,ptr2));  


    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "Ese código no esta en la tabla "); 

    }


    res = mysql_use_result(conn);             
    printf("\nDETALLE RESERVADO\n");
    printf("\n _______________ _________________ ___________________ _____________ ");
    printf("\n|id_Reservación |Cantidad_Asientos|Cantidad_Utilizados|Monto_Pagado |");
    printf("\n --------------- ----------------- ------------------- ------------- ");
                
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s              |%s                |%s                  |%s         |\n", row[0], row[1], row[2], row[3]);
    }
    printf("\n");
    res = mysql_use_result(conn);    

        
    printf("\n");
    mysql_free_result(res);
    mysql_close(conn);


}
