#include "calculator.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Calculator calculator;
    calculator.setWindowTitle("Calculator");
    calculator.resize(230, 200);
    calculator.setFixedSize(1280, 720);
    calculator.show();
    return app.exec();
}
