#include "calculator.h"

Calculator::Calculator(QWidget *parent)
    : QWidget{parent}
{
    displaystring = new QLabel("");
    displaystring->setMinimumSize(120, 50);
    QChar aButton[4][4] = {
        {'7', '8', '9', '/'},
        {'4', '5', '6', '*'},
        {'1', '2', '3', '-'},
        {'0', '.', '=', '+'}
    };
    QGridLayout *myLayout = new QGridLayout;
    myLayout->addWidget(displaystring, 0, 0, 1, 4);
    myLayout->addWidget(createButton("CE"), 1, 3);
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            myLayout->addWidget(createButton(aButton[i][j]), i + 2, j);
        }
    }
    setLayout(myLayout);
}

QPushButton* Calculator::createButton(const QString& str) {
    QPushButton* pcmd = new QPushButton(str);
    pcmd->setMinimumSize(100, 100);
    connect(pcmd, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
    return pcmd;
}

void Calculator::calculate() {
    double dOperand2 = stack.pop().toDouble();
    QString strOperation = stack.pop();
    double dOperand1 = stack.pop().toDouble();
    double dResult = 0;
    if(strOperation == "+") {
        dResult = dOperand1 + dOperand2;
    }
    else if(strOperation == "-") {
        dResult = dOperand1 - dOperand2;
    }
    else if(strOperation == "/") {
        dResult = dOperand1 / dOperand2;
    }
    else if(strOperation == "*") {
        dResult = dOperand1 * dOperand2;
    }
    displaystring->setText(QString("%1").arg(dResult, 0, 'f', 3));
}

void Calculator::slotButtonClicked() {
    QString str = ((QPushButton*)sender())->text();
    if(str == "CE") {
        stack.clear();
        displaystring->setText("");
        return;
    }
    QString text = displaystring->text();
    int len = text.length();
    QString last = "";
    if(len > 0) {
        last = text.right(1);
    }
    static QRegularExpression re1("[0-9]");
    static QRegularExpression re2("^-?[0-9]+\\.?[0-9]*$");
    if(((len == 0 && stack.count() == 0) || ((stack.count() == 2 && len > 1 && (last == "+" || last == "-" || last == "*" || last == "/")))) && (str.contains(re1) || str == "-")) {
        text = str;
    }
    else if((text + str).contains(re2)) {
        text += str;
    }
    else if(text.contains(re2)) {
        if(str == "*" || str == "/" || str == "+" || str == "-" || str == "=") {
            if(stack.count() == 2) {
                stack.push(text);
                calculate();
                text = displaystring->text();
            }
            if(str != "=") {
                stack.push(text);
                text += str;
                stack.push(str);
            }
        }
    }
    displaystring->setText(text);

}
