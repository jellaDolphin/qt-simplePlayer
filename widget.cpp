#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDir>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_layout = NULL;
    // Настройка таблицы плейлиста
    m_player = new QMediaPlayer(this);          // Инициализируем плеер
    m_player->setVolume(70);                    // Устанавливаем громкость воспроизведения треков
    oldButton = NULL;
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    on_lineEdit_textEdited("");
    ui->pushButton->setHidden(true);
    ui->pushButton_2->hide();
    myProcess = NULL;
    connect(ui->pushButton_00, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_01, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_02, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_03, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_04, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_05, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_06, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_07, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_08, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_09, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_15, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_16, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_17, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_18, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_19, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_191, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_20, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_21, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_22, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_23, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_24, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_25, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_26, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_27, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_28, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_29, SIGNAL(clicked()), this, SLOT(keyinput()));
    connect(ui->pushButton_291, SIGNAL(clicked()), this, SLOT(keyinput()));
}

Widget::~Widget()
{
    delete ui;
    delete m_player;

    foreach (QLabel* label, m_listLabel) {
        delete label;
    }
    m_listLabel.clear();

    foreach (QToolButton* button, m_listButton) {
        delete button;
    }
    m_listButton.clear();

    if (m_layout)
    {
        delete m_layout;
    }

    if (myProcess) {
//        myProcess->kill();
//        myProcess->close();
        delete myProcess;
    }
}

void Widget::clearItems()
{
    foreach (QLabel* label, m_listLabel) {
        m_layout->removeWidget(label);
        delete label;
    }
    m_listLabel.clear();

    foreach (QToolButton* button, m_listButton) {
        m_layout->removeWidget(button);
        delete button;
    }
    m_listButton.clear();
    oldButton = NULL;


    if (m_layout)
    {
        delete m_layout;
    }

    m_layout = new QGridLayout();
}

