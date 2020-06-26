# Paging Pipe Uygulaması

## Amaç
Paging Pipe Uygulaması ordinary pipe kullanarak iki prosesin haberleştirilmesi amaçlamaktadır. Bu amaç doğrultusunda bir komut üzerinden alınan çıktı başka bir komutun girdisi olarak yönlendirilmiştir.

## Uygulama Çalışma Mantığı
İki proses arasında haberleşmenin sağlanması için myData prosesinde oluşturulmuş olan çocuk proses myMore, execv fonksiyonu ile myData üzerinden çalıştırılır. Execv fonksiyonu program adını ve okuma kapısını (READ_END) parametre olarak alır. Çocuk proses olan myMore prosesi parametre olarak gelen okuma kapısı ile pipe üzerinden okuma işlemi gerçekleştirir. Okunan veriler 24 satırlık parçalar halinde ekranda gösterilir. Her 24 satırın sonunda kullanıcıdan bir karakter istenir. Boşluk karakteri girildiğinde 24 satır daha okunur,'q' karakteri girildiğinde okuma işlemi sonlandırılarak uygulamadan çıkış yapılır.

## Uygulamayı Derleme ve Çalıştırma

* Derleme

    ```gcc -o myData myData.c```
 
    ```gcc -o myMore myMore.c ```

* myData prosesini çalıştırma;
  
    ``` ./myData inputFile.txt ```

* myMore prosesini çalıştırma;

    ``` ./myData inputFile.txt = myMore```


## Ekran Çıktıları

* myData

![resim](https://user-images.githubusercontent.com/48556212/85899274-83df8580-b806-11ea-9ed4-1dbc76175e80.png)

* myMore

![resim](https://user-images.githubusercontent.com/48556212/85899722-2ac42180-b807-11ea-8036-9a4aedd2a836.png)
![resim](https://user-images.githubusercontent.com/48556212/85899791-534c1b80-b807-11ea-987c-a64ea7a58475.png)
## Kullanılan Teknolojiler

C
