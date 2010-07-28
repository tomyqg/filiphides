#use variables.lib
#use GPS_ET332.lib
#use MODEM_SIMCOM.lib

#define tout 50

void main(){

	static char data[TAM];
   static char msj[TAM];
   auto int n;

   InicializarGPS();
   n=0;

   for(;;)
   {
   	costate
   	{
   		waitfordone n = cof_serDread(data, sizeof(data), tout);
         data[n]='\0';
         /*printf("\n%s\n\n", data);*/
         ProcesarGPS(data, n);
         n=0;
         getTimeStamp(timeStamp);
         sprintf(msj, "Latitud: %s\nLongitud: %s\nTimeStamp:\n%s\n\n", latitud, longitud, timeStamp);
      	printf("%s", msj);
      }

   }
}