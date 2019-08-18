#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSignalMapper>
#include <QtNetwork>

#define BUFFSIZE 361 //90*4 + HEADERSIZE
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
//public signals:

public slots:
    void handleButton(int x, int y);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setmap();
    void drawmap();

    void kingmove(int ,int , int);
    void guardmove(int ,int , int);
    void bishopmove(int ,int , int);
    void rookmove(int ,int , int);
    void horsemove(int ,int , int);
    void cannonmove(int ,int , int);
    void pawnmove(int ,int , int);
    void eat(int , int ,int);

    void movechess(int number);

public slots:
    void on_start_released();

    void on_setgame_clicked();

    void on_startsetgame_clicked();

    void on_server_clicked();

    void on_client_clicked();

    void acceptConnection(); // server accept

    void sendclient(); // server send to cient

    void getserver();
private slots:
    void on_enter_pressed();

    void on_sendmap_clicked();

    void on_restart_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap pix[20];
    QLabel  lab[20];
    QPushButton *button[10][9];
    QSignalMapper *signalMapper;
    int map[10][9];
    int savemap[10][9];
    bool check;
    int clickedx, clickedy;//last time click
    int play; //red or black move
    QPushButton *set[50];
    int choose; //set map choose
    int startsetgame;
    int checkkingup;
    int checkkingdown;
    QString clientip;
    QString clientport;
    QString serverport;
    QTcpSocket *client;

    int whoplay; //client or server play

    QTcpSocket *clientConnection;
    QTcpServer *server;
    QTcpSocket  *serverSocket;

    QTcpSocket *chatroom;

    char sendbuff[BUFFSIZE];
    char recbuff[BUFFSIZE];

    int status; //to check if connect or not
};

#endif // MAINWINDOW_H