void Widget::on_lineEdit_textEdited(const QString &arg1)
{
    clearItems();
    QString fileName = arg1;
    QString path = QDir::cleanPath(QDir::currentPath() + "/files");
    QStringList filter("*.mp3");

    QDirIterator it(path, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList files;
    while (it.hasNext())
    {
        it.next();
        if (it.fileName().contains(fileName))
        {
            files << it.fileName();
            QString name;
            name = it.fileName();
            name = name.mid(0, name.lastIndexOf("."));
            createItem(name, it.filePath());
        }
    }
    ui->verticalLayout->insertLayout(0, m_layout);
}

void Widget::createItem(const QString &name, const QString &path)
{
    QLabel *label;
    QToolButton *playButton;
    QAction *action;

    label = new QLabel(name, this);
    label->setStyleSheet(QString("background-image:none;border-image:none;image:none;background-color: transparent;"));
    QFont font;
    font = label->font();
    font.setPointSize(22);
    label->setFont(font);

    playButton = new QToolButton(this);
    playButton->setMaximumSize(40, 40);
    playButton->setCursor(Qt::PointingHandCursor);
    playButton->setStyleSheet(QString("QToolButton{image: url(:/buttons/button.png);}"
                                      " QToolButton:hover:pressed{border: 3px solid #464646;border-radius:20px}"));

    action = new QAction(playButton);
    action->setData(path);
    playButton->setDefaultAction(action);
    connect(playButton, SIGNAL(clicked()), this, SLOT(itemPlay()));

    m_listLabel << label;
    m_listButton<< playButton;

    int row = m_layout->rowCount();
    m_layout->addWidget(label, row, 0);
    m_layout->addWidget(playButton, row, 1);
}

void Widget::itemPlay()
{
    QString filePath;

    QToolButton* button = qobject_cast<QToolButton*>(sender());

    if( button != NULL )
    {
        if (oldButton == button)
        {
            if (m_player->state() == QMediaPlayer::PlayingState)
            {
                m_player->pause();
                button->setStyleSheet(QString("QToolButton{image: url(:/buttons/button.png);}"
                                                 " QToolButton:hover:pressed{border: 3px solid #464646;border-radius:20px}"));
            }
            else
            {
                m_player->play();
                button->setStyleSheet(QString("QToolButton{image: url(:/buttons/pause.png);}"
                                                 " QToolButton:hover:pressed{border: 3px solid #464646;border-radius:20px}"));
            }
        }
        else
        {
            if (oldButton != NULL)
            {
                oldButton->setStyleSheet(QString("QToolButton{image: url(:/buttons/button.png);}"
                                                 " QToolButton:hover:pressed{border: 3px solid #464646;border-radius:20px}"));
            }

            filePath = button->defaultAction()->data().toString();
//            qDebug() << "filepath: " << filePath;
            m_player->stop();
            m_player->setMedia(QUrl(filePath));
            m_player->play();

            button->setStyleSheet(QString("QToolButton{image: url(:/buttons/pause.png);}"
                                             " QToolButton:hover:pressed{border: 3px solid #464646;border-radius:20px}"));
        }

        oldButton = button;
    }
}

void Widget::on_pushButton_clicked()
{
    close();
}

void Widget::showKeyboard()
{
    myProcess = new QProcess(this);
    myProcess->startDetached("C:/Windows/System32/osk.exe");
    // qDebug() << "showKeyboard:" << myProcess->state();
}


void Widget::on_pushButton_2_clicked()
{
    showKeyboard();
    ui->lineEdit->setFocus();
}

void Widget::keyinput()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString name = button->objectName();
//    qDebug() << "keyinput name : " << name;
    int n = name.split("_").at(1).toUInt();
    QString str;

    Qt::Key key;
    switch (n) {
    case 0:
        key = Qt::Key_Q;
        str = QString("/");
        break;
    case 1:
        key = Qt::Key_W;
        str = QString("'");
        break;
    case 2:
        key = Qt::Key_E;
        str = QString("ק");
        break;
    case 3:
        key = Qt::Key_R;
        str = QString("ר");
        break;
    case 4:
        key = Qt::Key_T;
        str = QString("א");
        break;
    case 5:
        key = Qt::Key_Y;
        str = QString("ט");
        break;
    case 6:
        key = Qt::Key_U;
        str = QString("ו");
        break;
    case 7:
        key = Qt::Key_I;
        str = QString("ן");
        break;
    case 8:
        key = Qt::Key_O;
        str = QString("ם");
        break;
    case 9:
        key = Qt::Key_P;
        str = QString("פ");
        break;
//    case 91:
//        key = Qt::Key_T;
//        str = QString("א");/////////////
//        break;
    case 92:
        key = Qt::Key_T;
        str = QString("א");//////////////
        break;
    case 10:
        key = Qt::Key_A;
        str = QString("ש");
        break;
    case 11:
        key = Qt::Key_S;
        str = QString("ד");
        break;
    case 12:
        key = Qt::Key_D;
        str = QString("ג");
        break;
    case 13:
        key = Qt::Key_F;
        str = QString("כ");
        break;
    case 14:
        key = Qt::Key_G;
        str = QString("ע");
        break;
    case 15:
        key = Qt::Key_H;
        str = QString("י");
        break;
    case 16:
        key = Qt::Key_J;
        str = QString("ח");
        break;
    case 17:
        key = Qt::Key_K;
        str = QString("ל");
        break;
    case 18:
        key = Qt::Key_L;
        str = QString("ך");
        break;
    case 19:
        key = Qt::Key_Semicolon;
        str = QString("ף");////////////
        break;
    case 191:
        key = Qt::Key_Apostrophe;
        str = QString(",");////////////
        break;
    case 20:
        key = Qt::Key_Z;
        str = QString("ז");
        break;
    case 21:
        key = Qt::Key_X;
        str = QString("ס");
        break;
    case 22:
        key = Qt::Key_C;
        str = QString("ב");
        break;
    case 23:
        key = Qt::Key_V;
        str = QString("ה");
        break;
    case 24:
        key = Qt::Key_B;
        str = QString("נ");
        break;
    case 25:
        key = Qt::Key_N;
        str = QString("מ");
        break;
    case 26:
        key = Qt::Key_M;
        str = QString("צ");
        break;
    case 27:
        key = Qt::Key_Less;
        str = QString("ת");
        break;
    case 28:
        key = Qt::Key_Greater;
        str = QString("ץ");
        break;
    case 29:
        key = Qt::Key_Question;
        str = QString(".");
        break;
    case 291:
        key = Qt::Key_Backspace;
        str = QKeySequence(key).toString();
        break;
    default:
        return;
        break;
    }

    QKeyEvent pressEvent = QKeyEvent(QEvent::KeyPress, key, Qt::NoModifier, str);
    QKeyEvent releaseEvent = QKeyEvent(QEvent::KeyRelease, key, Qt::NoModifier);
    QCoreApplication::sendEvent(QGuiApplication::focusObject(), &pressEvent);
    QCoreApplication::sendEvent(QGuiApplication::focusObject(), &releaseEvent);
}
