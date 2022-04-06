#include "widget.h"
#include "ui_widget.h"


Win::Win(QWidget* parent): QWidget(parent)
{
    setWindowTitle("Возведение в квадрат");  //устанавливаем заголовок приложения
    frame = new QFrame(this);//создание рамки
    frame->setFrameShadow(QFrame::Raised);//Данное свойство содержит значение тени рамки из стиля рамки
    frame->setFrameShape(QFrame::Panel);  //данное свойство содержит значение формы рамки из стиля рамки
    inputLabel = new QLabel("Введите число:", this); //создание метки ввода
    inputEdit = new QLineEdit("", this);// строчный редактор ввода
    StrValidator* v = new StrValidator(inputEdit);//создаем объект класса валидатор, передаем строку ввода
    inputEdit->setValidator(v);  //проверка введеной строки
    outputLabel = new QLabel("Результат:", this);//создание лейбла- метка вывода
    outputEdit = new QLineEdit("", this);// строчный редактор вывода
    nextButton = new QPushButton("Следующее", this); // создание кнопки Следующее
    exitButton = new QPushButton("Выход", this);// создание кнопки Выход

// компоновка приложения выполняется согласно рисунку 2.
    //создание менеджера компоновки для управления размещением меток и кнопок в окне
    QVBoxLayout* vLayout1 = new QVBoxLayout(frame); // вертикальный компоновщик
    // добавление виджетов
    vLayout1->addWidget(inputLabel);// добавление метки к компоновщику
    vLayout1->addWidget(inputEdit);// добавление кнопки к компоновщику
    vLayout1->addWidget(outputLabel);// добавление метки к компоновщику
    vLayout1->addWidget(outputEdit);// добавление кнопки к компоновщику
    vLayout1->addStretch();//добавление пружины, чтоб пространство нерастяжимым стало
    QVBoxLayout* vLayout2 = new QVBoxLayout();            // вертикальный компоновщик
    vLayout2->addWidget(nextButton); // добавление кнопки к компоновщику
    vLayout2->addWidget(exitButton);//добавление пружины
    vLayout2->addStretch(); //добавление пружины
    QHBoxLayout* hLayout = new QHBoxLayout(this);// горизонтальный компоновщик
    hLayout->addWidget(frame);// добавляем рамку
    hLayout->addLayout(vLayout2);//добавление компоновщика в контейнер другого компоновщика (гориз к вертик)
    begin(); //  метод начальной настройки интерфейса
    // связь сигналов и слотов
    connect(exitButton, SIGNAL(clicked(bool)), this, SLOT(close()));// связь сигнала нажатия кнопки с закрытием окна
    connect(nextButton, SIGNAL(clicked(bool)), this, SLOT(begin()));// связь сигнала нажатия кнопки с вызовом-begin(принятие изначальной формы окна)
    connect(inputEdit, SIGNAL(returnPressed()), this, SLOT(calc()));// запуск валидатора, на проверку корректного ввода, потомсвязь сигнала нажатия кнопки с вычислением( вызов calc())
}

void Win::begin()
{
    //изначальная форма
    inputEdit->clear(); //ввод очищен
    nextButton->setEnabled(false); //не способность принимать и обрабатывать сообщения от клавиатуры и мыши Для кнопки-Следующее
    nextButton->setDefault(false);// отключаем ввод когда нажал ввод
    inputEdit->setEnabled(true);//способность принимать и обрабатывать сообщения от клавиатуры и мыши Для кноки-ВВОД
    outputLabel->setVisible(false);//не видимость виджета и всех его подчиненных виджетов(редактора ввода)
    outputEdit->setVisible(false);//не видимость виджета и всех его подчиненных виджетов(метка вывода)
    outputEdit->setEnabled(false);//не способность принимать и обрабатывать сообщения от клавиатуры и мыши Для конпки- Вывод
    inputEdit->setFocus();//фокус ввода передана виджету
}
//реализует основную обработку, проверяет правильность ввода данных и выдает окно сообщения, если данные введены неверно
void Win::calc()
{
    bool Ok = true;
    double r, a;
    QString str = inputEdit->text();//ввод в строке храним
    a = str.toDouble(&Ok);       // конвертируем в число
    //Если происходит ошибка преобразования, *ok устанавливается в false;
    //в противном случае для *ok установлено значение true
    if (Ok) {                       // если конвертируется
        r = a * a;//возведение в квадрат
        str.setNum(r);// записываем в строку
        outputEdit->setText(str); //передаем на вывод в виде текста наш результат
        inputEdit->setEnabled(false);//в поле ввода-не способность принимать и обрабатывать сообщения от клавиатуры и мыши
        outputLabel->setVisible(true);//видимость виджета и всех его подчиненных виджетов(метка ввода)
        outputEdit->setVisible(true); // показываем редактор ввода
        nextButton->setDefault(true); // доступен ввод по нажатию кнопки ввода
        nextButton->setEnabled(true); //можно нажать кнопку следующее-для возвед в квадрат след числа (разблокировка)
        nextButton->setFocus(); //фокус клавиатуры на следующее
    } else {                         // если строка не конвертируется
        if (!str.isEmpty()) { //если строка на ввод не пуста
            QMessageBox msgBox(QMessageBox::Information, "Возведение в квадрат.",//вывод сообщения
                               "Введено неверное значение.", QMessageBox::Ok);
            msgBox.exec();
        }
    }
}








