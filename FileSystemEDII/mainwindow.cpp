#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    api = new API();
    raiz = api->root;
    folderActual = raiz;
    api->crearDiscoVirtual();

    refrescar();
}

QTreeWidgetItem * MainWindow::AddRoot(QTreeWidgetItem * parent,QString nombre)
{
    if(parent == NULL){
        QTreeWidgetItem * itm = new QTreeWidgetItem((ui->treeWidget));
        itm->setText(0,nombre);
        return itm;
    }
    else{
        QTreeWidgetItem * itm = new QTreeWidgetItem();
        itm->setText(0,nombre);
        parent->addChild(itm);
        return itm;
    }
}

void MainWindow::agregarLabel(char * nombre)
{
    listaEtiquetas.append(new QLabel(this));
    listaEtiquetas.at(cantLabel)->setText(nombre);
    listaEtiquetas.at(cantLabel)->setGeometry(QRect(QPoint(posX, posY+45),QSize(60, 40)));
    listaEtiquetas.at(cantLabel)->setAlignment(Qt::AlignCenter);
    listaEtiquetas.at(cantLabel)->show();
    cantLabel++;
}

void MainWindow::insertarCarpeta(char * nombre)
{
    agregarLabel(nombre);
    QPushButton * folder = new QPushButton(this);
    listaBotones.append(folder);
    listaBotones.at(cantBotones)->setObjectName(QString::fromStdString(nombre));
    listaBotones.at(cantBotones)->setGeometry(QRect(QPoint(posX, posY),QSize(50, 50)));
    listaBotones.at(cantBotones)->setStyleSheet("border-image: url(:/Folders-PNG-File.png);");
    listaBotones.at(cantBotones)->show();

    connect(listaBotones.at(cantBotones), SIGNAL (released()),this, SLOT (eventoCarpetas()));
    cantBotones++;
    posX = posX + 80;
    if(posX >=600)
    {
        posX = 170;
        posY = posY+90;
    }
}

void MainWindow::insertarArchivo(char * nombre)
{
    agregarLabel(nombre);
    QPushButton * file = new QPushButton(this);
    listaBotones.append(file);
    listaBotones.at(cantBotones)->setObjectName(QString::fromStdString(nombre));
    listaBotones.at(cantBotones)->setGeometry(QRect(QPoint(posX, posY),QSize(60, 60)));
    listaBotones.at(cantBotones)->setStyleSheet("border-image: url(:/Docs-icon-iloveimg-resized.png);");
    listaBotones.at(cantBotones)->show();
    connect(listaBotones.at(cantBotones), SIGNAL (released()),this, SLOT (eventoArchivos()));
    cantBotones++;
    posX = posX + 80;
    if(posX >=600)
    {
        posX = 170;
        posY = posY+90;
    }
}


void MainWindow::abrir_archivo()
{

}

void MainWindow::leer_archivo()
{

}


string MainWindow::obtenerNodo()
{
    QPushButton* temp = qobject_cast<QPushButton *>(sender());
    if(temp!=NULL)
    {
        for(int x = 0;x<listaBotones.size();x++){
            if(listaBotones.at(x)->objectName() == temp->objectName())
                return temp->objectName().toStdString();
        }
    }
    return NULL;
}

void MainWindow::on_btnNuevo_clicked()
{
    QMessageBox msgBoxNuevo;

    msgBoxNuevo.setWindowTitle("File System Utils");
    msgBoxNuevo.setText(tr("Crear Nuevo"));
    QAbstractButton * pButtonCarpeta = msgBoxNuevo.addButton(tr("Carpeta"), QMessageBox::YesRole);
    QPixmap pixmap(":/Folders-PNG-File.png");
    QIcon buttonicon(pixmap);
    pButtonCarpeta->setIcon(buttonicon);

    QAbstractButton * pButtonArchivo = msgBoxNuevo.addButton(tr("Archivo"), QMessageBox::YesRole);
    QPixmap pixmap1(":/Docs-icon-iloveimg-resized.png");
    QIcon buttonicon1(pixmap1);
    pButtonArchivo->setIcon(buttonicon1);

    QAbstractButton * pButtonCancelar = msgBoxNuevo.addButton(tr("Cancelar"), QMessageBox::NoRole);
    QPixmap pixmap2(":/Cancel_Icon-128.png");
    QIcon buttonicon2(pixmap2);
    pButtonCancelar->setIcon(buttonicon2);

    msgBoxNuevo.exec();
    if(msgBoxNuevo.clickedButton()==pButtonCarpeta)
        nuevaCarpeta();
    else if(msgBoxNuevo.clickedButton()==pButtonArchivo)
        nuevoArchivo();

}

