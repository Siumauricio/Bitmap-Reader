#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Bmp.h"
#include <iostream>
#include <QMessageBox>
#include <fstream>
#include <QFile>
using namespace  std;

QString DesplegarInformacion(Bitmap);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Aceptar_clicked()
{
    QString tuna=ui->nombre->text();
    string palabra=ui ->nombre->text().toStdString();
    QImage imagen;
    QImage image;
    Bitmap bmp("//home//siumauricio//Escritorio//Imagenes//"+palabra+".bmp");
    imagen=QImage("//home//siumauricio//Escritorio//Imagenes//"+tuna+".bmp");
    
    if (imagen.isNull()) {
        QMessageBox::about(this,"Error","Error Archivo No Existe en del directorio!");
        return;
    }
    if(bmp.getTipo()==24){
        image=QImage(imagen.width(),imagen.height(),QImage::Format_RGB30);
        bmp.crearGrafica24Bits(image,"//home//siumauricio//Escritorio//Imagenes//"+palabra+".bmp");
        ui->Info->setText(DesplegarInformacion(bmp));

    }else if(bmp.getTipo()==16){
        image=QImage(imagen.width(),imagen.height(),QImage::Format_RGB30);
         bmp.crearGrafica16Bits(image,"//home//siumauricio//Escritorio//Imagenes//"+palabra+".bmp");
         ui->Info->setText(DesplegarInformacion(bmp));

    }else if(bmp.getTipo()==8){
        image=QImage(imagen.width(),imagen.height(),QImage::Format_RGB30);
        bmp.crearGrafica8Bits(image,"//home//siumauricio//Escritorio//Imagenes//"+palabra+".bmp");
        ui->Info->setText(DesplegarInformacion(bmp));

    }else{
     QMessageBox::about(this,"Error","Formato Invalido!");
    }

    QGraphicsScene *graphic=new QGraphicsScene(this);
    graphic->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(graphic);
}

QString DesplegarInformacion(Bitmap bmp){
    bmp.Header.Tipo[2]='\0';
    string type=bmp.Header.Tipo;
    string pl= "==== BMP HEADER ====\nTipo: " +type+"\nTamano Archivo: "+to_string(bmp.Header.Tamano)+"\nEspacio Reservado: "+to_string(sizeof(bmp.Header.Reservado))+"\nDataOffset: "+to_string(bmp.Header.OffsetData)+"\nBytes: "+to_string(bmp.cBYtes)+"\n SizeV: "+to_string(bmp.Colores24.size());
    string inf="==== BMP INFOHEADER ====\nTamano: "+to_string(40)+"\nAnchura: "+to_string(bmp.InfoHeader.Anchura)+"\nAltura: "+to_string(bmp.InfoHeader.Altura)+"\nPlanos: "+to_string((int)bmp.InfoHeader.Planes[0])+"\nBits: "+to_string((int)bmp.InfoHeader.ContadorBits[0])+"\nCompresion: "+to_string(bmp.InfoHeader.Compresion)+"\nTamano Imagen: "+to_string(bmp.InfoHeader.TamanoImagen)+"\nPixel X: "+to_string(bmp.InfoHeader.Pixeles_X)+"\nPixel Y:"+to_string(bmp.InfoHeader.Pixeles_Y)+"\nColores U: "+to_string(bmp.InfoHeader.Colores_Usados)+"\nColores I: "+to_string(bmp.InfoHeader.Colores_Importantes) ;
    QString qstr = QString::fromStdString(pl+"\n\n"+inf);
    return qstr;
}

void MainWindow::on_Limpiar_clicked()
{
    QGraphicsScene *graphic=new QGraphicsScene(this);
    ui->nombre->setText("");
    ui->Info->setText("");
    ui->graphicsView->setScene(graphic);
}
