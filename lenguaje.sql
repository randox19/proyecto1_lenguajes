
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

-- CREATES

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

-- INSERTS

-- inserts aerolinea 
-- para validar la contraseña usar MD5 y compararla con lo almacenado
INSERT INTO aerolinea VALUES (15121910,"Alajuela","Avianca","Avi_oncito", MD5('pluto'));

-- inserts aviones
INSERT INTO avion VALUES (10001,"Boeing","747",2000,15121910);
INSERT INTO avion VALUES (10002,"Airbus","A320",2015,15121910);
INSERT INTO avion VALUES (10003,"Tupolev","Tu-204C",1995,15121910);
INSERT INTO avion VALUES (10004,"Ilyushin","Il-96-300",2001,15121910);
INSERT INTO avion VALUES (10005,"Bombardier Aerospace","CRJ200",2005,15121910);
INSERT INTO avion VALUES (10006,"Boeing","757-200",1985,15121910);
INSERT INTO avion VALUES (10007,"Boeing","777-300",2018,15121910);
INSERT INTO avion VALUES (10008,"Airbus","A380-800",2006,15121910);
INSERT INTO avion VALUES (10009,"Tupolev","Tu-134",1983,15121910);
INSERT INTO avion VALUES (10010,"Bombardier Aerospace","CRJ700NG",1983,15121910);

-- inserts ciudades
INSERT INTO ciudad VALUES ("ALA","Costa Rica","Alajuela");
INSERT INTO ciudad VALUES ("NIC","Costa Rica","Nicoya");
INSERT INTO ciudad VALUES ("MAD","España","Madrid");
INSERT INTO ciudad VALUES ("SCL","Chile","Santiago");
INSERT INTO ciudad VALUES ("MTY","Mexico","Monterrey");
INSERT INTO ciudad VALUES ("CGH","Brasil","Sao Paulo");
INSERT INTO ciudad VALUES ("MEX","Mexico","Ciudad de Mexico");
INSERT INTO ciudad VALUES ("GIG","Brasil","Rio de Janeiro");
INSERT INTO ciudad VALUES ("LHR","Inglaterra","Londres");
INSERT INTO ciudad VALUES ("AEP","Argentina","Buenos aires");

-- inserts vuelos

INSERT INTO vuelo VALUES (11111,10001,STR_TO_DATE('2020,5,01 9:30','%Y,%m,%d %h:%i'), STR_TO_DATE('2020,5,01 10:30','%Y,%m,%d %h:%i'));
INSERT INTO vuelo VALUES (11112,10002,STR_TO_DATE('2020,7,10 1:30','%Y,%m,%d %h:%i'), STR_TO_DATE('2020,7,10 4:30','%Y,%m,%d %h:%i'));
INSERT INTO vuelo VALUES (11113,10003,STR_TO_DATE('2020,4,12 5:30','%Y,%m,%d %h:%i'), STR_TO_DATE('2020,4,12 10:30','%Y,%m,%d %h:%i'));
INSERT INTO vuelo VALUES (11114,10004,STR_TO_DATE('2020,8,01 10:30','%Y,%m,%d %h:%i'), STR_TO_DATE('2020,8,01 8:30','%Y,%m,%d %h:%i'));
INSERT INTO vuelo VALUES (11115,10005,STR_TO_DATE('2020,1,20 3:30','%Y,%m,%d %h:%i'), STR_TO_DATE('2020,1,20 5:30','%Y,%m,%d %h:%i'));
INSERT INTO vuelo VALUES (11116,10006,STR_TO_DATE('2020,8,21 7:00','%Y,%m,%d %h:%i'), STR_TO_DATE('2020,8,21 3:00','%Y,%m,%d %h:%i'));
INSERT INTO vuelo VALUES (11117,10001,STR_TO_DATE('2020,7,19 11:00','%Y,%m,%d %h:%i'), STR_TO_DATE('2020,7,20 2:30','%Y,%m,%d %h:%i'));
INSERT INTO vuelo VALUES (11118,10008,STR_TO_DATE('2020,12,01 9:30','%Y,%m,%d %h:%i'), STR_TO_DATE('2020,12,01 11:30','%Y,%m,%d %h:%i'));
INSERT INTO vuelo VALUES (11119,10009,STR_TO_DATE('2020,01,10 4:30','%Y,%m,%d %h:%i'), STR_TO_DATE('2020,01,10 7:30','%Y,%m,%d %h:%i'));
INSERT INTO vuelo VALUES (11121,10004,STR_TO_DATE('2020,10,15 11:30','%Y,%m,%d %h:%i'), STR_TO_DATE('2020,10,15 3:30','%Y,%m,%d %h:%i'));

