#include "mydoc.h"

MyDoc::MyDoc(QStringList pdfFiles, bool startNow, int renderDPI)
{
    fileNumber = -1;
    fileNumberCount = -1;
    pageNumber = -1;
    pageNumberCount = -1;

    datoteke = new QStringList(pdfFiles);
    slikaDPI = renderDPI/2; //pac cetrtina

    printer = new QPrinter(QPrinter::HighResolution);
    printer->setResolution(renderDPI);

    if(startNow)
        start();
}

MyDoc::~MyDoc()
{
    delete slika;
    delete datoteke;
    delete document;
    delete printer;
    delete painter;
}

void MyDoc::setDocument(QString fileName)
{
    QFileInfo *fileInfo = new QFileInfo(fileName);
    document = Poppler::Document::load(fileName);
    document->setRenderHint(Poppler::Document::Antialiasing, true);
    document->setRenderHint(Poppler::Document::TextAntialiasing, true);
    document->setRenderHint(Poppler::Document::TextHinting, true);
    printer->setOutputFileName(QString("%1/Prosojnice-%2").arg(fileInfo->absolutePath(), fileInfo->fileName()));  //to je za mal za polepsat se
    delete fileInfo;
}

void MyDoc::setPageNumber(int value)
{
    if (value != pageNumber) {
        pageNumber = value;
        emit pageChanged(pageNumber);
    }
}

void MyDoc::setPageNumberCount(int value)
{
    if (value != pageNumberCount) {
        pageNumberCount = value;
        emit maxPageChanged(pageNumberCount);
    }
}

void MyDoc::incPageNumber(int value)
{
    pageNumber += value;
    emit pageChanged(pageNumber);
}

void MyDoc::setFileNumber(int value)
{
    if (value != fileNumber) {
        fileNumber = value;
        emit fileChanged(fileNumber);
    }
}

void MyDoc::setFileNumberCount(int value)
{
    if (value != fileNumberCount) {
        fileNumberCount = value;
        emit maxFileChanged(fileNumberCount);
    }
}

void MyDoc::incFileNumber(int value)
{
    fileNumber += value;
    emit fileChanged(fileNumber);
}

void MyDoc::run()
{
    emit finished(false);

    const int PAGE_SPACE = 50;
    int y = 0;

    setFileNumberCount(datoteke->count());
    for(setFileNumber(0); fileNumber<fileNumberCount; incFileNumber(1))
    {
        setDocument(datoteke->at(fileNumber));

        painter = new QPainter(printer);
        painter->setRenderHint(QPainter::Antialiasing, true);

        setPageNumberCount(document->numPages());
        for(setPageNumber(0); pageNumber<pageNumberCount; incPageNumber(1))
        {
            getImage(pageNumber);
            if(y+slika->height()>=printer->height())
            {
                printer->newPage();
                y = 0;
            }
            painter->drawImage(0, y, *slika);
            y += slika->height() + PAGE_SPACE;
            painter->drawLine(0, y-PAGE_SPACE/2, slika->width(), y-PAGE_SPACE/2); //za locenje slik
        }
        painter->end();
    }

    emit finished(true);
}

void MyDoc::getImage(int pageNumber)
{
    slika = new QImage(document->page(pageNumber)->renderToImage(slikaDPI,slikaDPI));
    setLevo();
    setDesno();
    setGor();
    setDol();
    delete slika;
    slika = new QImage(document->page(pageNumber)->renderToImage(slikaDPI,slikaDPI,levo,gor,desno-levo,dol-gor));
}

void MyDoc::setLevo()
{
    levo = 0;
    for(int i=0; i<slika->width(); i++)
    {
        if(levo != 0)
            break;
        for(int j=0; j<slika->height(); j++)
            if(slika->pixel(i,j) != QColor(Qt::white).rgb())
            {
                levo = i;
                break;
            }
    }
}

void MyDoc::setDesno()
{
    desno = 0;
    for(int i=slika->width()-1; i>=0; i--)
    {
        if(desno != 0)
            break;
        for(int j=0; j<slika->height(); j++)
            if(slika->pixel(i,j) != QColor(Qt::white).rgb())
            {
                desno = i;
                break;
            }
    }
}

void MyDoc::setGor()
{
    gor = 0;
    for(int i=0; i<slika->height(); i++)
    {
        if(gor != 0)
            break;
        for(int j=0; j<slika->width(); j++)
            if(slika->pixel(j,i) != QColor(Qt::white).rgb())
            {
                gor = i;
                break;
            }
    }
}

void MyDoc::setDol()
{
    dol = 0;
    for(int i=slika->height()-1; i>=0; i--)
    {
        if(dol != 0)
            break;
        for(int j=0; j<slika->width(); j++)
            if(slika->pixel(j,i) != QColor(Qt::white).rgb())
            {
                dol = i;
                break;
            }
    }
}
