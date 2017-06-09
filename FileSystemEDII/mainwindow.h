#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>
#include <QMouseEvent>
#include <QTreeView>
#include <qlabel.h>
#include <qpushbutton.h>
#include "BloqueFolder.h"
#include "api.h"
#include <QTreeWidget>
#include <QtCore>
#include <QtGui>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private slots:
    void nuevoArchivo();
    void nuevaCarpeta();
    void abrir_archivo();
    void leer_archivo();
    void refrescar();
    void eventoArchivos();
    void eventoCarpetas();
    string obtenerNodo();

    void agregarLabel(char * nombre);
    void insertarCarpeta(char * nombre);
    void insertarArchivo(char * nombre);

    void on_btnNuevo_clicked();
    void on_btnAtras_clicked();
    void on_btnAdelante_clicked();


private:
    Ui::MainWindow *ui;
    QTreeView * arbol;
    int cantBotones,cantLabel,posY, posX;
    string ruta;
    QList<QPushButton*> listaBotones;
    QList<QLabel*> listaEtiquetas;

    QMessageBox msgBox;

    API *api;
    BloqueFolder * folderActual;
    BloqueFolder * raiz;
    QTreeWidgetItem * actual;
    QTreeWidgetItem * AddRoot(QTreeWidgetItem * parent,QString nombre);
};


#endif // MAINWINDOW_H
