#include "script.h"

char id_reserv[3];

void reserv_def(){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    int error=0;

    int bandera=0;
    char entrada_asiento[200];
    char entrada_pasaporte[200];
    char temp[40];
    char ptr[200];
    char ptr2[200];

    char * token_pasaportes;
    char extraido[40];
    int formato_incorrecto=0;
    int pasaporte_duplicado=0;
    int formato_incorrecto_p=0;

    char pasaporte[20];
    int num_asientos_int;


    char * token_asientos;
    int contador=0;
    char fila[3];
    char num_asi[2];
    char num_asi2[2];
    char tipo[3];
    int asiento_ocupado=0;
    int asiento_duplicado=0;
    char coma[2]=",";
    char comilla[2]="'";
    char num_asientos_A[3];
    char num_asientos_totales[2];
    
    char tipo_aux[3];
    
    char comprobante[200];
    char comprobante_pdf[200];
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
    
    if (mysql_query(conn,"truncate table temp_entradas_asiento;")){
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    mysql_close(conn);
    
    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn,"truncate table temp_entradas_pasaporte;")){
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    mysql_close(conn);
    
    do{

    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    printf("\nCÓDIGO DE VUELOS DISPONIBLES\n");
    if (mysql_query(conn,"select distinct codigo_vuelo from detalle_vuelo;")){
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_use_result(conn);
//PRIMERA PARTE CONSULTA   
    
    printf("\n ____________");
    printf("\n|Código_Vuelo|");
    printf("\n ------------");
    
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s       |\n", row[0]);
    }
        printf("\n");
    res = mysql_use_result(conn);
    mysql_free_result(res);
    mysql_close(conn);
    
    printf("\nIntroduzca la el código de vuelo a consultar(unicamente elija uno de la tabla anterior):");
    fflush(stdin);
    fgets(temp,40,stdin);
    quitar_Char(temp, '\n');

    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
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
    else {
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
    mysql_close(conn);
    
    

}while (bandera==1);
//Printea el menu
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

    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

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
        
    }
    mysql_free_result(res);
    mysql_close(conn);  

    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    strcpy(ptr,"SELECT fila, tipo_asiento,num_asiento from detalle_vuelo where codigo_vuelo=");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," and fila='B'");
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
        
    }
    mysql_free_result(res);
    mysql_close(conn);  
   
   
    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    strcpy(ptr,"SELECT fila, tipo_asiento,num_asiento from detalle_vuelo where codigo_vuelo=");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," and fila='C'");
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
        
        
    }
    mysql_free_result(res);
    mysql_close(conn);  
    

    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    strcpy(ptr,"SELECT fila, tipo_asiento,num_asiento from detalle_vuelo where codigo_vuelo=");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," and fila='D'");
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
    
        
    }
    mysql_free_result(res);  
    mysql_close(conn);


    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    strcpy(ptr,"SELECT fila, tipo_asiento,num_asiento from detalle_vuelo where codigo_vuelo=");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," and fila='E'");
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
    
        
    }
    mysql_free_result(res);  
    mysql_close(conn);



    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    strcpy(ptr,"SELECT fila, tipo_asiento,num_asiento from detalle_vuelo where codigo_vuelo=");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," and fila='F'");
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
        
        
    }
    mysql_free_result(res);
    mysql_close(conn);  
    

//MENU
    printf("\nIntroduzca los pasaportes de los usuarios para reservar Formato: 11111,11116,11117: ");
    fflush(stdin);
    fgets(entrada_pasaporte,200,stdin);
    quitar_Char(entrada_pasaporte, '\n');
    printf("\nSimbología:");
    printf("\nBL: Business libre.");
    printf("\nSL: Premium Economy.");
    printf("\nEL: Economy.");

    printf("\nIntroduzca los asientos de los usuarios para reservar(Siga la simbología anterior junto con el formato) Formato: A_BL_1,B_BL_2,C_BL_3: ");
    fflush(stdin);
    
    fgets(entrada_asiento,200,stdin);
    quitar_Char(entrada_asiento, '\n');
    


