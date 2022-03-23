#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>

#include <QLabel>
#include <QGridLayout>
#include <QToolButton>
#include <QIcon>
#include <QAction>
#include <QProcess>
#include <QKeyEvent>

namespace Ui {
class Widget;
}
class QKeyEvent;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void clearItems();

private slots:

    void on_lineEdit_textEdited(const QString &arg1);

    void createItem(const QString &name, const QString &path);

    void itemPlay();

    void on_pushButton_clicked();

    void showKeyboard();

    void on_pushButton_2_clicked();

    void keyinput();

private:
    Ui::Widget *ui;
    QMediaPlayer        *m_player;          // Проигрыватель треков
    QList<QLabel*> m_listLabel;
    QList<QToolButton*> m_listButton;
    QGridLayout *m_layout;
    QToolButton *oldButton;
    QProcess *myProcess;
};

#endif // WIDGET_H
