#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QGuiApplication>
#include <QLineEdit>

class LineEdit :public QLineEdit {
    Q_OBJECT

public:
    LineEdit(QWidget *parent = nullptr);
    LineEdit(const QString&, QWidget *parent = nullptr);

protected:
    bool event(QEvent*) override;

private:
    bool _moved = false;
    int _lastDiff = 0;
};

#endif // LINEEDIT_H