//PARTE PASAPORTE
    token_pasaportes= strtok(entrada_pasaporte, ",");
    while( token_pasaportes != NULL) {
            
            strcpy(extraido,token_pasaportes);
            quitar_Char(extraido,'\n');
            
            conn = mysql_init(NULL);

            // Connect to database /
            if (!mysql_real_connect(conn, server, user, password, 
                                            database, 0, NULL, 0)) {
                
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
            }

            strcpy(ptr,"Select * from cliente where  pasaporte_cliente= ");
            strcpy(ptr2,extraido);
            strcpy(ptr,strcat(ptr,ptr2));
            strcpy(ptr2,";");
            strcpy(ptr,strcat(ptr,ptr2));  
            if (mysql_query(conn,ptr)){
                fflush(stdout);
                fprintf(stdout, "\n%s", mysql_error(conn));
                formato_incorrecto=1; 
                
                 
                

            }
                
            else
            {
                res = mysql_use_result(conn);
                row = mysql_fetch_row(res);
                
                if (row==NULL){
                    fflush(stdout);     
                    formato_incorrecto=1;
                    error=1;
                }    
                mysql_free_result(res);
                mysql_close(conn); 
                if (error==0)
                {
                    conn = mysql_init(NULL);

                    // Connect to database /
                    if (!mysql_real_connect(conn, server, user, password, 
                                                    database, 0, NULL, 0)) {
                        
                        fprintf(stderr, "%s\n", mysql_error(conn));
                        exit(1);
                    }

                    formato_incorrecto=0;    
                    strcpy(ptr,"CALL insertar_pasaportes(");
                    strcpy(ptr2,extraido);
                    strcpy(ptr,strcat(ptr,ptr2));
                    strcpy(ptr2,");");
                    strcpy(ptr,strcat(ptr,ptr2)); 

                    if (mysql_query(conn,ptr)){
                        fflush(stdout);
                        fprintf(stdout, "\n%s",mysql_error(conn)); 
                        pasaporte_duplicado=1;

                    }
                    else
                    {
                        pasaporte_duplicado=0;
                    
                    } 
                
                    mysql_close(conn);
                }
            
            }
            
        token_pasaportes = strtok(NULL, ",");

    }

if (formato_incorrecto ==1)
{
    printf("\nFormato incorrecto o no se encontro");
    formato_incorrecto_p=1;  
}
if (pasaporte_duplicado==1)
{
    printf("\nAlmenos 1 pasaporte esta duplicado");
}
formato_incorrecto=0;

