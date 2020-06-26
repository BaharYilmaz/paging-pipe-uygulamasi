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
	//komut satýrýndan parametre girilmiþ mi kontrol edilir
	if(argc != 2){
		if(argc != 4){
			printf("Use: ./myData inputFile.txt || ./myData inputFile.txt = myMore\n");
			exit(-1);
		};
	};

	

	//oluþturacaðýmýz pipe için kapý id'leri tutulur
	int fd[2];
	pid_t pid;


	//komut satýrýndan grililen paramtereler alýnýr.Daha sonra bunlarýn doðrulu hakkýnda kontrol yapýlacaktýr.	
    argv[1];//okunacak dosya adý
	argv[2]; // eþittir iþareti 
	argv[3]; //my more deðerinin yazýldýðý yer
		

	//pipe oluþtur
	if(pipe(fd)==-1)
	{
		fprintf(stderr,"Pipe oluþturulamadý");
		return 1;
	}
	//child oluþturulur.
	pid=fork();
		
	if(pid < 0){
		
		fprintf(stderr,"Fork hatasý");
		return 1;
	}	
	else if(pid > 0){
		
		//dosyaOku fonksiyonuna ikinci parametremiz olan okunacak dosya ismi gönderilir
		dosyaOku(argv[1]);

		//parent pipe'a yazmak için okuma kapýsý kapanýr
		close(fd[READ_END]);
		int i=0;
				
		write(fd[WRITE_END],&write_msg,BUFFER_SIZE*rowCount);

        printf("\n\n") ;
        //dokümaný ekrana yazdýrma
		if(argv[2] == NULL){
			for (i=0; i<rowCount; i++ )
			{
				printf("%s",write_msg[i]);
			};
		}     
		printf("\n\n") ;
	
		// pipe write kapýsý ile iþ bittiði için bu kýsým kapanýr
		close(fd[WRITE_END]);
		//çalýþan child proses varsa onun iþi bitmesi beklenir
		wait(NULL);
		

	}else{

        //child proses

		if(argv[2] != NULL){
 
            close(fd[WRITE_END]);

            //cast iþlemi
			char str_r[10];
			sprintf(str_r, "%d", fd[READ_END]); 
			
			
			//myMore da kullacaðýz içinde verilerin olduðu dizi
			char *args[3]; //dizi

			//execv parametreleri dizi olarak aldýðýndan, parametre dizimizi oluþturuyoruz.
			args[0]="myMore";//çalýþcaðý ikinci dizin
			args[1]=str_r; //read_end
			args[2]=NULL;
			
			//execv ile myMore dosyasýna veriler gönderilir.
			execv(args[0], args);	
			
		}
	};
	 return 0;
};

char dosyaOku(char *dosyaAdi){

  FILE *fp;
  int j=0;
  char tampon[BUFFER_SIZE];

  //gelen parametrediki dosya ismi ile dosya açma okuma iþlemleri
  if((fp=fopen(dosyaAdi, "r")) == NULL) {
	printf("Dosya acilamadi!\n");
	exit(1);
  }
  else{

		while ( !feof(fp) )
		{  
			//dosya okuma ve diziye atma iþlemleri
			fgets(tampon, sizeof(tampon), fp);
			strcpy(write_msg[rowCount], tampon);
			rowCount++;			
			
		}
		

  fclose (fp);
   
  }
  return 1;
} 
