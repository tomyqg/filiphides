#use sensores.lib
#use "RCM43xx.LIB"
#use Modem_SIMCOM.lib

void main()
{
		float temp;
		brdInit();
      while(1)
		{
      	esperar(1000);
      	temp = Termistor();
         printf("Temperature at %.2f C\n", temp);
      }
}