//PARTE ASIENTOS

    token_asientos = strtok(entrada_asiento, "_,");
    while( token_asientos != NULL) {

        strcpy(extraido,token_asientos);
        quitar_Char(extraido,'\n');

        switch (contador)
        {
        case 0:
            strcpy(fila,extraido);
            contador=contador+1;
            break;
        case 1:
            strcpy(tipo_aux,extraido);
            if (strcmp(tipo_aux,"BO")==0)
            {
                strcpy(tipo,extraido);
                asiento_ocupado=1;
                
            }
            else if (strcmp(tipo_aux,"bo")==0)
            {
                strcpy(tipo,extraido);
                asiento_ocupado=1;
                
            }
            else{
                strcpy(tipo,extraido);
    

            }
            
            contador=contador+1;   
            break;
        case 2:
            conn = mysql_init(NULL);

            // Connect to database /
            if (!mysql_real_connect(conn, server, user, password, 
                                            database, 0, NULL, 0)) {
                
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
            }

            
            strcpy(num_asi,extraido);
            strcpy(ptr,"Select * from detalle_vuelo where codigo_vuelo= ");
            strcpy(ptr2,temp);
            strcpy(ptr,strcat(ptr,ptr2));
            strcpy(ptr2," and fila='");
            strcpy(ptr,strcat(ptr,ptr2));  
            strcpy(ptr2,fila);
            strcpy(ptr,strcat(ptr,ptr2));
            strcpy(ptr,strcat(ptr,comilla));
            strcpy(ptr2," and num_asiento=");
            strcpy(ptr,strcat(ptr,ptr2));  
            strcpy(ptr2,num_asi);
            strcpy(ptr,strcat(ptr,ptr2));
            strcpy(ptr2," and tipo_asiento='");
            strcpy(ptr,strcat(ptr,ptr2));
            quitar_Char(tipo,'0');
            quitar_Char(tipo,'1');
            quitar_Char(tipo,'2');
            quitar_Char(tipo,'3');
            quitar_Char(tipo,'4');
            quitar_Char(tipo,'5');
            quitar_Char(tipo,'6');
            quitar_Char(tipo,'7');
            quitar_Char(tipo,'8');
            quitar_Char(tipo,'9');
            strcpy(ptr2,tipo);
            strcpy(ptr,strcat(ptr,ptr2));
            strcpy(ptr2,"';");
            strcpy(ptr,strcat(ptr,ptr2));
   

            if (mysql_query(conn,ptr)){
                fflush(stdout);
                fprintf(stdout, "\n%s",mysql_error(conn)); 
                formato_incorrecto=1;
            }
            else
            {
                        
                res = mysql_use_result(conn);
                row = mysql_fetch_row(res);
                if (row==NULL){
                    fprintf(stdout, "\n%s",mysql_error(conn)); 
                    formato_incorrecto=1;

                }

                mysql_free_result(res);
                mysql_close(conn); 
 
      
                if (formato_incorrecto==0)
                {
                    conn = mysql_init(NULL);

                    // Connect to database /
                    if (!mysql_real_connect(conn, server, user, password, 
                                                    database, 0, NULL, 0)) {
                        
                        fprintf(stderr, "%s\n", mysql_error(conn));
                        exit(1);
                    }
                    strcpy(num_asi,extraido);
                    strcpy(ptr,"INSERT INTO temp_entradas_asiento (fila,num_asiento,tipo) values(");
                    strcpy(ptr,strcat(ptr,comilla));
                    strcpy(ptr2,fila);
                    strcpy(ptr,strcat(ptr,ptr2));
                    strcpy(ptr,strcat(ptr,comilla));
                    strcpy(ptr,strcat(ptr,coma));
                    strcpy(ptr2,num_asi);
                    strcpy(ptr,strcat(ptr,ptr2)); 
                    strcpy(ptr,strcat(ptr,coma));
                    strcpy(ptr,strcat(ptr,comilla));
                    quitar_Char(tipo,'0');
                    quitar_Char(tipo,'1');
                    quitar_Char(tipo,'2');
                    quitar_Char(tipo,'3');
                    quitar_Char(tipo,'4');
                    quitar_Char(tipo,'5');
                    quitar_Char(tipo,'6');
                    quitar_Char(tipo,'7');
                    quitar_Char(tipo,'8');
                    quitar_Char(tipo,'9');
                    strcpy(ptr2,tipo);
                    strcpy(ptr,strcat(ptr,ptr2));
                    strcpy(ptr,strcat(ptr,comilla));
                    strcpy(ptr2,");");
                    strcpy(ptr,strcat(ptr,ptr2));  
     
                    if (mysql_query(conn,ptr)){
                        fflush(stdout);
                        fprintf(stdout, "\n%s",mysql_error(conn)); 
                        asiento_duplicado=1;

                    }
                    mysql_close(conn);
                    
                    if (asiento_duplicado =0)
                    {
                        conn = mysql_init(NULL);
                        // Connect to database /
                        if (!mysql_real_connect(conn, server, user, password, 
                                                        database, 0, NULL, 0)) {
                            
                            fprintf(stderr, "%s\n", mysql_error(conn));
                            exit(1);
                        }
                        
                    
                        strcpy(ptr,"CALL validar_entradas_asiento(");
                        strcpy(ptr2,temp);
                        strcpy(ptr,strcat(ptr,ptr2));
                        strcpy(ptr,strcat(ptr,coma));
                        strcpy(ptr,strcat(ptr,comilla));
                        strcpy(ptr2,fila);
                        strcpy(ptr,strcat(ptr,ptr2));
                        strcpy(ptr,strcat(ptr,comilla));
                        strcpy(ptr,strcat(ptr,coma));
                        strcpy(ptr2,fila);
                        strcpy(ptr,strcat(ptr,ptr2));
                        strcpy(ptr2,");");
                        strcpy(ptr,strcat(ptr,ptr2));  
            
                        if (mysql_query(conn,ptr)){
                            fflush(stdout);
                            fprintf(stdout, "\n%s",mysql_error(conn));


                        }
                        else
                        {
                            
                            res = mysql_use_result(conn);
                            row = mysql_fetch_row(res);
                            if (row==NULL){
                                fprintf(stdout, "\n%s", mysql_error(conn)); 
                                asiento_ocupado=1;
            
                            }    
                        
                        
                        }    
                        mysql_free_result(res);
                        mysql_close(conn);
                   
                    


                    }
                }  
                    
                            
        
                
                
            }
            contador=0;
            break;
        default:
            bandera=1;
            break;
        }

    token_asientos = strtok(NULL, "_,");  
    }


    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                    database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    if (mysql_query(conn,"SELECT count(edad) from temp_entradas_pasaporte where edad='A';")){
        fflush(stdout);
        fprintf(stdout, "\n%s",mysql_error(conn));

    }
    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    strcpy(num_asientos_A,row[0]);
    mysql_free_result(res);
    mysql_close(conn);


        conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                    database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    if (mysql_query(conn,"SELECT count(num_asiento) from temp_entradas_asiento;")){
        fflush(stdout);
        fprintf(stdout, "\n%s",mysql_error(conn));

    }
    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    strcpy(num_asientos_totales,row[0]);
    mysql_free_result(res);
    mysql_close(conn);


