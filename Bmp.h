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

struct RGB24 {
    uint8_t r,g,b,t;
    void inverse () {
            r = 255 - r;
            g = 255 - g;
            b = 255 - b;
        }
};


class Bitmap
{
public:
    BMP_Header Header;
    BMP_InfoHeader InfoHeader;
    Bitmap ();
    Bitmap (char*);
    vector<int>Paleta;
    vector<int>Colores;
    vector<int>PaletaColores;
    void crearPaletaColores();
    void crearGrafica8Bits(QImage&);
    void ObtenerPaleta(char* Filename);
    void ObtenerBmp_Header(char*);
    void ObtenerBmp_InfoHeader (char*);
};
#endif // !BITMAP_H

