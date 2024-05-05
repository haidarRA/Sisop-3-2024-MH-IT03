# Sisop-3-2024-MH-IT03

## ***KELOMPOK IT 03***
| Nama      | NRP         |
  |-----------|-------------|
  | Haidar Rafi Aqyla | 5027231029   |
  | Hasan | 5027231073  |  
  | Muhammad kenas Galeno Putra  | 5027231069  |

# Praktikum Sistem Operasi Modul 3


# Soal 1

**soal :**

Pada zaman dahulu pada galaksi yang jauh-jauh sekali, hiduplah seorang Stelle. Stelle adalah seseorang yang sangat tertarik dengan Tempat Sampah dan Parkiran Luar Angkasa. Stelle memulai untuk mencari Tempat Sampah dan Parkiran yang terbaik di angkasa. Dia memerlukan program untuk bisa secara otomatis mengetahui Tempat Sampah dan Parkiran dengan rating terbaik di angkasa. Programnya berbentuk microservice sebagai berikut:
Dalam auth.c pastikan file yang masuk ke folder new-entry adalah file csv dan berakhiran  trashcan dan parkinglot. Jika bukan, program akan secara langsung akan delete file tersebut. 
Contoh dari nama file yang akan diautentikasi:
belobog_trashcan.csv
osaka_parkinglot.csv

File csv yang lolos tahap autentikasi akan dikirim ke shared memory. 
Dalam rate.c, proses akan mengambil data csv dari shared memory dan akan memberikan output Tempat Sampah dan Parkiran dengan Rating Terbaik dari data tersebut.

Pada db.c, proses bisa memindahkan file dari new-data ke folder microservices/database, WAJIB MENGGUNAKAN SHARED MEMORY.
Log semua file yang masuk ke folder microservices/database ke dalam file db.log dengan contoh format sebagai berikut:
[DD/MM/YY hh:mm:ss] [type] [filename]
ex : `[07/04/2024 08:34:50] [Trash Can] [belobog_trashcan.csv]

Contoh direktori awal:

.
├──  auth.c
├──  microservices
│   ├──   database
│   │   └──   db.log
│   ├──  db.c
│   └──  rate.c
└──  new-data
    ├──  belobog_trashcan.csv
    ├──  ikn.csv
    └──  osaka_parkinglot.csv

Contoh direktori akhir setelah dijalankan auth.c dan db.c:

.
├── auth.c
├── microservices
│   ├── database
│   │   ├── belobog_trashcan.csv
│   │   ├── db.log
│   │   └── osaka_parkinglot.csv
│   ├── db.c
│   └── rate.c
└── new-data



**STEP**

1. mkdir soal_1 (mambuat direktori soal_1)
2. cd soal_1(masuk ke direktori soal_1)
3. mkdir new-data
4. cd new-data
5. buat file csv (belobog,parkinglot,ikn)
6. cd ..
7. mkdir microservices
8. cd microservices 
9. mkdir database
10. buat db.log dengan touch (masih kosongan)
11. cd..
12.  sekalian buat rate.c dan db.c
13.  cd ..
14.  buat auth.c
15.  run auth.c
16.  run rate.c
17.  run db.c


**DOKUMENTASI**


**PERMASALAHAN YANG DIHADAPI SAAT PENGERJAAN**

1. Terdapat error
   


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