if (asiento_ocupado==1)
{
    printf("\nElegiste almenos un asiento ocupado");
}

if (formato_incorrecto==1)
{
    printf("\nFormato incorrecto o asiento inexistente");
}

if (strcmp(num_asientos_A,num_asientos_totales)!=0)
{
    printf("\nLa cantidad de asientos no concuerda con la cantidad de Adultos o elegiste almenos un asiento ocupado");    
}
if (strcmp(num_asientos_A,num_asientos_totales)==0 && formato_incorrecto==0 && asiento_ocupado==0 && pasaporte_duplicado==0 && formato_incorrecto_p==0)
{
    printf("\nProcesando petición...");

    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                    database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    strcpy(ptr,"INSERT INTO reservacion_vuelo (fecha_hora_reserv,codigo_vuelo) values (SYSDATE(),");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,");");
    strcpy(ptr,strcat(ptr,ptr2));  

    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "\n%s",mysql_error(conn)); 

    }
    res = mysql_use_result(conn);
    mysql_free_result(res);
    mysql_close(conn);


    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                    database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    strcpy(ptr,"SELECT * FROM reservacion_vuelo where codigo_vuelo= ");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," order by id_reserv DESC LIMIT 1;");
    strcpy(ptr,strcat(ptr,ptr2));      
   

    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "\n%s",mysql_error(conn)); 

    }
    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    strcpy(id_reserv,row[0]);
    mysql_free_result(res);
    mysql_close(conn);
    
    
//ACA UDATEA LOS ASIENTOS

num_asientos_int=atoi(num_asientos_totales);

