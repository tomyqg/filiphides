#use variables.lib
#use sensores.lib
#use "RCM43xx.LIB"
#use Modem_SIMCOM.lib

sensor termo[BUFF_TAM];


void main()
{
      sensor *ptr_termo, *ptr_termo_fin;
      brdInit();

      ptr_termo = termo;
      ptr_termo_fin = &termo[BUFF_TAM-1];

      while(1)
		{
      	esperar(1000);
      	ptr_termo->muestra = Termistor();
         getTimeStamp(timeStamp);
         printf("Temperatura %.2f C\nTimeStamp:\n%s\n", ptr_termo->muestra, timeStamp);

         if (ptr_termo > ptr_termo_fin)
         	ptr_termo = termo;
         ptr_termo+=1;
      }
}