#include "Bmp.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

Bitmap::Bitmap () {}

Bitmap::Bitmap (char* Filename) {
    ObtenerBmp_Header (Filename);
    ObtenerBmp_InfoHeader (Filename);
}

void Bitmap::ObtenerBmp_Header (char* Filename) {
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

void Bitmap::ObtenerBmp_InfoHeader (char* Filename) {
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
    cout << "+ Tamano: " << sizeof (BMP_InfoHeader) << endl;
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



  for (int i = 0; i < InfoHeader.Anchura*InfoHeader.Altura; i++) {
      RGB Pixel;
      File.read (reinterpret_cast<char*>(&Pixel), sizeof (RGB));
      Colores.push_back (Pixel);
  }
  File.close ();




   // for (int i = 0; i < Colores.size(); i++) {
      //  cout << i << " R: " << (int)Colores[i].r << " G: " << (int)Colores[i].g << " B:" <<(int) Colores[i].b << endl;
   // }
     File.close ();
}