while (num_asientos_int > 0)
{
   


        conn = mysql_init(NULL);

        // Connect to database /
        if (!mysql_real_connect(conn, server, user, password, 
                                        database, 0, NULL, 0)) {
            
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        
        if (mysql_query(conn,"select * from temp_entradas_pasaporte where edad='A';")){
            fflush(stdout);
            fprintf(stdout, "\n%s",mysql_error(conn)); 

        }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row!=NULL){
            strcpy(pasaporte,row[0]);

        }  
        
        
        mysql_free_result(res);
        mysql_close(conn);

        conn = mysql_init(NULL);

        // Connect to database /
        if (!mysql_real_connect(conn, server, user, password, 
                                        database, 0, NULL, 0)) {
            
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        
        if (mysql_query(conn,"delete from temp_entradas_pasaporte where edad='A' limit 1;")){
            fflush(stdout);
            fprintf(stdout, "\n%s",mysql_error(conn)); 

        }
        
        mysql_close(conn);

        conn = mysql_init(NULL);

        // Connect to database /
        if (!mysql_real_connect(conn, server, user, password, 
                                        database, 0, NULL, 0)) {
            
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        
        if (mysql_query(conn,"select * from temp_entradas_asiento;")){
            fflush(stdout);
            fprintf(stdout, "\n%s",mysql_error(conn)); 

        }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row!=NULL){
            strcpy(fila,row[0]);
            strcpy(tipo,row[1]);
            strcpy(num_asi,row[2]);
        }  
        
        
        mysql_free_result(res);
        mysql_close(conn);

               conn = mysql_init(NULL);
        
        // Connect to database /
        if (!mysql_real_connect(conn, server, user, password, 
                                        database, 0, NULL, 0)) {
            
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        strcpy(ptr,"CALL pone_asiento(");
        strcpy(ptr2,num_asi);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr,strcat(ptr,coma));
        strcpy(ptr2,temp);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr,strcat(ptr,coma));
        strcpy(ptr,strcat(ptr,comilla));
        strcpy(ptr2,fila);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr,strcat(ptr,comilla));
        strcpy(ptr,strcat(ptr,coma));
        strcpy(ptr,strcat(ptr,comilla));
        quitar_Char(tipo,'L');
        quitar_Char(tipo,'l');
        quitar_Char(tipo,'0');
        quitar_Char(tipo,'1');
        quitar_Char(tipo,'2');
        quitar_Char(tipo,'3');
        quitar_Char(tipo,'4');
        quitar_Char(tipo,'5');
        quitar_Char(tipo,'6');
        quitar_Char(tipo,'7');
        quitar_Char(tipo,'8');
        quitar_Char(tipo,'9');
        strcpy(ptr2,"O");
        strcpy(tipo,strcat(tipo,ptr2));
        strcpy(ptr2,tipo);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr,strcat(ptr,comilla));
        strcpy(ptr2,");");
        strcpy(ptr,strcat(ptr,ptr2));

        
        if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "\n%s",mysql_error(conn)); 

        }

        mysql_close(conn);

        conn = mysql_init(NULL);

        // Connect to database /
        if (!mysql_real_connect(conn, server, user, password, 
                                        database, 0, NULL, 0)) {
            
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        
        strcpy(ptr,"delete from temp_entradas_asiento where num_asiento= ");
        strcpy(ptr2,num_asi);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr2," and fila='");
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr2,fila);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr,strcat(ptr,comilla));
        strcpy(ptr2," and tipo='");
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr2,tipo);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr,strcat(ptr,comilla));
        strcpy(ptr2," limit 1 ;");
        strcpy(ptr,strcat(ptr,ptr2));
        

        if (mysql_query(conn,ptr)){
            fflush(stdout);
            fprintf(stdout, "\n%s",mysql_error(conn)); 

        }
        
        mysql_close(conn);


        conn = mysql_init(NULL);
        
        // Connect to database /
        if (!mysql_real_connect(conn, server, user, password, 
                                        database, 0, NULL, 0)) {
            
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        strcpy(num_asi2,num_asi);
        strcpy(ptr,"INSERT INTO clientexreservacion (id_reserv,pasaporte_cliente,fila_reserv,num_asiento_reserv,tipo_asiento_reserv,ind_edad)VALUES( ");
        strcpy(ptr2,id_reserv);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr,strcat(ptr,coma));
        strcpy(ptr2,pasaporte);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr,strcat(ptr,coma));
        strcpy(ptr,strcat(ptr,comilla));
        strcpy(ptr2,fila);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr,strcat(ptr,comilla));
        strcpy(ptr,strcat(ptr,coma));
        strcpy(ptr2,num_asi);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr,strcat(ptr,coma));
        strcpy(ptr,strcat(ptr,comilla));
        quitar_Char(tipo,'0');
        quitar_Char(tipo,'1');
        quitar_Char(tipo,'2');
        quitar_Char(tipo,'3');
        quitar_Char(tipo,'4');
        quitar_Char(tipo,'5');
        quitar_Char(tipo,'6');
        quitar_Char(tipo,'7');
        quitar_Char(tipo,'8');
        quitar_Char(tipo,'9');
        quitar_Char(tipo,'O');
        quitar_Char(tipo,'L');
        quitar_Char(tipo,'o');
        quitar_Char(tipo,'l');
        strcpy(ptr2,"L");
        strcpy(tipo,strcat(tipo,ptr2));
        strcpy(ptr2,tipo);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr,strcat(ptr,comilla));

        strcpy(ptr,strcat(ptr,coma));
        strcpy(ptr2," pone_edad(");
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr2,pasaporte);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr2,"));");
        strcpy(ptr,strcat(ptr,ptr2));    
   
        if (mysql_query(conn,ptr)){
            fflush(stdout);
            fprintf(stdout, "\n%s",mysql_error(conn)); 

        }


    
        mysql_close(conn);
        
        


    num_asientos_int=num_asientos_int-1;


}



