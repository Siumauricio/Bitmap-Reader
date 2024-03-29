
#include "Bmp.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <dirent.h>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <QColor>
#include <bitset>

#include <stdio.h>
using namespace std;

Bitmap::Bitmap () {}

Bitmap::Bitmap (string Filename) {
    ObtenerBmp_Header(Filename);
    ObtenerBmp_InfoHeader(Filename);
}

void Bitmap::ObtenerBmp_Header (string Filename) {
    ifstream File;
    File.open (Filename, ifstream::in | ifstream::binary);
    if (File.fail ()) {
        return;
    }
    char* Header_Posiciones = new char[sizeof (BMP_Header)];
    File.read (Header_Posiciones, sizeof (BMP_Header));
    char informacion[4];

    copy (Header_Posiciones + 0, Header_Posiciones + 2, informacion);
    memcpy (&Header.Tipo, informacion, 2);

    copy (Header_Posiciones + 2, Header_Posiciones + 6, informacion);
    memcpy (&Header.Tamano, informacion, 4);

    copy (Header_Posiciones + 10, Header_Posiciones + 14, informacion);
    memcpy (&Header.OffsetData, informacion, 4);

    cout << "==== BMP HEADER ====" << endl;
    cout << "+ Tipo: " << Header.Tipo[0] << Header.Tipo[1] << endl;
    cout << "+ Tamano Archivo: " << Header.Tamano << endl;
    cout << "+ Espacio Reservado: " << sizeof (Header.Reservado) << endl;
    cout << "+ DataOffset: " << Header.OffsetData << endl;

    cout << endl;
    File.close ();
}

void Bitmap::ObtenerBmp_InfoHeader (string Filename) {
    ifstream File;
    File.open (Filename, ifstream::in | ifstream::binary);
    if (File.fail ()) {
        return;
    }
    char* Info_Posiciones = new char[sizeof (BMP_InfoHeader) + sizeof (BMP_Header)];
    File.read (Info_Posiciones, sizeof (BMP_InfoHeader) + sizeof (BMP_Header));
    char informacion[4];

    copy (Info_Posiciones + 18, Info_Posiciones + 22, informacion);
    memcpy (&InfoHeader.Anchura, informacion, 4);

    copy (Info_Posiciones + 22, Info_Posiciones + 26, informacion);
    memcpy (&InfoHeader.Altura, informacion, 4);

    copy (Info_Posiciones + 26, Info_Posiciones + 28, informacion);
    memcpy (&InfoHeader.Planes, informacion, 2);

    copy (Info_Posiciones + 28, Info_Posiciones + 30, informacion);
    memcpy (&InfoHeader.ContadorBits, informacion, 2);

    copy (Info_Posiciones + 30, Info_Posiciones + 34, informacion);
    memcpy (&InfoHeader.Compresion, informacion, 4);

    copy (Info_Posiciones + 34, Info_Posiciones + 38, informacion);
    memcpy (&InfoHeader.TamanoImagen, informacion, 4);

    copy (Info_Posiciones + 38, Info_Posiciones + 42, informacion);
    memcpy (&InfoHeader.Pixeles_X, informacion, 4);

    copy (Info_Posiciones + 42, Info_Posiciones + 46, informacion);
    memcpy (&InfoHeader.Pixeles_Y, informacion, 4);

    copy (Info_Posiciones + 46, Info_Posiciones + 50, informacion);
    memcpy (&InfoHeader.Colores_Usados, informacion, 4);

    copy (Info_Posiciones + 50, Info_Posiciones + 54, informacion);
    memcpy (&InfoHeader.Colores_Importantes, informacion, 4);

    cout << "==== BMP INFOHEADER ====" << endl;
    cout << "+ Tamano: " << 40<< endl;
    cout << "+ Anchura: " << InfoHeader.Anchura << endl;
    cout << "+ Altura: " << InfoHeader.Altura << endl;
    cout << "+ Planos: " << (int)InfoHeader.Planes[0] << endl;
    cout << "+ Contador Bits: " << (int)InfoHeader.ContadorBits[0] << endl;
    cout << "+ Compresion: " << InfoHeader.Compresion << endl;
    cout << "+ Tamano Imagen: " << InfoHeader.TamanoImagen << endl;
    cout << "+ Pixel X: " << InfoHeader.Pixeles_X << endl;
    cout << "+ Pixel Y: " << InfoHeader.Pixeles_Y << endl;
    cout << "+ Colores U: " << InfoHeader.Colores_Usados << endl;
    cout << "+ Colores I: " << InfoHeader.Colores_Importantes << endl;
    File.seekg (Header.OffsetData, File.beg);

    if (getTipo()==24) {
        for (int row = 0; row < InfoHeader.Altura; row++){
                for (int col = 0; col < InfoHeader.Anchura; col++) {
                    RGB24B  Pixel;
                    File.read (reinterpret_cast<char*>(&Pixel), sizeof (RGB24B));
                    Colores24.push_back (Pixel);
                }
                File.seekg(InfoHeader.Anchura % 4, std::ios::cur);
        }
    }else if(getTipo()==16){
       for (int row = 0; row < InfoHeader.Altura; row++){
                for (int col = 0; col < InfoHeader.Anchura; col++) {
                    RGB16B  Pixel;
                    File.read (reinterpret_cast<char*>(&Pixel), 2);
                    RGB16B Color=obtenerRGB(decimaltoBinary(Pixel.r,Pixel.g));
                    Colores16B.push_back (Color);
                }
        }
    }else if (getTipo()==8) {
        for (int row = 0; row < InfoHeader.Altura; row++){
                for (int col = 0; col < InfoHeader.Anchura; col++) {
                    RGB8B Pixel;
                    File.read (reinterpret_cast<char*>(&Pixel), 1);
                    Colores8B.push_back (Pixel.r);
                }
        }
          ObtenerPaleta8Bits(Filename);
    }
  File.close ();
}

