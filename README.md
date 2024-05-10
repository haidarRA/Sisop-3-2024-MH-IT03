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

![Screenshot 2024-05-10 133406](https://github.com/haidarRA/Sisop-3-2024-MH-IT03/assets/150374973/ae450fca-65b7-442c-858b-049628ba991a)



**PERMASALAHAN YANG DIHADAPI SAAT PENGERJAAN**

1. Terdapat error

# Soal 3
Shall Leglerg🥶 dan Carloss Signs 😎 adalah seorang pembalap F1 untuk tim Ferrari 🥵. Mobil F1 memiliki banyak pengaturan, seperti penghematan ERS, Fuel, Tire Wear dan lainnya. Pada minggu ini ada race di sirkuit Silverstone. Malangnya, seluruh tim Ferrari diracun oleh Super Max Max pada hari sabtu sehingga seluruh kru tim Ferrari tidak bisa membantu Shall Leglerg🥶 dan Carloss Signs 😎 dalam race. Namun, kru Ferrari telah menyiapkan program yang bisa membantu mereka dalam menyelesaikan race secara optimal. Program yang dibuat bisa mengatur pengaturan - pengaturan dalam mobil F1 yang digunakan dalam balapan. Programnya ber ketentuan sebagai berikut:
1. Pada program actions.c, program akan berisi function function yang bisa di call oleh paddock.c
2. Action berisikan sebagai berikut:
   1. Gap [Jarak dengan driver di depan (float)]: Jika Jarak antara Driver dengan Musuh di depan adalah < 3.5s maka return Gogogo, jika jarak > 3.5s dan 10s return Push, dan jika jarak > 10s maka return Stay out of trouble.
   2. Fuel [Sisa Bensin% (string/int/float)]: Jika bensin lebih dari 80% maka return Push Push Push, jika bensin di antara 50% dan 80% maka return You can go, dan jika bensin kurang dari 50% return Conserve Fuel.
   3. Tire [Sisa Ban (int)]: Jika pemakaian ban lebih dari 80 maka return Go Push Go Push, jika pemakaian ban diantara 50 dan 80 return Good Tire Wear, jika pemakaian di antara 30 dan 50 return Conserve Your Tire, dan jika pemakaian ban kurang dari 30 maka return Box Box Box.
   4. Tire Change [Tipe ban saat ini (string)]: Jika tipe ban adalah Soft return Mediums Ready, dan jika tipe ban Medium return Box for Softs.

		Contoh:
		[Driver] : [Fuel] [55%]
		[Paddock]: [You can go]

3. Pada paddock.c program berjalan secara daemon di background, bisa terhubung dengan driver.c melalui socket RPC.
4. Program paddock.c dapat call function yang berada di dalam actions.c.
5. Program paddock.c tidak keluar/terminate saat terjadi error dan akan log semua percakapan antara paddock.c dan driver.c di dalam file race.log

    Format log:
    [Source] [DD/MM/YY hh:mm:ss]: [Command] [Additional-info]

    ex :

    [Driver] [07/04/2024 08:34:50]: [Fuel] [55%]

    [Paddock] [07/04/2024 08:34:51]: [Fuel] [You can go]

6. Program driver.c bisa terhubung dengan paddock.c dan bisa mengirimkan pesan dan menerima pesan serta menampilan pesan tersebut dari paddock.c sesuai dengan perintah atau function call yang diberikan.
7. Jika bisa digunakan antar device/os (non local) akan diberi nilai tambahan.
8. untuk mengaktifkan RPC call dari driver.c, bisa digunakan in-program CLI atau Argv (bebas) yang penting bisa send command seperti poin B dan menampilkan balasan dari paddock.c
		
    ex:
    Argv: 
    ./driver -c Fuel -i 55%
   
    in-program CLI:
   
    Command: Fuel
   
    Info: 55%

		Contoh direktori 😶‍🌫️:
.		.
├── client

│   └── driver.c

└── server

    ├── actions.c
    
    ├── paddock.c
    
    └── race.log

**STEP**
1. mkdir client
2. cd client
3. nano driver.c
4. gcc driver.c -o driver
5. mkdir server
6. cd server
7. nano actions.c
8. nano paddock.c
9. gcc paddock.c actions.c -o paddock
10. ./paddock
11. ./driver

**PERMASALAHAN YANG DIHADAPI SAAT PENGERJAAN**
1. Tidak ada.

# Soal 4
Lewis Hamilton 🏎 seorang wibu akut dan sering melewatkan beberapa episode yang karena sibuk menjadi asisten. Maka dari itu dia membuat list anime yang sedang ongoing (biar tidak lupa) dan yang completed (anime lama tapi pengen ditonton aja). Tapi setelah Lewis pikir-pikir malah kepikiran untuk membuat list anime. Jadi dia membuat file (harap diunduh) dan ingin menggunakan socket yang baru saja dipelajarinya untuk melakukan CRUD pada list animenya. 
1. Client dan server terhubung melalui socket. 
2. client.c di dalam folder client dan server.c di dalam folder server
3. Client berfungsi sebagai pengirim pesan dan dapat menerima pesan dari server.
4. Server berfungsi sebagai penerima pesan dari client dan hanya menampilkan pesan perintah client saja.  
5. Server digunakan untuk membaca myanimelist.csv. Dimana terjadi pengiriman data antara client ke server dan server ke client.
    1. Menampilkan seluruh judul
    2. Menampilkan judul berdasarkan genre
    3. Menampilkan judul berdasarkan hari
    4. Menampilkan status berdasarkan berdasarkan judul
    5. Menambahkan anime ke dalam file myanimelist.csv
    6. Melakukan edit anime berdasarkan judul
    7. Melakukan delete berdasarkan judul
    8. Selain command yang diberikan akan menampilkan tulisan “Invalid Command”
6. Karena Lewis juga ingin track anime yang ditambah, diubah, dan dihapus. Maka dia membuat server dapat mencatat anime yang dihapus dalam sebuah log yang diberi nama change.log.

    Format: [date] [type] [massage]

    Type: ADD, EDIT, DEL

    Ex:

   [29/03/24] [ADD] Kanokari ditambahkan.

   [29/03/24] [EDIT] Kamis,Comedy,Kanokari,completed diubah menjadi Jumat,Action,Naruto,completed.

   [29/03/24] [DEL] Naruto berhasil dihapus.

7. Koneksi antara client dan server tidak akan terputus jika ada kesalahan input dari client, cuma terputus jika user mengirim pesan “exit”. Program exit dilakukan pada sisi client.

Hasil akhir:

soal_4/

    ├── change.log
    
    ├── client/
    
    │   └── client.c
    
    ├── myanimelist.csv
    
    └── server/
    
        └── server.c

**STEP**
1. mkdir client
2. cd client
3. nano client.c
4. gcc client.c -o client
5. mkdir server
6. cd server
7. nano server.c
8. gcc server.c -o server
9. ./server
10. ./client

**PERMASALAHAN YANG DIHADAPI SAAT PENGERJAAN**
1. Hasil dari command untuk menampilkan seluruh judul, baik semuanya (show), berdasarkan genre (genre), maupun hari (hari) kadang tidak konsisten. Misalnya, pada saat sebuah testing outputnya untuk command show hanya 16 baris yang kemudian dilanjutkan lagi dengan input command show untuk menampilkan sisanya. Namun, testing yang lain justru lancar - lancar saja dan seluruh judul dapat ditampilkan dalam 1 command saja (bukan 2).
2. Setelah 1 sampai 2 command dari client ke server, program server tidak berfungsi lagi sehingga tidak ada output dari server ke client.
