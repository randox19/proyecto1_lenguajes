#include "script.h"

void registro_usuarios(){
    int opcion;
    char temp[40];
    
    do{
    printf("\n\t\t ************************************\n");
	printf("\n\t\t          Registro de aviones  \n");
	printf("\n\t\t ************************************\n");
    printf ("\n 1.Agregar un avión");
    printf ("\n 2.Mostrar aviones");
    printf ("\n 3.Eliminar un avion");
    printf ("\n 4.Volver al menu operativo\n");
    printf("\nIntroduzca su opcion del 1 al 4: ");
    fflush(stdin);
    fgets(temp,40,stdin);
    opcion=atoi(temp);

    switch (opcion)
    {
    case 1: 
        agregar_avion();
        break;
    case 2: 
        filtrar_aviones();
        break;
    case 3: 
        eliminar_avion();
        break;
    case 4: 
        break;
    default:
         printf("\n Seleccione una opción del 1-4\n");
        break;
    }
    }while (opcion != 4);
    


}
void agregar_avion (){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;


    char salir[2];
    char temp[40];
    char ptr[200];
    char ptr2[200];
    char coma[2]=",";
    char comilla[2]="'";
    int bandera;

    int matricula;
    char marca[20];
    char modelo[20];
    int anno;
    int id_aerolinea;

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
        printf("\nMATRÍCULAS NO DISPONIBLES\n");
    if (mysql_query(conn,"select * from avion;")){
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    res = mysql_use_result(conn);
    
    printf("\n _________");
    printf("\n|Matricula|");
    printf("\n ---------");
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s    |\n", row[0]);
    }
        printf("\n");

    
    printf("\nIntroduce la matricula (Número 10000-99999) y que NO se encuentre en la tabla anterior para el nuevo avión:");
    fflush(stdin);
    fgets(temp,40,stdin);
    matricula=atoi(temp); 

    strcpy(ptr,"Select matricula from avion where matricula = ");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,";");
    strcpy(ptr,strcat(ptr,ptr2));  
   
    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "%s", mysql_error(conn));
        bandera=1;
    }
    else
    {
         
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row==NULL){

            if (matricula<99999 && matricula>10000)
            { bandera=0;
            }
        }
        else
        {
            bandera=1;
            fflush(stdout);
            fprintf(stdout, "Ese avion esta en la tabla o no es un número");        
            
        }

    }
 

    mysql_free_result(res);
    
    }while (bandera==1);
    
    printf("\nIntroduce la marca del avión:");
    fgets(marca,40,stdin);
    printf("\nIntroduce el modelo del avión:");
    fgets(modelo,40,stdin);
    
    do{
    fflush(stdin);
    printf("\nIntroduce el año (Número 1900-3000) del avión:");
    fgets(temp,40,stdin);
    anno=atoi(temp);
        switch (anno)
        {
        default:
            break;
        }
    
    }while(anno>3000 || anno<1900);

    
    do{
    printf("\nAEROLINIAS DISPONIBLES\n");
    if (mysql_query(conn,"select * from aerolinea;")){
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_use_result(conn);
    printf("\n ________________________________________");
    printf("\n|id_aerolinea|   Hub  |Nombre |Usuario   |");
    printf("\n ----------------------------------------");
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s    |%s|%s|%s|\n", row[0], row[1], row[2], row[3]);
    }
    
    printf("\n");
    res = mysql_use_result(conn);
    printf("\nIntroduce el id (Seleccione unicamente uno de la tabla anterior) de la aerolinia en que se encuentra el avión:");
    fflush(stdin);
    fgets(temp,40,stdin);
    id_aerolinea=atoi(temp);

   
    strcpy(ptr,"Select id_aerolinea from aerolinea where id_aerolinea = ");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,";");
    strcpy(ptr,strcat(ptr,ptr2));    

    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "%s", mysql_error(conn));
        bandera=1;
    }
    else
    {
         
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
       
        if (row==NULL){
            bandera=1;
            fflush(stdout);
            fprintf(stdout, "Por favor seleccione un id_aerolinea de la tabla válido");  
        }
        else
        {
            bandera=0;
                 
        }

    }
    mysql_free_result(res);
    
    }while (bandera==1);
     

    // send SQL query /
    char matricula_c[20];
    sprintf(matricula_c, "%d",matricula);
    
    char anno_c[20];
    sprintf(anno_c,"%d",anno);

    char id_aerolinea_c[20];
    sprintf(id_aerolinea_c,"%d", id_aerolinea);

    quitar_Char(matricula_c, '\n');
    quitar_Char(anno_c, '\n');
    quitar_Char(marca, '\n');
    quitar_Char(modelo,'\n');
    quitar_Char(id_aerolinea_c, '\n');


    strcpy(ptr,"Insert into avion values(");
    strcpy(ptr2,matricula_c);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr,strcat(ptr,coma));
    strcpy(ptr,strcat(ptr,comilla));
    strcpy(ptr2,marca);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr,strcat(ptr,comilla));
    strcpy(ptr,strcat(ptr,coma));
    strcpy(ptr,strcat(ptr,comilla));
    strcpy(ptr2,modelo);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr,strcat(ptr,comilla));
    strcpy(ptr,strcat(ptr,coma));
    strcpy(ptr2,anno_c);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr,strcat(ptr,coma));
    strcpy(ptr2,id_aerolinea_c);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,")");
    strcpy(ptr,strcat(ptr,ptr2));


    
    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "No se pudo insertar '%s'\n No se siguió todas las instrucciones correctamente", ptr);
    }
    else
    {
        fflush(stdout);
        fprintf(stdout, "Se incerto con exito!");
    }

    res = mysql_use_result(conn);

    // close connection 
    mysql_commit(conn);
    mysql_close(conn);


    


}

