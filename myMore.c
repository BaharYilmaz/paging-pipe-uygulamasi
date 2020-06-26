#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100
#define ROW_COUNT 24
#define MAX_ROW 100



int main(int argc, char *argv[])
{
    

  char read_msg[BUFFER_SIZE][MAX_ROW];
  
  int k,dongu=1,toplamSatir=0;

  //cast iþlemi
  int READ_END  = atoi(argv[1]);
 

  // close(fd[WRITE_END]);
  read(READ_END,&read_msg,BUFFER_SIZE*MAX_ROW);
   

    while(toplamSatir<70)
    {

        if(k<ROW_COUNT){
            printf("%s",read_msg[toplamSatir]);
            k++;
            toplamSatir++;
        }
        else
        {
            while (dongu == 1) 
            {
                char girilenKarakter;
            

                printf("\n\n\n");
                printf("1.Okumaya devam etmek icin:[(bosluk)]\n");
                printf("2.Okumayi sonlandirmak icin:[q/Q]\n");
                scanf("%c",&girilenKarakter);

                //girilen karakterin kontrolü
                if(girilenKarakter=='q'|| girilenKarakter=='Q')
                {
                    printf("\nOkuma sonlandiriliyor..\n\n");
                    exit(1);

                }
                
                else if(girilenKarakter==' ')
                {
                    k=0;
                    break;
                }
                else
                {
                    printf("Hatali karakter..\n");
                    continue;
                }

            }
            
        }
        
    }
    printf("\n\nOkunacak yazi kalmadi...\n\n");    
    close(READ_END);
     
    return 0;

}