-- inserts ciudadxvuelo
INSERT INTO ciudadxvuelo VALUES (11111,'ALA','NIC');
INSERT INTO ciudadxvuelo VALUES (11112,'ALA','SCL');
INSERT INTO ciudadxvuelo VALUES (11113,'NIC','AEP');
INSERT INTO ciudadxvuelo VALUES (11114,'ALA','LHR');
INSERT INTO ciudadxvuelo VALUES (11115,'ALA','MTY');
INSERT INTO ciudadxvuelo VALUES (11116,'NIC','GIG');
INSERT INTO ciudadxvuelo VALUES (11117,'ALA','MEX');
INSERT INTO ciudadxvuelo VALUES (11118,'ALA','CGH');
INSERT INTO ciudadxvuelo VALUES (11119,'NIC','MTY');
INSERT INTO ciudadxvuelo VALUES (11119,'NIC','MAD');

-- inserts detalle_vuelo
-- para vuelo 11111
INSERT INTO detalle_vuelo VALUES (11111,'A','BL',1);
INSERT INTO detalle_vuelo VALUES (11111,'A','BL',2);
INSERT INTO detalle_vuelo VALUES (11111,'A','BL',3);
INSERT INTO detalle_vuelo VALUES (11111,'A','BL',4);
INSERT INTO detalle_vuelo VALUES (11111,'B','BL',1);
INSERT INTO detalle_vuelo VALUES (11111,'B','BL',2);
INSERT INTO detalle_vuelo VALUES (11111,'B','BL',3);
INSERT INTO detalle_vuelo VALUES (11111,'B','BL',4);
INSERT INTO detalle_vuelo VALUES (11111,'C','SL',1);
INSERT INTO detalle_vuelo VALUES (11111,'C','SL',2);
INSERT INTO detalle_vuelo VALUES (11111,'C','SL',3);
INSERT INTO detalle_vuelo VALUES (11111,'C','SL',4);
INSERT INTO detalle_vuelo VALUES (11111,'D','SL',1);
INSERT INTO detalle_vuelo VALUES (11111,'D','SO',2);
INSERT INTO detalle_vuelo VALUES (11111,'D','SL',3);
INSERT INTO detalle_vuelo VALUES (11111,'D','SL',4);
INSERT INTO detalle_vuelo VALUES (11111,'E','EO',1);
INSERT INTO detalle_vuelo VALUES (11111,'E','EO',2);
INSERT INTO detalle_vuelo VALUES (11111,'E','EL',3);
INSERT INTO detalle_vuelo VALUES (11111,'E','EL',4);
INSERT INTO detalle_vuelo VALUES (11111,'F','EO',1);
INSERT INTO detalle_vuelo VALUES (11111,'F','EO',2);
INSERT INTO detalle_vuelo VALUES (11111,'F','EL',3);
INSERT INTO detalle_vuelo VALUES (11111,'F','EL',4);
-- para vuelo 11112
INSERT INTO detalle_vuelo VALUES (11112,'A','BO',1);
INSERT INTO detalle_vuelo VALUES (11112,'A','BO',2);
INSERT INTO detalle_vuelo VALUES (11112,'A','BO',3);
INSERT INTO detalle_vuelo VALUES (11112,'A','BO',4);
INSERT INTO detalle_vuelo VALUES (11112,'A','BL',5);
INSERT INTO detalle_vuelo VALUES (11112,'B','BL',1);
INSERT INTO detalle_vuelo VALUES (11112,'B','BL',2);
INSERT INTO detalle_vuelo VALUES (11112,'B','BL',3);
INSERT INTO detalle_vuelo VALUES (11112,'B','BL',4);
INSERT INTO detalle_vuelo VALUES (11112,'B','BL',5);
INSERT INTO detalle_vuelo VALUES (11112,'C','SL',1);
INSERT INTO detalle_vuelo VALUES (11112,'C','SL',2);
INSERT INTO detalle_vuelo VALUES (11112,'C','SL',3);
INSERT INTO detalle_vuelo VALUES (11112,'C','SL',4);
INSERT INTO detalle_vuelo VALUES (11112,'C','SL',5);
INSERT INTO detalle_vuelo VALUES (11112,'D','SL',1);
INSERT INTO detalle_vuelo VALUES (11112,'D','SL',2);
INSERT INTO detalle_vuelo VALUES (11112,'D','SL',3);
INSERT INTO detalle_vuelo VALUES (11112,'D','SL',4);
INSERT INTO detalle_vuelo VALUES (11112,'D','SL',5);
INSERT INTO detalle_vuelo VALUES (11112,'E','EL',1);
INSERT INTO detalle_vuelo VALUES (11112,'E','EL',2);
INSERT INTO detalle_vuelo VALUES (11112,'E','EL',3);
INSERT INTO detalle_vuelo VALUES (11112,'E','EL',4);
INSERT INTO detalle_vuelo VALUES (11112,'E','EL',5);
INSERT INTO detalle_vuelo VALUES (11112,'F','EL',1);
INSERT INTO detalle_vuelo VALUES (11112,'F','EL',2);
INSERT INTO detalle_vuelo VALUES (11112,'F','EL',3);
INSERT INTO detalle_vuelo VALUES (11112,'F','EL',4);
INSERT INTO detalle_vuelo VALUES (11112,'F','EL',5);
-- para vuelo 11113
INSERT INTO detalle_vuelo VALUES (11113,'A','BL',1);
INSERT INTO detalle_vuelo VALUES (11113,'A','BL',2);
INSERT INTO detalle_vuelo VALUES (11113,'A','BL',3);
INSERT INTO detalle_vuelo VALUES (11113,'A','BL',4);
INSERT INTO detalle_vuelo VALUES (11113,'A','BL',5);
INSERT INTO detalle_vuelo VALUES (11113,'A','BL',6);
INSERT INTO detalle_vuelo VALUES (11113,'B','BO',1);
INSERT INTO detalle_vuelo VALUES (11113,'B','BL',2);
INSERT INTO detalle_vuelo VALUES (11113,'B','BL',3);
INSERT INTO detalle_vuelo VALUES (11113,'B','BL',4);
INSERT INTO detalle_vuelo VALUES (11113,'B','BL',5);
INSERT INTO detalle_vuelo VALUES (11113,'B','BL',6);
INSERT INTO detalle_vuelo VALUES (11113,'C','SL',1);
INSERT INTO detalle_vuelo VALUES (11113,'C','SL',2);
INSERT INTO detalle_vuelo VALUES (11113,'C','SL',3);
INSERT INTO detalle_vuelo VALUES (11113,'C','SL',4);
INSERT INTO detalle_vuelo VALUES (11113,'C','SL',5);
INSERT INTO detalle_vuelo VALUES (11113,'C','SL',6);
INSERT INTO detalle_vuelo VALUES (11113,'D','SL',1);
INSERT INTO detalle_vuelo VALUES (11113,'D','SL',2);
INSERT INTO detalle_vuelo VALUES (11113,'D','SL',3);
INSERT INTO detalle_vuelo VALUES (11113,'D','SL',4);
INSERT INTO detalle_vuelo VALUES (11113,'D','SL',5);
INSERT INTO detalle_vuelo VALUES (11113,'D','SL',6);
INSERT INTO detalle_vuelo VALUES (11113,'E','EL',1);
INSERT INTO detalle_vuelo VALUES (11113,'E','EO',2);
INSERT INTO detalle_vuelo VALUES (11113,'E','EL',3);
INSERT INTO detalle_vuelo VALUES (11113,'E','EL',4);
INSERT INTO detalle_vuelo VALUES (11113,'E','EL',5);
INSERT INTO detalle_vuelo VALUES (11113,'E','EL',6);
INSERT INTO detalle_vuelo VALUES (11113,'F','EL',1);
INSERT INTO detalle_vuelo VALUES (11113,'F','EL',2);
INSERT INTO detalle_vuelo VALUES (11113,'F','EL',3);
INSERT INTO detalle_vuelo VALUES (11113,'F','EL',4);
INSERT INTO detalle_vuelo VALUES (11113,'F','EL',5);
INSERT INTO detalle_vuelo VALUES (11113,'F','EL',6);

