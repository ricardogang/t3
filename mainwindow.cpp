#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUpText();
}
void MainWindow:: setUpText(){

    highlighter = new Highlighter(ui->plainTextEdit->document());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    cursor = ui->plainTextEdit->textCursor();
    cursor.insertText( "\nif () {\n\n}");
}

void MainWindow::on_pushButton_4_clicked()
{
    cursor = ui->plainTextEdit->textCursor();
    cursor.insertText( "\nfor () {\n\n}");
}

void MainWindow::on_pushButton_5_clicked()
{
    cursor = ui->plainTextEdit->textCursor();
    cursor.insertText( "\nwhile () {\n\n}");
}

void MainWindow::on_pushButton_6_clicked()
{
    cursor = ui->plainTextEdit->textCursor();
    cursor.insertText( "\ntry {\n\n} catch () {\n\n}");
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName;

    if (fileName.isNull())
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", ".txt Files (*.txt)");
        curFile = fileName;

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            ui->plainTextEdit->setPlainText(file.readAll());
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(curFile.isEmpty()){
        on_actionSave_as_triggered();
    }else{
        SaveFile();
    }
}

void MainWindow::on_actionSave_as_triggered()
{
   QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"), "", ".txt Files (*.txt)");

    if (!fileName.isEmpty()) {
      curFile= fileName;
      SaveFile();
    }
}
void MainWindow:: SaveFile(){
    QFile file(curFile);
    if(file.open(QFile::WriteOnly)){
        file.write(ui->plainTextEdit->toPlainText().toUtf8());
    }
}

void MainWindow::on_actionNew_triggered()
{
    ui->plainTextEdit->clear();
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Guardar"), "","" );
    ui->label->setToolTip(filename);
    if (filename != "") {

        QFile file(filename);

        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            stream << ui->plainTextEdit->toPlainText();
            file.flush();
            file.close();
        } else {
            QMessageBox::critical(this, tr("Error"), tr("error"));
            return;
        }
    }

    QProcess compilar;
    QString exec = "c:\\develop\\jdk\\bin\\javac";
    QStringList parametros;
    parametros << filename ;

    compilar.start(exec, parametros);

    if (compilar.waitForFinished()){ // sets current thread to sleep and waits for pingProcess end
        QString resultado(compilar.readAllStandardError());
        resultado+= compilar.readAllStandardOutput();
        ui->label->setText(resultado);
    } else {
        ui->label->setText("Error:"+compilar.errorString());
    }
}

void MainWindow::on_pushButton_2_clicked()
{

    QString classname= "Clase";  //conseguir el nombre de la clase
    QProcess correr;
    QString exec = "c.bat"; //crear un archivo con java %1
    QStringList parametros2;

    parametros2 << classname ;

    correr.start(exec, parametros2);

    if (correr.waitForFinished()){ // sets current thread to sleep and waits for pingProcess end
        QString resultado(correr.readAllStandardError());
        resultado+= correr.readAllStandardOutput();
        ui->label->setText(resultado);
    } else {
        ui->label->setText(correr.errorString());
    }

}
