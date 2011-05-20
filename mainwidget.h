#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include "mydoc.h"

namespace Ui {
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    MyDoc *doc;

private:
    Ui::MainWidget *ui;

private slots:
    void on_btnQuit_clicked();
};

#endif // MAINWIDGET_H