//INFANTES

    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                    database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    if (mysql_query(conn,"SELECT count(pasaporte) from temp_entradas_pasaporte where edad='I';")){
        fflush(stdout);
        fprintf(stdout, "\n%s",mysql_error(conn));

    }
    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    strcpy(num_asientos_totales,row[0]);
    mysql_free_result(res);
    mysql_close(conn);


num_asientos_int=atoi(num_asientos_totales);

while (num_asientos_int > 0)
{
   


        conn = mysql_init(NULL);

        // Connect to database /
        if (!mysql_real_connect(conn, server, user, password, 
                                        database, 0, NULL, 0)) {
            
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        
        if (mysql_query(conn,"select * from temp_entradas_pasaporte where edad='I';")){
            fflush(stdout);
            fprintf(stdout, "\n%s",mysql_error(conn)); 

        }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row!=NULL){
            strcpy(pasaporte,row[0]);

        }  
        
        
        mysql_free_result(res);
        mysql_close(conn);

        conn = mysql_init(NULL);

        // Connect to database /
        if (!mysql_real_connect(conn, server, user, password, 
                                        database, 0, NULL, 0)) {
            
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        
        if (mysql_query(conn,"delete from temp_entradas_pasaporte where edad='I' limit 1;")){
            fflush(stdout);
            fprintf(stdout, "\n%s",mysql_error(conn)); 

        }


        mysql_close(conn);

        conn = mysql_init(NULL);
        
        // Connect to database /
        if (!mysql_real_connect(conn, server, user, password, 
                                        database, 0, NULL, 0)) {
            
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        strcpy(ptr,"INSERT INTO clientexreservacion (id_reserv,pasaporte_cliente,tipo_asiento_reserv,ind_edad) VALUES (");
        strcpy(ptr2,id_reserv);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr,strcat(ptr,coma));
        strcpy(ptr2,pasaporte);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr,strcat(ptr,coma));
        strcpy(ptr,strcat(ptr,comilla));
        strcpy(ptr2,"EL");
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr,strcat(ptr,comilla));
        strcpy(ptr,strcat(ptr,coma));
        strcpy(ptr2," pone_edad(");
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr2,pasaporte);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr2,"));");
        strcpy(ptr,strcat(ptr,ptr2));    
   

        if (mysql_query(conn,ptr)){
            fflush(stdout);
            fprintf(stdout, "\n%s",mysql_error(conn)); 

        }


    
        mysql_close(conn);
        
        


    num_asientos_int=num_asientos_int-1;


}