INSERT INTO clientexreservacion VALUES (1,11116,'E','EL',2,pone_edad (11116));

-- inserts detalle_asiento
-- para vuelo 11111
INSERT INTO detalle_asiento VALUES (11111,'BL','A',1000);
INSERT INTO detalle_asiento VALUES (11111,'BL','I',300);
INSERT INTO detalle_asiento VALUES (11111,'SL','A',750);
INSERT INTO detalle_asiento VALUES (11111,'SL','I',200);
INSERT INTO detalle_asiento VALUES (11111,'EL','A',500);
INSERT INTO detalle_asiento VALUES (11111,'EL','I',100);
-- para vuelo 11112
INSERT INTO detalle_asiento VALUES (11112,'BL','A',1500);
INSERT INTO detalle_asiento VALUES (11112,'BL','I',600);
INSERT INTO detalle_asiento VALUES (11112,'SL','A',1000);
INSERT INTO detalle_asiento VALUES (11112,'SL','I',450);
INSERT INTO detalle_asiento VALUES (11112,'EL','A',650);
INSERT INTO detalle_asiento VALUES (11112,'EL','I',200);
-- para vuelo 11113
INSERT INTO detalle_asiento VALUES (11113,'BL','A',1600);
INSERT INTO detalle_asiento VALUES (11113,'BL','I',700);
INSERT INTO detalle_asiento VALUES (11113,'SL','A',1100);
INSERT INTO detalle_asiento VALUES (11113,'SL','I',550);
INSERT INTO detalle_asiento VALUES (11113,'EL','A',750);
INSERT INTO detalle_asiento VALUES (11113,'EL','I',300);

