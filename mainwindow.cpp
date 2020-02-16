#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Bmp.h"
#include <iostream>
#include <fstream>
#include <QFile>
using namespace  std;


QImage imagen=QImage("//home//siumauricio//Escritorio//24Bits//x.bmp");
Bitmap bmp((char*)"//home//siumauricio//Escritorio//24Bits/x.bmp");                  //Y ese Bitmap es tu clase sique interesante y se llama asi directamente y se crea el objeto que chiste esto
int sizeX=bmp.InfoHeader.Anchura;
int sizeY=bmp.InfoHeader.Altura;//Setearle el tamano al Layout

 //Format_RGB30
QImage image(sizeX,sizeY,QImage::Format_RGB30);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
      int r, g, b;
      int posbit=0;
      int pos=0;





     // bmp.crearGrafica8Bits(image);
      for (int h = sizeY -1; h >= 0; h--) {
               for (int w = 0; w < sizeX; w++) {
                   b =bmp.Colores24[posbit].b;
                   g= bmp.Colores24[posbit].g;
                   r = bmp.Colores24[posbit].r;
                   posbit+=1;
                   image.setPixel(w, h, qRgb(b,g,r));
               }
          
             //posbit+=1;
}





/*
      for (int h = sizeY -1; h >= 0; h--) {
               for (int w = 0; w < sizeX; w++) {
                   b =bmp.Colores16B[posbit].b;
                   g= bmp.Colores16B[posbit].g;
                   r = bmp.Colores16B[posbit].r;
                   posbit+=1;
                   image.setPixel(w, h, qRgb(r,g,b));
               }
          //    posbit+=1;
}
*/
      //bmp.crearGrafica8Bits(image);
      QGraphicsScene *graphic=new QGraphicsScene(this);
      graphic->addPixmap(QPixmap::fromImage(image));
      ui->graphicsView->setScene(graphic);
}
//24Bits
/*

*/
MainWindow::~MainWindow()
{
    delete ui;
}
