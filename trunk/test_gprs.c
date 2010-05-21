#use Modem_SIMCOM.lib

#define BPS  19200

/* ***Comando para listar operador seleccionado y banda de frecuencia *** */
static const char CMD_COPS[]    ="AT+COPS?\r";
static const char CMD_CBAND[]   ="AT+CBAND?\r";
static const char CMD_CSMINS[]  ="AT+CSMINS?\r";

/* ***Comandos para abrir un contexto PDP*** */
static const char CMD_CGATT[]    ="AT+CGATT=1\r";	                					/*Adjunta el servicio GPRS*/
static const char CMD_CGDCONT[]  ="AT+CGDCONT=1,\"IP\",\"adslmovil\"\r"; 			/*Define el contexto PDP(cid, tipo PDP, APN)*/
static const char CMD_CSTT[]     ="AT+CSTT=\"adslmovil\",\"daicav@adsl37\",\"nasd27\"\r"; /*Configura APN, User ID, y password*/
static const char CMD_CIICR[]    ="AT+CIICR\r";                    					/*Levanta la conexion GPRS*/
static const char CMD_CIFSR[]    ="AT+CIFSR\r";                                  /*muestra la ip local asignada*/
static const char CMD_CIPSTATUS[]="AT+CIPSTATUS\r";				    					/*Obtiene el estado de conexion*/
static const char CMD_CGPADDR[]  ="AT+CGPADDR=\r";                               /*Devuelve la direccion del contexto definido*/

/* ***Comandos para conectar a un servidor y enviar datos*** */
static const char CMD_CDNSORIP[]="AT+CDNSORIP=1\r";                         		/*Conexion sera por IP(0), o nombre de dominio(1)*/
static const char CMD_CIPSTART[]="AT+CIPSTART=\"TCP\",\"www.google.com.uy\",\"80\"\r";  /*Arranca la conexion TCP con el servidor*/
static const char CMD_CIPSEND[] ="AT+CIPSEND\r";                            		/*Enviar los datos terminados en Ctrl-Z, luego de devolvernos el caracter >*/
static const char PROMPT[]      =">";

static const char CMD_CIPCLOSE[]="AT+CIPCLOSE\r";  										/*Cierra la conexion TCP o UDP*/
static const char CMD_CIPSHUT[] ="AT+CIPSHUT\r";                            		/*Cierra la conexion*/



void main(){

	int i;
	char datos[100];        																		/*El ultimo caracter debe ser Ctrl-Z*/
   char d_csmins[20];
   char servidor[1000];
   datos[0]='\0';
   //d_csmins[0]='\0';
   servidor[0]='\0';
   i=0;

   Inicio_Modem(BPS);

   while(i<10)
   {
   	if(Registrado() == RESP_OK)
      	i=11;
      else
      {
      	i++;
   		esperar(5000);
      }
   }

   serCrdFlush();
   Enviar_CMD(CMD_CSMINS);
   esperar(100);
   Respuesta_Modem(ESPERO_OK, d_csmins, TIEMPO);
   printf("\nRespuesta al comando CSMINS:\n%s", d_csmins);

   serCrdFlush();
   Enviar_CMD(CMD_CBAND);
   Respuesta_Modem(ESPERO_OK, datos, TIEMPO);
   printf("\nRespuesta al comando CBAND:\n%s", datos);

   serCrdFlush();
   Enviar_CMD(CMD_COPS);
   Respuesta_Modem(ESPERO_OK, datos, TIEMPO);
   printf("\nRespuesta al comando COPS:\n%s", datos);

   if(i==11)
   {
   serCrdFlush(); 																					/*Limpia el buffer de entrada del puerto serial C*/

   Enviar_CMD(CMD_CGATT);
   Respuesta_Modem(ESPERO_OK, datos, TIEMPO);
   printf("\nRespuesta al comando CGATT:\n%s", datos);

   Enviar_CMD(CMD_CGDCONT);
   Respuesta_Modem(ESPERO_OK, datos, TIEMPO);
   printf("\nRespuesta al comando CGDCONT:\n%s", datos);

   Enviar_CMD(CMD_CSTT);
   esperar(5000);
   Respuesta_Modem(ESPERO_OK, datos, TIEMPO);
   printf("\nRespuesta al comando CSTT:\n%s", datos);

   Enviar_CMD(CMD_CIICR);
   esperar(10000);
   Respuesta_Modem(ESPERO_OK, datos, TIEMPO);
   printf("\nRespuesta al comando CIICR:\n%s", datos);

  	Enviar_CMD(CMD_CIFSR);
   Respuesta_Modem(ESPERO_OK, datos, TIEMPO);
   printf("\nRespuesta al comando CIFSR:\n%s", datos);

   Enviar_CMD(CMD_CIPSTATUS);
   Respuesta_Modem(ESPERO_OK, datos, TIEMPO);
   printf("\nRespuesta al comando CIPSTATUS:\n%s", datos);


   Enviar_CMD(CMD_CDNSORIP);
   Respuesta_Modem(ESPERO_OK, datos, TIEMPO);
   printf("\nRespuesta al comando CDNSORIP:\n%s", datos);

   Enviar_CMD(CMD_CIPSTART);
   esperar(10000);
   Respuesta_Modem(ESPERO_OK, datos, TIEMPO);
   printf("\nRespuesta al comando CIPSTART:\n%s", datos);

   Enviar_CMD(CMD_CIPSEND);
   esperar(5000);
   Respuesta_Modem(PROMPT, datos, TIEMPO);
   printf("\nRespuesta al comando CIPSEND:\n%s", datos);

   Enviar_CMD("GET /HTTP/1.1");
	Respuesta_Modem(ESPERO_OK, servidor, TIEMPO);
   printf("\nRespuesta desde servidor:\n%s", servidor);

   Enviar_CMD("\032");

//   Enviar_CMD(CMD_CIPSHUT);
//   Respuesta_Modem(ESPERO_OK, datos, TIEMPO);
//   printf("\nRespuesta al comando CIPSHUT:\n%s", datos);
   }
   esperar(20000);
   Apagado_Modem();
}


