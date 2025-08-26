#ifndef LEHFUNCAO_H
#define LEHFUNCAO_H

#include <QDialog>

namespace Ui {
class LehFuncao;
}

class LehFuncao : public QDialog
{
    Q_OBJECT

public:
    explicit LehFuncao(QWidget *parent = nullptr);
    ~LehFuncao();
    void clear();
signals:
    void signDefinirFuncao(const QString &funcao);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::LehFuncao *ui;
};

#endif // LEHFUNCAO_H
