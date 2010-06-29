#use MODEM_SIMCOM.LIB

#define BPS	38400

void main()
{
	int i;

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

   Listar_SMSs();
   Borrar_ALL();
   Listar_SMSs();

   esperar(5000);
   Apagado_Modem();
}