//Calcular el precio


    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                    database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    strcpy(ptr,"SELECT calcula_monto(");
    strcpy(ptr2,id_reserv);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,");");
    strcpy(ptr,strcat(ptr,ptr2));    

    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "\n%s",mysql_error(conn));

    }
    
    mysql_close(conn);

    printf("\nReservación Exitosa! \nPor favor introduzca un nombre para el comprobante:");
    fgets(comprobante,40,stdin);
    quitar_Char(comprobante,'\n');
    quitar_Char(comprobante,' ');
    strcpy(ptr,"/home/randall/Desktop/TEC/Lenguajes/Proyecto#1/detalle_reserva/");
    strcpy(ptr2,comprobante);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(comprobante_pdf,ptr);;
    strcpy(ptr2,".txt");
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(comprobante,ptr);

    FILE * flujo = fopen(ptr,"a");
    if (flujo==NULL){
        perror("\nError en la creación del archivo");
    }
    else
    {
         conn = mysql_init(NULL);

        // Connect to database /
        if (!mysql_real_connect(conn, server, user, password, 
                                        database, 0, NULL, 0)) {
            
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        
        strcpy(ptr,"CALL sh_info_reserv (");
        strcpy(ptr2,id_reserv);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr2,");");
        strcpy(ptr,strcat(ptr,ptr2));  
        

        if (mysql_query(conn,ptr)){
            fflush(stdout);
            fprintf(stdout, "\n%s",mysql_error(conn)); 

        }


        res = mysql_use_result(conn);             
        fprintf(flujo,"\nDETALLE RESERVA\n");
        
        fprintf(flujo,"\n|id_Reservacion|Cantidad_Asientos|Fecha_Hora_Reserv|Id_Aerolinea|Nombre_Aerolinea|hub|Codigo_Vuelo|Nombre_Ciudad_D|Salida_Vuelo|Nombre_Ciudad_S|Monto_Reserva|");
        fprintf(flujo, "\n");
                    
        while ((row = mysql_fetch_row(res)) != NULL){
            fprintf(flujo,"\n|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10],row[11]);
        }
        printf("\n");
        
        

        conn = mysql_init(NULL);
        // Connect to database /
        if (!mysql_real_connect(conn, server, user, password, 
                                        database, 0, NULL, 0)) {
            
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        strcpy(ptr,"CALL sh_info_reserv_personas (");
        strcpy(ptr2,id_reserv);
        strcpy(ptr,strcat(ptr,ptr2));
        strcpy(ptr2,");");
        strcpy(ptr,strcat(ptr,ptr2));  


        if (mysql_query(conn,ptr)){
            fflush(stdout);
            fprintf(stdout, "Ese código no esta en la tabla "); 

        }

        
        res = mysql_use_result(conn);             
        fprintf(flujo,"\nDETALLE PERSONA RESERVADO\n");
        fprintf(flujo,"\n _________________ ___________________ _____________ _____________  ");
        fprintf(flujo,"\n|Pasaporte_Cliente| Nombre_Cliente    |Prim_Apellido| Seg_Apellido| ");
        fprintf(flujo,"\n ----------------- ------------------- ------------- -------------\n ");
                    
        while ((row = mysql_fetch_row(res)) != NULL){
            fprintf(flujo,"\n|%s           |%s         |%s|%s\n", row[0], row[1], row[2], row[3]);
        }
        fprintf(flujo,"\n");
    
        mysql_free_result(res);
        mysql_close(conn);  
    
    }
    fflush(flujo);
    fclose(flujo);
 
    strcpy(ptr,"enscript ");
    strcpy(ptr2,comprobante);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2," -o - | ps2pdf - ");
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,comprobante_pdf);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,".pdf");
    strcpy(ptr,strcat(ptr,ptr2));
 
    system(ptr);

    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    strcpy(ptr,"SELECT * FROM reservacion_vuelo where id_reserv=");
    strcpy(ptr2,id_reserv);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,";");
    strcpy(ptr,strcat(ptr,ptr2));
    
    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "\n%s", mysql_error(conn));

    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    if (row==NULL){
        fflush(stdout);
        fprintf(stdout, "\n%s",mysql_error(conn));       
       
    }

    mysql_free_result(res);
    mysql_close(conn);  
    

    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    strcpy(ptr,"CALL sh_info_reserv (");
    strcpy(ptr2,id_reserv);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,");");
    strcpy(ptr,strcat(ptr,ptr2));  


    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "\n%s",mysql_error(conn)); 

    }


    res = mysql_use_result(conn);             
    printf("\nDETALLE RESERVA\n");
    printf("\n _______________ _________________ __________________ ____________ ________________ __________ ____________ _______________ ___________________ _______________ _____________  ");
    printf("\n|id_Reservación |Cantidad_Asientos|Fecha_Hora_Reserv |Id_Aerolinea|Nombre_Aerolinea|hub       |Codigo_Vuelo|Nombre_Ciudad_D|Salida_Vuelo       |Nombre_Ciudad_S|Monto_Reserva|");
    printf("\n --------------- ----------------- ------------------ ------------ ---------------- ---------- ------------ --------------- ------------------- --------------- ------------\n ");
                
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s              |%s                |%s|%s  |%s   |%s  |%s  |%s    |%s|%s    |%s    |%s\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10],row[11]);
    }
    printf("\n");
    

    mysql_free_result(res);
    mysql_close(conn);

    conn = mysql_init(NULL);
    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    strcpy(ptr,"CALL sh_info_reserv_personas (");
    strcpy(ptr2,id_reserv);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,");");
    strcpy(ptr,strcat(ptr,ptr2));  


    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "Ese código no esta en la tabla "); 

    }

    
    res = mysql_use_result(conn);             
    printf("\nDETALLE PERSONA RESERVADO\n");
    printf("\n _________________ ___________________ _____________ _____________  ");
    printf("\n|Pasaporte_Cliente| Nombre_Cliente    |Prim_Apellido| Seg_Apellido| ");
    printf("\n ----------------- ------------------- ------------- -------------\n ");
                
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s           |%s         |%s|%s\n", row[0], row[1], row[2], row[3]);
    }
    printf("\n");
   
    mysql_free_result(res);
    mysql_close(conn);  
}

}