/*INICIO 24 BITS*/
void Bitmap::crearGrafica24Bits(QImage &img,string path){
    int posbit = 0;
    int r,g,b=0;
    for (int h = InfoHeader.Altura  -1; h >= 0; h--) {
         for (int w = 0; w < InfoHeader.Anchura; w++) {
             b =Colores24[posbit].b;
             g =Colores24[posbit].g;
             r =Colores24 [posbit].r;
             posbit+=1;
             img.setPixel(w, h, qRgb(b,g,r));
         }
       }
}
/*FIN 24 BITS*/

/*INICIO 16 BITS*/
void Bitmap::crearGrafica16Bits(QImage &img,string path){
   int posbit = 0;
   int r,g,b=0;
   int relleno = 0;
   int anchoAjustable = InfoHeader.Anchura;
   while((anchoAjustable %2) != 0){
       relleno += 1;
       anchoAjustable += relleno;
   }
   for (int h = InfoHeader.Altura  -1; h >= 0; h--) {
        for (int w = 0; w < anchoAjustable; w++) {
            if (w<InfoHeader.Anchura) {
                b =Colores16B[posbit].b;
                g =Colores16B[posbit].g;
                r =Colores16B[posbit].r;
                img.setPixel(w, h, qRgb(r,g,b));
            }
            posbit+=1;
        }
      }
}
string Bitmap::decimaltoBinary(int decimal,int decimal2){
    std::bitset<8> bin_x(decimal2);
    string digito=bin_x.to_string();
    std::bitset<8> bin_x2(decimal);
    string digito2=bin_x2.to_string();
    digito+=digito2;
    return digito;
}

RGB16B Bitmap::obtenerRGB(string digito){
    RGB16B Pixel;
    string R;
    string G;
    string B;
    for (int i = 1; i <= digito.length(); ++i) {
        if (i<=5) {
           R += digito[i];
        }else if (i>5&&i<=10) {
          G += digito[i];
         }else if (i>10&&i<=15) {
          B+=digito[i];
          }
    }
    int r_= (stoi(R, 0, 2)* 255) / 31;
    int g_= (stoi(G, 0, 2)* 255) / 31;
    int b_= (stoi(B, 0, 2)* 255) / 31;
    Pixel.r=r_;
    Pixel.g=g_;
    Pixel.b=b_;
    return Pixel;
}
/*FIN 16 BITS*/

/*INICIO 8 BITS*/
void Bitmap::crearGrafica8Bits(QImage &img,string path){
    ObtenerBmp_Header (path);
    ObtenerBmp_InfoHeader (path);
    int posbit = 0;
    int rgb = 0;
    int indice = 0;
    int relleno = 0;
    int anchoAjustable = InfoHeader.Anchura;
    while((anchoAjustable % 4) != 0){
        relleno += 1;
        anchoAjustable += relleno;
    }

    for (int h = InfoHeader.Altura - 1; h >= 0; h--) {
         for (int w = 0; w < anchoAjustable; w++) {
             if(w<InfoHeader.Anchura){
              indice = (int)Colores8B[posbit];
              rgb = this->Paleta[indice];
              img.setPixel(w, h, rgb);
             }
                   posbit++;
          }
     }
}

void Bitmap::ObtenerPaleta8Bits(string Filename){
    ifstream File;
    File.open (Filename, ifstream::in | ifstream::binary);
    if (File.fail ()) {
        return;
    }
    char* Informacion = new char[sizeof (BMP_InfoHeader) + sizeof (BMP_Header)];
    File.read (Informacion, sizeof (BMP_InfoHeader) + sizeof (BMP_Header));
    File.seekg(54,File.beg);
      int r, g, b, t;
    for (int i = 0; i < 256; ++i) {
        RGB8B  Pixel;
        File.read (reinterpret_cast<char*>(&Pixel),sizeof(RGB8B));
        r = (int)Pixel.r;
        g = (int)Pixel.g;
        b = (int)Pixel.b;
        Paleta.push_back(qRgb(b,g,r));
    }
}
/*FIN 8 BITS*/
int Bitmap::getTipo(){
   int bit=InfoHeader.ContadorBits[0];
    return bit;
}
