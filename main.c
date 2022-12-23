#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FALSE 0
#define TRUE 1
#define MAX_TEXTO 100

#define MAX_CONTACTOS 10
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct{
	int dia;
	int mes;
	int ano;
}Fecha;

typedef struct{
	char nombre[50];
	Fecha;
	char nif[10];
	char tipo; //Amigo, Enenmigo, Familiar, Trabajo
	long telefono;
}Contacto;

int ocupacion=0;
Contacto Lista[MAX_CONTACTOS];
int i, j;
char pregunta[100];
char opcion[100];



void lectura(){
	char frase[MAX_TEXTO];
	
	FILE* f;
	f = fopen("AgendaContactos.txt","r");
	if(f==NULL){
		printf("No se ha podido abrir fichero. ");
		return 0;
	}
	fgets(frase,MAX_TEXTO,f);
	frase[strlen(frase)-1]='\0';
	ocupacion=atoi(frase);

	for(j=0; j<ocupacion; j++){
		fgets(frase,MAX_TEXTO,f);
		strcpy(Lista[j].nombre,strtok(frase,"#"));	
		Lista[j].dia=atoi(strtok(NULL,"#"));
		Lista[j].mes=atoi(strtok(NULL,"#"));
		Lista[j].ano=atoi(strtok(NULL,"#"));
		strcpy(Lista[j].nif, strtok(NULL,"#"));
		Lista[j].tipo=strtok(NULL,"#");
		Lista[j].telefono=atol(strtok(NULL,"#"));
	}
	fclose(f);


	printf("\n");
	printf("Se han importado los contactos guardados correctamente\n");

}

void lecturabin(){
	FILE* f;
	f=fopen("AgendaContactos.bin","rb");
	if(f==NULL){
		printf("No se ha podido abrir fichero. ");
		return 0;
	}
	//Voy leyendo del fichero
	fread(&ocupacion, sizeof(int),1,f);
	fread(&Lista, sizeof(Contacto),ocupacion,f);
	fclose(f);
	printf("\n");
	printf("Se han importado los contactos guardados correctamente\n");
	
}

void escritura(){
	FILE* f;
	f = fopen("AgendaContactos.txt","w");
	if(f==NULL){
		printf("No se ha podido abrir fichero. ");
		return 0;
	}
		
	fprintf(f,"%d\n",ocupacion);
	for(i=0; i<ocupacion; i++){
		fprintf(f,"%s#%02d#%02d#%02d#%s#%c#%lu\n",Lista[i].nombre,Lista[i].dia, Lista[i].mes, Lista[i].ano, Lista[i].nif, Lista[i].tipo, Lista[i].telefono);
	}
		
	fclose(f);
	
	f=fopen("AgendaContactos.bin","wb");
	if(f==NULL){
		printf("No se ha podido abrir fichero. ");
		return 0;
	}
	
	
	
	printf("\n");
	printf("Se han guardado los contactos correctamente\n");
}

void escriturabin(){
	FILE* f;
	f = fopen("AgendaContactos.bin","wb");
	if(f==NULL){
		printf("No se ha podido abrir fichero. ");
		return 0;
	}
	//Escribimos en binario
	fwrite(&ocupacion,sizeof(int),1,f);
	fwrite(Lista, sizeof(Contacto),ocupacion,f);
	//Cerramos el fichero
	fclose(f);
	printf("\n");
	printf("Se han guardado los contactos correctamente\n");
}

void Listar(){
	int i;
	Contacto c;
	for(i=0; i<ocupacion; i++){
		c = Lista[i];
		printf("%d. %s %ld\n", i, c.nombre, c.telefono);
	}	
}

