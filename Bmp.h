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
    uint ContadorBits[2];
    int Compresion;
    int TamanoImagen;
    int Pixeles_X;
    int Pixeles_Y;
    int Colores_Usados;
    int Colores_Importantes;
};
#pragma pack(pop)

struct RGB24 {
    uint8_t r,g,b,t;
    void inverse () {
            r = 255 - r;
            g = 255 - g;
            b = 255 - b;
        }
};
struct RGB24B {
    uint8_t r,g,b;
    void inverse () {
            r = 255 - r;
            g = 255 - g;
            b = 255 - b;
        }
};
struct RGB16 {
   uint8_t r,g,b;
};
struct RGBT {
    unsigned char  r,g;
};

class Bitmap
{
public:
    BMP_Header Header;
    BMP_InfoHeader InfoHeader;
    Bitmap ();
    Bitmap (string);
    vector<int>Paleta;
    vector<int>Colores;
    vector<int>PaletaColores;
    vector<RGB16>Colores16B;
    vector<RGB24B>Colores24;
    void crearPaletaColores8Bits();
    string decimaltoBinary(int,int);
    RGB16 obtenerRGB(string digito);
    void decToHexa(int n) ;

    void ObtenerPaleta8Bits(string Filename);

    void crearGrafica8Bits(QImage&,string);
    void crearGrafica16Bits(QImage&,string);
    void crearGrafica24Bits(QImage&,string);

    void ObtenerBmp_Header(string);
    void ObtenerBmp_InfoHeader (string);

    int getTipo();
};
#endif // !BITMAP_H

