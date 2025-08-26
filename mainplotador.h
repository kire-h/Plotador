#ifndef MAINPLOTADOR_H
#define MAINPLOTADOR_H

#include <QMainWindow>

#include "lehfuncao.h"
#include "grafico.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainPlotador;
}
QT_END_NAMESPACE

class MainPlotador : public QMainWindow
{
    Q_OBJECT

public:
    MainPlotador(QWidget *parent = nullptr);
    ~MainPlotador();

private slots:
    void on_actionFun_o_triggered();

    void on_actionPlotar_triggered();

    void on_actionApagar_triggered();

    void on_actionSair_triggered();

    void on_spinMinX_valueChanged(const int arg1);

    void on_spinMaxX_valueChanged(const int arg1);

    void on_spinMinY_valueChanged(const int arg1);

    void on_spinMaxY_valueChanged(const int arg1);

    void on_spinExpoente_valueChanged(int);

    void on_radioAzul_clicked();

    void on_radioVermelho_clicked();

    void on_radioVerde_clicked();

    void on_pushPlotar_clicked();

    void on_pushApagar_clicked();

    void slotDefinirFuncao(const QString &funcao);

    void slotGraficoClicked(const double x, const double y);

private:

    LehFuncao* lehFuncao;
    Ui::MainPlotador *ui;
    Grafico* grafico;
};
#endif // MAINPLOTADOR_H
