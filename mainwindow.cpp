#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include "Bmp.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

QImage imagen=QImage("C:\\Users\\Mauricio\\source\\repos\\Proyecto_Bitmap\\Proyecto_Bitmap\\m.bmp");

 Bitmap bmp((char*)"C:\\Users\\Mauricio\\source\\repos\\Proyecto_Bitmap\\Proyecto_Bitmap\\m.bmp");                  //Y ese Bitmap es tu clase sique interesante y se llama asi directamente y se crea el objeto que chiste esto
 int sizeX=bmp.InfoHeader.Anchura;
 int sizeY=bmp.InfoHeader.Altura;//Setearle el tamano al Layout
 QImage image=QImage(sizeX,sizeY,imagen.format());

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   QRgb value;
/*
    for(int i=0, width=bmp.InfoHeader.Anchura; i<width; i++){
          for(int j=0, height=bmp.InfoHeader.Altura; j<height; j++){
              QColor pixel  =QColor(imagen.pixel(i,j));              // value = qRgb((int)bmp.Colores[i][j].r,(int)bmp.Colores[i][j].g,(int)bmp.Colores[i][j].b);
              int color = (pixel.red()+pixel.green()+pixel.blue());
              pixel.setRed(pixel.red());
              pixel.setBlue(pixel.blue());
              pixel.setGreen( pixel.green());

              image.setPixel(i,j,pixel.rgba());

            }
          }

   for (int j=0 ; j<sizeY ; j++){
          for (int i=0 ; i<sizeX ; i++){
            int  r = (int)bmp.Colores[j*sizeX+3*i].r;
                int  g = (int)bmp.Colores[j*sizeX+3*i+1].g;
             int     b = (int)bmp.Colores[j*sizeX+3*i+2].b;
                int    p = (int)bmp.Colores[j*sizeX+3*i+3].p;
              image.setPixel(i,j,qRgba(r,g,b,p));

 }
   }
*/

   for(int i = 0; i < sizeY; i++)
     {

         for(int j = 0; j < sizeX*3; j += 3)
         {
             // Convert (B, G, R) to (R, G, B)
             int  r = (int)bmp.Colores[j*sizeX+3*i].r;
                 int  g = (int)bmp.Colores[j*sizeX+3*i+1].g;
              int     b = (int)bmp.Colores[j*sizeX+3*i+2].b;

                     image.setPixel(sizeX - j / 3 - 1, sizeY- i - 1, qRgb(r,g,b));
         }
     }


    QGraphicsScene *graphic=new QGraphicsScene(this);
    graphic->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(graphic);
}




MainWindow::~MainWindow()
{
    delete ui;
}

