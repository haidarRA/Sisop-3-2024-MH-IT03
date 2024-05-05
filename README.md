# Sisop-3-2024-MH-IT03

## ***KELOMPOK IT 03***
| Nama      | NRP         |
  |-----------|-------------|
  | Haidar Rafi Aqyla | 5027231029   |
  | Hasan | 5027231073  |  
  | Muhammad kenas Galeno Putra  | 5027231069  |

# Praktikum Sistem Operasi Modul 3


# Soal 1
# Soal 2

**soal :**

Max Verstappen 🏎️ seorang pembalap F1 dan programer memiliki seorang adik bernama Min Verstappen (masih SD) sedang menghadapi tahap paling kelam dalam kehidupan yaitu perkalian matematika, Min meminta bantuan Max untuk membuat kalkulator perkalian sederhana (satu sampai sembilan). Sembari Max nguli dia menyuruh Min untuk belajar perkalian dari web (referensi) agar tidak bergantung pada kalkulator.

(Wajib menerapkan konsep pipes dan fork seperti yang dijelaskan di modul Sisop. Gunakan 2 pipes dengan diagram seperti di modul 3).

a. Sesuai request dari adiknya Max ingin nama programnya dudududu.c. Sebelum program parent process dan child process, ada input dari user berupa 2 string. Contoh input: tiga tujuh. 

b. Pada parent process, program akan mengubah input menjadi angka dan melakukan perkalian dari angka yang telah diubah. Contoh: tiga tujuh menjadi 21. 

c. Pada child process, program akan mengubah hasil angka yang telah diperoleh dari parent process menjadi kalimat. Contoh: `21` menjadi “dua puluh satu”.

d. Max ingin membuat program kalkulator dapat melakukan penjumlahan, pengurangan, dan pembagian, maka pada program buatlah argumen untuk menjalankan program : 
    perkalian	: ./kalkulator -kali
    penjumlahan	: ./kalkulator -tambah
    pengurangan	: ./kalkulator -kurang
    pembagian	: ./kalkulator -bagi
  Beberapa hari kemudian karena Max terpaksa keluar dari Australian Grand Prix 2024 membuat Max tidak bersemangat untuk melanjutkan programnya sehingga kalkulator yang dibuatnya cuma menampilkan hasil positif jika bernilai negatif maka          program akan print “ERROR” serta cuma menampilkan bilangan bulat jika ada bilangan desimal maka dibulatkan ke bawah.
  
e. Setelah diberi semangat, Max pun melanjutkan programnya dia ingin (pada child process) kalimat akan di print dengan contoh format : 
    perkalian	: “hasil perkalian tiga dan tujuh adalah dua puluh satu.”
    penjumlahan	: “hasil penjumlahan tiga dan tujuh adalah sepuluh.”
    pengurangan	: “hasil pengurangan tujuh dan tiga adalah empat.”
    pembagian	: “hasil pembagian tujuh dan tiga adalah dua.”
    
f. Max ingin hasil dari setiap perhitungan dicatat dalam sebuah log yang diberi nama histori.log. Pada parent process, lakukan pembuatan file log berdasarkan data yang dikirim dari child process. 

**STEP**

1. mkdir soal_2 (mambuat direktori soal_2)
2. cd soal_2 (masuk ke direktori soal_2)
3. nano dudududu.c (membuka dan mengedit file dudududu.c)
4.  gcc dudududu.c -o kalkulator (mengkompilasi file sumber C yang disebut "dudududu.c" menjadi sebuah program yang dapat dijalankan dengan nama "kalkulator")
5.  ./kalkulator -kali (menjalankan program "kalkulator" dengan memberikan opsi untuk melakukan operasi perkalian)
6.  ./kalkulator -bagi (menjalankan program "kalkulator" dengan memberikan opsi untuk melakukan operasi pembagian)
7.  ./kalkulator -tambah (menjalankan program "kalkulator" dengan memberikan opsi untuk melakukan operasi penjumlahan)
8.  ./kalkulator -kurang (menjalankan program "kalkulator" dengan memberikan opsi untuk melakukan operasi pengurangan)

**DOKUMENTASI**

![Screenshot 2024-05-04 201741](https://github.com/haidarRA/Sisop-3-2024-MH-IT03/assets/150374973/fa53e177-8667-4acf-9268-dceb40f55fcd)



**PERMASALAHAN YANG DIHADAPI SAAT PENGERJAAN**

1. Terdapat error

# Soal 3
# Soal 4

