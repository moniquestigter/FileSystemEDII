#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    api = new API();

    api->crearDiscoVirtual();
    raiz = api->root;
    folderActual = raiz;
    actual = NULL;
    api->initFromChar(folderActual);
    refrescar();
    api->initIDX();
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

    folder->setObjectName(QString::fromStdString(nombre));
    folder->setGeometry(QRect(QPoint(posX, posY),QSize(50, 50)));
    folder->setStyleSheet("border-image: url(:/Folders-PNG-File.png);");
    folder->show();
    connect(folder, SIGNAL (released()),this, SLOT (abrir_archivo()));
    listaBotones.append(folder);
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

    file->setObjectName(QString::fromStdString(nombre));
    file->setGeometry(QRect(QPoint(posX, posY),QSize(60, 60)));
    file->setStyleSheet("border-image: url(:/Docs-icon-iloveimg-resized.png);");
    file->show();
    connect(file, SIGNAL (released()),this, SLOT (leer_archivo()));
    listaBotones.append(file);
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
    BloqueFolder * bf = api->abrirFolder(obtenerNodo(),folderActual);
    if(bf!=NULL)
    {
        BloqueFolder * temp = folderActual;
        folderActual = bf;
        folderActual->anterior = temp;
        actual = folderActual->item;
        refrescar();
    }
}

void MainWindow::leer_archivo()
{
        //char * contenido = {"Hola"};
        char * contenido = api->leerArchivo(obtenerNodo(),folderActual);
        QMessageBox msgBox;
        std::string str = std::string(contenido);
        QString qstr = QString::fromStdString(str);
        //QString q = "Hola";
        msgBox.setText(qstr);
        msgBox.exec();

}


char * MainWindow::obtenerNodo()
{
    QPushButton* temp = qobject_cast<QPushButton *>(sender());
    if(temp!=NULL)
    {
        for(int x = 0;x<listaBotones.size();x++){
            if(listaBotones.at(x)->objectName() == temp->objectName()){
                string x = temp->objectName().toStdString();
                char * nombre = (char *)malloc(temp->objectName().length());
                strcpy( nombre, x.c_str() );
                return nombre;
            }
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
    //x_1 = api->Duplicados(x_1,2);
    char * nombre = (char *)malloc(x.length());
    strcpy( nombre, x_1.c_str() );

    if(x != "")
    {
        BloqueFolder * bf = api->crearFolder(nombre,folderActual);
        bf->item = AddRoot(actual,QString::fromStdString(nombre));
        insertarCarpeta(nombre);
    }

}

void MainWindow::nuevoArchivo()
{
    QString x = QInputDialog::getText(this,"Nuevo Archivo de Texto","Ingrese el Nombre del Archivo:");
    string x_1 = x.toStdString();
    //x_1 = api->Duplicados(x_1,1);
    char * nombre = (char *)malloc(x.length());
    strcpy( nombre, x_1.c_str() );
    if(x != ""){
        QString x2 = QInputDialog::getText(this,"Contenido","Ingrese el contenido del archivo:");
        string x2_1 = x2.toStdString();
        char * contenido = (char *)malloc(x2.length());
        strcpy( contenido, x2_1.c_str() );

        if(x2 != "")
        {
            BloqueArchivo * ba = api->crearArchivo(nombre,folderActual,contenido);
            ba->item = AddRoot(actual,QString::fromStdString(nombre));
            insertarArchivo(nombre);

        }
    }
}


void MainWindow::on_btnAtras_clicked()
{
    BloqueFolder * temp = folderActual;
    if(folderActual->anterior!=NULL)
    {
        folderActual = folderActual->anterior;
        folderActual->siguiente = temp;
        actual = folderActual->item;
        refrescar();
    }
}

void MainWindow::on_btnAdelante_clicked()
{
    if(folderActual->siguiente != NULL)
    {
        folderActual = folderActual->siguiente;
        actual = folderActual->item;
        refrescar();
    }
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

    //ui->treeWidget->clear();
    vector<BloqueFolder*> folders = folderActual->listaBloqueFolder;

    vector<BloqueArchivo*> archivos = folderActual->listaBloqueArchivo;


    cantBotones = 0;
    cantLabel = 0;
    posX = 170;
    posY = 80;
    ui->lblRuta->setText(folderActual->nombre);

    for(int x = 0; x<folders.size();x++)
        insertarCarpeta(folders.at(x)->nombre);

    for(int x = 0; x<archivos.size();x++)
        insertarArchivo(archivos.at(x)->nombre);   
}

void MainWindow::on_pushButton_clicked()
{
     api->formatear();
     folderActual = api->root;
     actual = folderActual->item;
     ui->treeWidget->clear();
     refrescar();
}

void MainWindow::on_pushButton_2_clicked()
{

    refrescar();
}
