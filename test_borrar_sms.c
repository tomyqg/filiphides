#use "RCM43xx.LIB"
#use MODEM_SIMCOM.LIB

#define BPS      38400
#define MSJ_TAM  255
#define MAX_SMS  31

void Borrar_ALL();

void main()
{
		int i;
		char txt_msj[MSJ_TAM];
      char command[30];
      char num_msj[4];

  	/*Inicializo el Modem*/
   Inicio_Modem(BPS);
   /* Me mantengo en el loop hasta registrarse en la red */
   i=0;
   while(Registrado() != RESP_OK)
   {
         if(i<10){
             i++;
         }else{
         		Apagado_Modem();
         		esperar(3000);
         		Encendido_Modem();
            	i=0;
               }
         esperar(20000);
   }

	/*Limpia el buffer rx y tx del puerto serial C*/
	serCrdFlush();
	serCwrFlush();
	Config_modo_txt();   						/*Configura el modem en modo texto*/
   printf("Se registro en la red\n\n");

   Borrar_ALL();

   /*Imprime los mensajes en memoria del modem*/
   for(i=1; i<MAX_SMS; i++)
   {
   	command[0]='\0';             /*Inicializa el comando*/
      txt_msj[0]='\0';             /*Inicializa el texto del mensaje a ser leido*/
      sprintf(num_msj, "%d", i);   /*Conversion de entero a string*/
      strcat(num_msj, "\r\0");
      strcpy(command, "AT+CMGR=");
      strcat(command, num_msj);
   	Enviar_CMD(command);
   	Respuesta_Modem(ESPERO_OK, txt_msj, TIEMPO);
   	printf("Texto del mensaje:\n%s\n", txt_msj);
   }
   esperar(5000);
   Apagado_Modem();
}

void Borrar_ALL()
{
		int i;
		char ind_msj[4];
  		for(i=1; i<MAX_SMS; i++)
     	{
        	sprintf(ind_msj, "%d", i);   /*Conversion de entero a string*/
        	strcat(ind_msj, "\r\0");
        	Borrar_SMS(ind_msj);         /*Borra el mensaje en la posicion ind_msj*/
      }
}