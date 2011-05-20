#ifndef MYDOC_H
#define MYDOC_H

#include <QPrinter>
#include <QPainter>
#include <QThread>
#include <QFileInfo>
#include <poppler/qt4/poppler-qt4.h>

const int PRINT_DPI = 300;

class MyDoc : public QThread
{
    Q_OBJECT

public:
    MyDoc(QStringList pdfFiles, bool startNow = false, int renderDPI = PRINT_DPI);
    ~MyDoc();

private:
    int levo;
    int desno;
    int gor;
    int dol;
    int slikaDPI;
    Poppler::Document *document;
    QStringList *datoteke;
    QPrinter *printer;
    QPainter *painter;
    QImage *slika;

    void setLevo();
    void setDesno();
    void setGor();
    void setDol();
    void getImage(int pageNumber);
    void setDocument(QString fileName);

    int pageNumber;
    int pageNumberCount;
    int fileNumber;
    int fileNumberCount;

protected:
    void run();

private slots:
    void setPageNumber(int value = 0);
    void incPageNumber(int value = 1);
    void setPageNumberCount(int value);
    void setFileNumber(int value = 0);
    void incFileNumber(int value = 1);
    void setFileNumberCount(int value);

signals:
    void pageChanged(int newValue);
    void maxPageChanged(int newValue);
    void fileChanged(int newValue);
    void maxFileChanged(int newValue);
    void finished(bool value);
};

#endif // MYDOC_H