void eliminar_avion (){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    int bandera;
    int bandera2;
    char temp[40];
    char ptr[200];
    char ptr2[200];
    char coma[2]=",";
    char comilla[2]="'";

    int matricula;

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
        printf("\nMATRÍCULAS  DISPONIBLES\n");
    if (mysql_query(conn,"select * from avion;")){
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_use_result(conn);
    
    printf("\n _________");
    printf("\n|Matricula|");
    printf("\n ---------");
    
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s    |\n", row[0]);
    }
        printf("\n");
    
    printf("\nAVIONES CON VUELOS ASIGNADOS\n");
    if (mysql_query(conn,"select * from vuelo;")){
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_use_result(conn);
    
    printf("\n ______");
    printf("\n|Vuelos|");
    printf("\n ------");
    
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s |\n", row[1]);
    }
        printf("\n");
    res = mysql_use_result(conn);
    printf("\nIntroduce la matrícula (Número 10000-99999) y que SI se encuentre en la tabla \n'MATRICULAS  DISPONIBLES' y además que NO esté en 'AVIONES CON VUELOS ASIGNADOS':");
    fflush(stdin);
    fgets(temp,40,stdin);
    matricula=atoi(temp);
    
    strcpy(ptr,"Select matricula from avion where matricula = ");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,";");
    strcpy(ptr,strcat(ptr,ptr2));  
   
    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "%s", mysql_error(conn));
        bandera=1;
        bandera2=1;
    }
    else
    {
         
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row==NULL){
            bandera=1;
            bandera2=1;
            fflush(stdout);
            fprintf(stdout, "Ese avion no esta en la tabla o no es un número");        
           
        }
        else
        {
                
            if (matricula<99999 && matricula>10000)
            { bandera=0;
              bandera2=0;
            }
            
        }
    }
    
    mysql_free_result(res);

   
    
    //REALIZARN CONSULTAS CRUDS

    // send SQL query /
    char matricula_c[20];
    sprintf(matricula_c, "%d",matricula);

    strcpy(ptr,"DELETE FROM avion where matricula = ");
    strcpy(ptr2,matricula_c);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr2,";");
    strcpy(ptr,strcat(ptr,ptr2));
    
    
    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "\nEse avion tiene un vuelo asignado no se puede eliminar");
        bandera2=1;
    }
    else
    {
        bandera=0;
        if(bandera2==0){
        fflush(stdout);
        fprintf(stdout, "\nEliminado con exito!");
        }
    }
    

    }while (bandera==1 || bandera2==1);


    // close connection 
    mysql_close(conn);




}

void filtrar_aviones(){

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
     printf("\nMARCA DE LOS AVIONES DISPONIBLES\n");
    if (mysql_query(conn,"select * from avion;")){
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_use_result(conn);
    
    printf("\n ______");
    printf("\n|Marcas|");
    printf("\n ------\n");
    
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s |\n", row[1]);
    }
        printf("\n");
    res = mysql_use_result(conn);

    
    printf("\nIntroduzca la marca del avión que desea filtrar(unicamente elija una de la tabla anterior):");
    fflush(stdin);
    fgets(temp,40,stdin);
    quitar_Char(temp, '\n');
    strcpy(ptr,"Select distinct marca from avion where marca ='");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr,strcat(ptr,comilla));
    strcpy(ptr2,";");
    strcpy(ptr,strcat(ptr,ptr2));  


    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "Esa marca de avion no esta en la tabla "); 
        bandera=1;

    }
    else
    {
         
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        if (row==NULL){
            bandera=1;
            fflush(stdout);
            fprintf(stdout, "Esa marca de avion no esta en la tabla ");        
           
        }
        else
        {
           bandera=0;
        
            
            
        }
    }
    
    mysql_free_result(res);
    }while (bandera==1);


    strcpy(ptr,"CALL sh_marca_avion('");
    strcpy(ptr2,temp);
    strcpy(ptr,strcat(ptr,ptr2));
    strcpy(ptr,strcat(ptr,comilla));
    strcpy(ptr2,");");
    strcpy(ptr,strcat(ptr,ptr2));  

    if (mysql_query(conn,ptr)){
        fflush(stdout);
        fprintf(stdout, "%s", mysql_error(conn));

    }
    res = mysql_use_result(conn);
    printf("\n _________ _____ ______ ____ ____________");
    printf("\n|Matricula|Marca|modelo|anno|id_aerolinea| ");
    printf("\n --------- ----- ------ ---- ------------\n");
    while ((row = mysql_fetch_row(res)) != NULL){
        printf("\n|%s|%s|%s|%s|%s|\n",row[0],row[1],row[2],row[3],row[4]);
    }
        printf("\n");
    res = mysql_use_result(conn); 
    mysql_free_result(res);
    mysql_close(conn);

}