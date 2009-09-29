#use sensores.lib
#use "RCM43xx.LIB"
#use Modem_SIMCOM.lib

#define BUFF_TAM 100

sensor termo[BUFF_TAM];

void main()
{
      sensor *ptr_termo, *ptr_termo_fin;
      brdInit(); 

      ptr_termo = termo;
      ptr_termo_fin = &termo[BUFF_TAM-1];

      while(1)
		{
      	esperar(100);
      	ptr_termo->muestra = Termistor();
         //printf("Temperature at %.2f C\n", ptr_termo->muestra);

         if (ptr_termo > ptr_termo_fin)
         	ptr_termo = termo;
         ptr_termo+=1;
      }
}