#include "grafico.h"
#include <QPainter>
#include <QResizeEvent>
#include <QPointF>

Grafico::Grafico(QWidget *parent)
    :QLabel(parent)
    , eval()
    , img()
    , cor(0,0,255)
    , largura(0), altura(0)
    , minX(0.0)
    , maxX(0.0)
    , minY(0.0)
    , maxY(0.0)
    , nMarcX(0)
    , nMarcY(0)
{

}



bool Grafico::empty() const
{
    return eval.empty();
}

void Grafico::setLimites(int MinX, int MaxX, int MinY, int MaxY, int Expoente)
{
    minX = MinX * std::pow(10.0,Expoente);
    maxX = MaxX * std::pow(10.0,Expoente);
    minY = MinY * std::pow(10.0,Expoente);
    maxY = MaxY * std::pow(10.0,Expoente);

    nMarcX = 1+MaxX-MinX;
    nMarcY = 1+MaxY-MinY;
}

void Grafico::setFuncao(const std::string &S)
{
    eval.set(S);
}

void Grafico::clearFuncao()
{
    eval.clear();
}

void Grafico::setCor(int R, int G, int B)
{
    cor = QColor(R,G,B);
}

void Grafico::apagar()
{
    largura = width();
    altura = height();
    img = QPixmap(largura,altura);
    img.fill(Qt::white);
    QPainter painter(&img);
    QPen pen(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);
    double Izero = convYtoI(0.0);
    if (Izero>= 0 && Izero<= altura-1){
        painter.drawLine(0,Izero,largura-1,Izero);
        for(int i=0; i<nMarcX; ++i){
            double Jmarc = convXtoJ(minX + (maxX-minX)*i/(nMarcX-1));
            painter.drawLine(Jmarc,Izero-3,Jmarc,Izero+3);
        }
    }
    double Jzero = convXtoJ(0.0);
    if (Jzero>= 0 && Jzero<= largura-1){
        painter.drawLine(Jzero,0,Jzero,altura-1);
        for(int i=0; i<nMarcY; ++i){
            double Imarc = convYtoI(minY + (maxY-minY)*i/(nMarcY-1));
            painter.drawLine(Jzero-3,Imarc,Jzero+3,Imarc);
        }
    }
    setPixmap(img);
}

void Grafico::plotar()
{
    QPainter painter(&img);
    QPen pen(cor);
    pen.setWidth(1);
    painter.setPen(pen);
    double Iant = -1;
    for(int j = 0; j<largura; ++j){
        double X = convJtoX(j);
        double Y = eval(X);
        double I = convYtoI(Y);
        if(I>=0 && I<altura && Iant>= 0 && Iant<altura){
            QLineF line(j-1,Iant,j,I);
            painter.drawLine(line);
        }
        Iant = I;
    }
    setPixmap(img);
}

double Grafico::convXtoJ(const double X) const
{
    return ((largura-1)*(X-minX)/(maxX-minX));
}

double Grafico::convYtoI(const double Y) const
{
    return ((altura-1)*(maxY-Y)/(maxY-minY));
}

double Grafico::convJtoX(const double J) const
{
    return (minX+(maxX-minX)*J/(largura-1));
}

double Grafico::convItoY(const double I) const
{
    return (maxY-(maxY-minY)*I/(altura-1));
}

void Grafico::resizeEvent(QResizeEvent *event)
{
    if (event->oldSize() != event->size()){
        apagar();
        if(!empty()){
            plotar();
        }
    }
}

void Grafico::mouseReleaseEvent(QMouseEvent *event)
{
    event->position();
    double x = convJtoX(event->pos().x());
    double y = convItoY(event->pos().y());
    emit signGraficoClicked(x,y);
}