-- inserts cliente
INSERT INTO cliente VALUES (11116,'Jeremy','Madrigal','Portilla','M',STR_TO_DATE('2000,10,15','%Y,%m,%d'));
INSERT INTO cliente VALUES (11111,'Randall','Zumbado','Huertas','M',STR_TO_DATE('2020,9,30','%Y,%m,%d'));
INSERT INTO cliente VALUES (11112,'Nikol','Vargas','Arroyo','F',STR_TO_DATE('2000,12,1','%Y,%m,%d'));
INSERT INTO cliente VALUES (11113,'Jennifer','Madrigal','Portilla','F',STR_TO_DATE('1994,10,9','%Y,%m,%d'));
INSERT INTO cliente VALUES (11114,'Randy','Conejo','Otroapellido','M',STR_TO_DATE('2001,11,5','%Y,%m,%d'));
INSERT INTO cliente VALUES (11115,'Joseph','Valenciano','Otroapellidin','M',STR_TO_DATE('2001,3,15','%Y,%m,%d'));

-- inserts reservacion_vuelo
INSERT INTO reservacion_vuelo (fecha_hora_reserv,codigo_vuelo)
	VALUES (SYSDATE(),11111);
INSERT INTO reservacion_vuelo (fecha_hora_reserv,codigo_vuelo)
	VALUES (SYSDATE(),11111);
INSERT INTO reservacion_vuelo(fecha_hora_reserv,codigo_vuelo)
	values (SYSDATE(),11111);
INSERT INTO reservacion_vuelo (fecha_hora_reserv,codigo_vuelo)
	VALUES (SYSDATE(),11112);
INSERT INTO reservacion_vuelo (fecha_hora_reserv,codigo_vuelo)
	VALUES (SYSDATE(),11113);
INSERT INTO reservacion_vuelo (fecha_hora_reserv,codigo_vuelo)
	VALUES (SYSDATE(),11113);

-- inserts clientexreservacion
-- para vuelo 11111
INSERT INTO clientexreservacion VALUES (1,11115,'E','EL',1,pone_edad (11115));
INSERT INTO clientexreservacion (id_reserv,pasaporte_cliente,tipo_asiento_reserv,ind_edad)
	VALUES (1,11111,'EL',pone_edad (11111));

INSERT INTO clientexreservacion VALUES (2,11114,'F','EL',1,pone_edad (11114));
INSERT INTO clientexreservacion VALUES (2,11116,'F','EL',2,pone_edad (11116));
INSERT INTO clientexreservacion VALUES (3,11113,'D','SL',2,pone_edad (11113));
-- para vuelo 11112
INSERT INTO clientexreservacion VALUES (4,11112,'A','BL',1,pone_edad (11112));
INSERT INTO clientexreservacion VALUES (4,11116,'A','BL',2,pone_edad (11116));
INSERT INTO clientexreservacion VALUES (4,11115,'A','BL',3,pone_edad (11115));
INSERT INTO clientexreservacion VALUES (4,11114,'A','BL',4,pone_edad (11114));
-- para vuelo 11113
INSERT INTO clientexreservacion VALUES (5,11116,'B','BL',1,pone_edad (11116));
INSERT INTO clientexreservacion VALUES (6,11115,'E','EL',2,pone_edad (11115));
INSERT INTO clientexreservacion (id_reserv,pasaporte_cliente,tipo_asiento_reserv,ind_edad)
	VALUES (6,11111,'EL',pone_edad (11111));
select * from clientexreservacion;
-- para registro de aviones


select pone_edad(11114);
/*
Entrada: Un varchar(20)
Salida: No posee
Funcionalidad: Procedure encargado de filtrar los aviones por su marca
*/
DROP procedure IF EXISTS  sh_marca_avion;
DELIMITER //
create procedure sh_marca_avion (in v_marca VARCHAR(20))
begin
    SELECT * 
    FROM avion
    WHERE marca = v_marca;
end
//