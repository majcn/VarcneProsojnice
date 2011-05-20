#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint);

    doc = new MyDoc(QFileDialog::getOpenFileNames(0, "Izberi svoje prosojnice", "", "Dokumenti (*.pdf)",0,0), true);
    connect(doc, SIGNAL(maxFileChanged(int)), ui->pbarFile, SLOT(setMaximum(int)));
    connect(doc, SIGNAL(fileChanged(int)), ui->pbarFile, SLOT(setValue(int)));
    connect(doc, SIGNAL(maxPageChanged(int)), ui->pbarPage, SLOT(setMaximum(int)));
    connect(doc, SIGNAL(pageChanged(int)), ui->pbarPage, SLOT(setValue(int)));
    connect(doc, SIGNAL(finished(bool)), ui->btnQuit, SLOT(setEnabled(bool)));
}

MainWidget::~MainWidget()
{
    delete doc;
    delete ui;
}

void MainWidget::on_btnQuit_clicked()
{
    QApplication::quit();
}
