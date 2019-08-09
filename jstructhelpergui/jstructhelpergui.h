#ifndef JSTRUCTHELPERGUI_H
#define JSTRUCTHELPERGUI_H

#include <QtGui/QMainWindow>
#include "ui_jstructhelpergui.h"
#include "../jstructdecompiler/align/align.h"

class jstructhelpergui : public QMainWindow
{
    Q_OBJECT

public:
    jstructhelpergui(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~jstructhelpergui();

private slots:
    void on_pushButtonSave_clicked();

private:
    Ui::jstructhelperguiClass ui;
    align                     align_;
};

#endif // JSTRUCTHELPERGUI_H