void MasFiltros(Contacto Lista[], int ocupacion){
	int i, longitud;
	Contacto c;
	char opcion2;
	char opcion[5];
	char pregunta[5];
	
	
	
	do{
		printf("Seleccione el modo: \n");
		printf(" 1) Un filtro \n");
		printf(" 2) Varios filtros\n");
		fflush(stdin);
		gets(pregunta);
	}while(atoi(pregunta)<1 || atoi(pregunta)>2);
	
	
	
	if(atoi(pregunta)==1){
		printf("Que listado quieres?: ");
		scanf("%c",&opcion2);
		
		if(opcion2=='A'){
			for(i=0; i<ocupacion; i++){
				c = Lista[i];
				if(c.tipo==opcion2){
					printf(" %d. %s %ld\n",i, Lista[i].nombre, Lista[i].telefono);
				}
			}
		}else if(opcion2=='E'){
			for(i=0; i<ocupacion; i++){
				c = Lista[i];
				if(c.tipo==opcion2){
					printf(" %d. %s %ld\n",i, Lista[i].nombre, Lista[i].telefono);
				}
			}
		}else if(opcion2=='T'){
			for(i=0; i<ocupacion; i++){
				c = Lista[i];
				if(c.tipo==opcion2){
					printf(" %d. %s %ld\n",i, Lista[i].nombre, Lista[i].telefono);
				}
			}
		}else if (opcion2=='E'){
			for(i=0; i<ocupacion; i++){
				c = Lista[i];
				if(c.tipo==opcion2){
					printf(" %d. %s %ld\n",i, Lista[i].nombre, Lista[i].telefono);
				}
			}
		}else{
			printf("FILTRO NO VALIDO\n");
		}
	
	}else {
		printf("Que listado quieres?: ");
		gets(opcion);
		longitud=strlen(opcion);
		
		for(i=0; i<ocupacion; i++){
			if(strchr(opcion, Lista[i].tipo)!='\0'){
				printf(" %d. %s %ld\n",i, Lista[i].nombre, Lista[i].telefono);
			}
		}
	}
}

void Mostrar(Contacto Lista[], int ocupacion){
	Contacto c;
	Fecha f;
	char cadena[128];
	
	printf("Escribe la posicion del contacto que quiere conocer: ");
	fflush(stdin);
	gets(cadena);
	i = atoi(cadena);
	printf("\n");
	
	if(i<0 || i> ocupacion){
		printf("No existe ese contacto\n");
		return;
	}
	
	c = Lista[i];
	printf("Nombre: %s\n", c.nombre);
	printf("Fecha: %02d/%02d/%02d\n", c.dia, c.mes, c.ano);
	printf("NIF: %s\n", c.nif);
	printf("Tipo: %c \n", c.tipo);
	printf("Telefono: %lu\n", c.telefono);
	
	
	
	/*
	printf("Escribe la posicion del contacto que quiere conocer: ");
	fflush(stdin);
	gets(posicion);
	
	for(i=0; i!=ocupacion; i++){
		if(atoi(posicion)==i){
			printf("Nombre: %s				|\n", Lista[posicion].nombre);
			printf("Fecha: %02d/%02d/%02d	|\n", Lista[posicion].fecha.dia, Lista[posicion].fecha.mes, Lista[posicion].fecha.ano);
			printf("NIF: %s					|\n", Lista[posicion].nif);
			printf("Tipo: %c 				|\n", Lista[posicion].tipo);
			printf("Telefono: %lu			|\n", Lista[posicion].telefono);
			break;	
		}else{
			printf("No existe ese contacto\n");
		}
	}*/
}

void nuevoContacto(){
	#define FALSE 0
	#define TRUE 1
	Contacto c;
	c = Lista[i];
	int Nifvalido;
	char cadena[128];
	
	
	if(ocupacion==MAX_CONTACTOS){
		printf("La agenda esta llena. No admite mas contactos.\n");
		return;
	}
	
	printf("Escribe el nombre: ");
	gets(c.nombre);
		
	printf("Escribe la fecha: \n");
	printf("DIA:");
	gets(cadena);
	c.dia=atoi(cadena);
	printf("\n");		
	printf("MES:");
	gets(cadena);
	c.mes=atoi(cadena);
	printf("\n");
	printf("ANO:");
	gets(cadena);
	c.ano=atoi(cadena);
	printf("\n");
		
	do{
		printf("Escriba el NIF: ");
		fflush(stdin);
		gets(c.nif);
		printf("\n");
			
		char letras[23] = {'T','R','W','A','G','M','Y','F','P','D','X','B','N','J','Z','S','Q','V','H','L','C','K','E'};
		char strNumero[10];
		char letra;
		int indice;
		int dni;
		int longitud;
		
		longitud = strlen(c.nif);
		letra = c.nif[longitud-1];
		strcpy(strNumero,c.nif);
		strNumero[longitud-1] = '\0';
		
		dni = atoi(strNumero);
		indice = dni%23;
		
		if(letras[indice]==letra){
			printf("El NIF es valido\n");
			printf("%d-%c\n",dni,letra);
			Nifvalido=TRUE;
		}else{
			printf("El NIF no es valido\n");
			Nifvalido=FALSE;
		}	
	}while(Nifvalido==FALSE);
		
	printf("Escriba el tipo(A,E,F,T): ");
	fflush(stdin);
	gets(cadena);
	c.tipo = cadena[0];
	printf("\n");
		
	printf("Escribe el telefono: ");
	fflush(stdin);
	gets(cadena);
	c.telefono = atol(cadena);
	printf("\n");

		
	Lista[ocupacion] = c;		
	ocupacion++;
	printf("\n");
	
}

