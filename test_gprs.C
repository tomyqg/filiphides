#use Modem_SIMCOM.lib

#define BPS  19200

static const char CMD_APN[]="AT+CSTT=\"gprsancel\",\"daicav@adsl37\",\"nasd27\"\r";
static const char CMD_GPRS[]="AT+CIICR\r";
static const char CMD_IP[]="AT+CIFSR\r";
static const char CMD_TCP_IP[]="AT+CIPSTART=\"TCP\",";     //concatenar nºip y puerto
static const char CMD_ENVIAR[]="AT+CIPSEND\r";
static const char CMD_FIN_CXN[]="AT+CIPCLOSE\r";
static const char CMD_LIB_IP[]="AT+CIPSHUT\r";
static const char CMD_IP_STATUS[]="AT+CIPSTATUS\r";
static const char PROMPT[]=">";


void main(){

	static char datos[200];        //el ultimo caracter debe ser Ctrl-Z
   static char num_ip_tcp[25];
   char iniciado[100];

   Inicio_Modem(BPS);
   strcpy(datos, "Prueba de envio de datos a un servidor\032");
	strcpy(num_ip_tcp, "\"200.114.232.92\",\"2020\"\r");

   serCread(iniciado, 100, 10*TIEMPO);

   Enviar_CMD(CMD_APN);
   Respuesta_Modem(ESPERO_OK, respuesta, TIEMPO);

   serCrdFlush();

   Enviar_CMD(CMD_GPRS);
   Respuesta_Modem(ESPERO_OK, respuesta, TIEMPO);

   serCrdFlush();

   Enviar_CMD(CMD_IP_STATUS);
   Respuesta_Modem(ESPERO_OK, respuesta, TIEMPO);

   serCrdFlush();

   Enviar_CMD(CMD_IP);
   esperar(8000);
   Respuesta_Modem(ESPERO_OK, respuesta, TIEMPO);

   Enviar_CMD(CMD_IP_STATUS);
   Respuesta_Modem(ESPERO_OK, respuesta, TIEMPO);

   /*strcat(CMD_TCP_IP, num_ip_tcp);
   Enviar_CMD(CMD_TCP_IP);
   Respuesta_Modem(ESPERO_OK, respuesta, TIEMPO);

   Enviar_CMD(CMD_ENVIAR);
   Respuesta_Modem(PROMPT, respuesta, TIEMPO);
   Enviar_CMD(datos);
   Respuesta_Modem(ESPERO_OK, respuesta, TIEMPO);

	Enviar_CMD(CMD_FIN_CXN);
   Respuesta_Modem(ESPERO_OK, respuesta, TIEMPO);

   Enviar_CMD(CMD_LIB_IP);
   Respuesta_Modem(ESPERO_OK, respuesta, TIEMPO);

   Apagado_Modem();*/
}