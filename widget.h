#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include <QPushButton>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

//данный файл содержит минимальное описание класса окна
class Win : public QWidget          // класс окна
{
Q_OBJECT  // макрос Qt, обеспечивающий корректное создание сигналов и слотов
protected:
    QFrame* frame;                  // рамка
    QLabel* inputLabel;             // метка ввода
    QLineEdit* inputEdit;           // строчный редактор ввода
    QLabel* outputLabel;            // метка вывода
    QLineEdit* outputEdit;          // строчный редактор вывода
    QPushButton* nextButton;        // кнопка Следующее
    QPushButton* exitButton;        // кнопка Выход
public:
    Win(QWidget* parent = nullptr); //конструктор, у которого параметр – родитель,
    //помощью этого параметра строятся иерархии объектов-виджетов
public slots:
    void begin();                   // метод начальной настройки интерфейса
    void calc();                    // метод реализации вычислений
};


class StrValidator : public QValidator // класс компонента проверки ввода
{
public:
    StrValidator(QObject* parent): QValidator(parent){}
    //Объект этого класса, включающий метод проверки вводимой строки validate, передается строчному редактору,
     //осуществляющему ввод. При завершении ввода этот метод автоматически вызывается.
     //Если этот метод возвращает Acceptable, то редактор ввода генерирует сигналы
    virtual State validate(QString& str, int& pos) const
    {
        return Acceptable;             // метод всегда принимает вводимую строку
    }
};

#endif // WIDGET_H
