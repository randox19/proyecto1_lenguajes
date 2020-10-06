
-- DROPS
drop table clientexreservacion;
drop table reservacion_vuelo;
drop table ciudadxvuelo;
drop table ciudad;
drop table detalle_vuelo;
drop table detalle_asiento;
drop table vuelo;
drop table avion;
drop table aerolinea;
drop table cliente;
drop table temp_entradas_asiento;
drop table temp_entradas_pasaporte;

-- CREATES

/*
Tabla que guardara los datos de entrada de las personas de la reserva
Esta tabla se eliminará cada vez que se realice una reserva
*/
CREATE TABLE temp_entradas_pasaporte(
	pasaporte INT(20) NOT NULL PRIMARY KEY,
    edad varchar(2) NOT NULL
);

/*
Tabla que guardara los datos de entrada de los asientos de la reserva
Esta tabla se eliminará cada vez que se realice una reserva
*/
CREATE TABLE temp_entradas_asiento(
	 fila varchar(2) NOT NULL,
     tipo varchar(3) NOT NULL,
     num_asiento INT(2) NOT NULL ,
	PRIMARY KEY (fila,tipo,num_asiento)
);
CREATE TABLE cliente(
pasaporte_cliente INT(12) NOT NULL,
nombre_cli VARCHAR (20) NOT NULL,
pri_apellido VARCHAR (20) NOT NULL,
seg_apellido VARCHAR (20) NOT NULL,
sexo VARCHAR (1) NOT NULL,
fecha_nac DATE NOT NULL);

CREATE TABLE reservacion_vuelo(
id_reserv INT(11) AUTO_INCREMENT PRIMARY KEY,
fecha_hora_reserv DATETIME NOT NULL, 
codigo_vuelo INT (12) NOT NULL);

CREATE TABLE clientexreservacion(
id_reserv INT (11) NOT NULL,
pasaporte_cliente INT(12) NOT NULL,
fila_reserv VARCHAR (1),
tipo_asiento_reserv VARCHAR (5),
num_asiento_reserv  INT (10),
ind_edad VARCHAR (1) NOT NULL);

CREATE TABLE vuelo(
codigo_vuelo INT (12) NOT NULL,
matricula INT(12) NOT NULL,
salida_vuelo DATETIME NOT NULL,
llegada_vuelo DATETIME NOT NULL);

CREATE TABLE ciudad(
codigo_ciudad VARCHAR (5) NOT NULL,
pais VARCHAR (30) NOT NULL,
nombre_ciudad  VARCHAR (40) NOT NULL);

CREATE TABLE ciudadxvuelo(
codigo_vuelo INT (12) NOT NULL,
origen_vuelo VARCHAR (10) NOT NULL,
destino_vuelo VARCHAR (10) NOT NULL);

CREATE TABLE detalle_vuelo(
codigo_vuelo INT (12) NOT NULL,
fila VARCHAR (1) NOT NULL,
tipo_asiento VARCHAR (5) NOT NULL,
num_asiento  INT (10) NOT NULL);

CREATE TABLE detalle_asiento(
codigo_vuelo INT (12) NOT NULL,
rango_asiento VARCHAR (5) NOT NULL,
ind_edad_rango VARCHAR (1) NOT NULL,
precio_asiento INT (7) NOT NULL);

CREATE TABLE aerolinea(
id_aerolinea INT (12) NOT NULL,
hub VARCHAR (20) NOT NULL,
nombre_aerolinea VARCHAR (20) NOT NULL,
nombre_usuario VARCHAR (20) NOT NULL,
contrasenna VARCHAR(32) NOT NULL);

CREATE TABLE avion(
matricula INT (12) NOT NULL,
marca VARCHAR (20) NOT NULL,
modelo VARCHAR (20) NOT NULL,
anno INT (12) NOT NULL,
id_aerolinea INT (12) NOT NULL);

-- ALTERS

-- alters cliente 
ALTER TABLE cliente
ADD CONSTRAINT cliente_PK
PRIMARY KEY (pasaporte_cliente);

-- alters aerolinea
ALTER TABLE aerolinea
ADD CONSTRAINT aerolinea_PK
PRIMARY KEY (id_aerolinea);

-- alters avion
ALTER TABLE avion
ADD CONSTRAINT avion_PK
PRIMARY KEY (matricula);

ALTER TABLE avion
ADD CONSTRAINT id_aerolinea_FK
FOREIGN KEY (id_aerolinea) 
REFERENCES aerolinea (id_aerolinea);

-- alters vuelo
ALTER TABLE vuelo
ADD CONSTRAINT vuelo_PK
PRIMARY KEY (codigo_vuelo);

ALTER TABLE vuelo
ADD CONSTRAINT matricula_FK
FOREIGN KEY (matricula) 
REFERENCES avion (matricula);

-- alters detalle_vuelo
ALTER TABLE detalle_vuelo
ADD CONSTRAINT detalle_vuelo_PK
PRIMARY KEY (codigo_vuelo, fila, tipo_asiento, num_asiento);

ALTER TABLE detalle_vuelo
ADD CONSTRAINT codigo_vuelo_FK
FOREIGN KEY (codigo_vuelo) 
REFERENCES vuelo (codigo_vuelo);

-- alters detalle_asiento
ALTER TABLE detalle_asiento
ADD CONSTRAINT detalle_asiento_PK
PRIMARY KEY (codigo_vuelo, rango_asiento,ind_edad_rango, precio_asiento);

ALTER TABLE detalle_asiento
ADD CONSTRAINT codigo_vuelo_FK2
FOREIGN KEY (codigo_vuelo) 
REFERENCES vuelo (codigo_vuelo);

-- alters ciudad
ALTER TABLE ciudad
ADD CONSTRAINT ciudad_PK
PRIMARY KEY (codigo_ciudad);

-- alters ciudadxvuelo
ALTER TABLE ciudadxvuelo
ADD CONSTRAINT ciudadxvuelo_PK
PRIMARY KEY (codigo_vuelo, origen_vuelo, destino_vuelo);

ALTER TABLE ciudadxvuelo
ADD CONSTRAINT codigo_vuelo_FK3
FOREIGN KEY (codigo_vuelo) 
REFERENCES vuelo (codigo_vuelo);

ALTER TABLE ciudadxvuelo
ADD CONSTRAINT codigo_ciudad_FK
FOREIGN KEY (origen_vuelo) 
REFERENCES ciudad (codigo_ciudad);

ALTER TABLE ciudadxvuelo
ADD CONSTRAINT codigo_ciudad_FK2
FOREIGN KEY (destino_vuelo) 
REFERENCES ciudad (codigo_ciudad);

-- alters reservacion_vuelo

ALTER TABLE reservacion_vuelo
ADD CONSTRAINT codigo_vuelo_FK4
FOREIGN KEY (codigo_vuelo) 
REFERENCES vuelo (codigo_vuelo);

-- alters clientexreservacion
ALTER TABLE clientexreservacion
ADD CONSTRAINT clientexreservacion_PK
PRIMARY KEY (id_reserv,pasaporte_cliente);

ALTER TABLE clientexreservacion
ADD CONSTRAINT pasaporte_cliente_FK
FOREIGN KEY (pasaporte_cliente) 
REFERENCES cliente (pasaporte_cliente);

ALTER TABLE clientexreservacion
ADD CONSTRAINT id_reserv_FK
FOREIGN KEY (id_reserv) 
REFERENCES reservacion_vuelo (id_reserv);

