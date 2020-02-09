#ifndef BMP_H
#define BMP_H
#include <vector>
using namespace std;


#pragma pack(push,1)
class BMP_Header {
public:
    char Tipo[2];
    int Tamano;
    int Reservado;
    int OffsetData;
};
#pragma pack(pop)
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

struct RGB {
    unsigned char r,g, b= 0;
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
    vector<RGB>Colores;
    void ObtenerBmp_Header(char*);
    void ObtenerBmp_InfoHeader (char*);
    void color(int, int, int, int,int);
};
#endif // !BITMAP_H



