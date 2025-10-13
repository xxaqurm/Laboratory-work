#include <QApplication>
#include <QWidget>
#include <QPainter>

const int MAX_DEPTH = 5;

void drawCantor(QPainter &painter, int x, int y, int length, int depth) {
    if (depth == 0 || length < 1)
        return;

    // Рисуем текущий отрезок
    painter.drawLine(x, y, x + length, y);

    // Переходим на следующую строку
    int newY = y + 30;
    int newLength = length / 3;

    // Рекурсивно рисуем левый и правый отрезки
    drawCantor(painter, x, newY, newLength, depth - 1);
    drawCantor(painter, x + 2 * newLength, newY, newLength, depth - 1);
}

// Создаем свой виджет, наследник QWidget
class CantorWidget : public QWidget {
protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setPen(Qt::black);

        int startX = 50;
        int startY = 50;
        int length = width() - 100;

        drawCantor(painter, startX, startY, length, MAX_DEPTH);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CantorWidget window;
    window.resize(800, 600);
    window.setWindowTitle("Множество Кантора");
    window.show();

    return app.exec();
}