void MainWindow::nuevaCarpeta()
{
    QString x = QInputDialog::getText(this,"Nueva Carpeta","Ingrese el Nombre de la Carpeta:");
    string x_1 = x.toStdString();
    char * nombre = (char *)malloc(x.length());
    strcpy( nombre, x_1.c_str() );

    if(x != "")
    {
        BloqueFolder * bf = api->crearFolder(nombre,folderActual);
        //bf->setItem(AddRoot(actual,QString::fromStdString(nombre)));
        insertarCarpeta(nombre);
    }
}

void MainWindow::nuevoArchivo()
{
    QString x = QInputDialog::getText(this,"Nuevo Archivo de Texto","Ingrese el Nombre del Archivo:");
    string x_1 = x.toStdString();
    char * nombre = (char *)malloc(x.length());
    strcpy( nombre, x_1.c_str() );

    QString x2 = QInputDialog::getText(this,"Contenido","Ingrese el contenido del archivo:");
    string x2_1 = x2.toStdString();
    char * contenido = (char *)malloc(x2.length());
    strcpy( contenido, x2_1.c_str() );


    if(x != "")
    {
        BloqueArchivo * ba =api->crearArchivo(nombre,folderActual,contenido);
        //ba->setItem(AddRoot(actual,QString::fromStdString(nombre)));
        insertarArchivo(nombre);
    }
}

void MainWindow::eventoArchivos()
{
    QMessageBox msgBoxArchivos;
    msgBoxArchivos.setWindowTitle("File System Utils");
    msgBoxArchivos.setText(tr("Que desea hacer?"));

    QAbstractButton * pButtonAbrir = msgBoxArchivos.addButton(tr("Leer"), QMessageBox::YesRole);
    QPixmap pixmap(":/oYPS__file_document_enlarge_magnifier_magnify_examine_read_paper_page_text-512.png");
    QIcon buttonicon(pixmap);
    pButtonAbrir->setIcon(buttonicon);

    QAbstractButton * pButtonCancelar = msgBoxArchivos.addButton(tr("Cancelar"), QMessageBox::NoRole);
    QPixmap pixmap2(":/Cancel_Icon-128.png");
    QIcon buttonicon2(pixmap2);
    pButtonCancelar->setIcon(buttonicon2);

    msgBoxArchivos.exec();

    if(msgBoxArchivos.clickedButton()==pButtonAbrir){
        leer_archivo();
        msgBoxArchivos.close();
    }

    else
        msgBoxArchivos.close();
}

void MainWindow::eventoCarpetas()
{
    QMessageBox msgBoxCarpetas;
    msgBoxCarpetas.setWindowTitle("File System Utils");
    msgBoxCarpetas.setText(tr("Que desea hacer?"));

    QAbstractButton * pButtonAbrir = msgBoxCarpetas.addButton(tr("Abrir"), QMessageBox::YesRole);
    QPixmap pixmap(":/oYPS__file_document_enlarge_magnifier_magnify_examine_read_paper_page_text-512.png");
    QIcon buttonicon(pixmap);
    pButtonAbrir->setIcon(buttonicon);

    QAbstractButton * pButtonCancelar = msgBoxCarpetas.addButton(tr("Cancelar"), QMessageBox::NoRole);
    QPixmap pixmap2(":/Cancel_Icon-128.png");
    QIcon buttonicon2(pixmap2);
    pButtonCancelar->setIcon(buttonicon2);

    msgBoxCarpetas.exec();

    if(msgBoxCarpetas.clickedButton()==pButtonAbrir){
        abrir_archivo();
        msgBoxCarpetas.close();
    }

    else
        msgBoxCarpetas.close();
}

void MainWindow::on_btnAtras_clicked()
{

}

void MainWindow::on_btnAdelante_clicked()
{

}

void MainWindow::refrescar()
{
    for(int x = 0;x<listaBotones.size();x++)
    {
        listaBotones.at(x)->close();
        listaEtiquetas.at(x)->close();
    }

    for(int x = 0;x<listaBotones.size();x++)
    {
        listaBotones.removeAt(x);
        listaEtiquetas.removeAt(x);
    }


    cantBotones = 0;
    cantLabel = 0;
    posX = 170;
    posY = 80;


    ui->lblRuta->setText(ruta.c_str());
}