void estado_reserv(){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    

    char temp[40];
    char ptr[200];
    char ptr2[200];

    int bandera_sigu=0;

    char *server = "localhost"; 
    char *database = "sys";
    char *user="root";
    char *password="root";


    printf("\nIntroduzca el id de reservación: "); 
    fflush(stdin);
    fgets(temp,40,stdin);
    quitar_Char(temp,'\n');
    
if (atoi(temp)!=0)
{
    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    strcpy(ptr,"SELECT * FROM reservacion_vuelo where id_reserv=");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,";");
    strcpy(ptr,strcat(ptr,ptr2));
    
    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "\n%s", mysql_error(conn));

    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    if (row==NULL){
        fflush(stdout);
        fprintf(stdout, "\nEse id de reserva no se encuentra");       
        bandera_sigu=1;
    }
    else
    {
        bandera_sigu=0;
        
        
    }
    mysql_free_result(res);
    mysql_close(conn);  
    

   if (bandera_sigu==0)
   {
       
   
   
    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    strcpy(ptr,"CALL sh_info_reserv (");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,");");
    strcpy(ptr,strcat(ptr,ptr2));  


    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "\n%s",mysql_error(conn)); 

    }


    res = mysql_use_result(conn);             
    printf("\nDETALLE RESERVA\n");
    printf("\n _______________ _________________ __________________ ____________ ________________ __________ ____________ _______________ ___________________ _______________ _____________  ");
    printf("\n|id_Reservación |Cantidad_Asientos|Fecha_Hora_Reserv |Id_Aerolinea|Nombre_Aerolinea|hub       |Codigo_Vuelo|Nombre_Ciudad_D|Salida_Vuelo       |Nombre_Ciudad_S|Monto_Reserva|");
    printf("\n --------------- ----------------- ------------------ ------------ ---------------- ---------- ------------ --------------- ------------------- --------------- ------------\n ");
                
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s              |%s                |%s|%s  |%s   |%s  |%s  |%s    |%s|%s    |%s    |%s\n", row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10],row[11]);
    }
    printf("\n");
    

    mysql_free_result(res);
    mysql_close(conn);
    
    conn = mysql_init(NULL);

    // Connect to database /
    if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
        
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    strcpy(ptr,"CALL sh_info_reserv_personas (");
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
    printf("\n _________________ ___________________ _____________ _____________  ");
    printf("\n|Pasaporte_Cliente| Nombre_Cliente    |Prim_Apellido| Seg_Apellido| ");
    printf("\n ----------------- ------------------- ------------- -------------\n ");
                
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s           |%s         |%s|%s\n", row[0], row[1], row[2], row[3]);
    }
    printf("\n");
   }
    mysql_free_result(res);
    mysql_close(conn);  
}
else
{
    printf("\nFavor introducir un número");
}

 
}