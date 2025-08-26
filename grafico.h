#ifndef GRAFICO_H
#define GRAFICO_H

#include <QLabel>
#include "evaluator.h"
#include <QResizeEvent>
#include <QMouseEvent>

class Grafico : public QLabel
{
    Q_OBJECT
public:
    Grafico(QWidget *parent = nullptr);
    bool empty() const;
    void setLimites(int MinX, int MaxX, int MinY, int MaxY, int Expoente);
    void setFuncao(const std::string& S);
    void clearFuncao();
    void setCor(int R, int G, int B);
    void apagar();
    void plotar();
signals:
    void signGraficoClicked(double x,double y);
private:

    Evaluator eval;
    QPixmap img;
    QColor cor;
    int largura,altura;
    double minX,maxX,minY,maxY;
    int nMarcX,nMarcY;

    double convXtoJ(const double X) const;
    double convYtoI(const double Y) const;
    double convJtoX(const double J) const;
    double convItoY(const double I) const;

    void resizeEvent(QResizeEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

};
#endif // GRAFICO_H