void borrarContacto(Contacto Lista[], int ocupacion){
	Contacto c;
	Fecha f;
	char cadena[128];
	int localizado;
	
	c = Lista[i];
	
	printf("\n");
	printf("Escriba el numero de  posicion del producto que quiere eliminar: ");
	fflush(stdin);
	gets(cadena);
	i = atoi(cadena);
	printf("\n");
	
	if(i<0 || i>ocupacion){
		printf("No existe ese contacto\n");
		return;
	}
	
	for(i=atoi(cadena); i<ocupacion; i++){
		Lista[i]=Lista[i+1];
	}
	ocupacion--;

}

void editar(Contacto Lista[], int ocupacion){
	Contacto c;
	char cadena[1];
	char nombrenuevo[20];
	char nifnuevo[9];
	char pregunta[1];

	printf("Escribe la posicion del contacto que quiere editar: ");
	gets(cadena);
	i = atoi(cadena);
	printf("\n");
	
	if(i<0 || i> ocupacion){
		printf("No existe ese contacto\n");
		return;
	}
	
	do{
		printf("Que quieres editar?: \n");
		printf("1) Nombre\n");
		printf("2) NIF\n");
		gets(pregunta);
	}while(atoi(pregunta)<1 || atoi(pregunta)>2);
	
	
	
	
	if(atoi(pregunta)==1){
		printf("Escribe el nuevo nombre: ");
		gets(nombrenuevo);
		strcpy(Lista[i].nombre, nombrenuevo);		
	}else{
		printf("Escribe el nuevo NIF: ");
		gets(nombrenuevo);
		strcpy(Lista[i].nif, nifnuevo);
	}
	

	
	/*NO FUNCIONA COMO DEBE
	printf("Escribe el nuevo tipo: ");
	gets(tiponuevo);
	strcpy(Lista[i].tipo, tiponuevo);*/

}

void aviso(Contacto Lista[], int ocupacion){
	Contacto c;
	c = Lista[i];
	
	time_t ahora;
	struct tm tm_ahora;
	time(&ahora);
	tm_ahora = *localtime(&ahora);
	printf("Hoy es %02d-%02d-%02d\n",tm_ahora.tm_mday,tm_ahora.tm_mon+1,tm_ahora.tm_year+1900);
	
	
	for(i=0; i<ocupacion; i++){
		if(tm_ahora.tm_mday==c.dia){
			if(tm_ahora.tm_mon+1==c.mes){
				printf("Es el aniversario de %s \n",c.nombre);
				break;
			}
		}else{
			printf("No es el aniversario de ningun contacto \n");
			break;
		}
	}
}

void Buscarcumple(){	
	int diacumple;
	int mescumple;		
	printf("Escriba el dia de aniversario: ");
	fflush(stdin);
	scanf("%d",&diacumple);
	printf("Escriba el mes de aniversario: ");
	fflush(stdin);
	scanf("%d",&mescumple);
				
	for(i=0; i<ocupacion; i++){
		if(diacumple==Lista[i].dia){
			if(mescumple==Lista[i].mes){
				printf("Es el aniversario de %s \n",Lista[i].nombre);
			break;
			}
		}else{
			printf("No es el aniversario de ninguno de tus contactos\n");
			break;
		}
	}
}

/*void alarma(){
	char cadena[25];
	int i, sec, min, total, total_tiempo_1, total_tiempo_2;
	
	time_t tiempo_1, tiempo_2;
	struct tm tm_tiempo_1, tm_tiempo_2;
	
	do{
		gets(cadena);
		printf("Cuantos minutos quieres que dure la alarma?: ");
		gets(cadena);
		min=atoi(cadena);
		
		printf("\nCuantos segundos quieres que dure la alarma?: ");
		gets(cadena);
		sec=atoi(cadena);
		printf("\n");
		
		if(min<0 || sec<0){
			printf("\nAlguno de los valores que has introducido no es posible\n\n");
		}
	}while(min<0 || sec<0);
	
	printf("\nEsperando %d minutos y %d segundos\n\n", min, sec);
	total= min*60 + sec;
	time(&tiempo_1);
	time(&tiempo_2);
	
	while(tiempo_1+total!=tiempo_2){
		time(&tiempo_2);
	}
	printf("ALARMA!!!!!!!!\n");	
}




int main(int argc, char *argv[]) {
	int tabla[3][3]={{1,2,3},{4,5,6},{7,8,9}};
	int veces;
	int i,j;
	
	int fa,ca; // fila a, columna a, filab,columna b. Cordenadas de una de las celdas y de otra
	int fb,cb;
	int tmp; //Para el intercambio de celdas
	
	//Inicializamos el generador de aleatorios
	srand(time(NULL));
	
	
	//repetimos MAX__VECES el intercambio de celdas
	for(veces=0; veces<MAX_VECES; veces++){
		fa = rand()%3;
		ca = rand()%3;
		fb = rand()%3;
		cb = rand()%3;
		
		//Intercambiamos las celdas
		tmp = tabla[fa][ca];
		tabla[fa][ca] = tabla[fb][cb];
		tabla[fb][cb] = tmp;
	}
	
	//mostramos la tabla
	for(i=0; i<3; i++){
		for(j=0; j<3; j++ ){
			printf("%d ",tabla[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
*/

