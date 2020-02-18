#ifndef BMP_H
#define BMP_H
#include <vector>
#include <QImage>
using namespace std;
#include <string>

#pragma pack(push,1)
class BMP_Header {
public:
    char Tipo[2];
    int Tamano;
    int Reservado;
    int OffsetData;
};
#pragma pack(pop)

#pragma pack(push,1)
class BMP_InfoHeader {
public:
    int Tamano;
    int Anchura;
    int Altura;
    char Planes[2];
    char ContadorBits[2];
    int Compresion;
    int TamanoImagen;
    int Pixeles_X;
    int Pixeles_Y;
    int Colores_Usados;
    int Colores_Importantes;
};
#pragma pack(pop)

struct RGB24B {
    uint8_t r,g,b;
};

struct RGB16B {
   uint8_t r,g,b;
};

struct RGB8B {
    uint8_t r,g,b,t;
};
class Bitmap
{
public:
    BMP_Header Header;
    BMP_InfoHeader InfoHeader;
    Bitmap ();
    Bitmap (string);
    void ObtenerBmp_Header(string);
    void ObtenerBmp_InfoHeader (string);

   /*24Bits*/
    int cBYtes=0;
    vector<RGB24B>Colores24;
    void crearGrafica24Bits(QImage&,string);

     /*16Bits*/
    vector<RGB16B>Colores16B;
    void crearGrafica16Bits(QImage&,string);
    string decimaltoBinary(int,int);
    RGB16B obtenerRGB(string digito);

    /*8Bits*/
    vector<int>Paleta;
    vector<int>Colores8B;
    void crearGrafica8Bits(QImage&,string);
    void ObtenerPaleta8Bits(string Filename);

    int getTipo();
};
#endif // !BITMAP_H

