#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100
#define ROW_SIZE 100
#define READ_END  0
#define WRITE_END 1


char dosyaOku(char *dosyaAdi);

char write_msg[ROW_SIZE][BUFFER_SIZE];
int rowCount = 0; 


int main(int argc, char *argv[])
{
	//komut sat�r�ndan parametre girilmi� mi kontrol edilir
	if(argc != 2){
		if(argc != 4){
			printf("Use: ./myData inputFile.txt || ./myData inputFile.txt = myMore\n");
			exit(-1);
		};
	};

	

	//olu�turaca��m�z pipe i�in kap� id'leri tutulur
	int fd[2];
	pid_t pid;


	//komut sat�r�ndan grililen paramtereler al�n�r.Daha sonra bunlar�n do�rulu hakk�nda kontrol yap�lacakt�r.	
    argv[1];//okunacak dosya ad�
	argv[2]; // e�ittir i�areti 
	argv[3]; //my more de�erinin yaz�ld��� yer
		

	//pipe olu�tur
	if(pipe(fd)==-1)
	{
		fprintf(stderr,"Pipe olu�turulamad�");
		return 1;
	}
	//child olu�turulur.
	pid=fork();
		
	if(pid < 0){
		
		fprintf(stderr,"Fork hatas�");
		return 1;
	}	
	else if(pid > 0){
		
		//dosyaOku fonksiyonuna ikinci parametremiz olan okunacak dosya ismi g�nderilir
		dosyaOku(argv[1]);

		//parent pipe'a yazmak i�in okuma kap�s� kapan�r
		close(fd[READ_END]);
		int i=0;
				
		write(fd[WRITE_END],&write_msg,BUFFER_SIZE*rowCount);

        printf("\n\n") ;
        //dok�man� ekrana yazd�rma
		if(argv[2] == NULL){
			for (i=0; i<rowCount; i++ )
			{
				printf("%s",write_msg[i]);
			};
		}     
		printf("\n\n") ;
	
		// pipe write kap�s� ile i� bitti�i i�in bu k�s�m kapan�r
		close(fd[WRITE_END]);
		//�al��an child proses varsa onun i�i bitmesi beklenir
		wait(NULL);
		

	}else{

        //child proses

		if(argv[2] != NULL){
 
            close(fd[WRITE_END]);

            //cast i�lemi
			char str_r[10];
			sprintf(str_r, "%d", fd[READ_END]); 
			
			
			//myMore da kullaca��z i�inde verilerin oldu�u dizi
			char *args[3]; //dizi

			//execv parametreleri dizi olarak ald���ndan, parametre dizimizi olu�turuyoruz.
			args[0]="myMore";//�al��ca�� ikinci dizin
			args[1]=str_r; //read_end
			args[2]=NULL;
			
			//execv ile myMore dosyas�na veriler g�nderilir.
			execv(args[0], args);	
			
		}
	};
	 return 0;
};

char dosyaOku(char *dosyaAdi){

  FILE *fp;
  int j=0;
  char tampon[BUFFER_SIZE];

  //gelen parametrediki dosya ismi ile dosya a�ma okuma i�lemleri
  if((fp=fopen(dosyaAdi, "r")) == NULL) {
	printf("Dosya acilamadi!\n");
	exit(1);
  }
  else{

		while ( !feof(fp) )
		{  
			//dosya okuma ve diziye atma i�lemleri
			fgets(tampon, sizeof(tampon), fp);
			strcpy(write_msg[rowCount], tampon);
			rowCount++;			
			
		}
		

  fclose (fp);
   
  }
  return 1;
} 