int main(int argc, char *argv[]) {
	do{
		//Lista de opciones, si elegimos una opcion inexistente (menor que 1 o mayor que 4) nos volverá a preguntar
		do{
			printf("=====AGENDA DE CONTACTOS=====\n");
			printf("Elija una opcion: \n");
			printf("\n");
			printf(" 1) Lista de contactos \n");
			printf(" 2) Lista de contactos (FILTROS)\n");
			printf(" 3) Mostrar detalles \n");
			printf(" 4) Agregar contacto \n");
			printf(" 5) Borrar contacto \n");
			printf(" 6) Editar contacto \n");
			printf(" 7) Calendario de aniversarios \n");
			printf(" 8) Buscar aniversario \n");
			printf(" 9) Cargar contactos \n");
			printf(" 10) Cargar contactos (binario)\n ");
			printf("11) Guardar contactos\n");
			printf(" 12) Guardar contactos(binario)\n");
			printf(" 13) Salir de contactos \n");
			fflush(stdin);
			gets(opcion);
		}while(atoi(opcion)<1 || atoi(opcion)>13);
		
		//Mostrar una funcion  dependiendo de que hayamos elegido
		switch(atoi(opcion)){
			case 1:
				printf("\n");
				printf(" Listar contactos\n");
				Listar();
				break;
				
			case 2:
				printf("\n");
				printf(" Filtrar\n");
				MasFiltros(Lista, ocupacion);
				break;

			case 3:
				printf("\n");
				printf("Mostrar detalles\n");
				Mostrar(Lista, ocupacion);
				break;
			
			case 4:
				printf("\n");
				printf("Agregar Contacto\n");
				nuevoContacto();
				break;
			
			case 5:
				printf("\n");
				printf("Borrar Contacto\n");
				borrarContacto(Lista, ocupacion);
				break;
				
			case 6:
				printf("\n");
				printf("Editar contacto\n");
				editar(Lista, ocupacion);
				break;
			
			case 7:
				printf("\n");
				printf("Aviso de aniversarios\n");
				aviso(Lista, ocupacion);
				break;
			
			case 8:
				printf("\n");
				printf("Buscar aniversarios\n");
				Buscarcumple(Lista, ocupacion);
				break;
				
			case 9:
				printf("\n");
				printf("Cargar contactos\n");
				lectura();
				break;
				
			case 10:
				printf("\n");
				printf("Cargar contactos (binario)\n");
				lecturabin();
				break;
				
			case 11:
				printf("\n");
				printf("Guardar contactos(binario)\n");
				lectura();
				break;
				
			case 12:
				printf("\n");
				printf("Guardar contactos(binario)\n");
				escriturabin();
				break;
		}
		
		/*En el caso de que acabamos de hacer una funcion pero no queremos salir
		nos da la opcion de hacer otra cosa.
		Sin embargo si le damos que no queremos hacer otra accion o anteriormente le damos a finalizar
		nos sacaran del programa.*/
		if(atoi(opcion)!=13){
			printf("\n");
			printf("_____________________________\n");
			printf("Desea realizar otra accion?: \n");
			printf(" 1) SI\n");
			printf(" 2) NO \n");
			fflush(stdin);
			gets(pregunta);
			printf("\n");
			printf("\n");
		}else{
			printf("Finalizando programa\n");
		}
	}while(atoi(pregunta)==1);
	return 0;
}

/*int esNumero(char c){
	if(c>='0'&& c<='9'){
		return TRUE;
	}else{
		return FALSE;
	}
}

int esMayuscula(char c){
	if(c>='A'&& c<='Z'){
		return TRUE;
	}else{
		return FALSE;
	}

int esContrasena(char contrasena[]){
	int i, longitud, digito;
	
	longitud=strlen(contrasena);
	digito=FALSE;
	
	for(i=0; i<longitud; i++){
		if(esNumero(contrasena[i])){
			digito=TRUE;
		}
	}
	
	return digito;
}
*/
