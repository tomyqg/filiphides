#use GPS_ET332.lib
#use MODEM_SIMCOM.lib

#define tout 50
#define TAM 200

#define BPS 19200
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
         printf("\n%s\n\n", data);
         ProcesarGPS(data, n);
         n=0;
         sprintf(msj, "Latitud: %s\nLongitud: %s\nHora: %s\nFecha: %s\n\n", latitud, longitud, hora_utc, fecha);
      	printf("%s", msj);
      }

   }
}

