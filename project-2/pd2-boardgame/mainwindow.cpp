#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QWidget>
#include <QVector>
#include <QDebug>
#include <QSignalMapper>
#include <QMessageBox>
#include <QtNetwork>
#include <string>

#define king 7
#define guard 6
#define bishop 5
#define rook 4
#define horse 3
#define cannon 2
#define pawn 1
#define canmove 10
#define BUFFSIZE 361
#define HEADERSIZE 1

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap background(":/new/prefix1/8");
    ui->board->setPixmap(background);
    ui->board->setGeometry(30+50,15+100,560,630);
    ui->board->show();
    check = 0; //select or eat(move)
    clickedx = 2; //set last time click x
    clickedy = 0; //set last time click y
    status = 1;//normal type
    whoplay = 1; // connection red server first play
    memset(map, 0, sizeof(map));
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 9; j++) {

            QPushButton *tmp = new QPushButton();
            tmp->setGeometry(j*70+50, i*70+100, 60, 60);
            tmp->setParent(this);
            tmp->setStyleSheet("border-radius:60px;");

            connect(tmp, &QPushButton::clicked, this, [=](){ handleButton(i , j);} );

            button[i][j] = tmp;
        }
    }

    for(int i = 0; i < 16; i++){
        //black set chess
        QPushButton *tmp = new QPushButton();
        tmp->setGeometry(i*70+50, 30, 60, 60);
        tmp->setParent(this);
        tmp->setStyleSheet("border-radius:60px;");
        set[i] = tmp;
        connect(tmp,  &QPushButton::clicked,this, [=](){movechess(i);});
    }
    for(int i = 0; i < 16; i++){
        //red set chess
        QPushButton *tmp = new QPushButton();
        tmp->setGeometry(i*70+50, 800, 60, 60);
        tmp->setParent(this);
        tmp->setStyleSheet("border-radius:60px;");
        //tmp->setStyleSheet("border:2px solid red;");
        set[i+16] = tmp;
         connect(tmp,  &QPushButton::clicked,this, [=](){movechess(16+i);});

    }




    //load picture
    pix[1].load(":/new/prefix1/1");
    pix[2].load(":/new/prefix1/2");
    pix[3].load(":/new/prefix1/3");
    pix[4].load(":/new/prefix1/4");
    pix[5].load(":/new/prefix1/5");
    pix[6].load(":/new/prefix1/6");
    pix[7].load(":/new/prefix1/7");
    pix[8].load(":/new/prefix1/-1");
    pix[9].load(":/new/prefix1/-2");
    pix[10].load(":/new/prefix1/-3");
    pix[11].load(":/new/prefix1/-4");
    pix[12].load(":/new/prefix1/-5");
    pix[13].load(":/new/prefix1/-6");
    pix[14].load(":/new/prefix1/-7");
    pix[15].load("9");


    connect(ui->start,SIGNAL(released()), this, SLOT(on_start_released()));
    connect(ui->setgame,SIGNAL(clicked()), this, SLOT(on_setgame_clicked()));
    connect(ui->startsetgame,SIGNAL(clicked()), this, SLOT(on_startsetgame_clicked()) );

}

void MainWindow::setmap(){
    int oldmap[10][10];
    memset(oldmap, 0, sizeof(oldmap));
    //black
    oldmap[0][0] = -rook;
    oldmap[0][1] = -horse;
    oldmap[0][2] = -bishop;
    oldmap[0][3] = -guard;
    oldmap[0][4] = -king;
    oldmap[0][5] = -guard;
    oldmap[0][6] = -bishop;
    oldmap[0][7] = -horse;
    oldmap[0][8] = -rook;
    oldmap[2][1] = -cannon;
    oldmap[2][7] = -cannon;
    oldmap[3][0] = -pawn;
    oldmap[3][2] = -pawn;
    oldmap[3][4] = -pawn;
    oldmap[3][6] = -pawn;
    oldmap[3][8] = -pawn;
    //red
    oldmap[6][0] = pawn;
    oldmap[6][2] = pawn;
    oldmap[6][4] = pawn;
    oldmap[6][6] = pawn;
    oldmap[6][8] = pawn;
    oldmap[9][0] = rook;
    oldmap[9][1] = horse;
    oldmap[9][2] = bishop;
    oldmap[9][3] = guard;
    oldmap[9][4] = king;
    oldmap[9][5] = guard;
    oldmap[9][6] = bishop;
    oldmap[9][7] = horse;
    oldmap[9][8] = rook;
    oldmap[7][1] = cannon;
    oldmap[7][7] = cannon;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 9; j++){
            map[i][j] = oldmap[i][j];
            savemap[i][j] = oldmap[i][j];
        }
    }


}

void MainWindow::drawmap(){


    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 9; j++){

            if(map[i][j] == 1){
                button[i][j]->setIcon(pix[1]);

                button[i][j]->setIconSize(QSize(60, 60));
            }
            if(map[i][j] == 2){
                button[i][j]->setIcon(pix[2]);
                button[i][j]->setIconSize(QSize(60, 60));
            }
            if(map[i][j] == 3){
                button[i][j]->setIcon(pix[3]);
                button[i][j]->setIconSize(QSize(60, 60));
            }

            if(map[i][j] == 4){
                button[i][j]->setIcon(pix[4]);
                button[i][j]->setIconSize(QSize(60, 60));
            }
            if(map[i][j] == 5){
                button[i][j]->setIcon(pix[5]);
                button[i][j]->setIconSize(QSize(60, 60));
            }
            if(map[i][j] == 6){
                button[i][j]->setIcon(pix[6]);
                button[i][j]->setIconSize(QSize(60, 60));
            }
            if(map[i][j] == 7){
                button[i][j]->setIcon(pix[7]);
                button[i][j]->setIconSize(QSize(60, 60));
            }
            if(map[i][j] == -1){
                button[i][j]->setIcon(pix[8]);
                button[i][j]->setIconSize(QSize(60, 60));
            }
            if(map[i][j] == -2){
                button[i][j]->setIcon(pix[9]);
                button[i][j]->setIconSize(QSize(60, 60));
            }
            if(map[i][j] == -3){
                button[i][j]->setIcon(pix[10]);
                button[i][j]->setIconSize(QSize(60, 60));
            }
            if(map[i][j] == -4){
                button[i][j]->setIcon(pix[11]);
                button[i][j]->setIconSize(QSize(60, 60));
            }
            if(map[i][j] == -5){
                button[i][j]->setIcon(pix[12]);
                button[i][j]->setIconSize(QSize(60, 60));
            }
            if(map[i][j] == -6){
                button[i][j]->setIcon(pix[13]);
                button[i][j]->setIconSize(QSize(60, 60));
            }
            if(map[i][j] == -7){
                button[i][j]->setIcon(pix[14]);
                button[i][j]->setIconSize(QSize(60, 60));
            }
            if(map[i][j] == 0){
                button[i][j]->setIcon(pix[15]);
                button[i][j]->setIconSize(QSize(60,60));
            }


        }
    }
}

//handle button click
void MainWindow::handleButton(int x, int y){

    if(status == 1){
        //red first && red > 0 black < 0
        checkkingup = 1;
        checkkingdown = 1;
        for(int i = 1; i < 10 && x+i < 10; i++){
            if(map[x+i][y] != 0 && map[x+i][y] != 7 && map[x+i][y] != -7 )break;
            if( map[x+i][y] == 7 && map[x][y] != 7 && map[x][y] != -7){
                checkkingdown = 0;
            }
        }
        for(int i = 1; i < 10 && x-i >= 0; i++){
            if(map[x-i][y] != 0 && map[x-i][y] != 7 && map[x-i][y] != -7 )break;
            if( map[x-i][y] == -7 && map[x][y] != 7 && map[x][y] != -7){
                checkkingup = 0;
            }
        }
        //set game
        if(clickedx == -1 && clickedy == -1){

            if(choose == 0)map[x][y] = -king;
            else if(choose == 1 || choose == 2)map[x][y] = -guard;
            else if(choose == 3 || choose == 4)map[x][y] = -bishop;
            else if(choose == 5 || choose == 6)map[x][y] = -rook;
            else if(choose == 7 || choose == 8)map[x][y] = -horse;
            else if(choose == 9 || choose == 10)map[x][y] = -cannon;
            else if(choose > 10 && choose < 16)map[x][y] = -pawn;
            else if(choose == 16)map[x][y] = king;
            else if(choose == 17 || choose == 18)map[x][y] = guard;
            else if(choose == 19 || choose == 20)map[x][y] = bishop;
            else if(choose == 21 || choose == 22)map[x][y] = rook;
            else if(choose == 23 || choose == 24)map[x][y] = horse;
            else if(choose == 25 || choose == 26)map[x][y] = cannon;
            else if(choose > 26 && choose < 32)map[x][y] = pawn;
            set[choose]->hide();
            drawmap();
            //the last time put player first play
            if(map[x][y] > 0)play = 1;
            else play = -1;
        }//&& (checkkingup || checkkingdown)
        //clickedx & clickedy are set board
        //map * play is the player to play
        else if(check == 0 && map[x][y] != 0 && map[x][y] * play > 0  && clickedx > -1 && clickedy > -1){

            if(map[x][y] == 1 || map[x][y] == -1){
                pawnmove(map[x][y], x, y);
            }
            if(map[x][y] == 2 || map[x][y] == -2){
                cannonmove(map[x][y], x, y);
            }
            if(map[x][y] == 3 || map[x][y] == -3){
                horsemove(map[x][y], x, y);
            }
            if(map[x][y] == 4 || map[x][y] == -4){
                rookmove(map[x][y], x, y);
            }
            if(map[x][y] == 5 || map[x][y] == -5){
                bishopmove(map[x][y], x, y);
            }
            if(map[x][y] == 6 || map[x][y] == -6){
                guardmove(map[x][y], x, y);
            }
            if(map[x][y] == 7 || map[x][y] == -7){
               kingmove(map[x][y], x, y);
            }
            clickedx = x;
            clickedy = y;
            button[x][y]->setStyleSheet("color: blue;""background-color:rgba(205,0,0,100%);""selection-background-color: blue;");
            //then eat(move)
            check = 1;
            //if last time
            //if(map[clickedx][clickedy] * play > 0)check = 0;

        }
        else {

            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 9; j++){
                    if(savemap[i][j] == canmove){
                        button[i][j]->setStyleSheet("border: 2px solid transparent");
                    }
                }
            }

            eat(map[x][y], x, y);
            check = 0;//turn to select & move

            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 9; j++){
                    savemap[i][j] = map[i][j];
                }
            }
         }
    }
    else if(status == 2 && whoplay == 1){
        //server
        play = 1;//red
        checkkingup = 1;
        checkkingdown = 1;
        for(int i = 1; i < 10 && x+i < 10; i++){
            if(map[x+i][y] != 0 && map[x+i][y] != 7 && map[x+i][y] != -7 )break;
            if( map[x+i][y] == 7 && map[x][y] != 7 && map[x][y] != -7){
                checkkingdown = 0;
            }
        }
        for(int i = 1; i < 10 && x-i >= 0; i++){
            if(map[x-i][y] != 0 && map[x-i][y] != 7 && map[x-i][y] != -7 )break;
            if( map[x-i][y] == -7 && map[x][y] != 7 && map[x][y] != -7){
                checkkingup = 0;
            }
        }
        if(clickedx == -1 && clickedy == -1){

            if(choose == 0)map[x][y] = -king;
            else if(choose == 1 || choose == 2)map[x][y] = -guard;
            else if(choose == 3 || choose == 4)map[x][y] = -bishop;
            else if(choose == 5 || choose == 6)map[x][y] = -rook;
            else if(choose == 7 || choose == 8)map[x][y] = -horse;
            else if(choose == 9 || choose == 10)map[x][y] = -cannon;
            else if(choose > 10 && choose < 16)map[x][y] = -pawn;
            else if(choose == 16)map[x][y] = king;
            else if(choose == 17 || choose == 18)map[x][y] = guard;
            else if(choose == 19 || choose == 20)map[x][y] = bishop;
            else if(choose == 21 || choose == 22)map[x][y] = rook;
            else if(choose == 23 || choose == 24)map[x][y] = horse;
            else if(choose == 25 || choose == 26)map[x][y] = cannon;
            else if(choose > 26 && choose < 32)map[x][y] = pawn;
            set[choose]->hide();
            drawmap();
            //the last time put player first play
            if(map[x][y] > 0)play = 1;
            else play = -1;
        }//&& (checkkingup || checkkingdown)
        //clickedx & clickedy are set board
        //map * play is the player to play
        else if(check == 0 && map[x][y] != 0 && map[x][y] * play > 0  && clickedx > -1 && clickedy > -1){

            if(map[x][y] == 1 || map[x][y] == -1){
                pawnmove(map[x][y], x, y);
            }
            if(map[x][y] == 2 || map[x][y] == -2){
                cannonmove(map[x][y], x, y);
            }
            if(map[x][y] == 3 || map[x][y] == -3){
                horsemove(map[x][y], x, y);
            }
            if(map[x][y] == 4 || map[x][y] == -4){
                rookmove(map[x][y], x, y);
            }
            if(map[x][y] == 5 || map[x][y] == -5){
                bishopmove(map[x][y], x, y);
            }
            if(map[x][y] == 6 || map[x][y] == -6){
                guardmove(map[x][y], x, y);
            }
            if(map[x][y] == 7 || map[x][y] == -7){
               kingmove(map[x][y], x, y);
            }
            clickedx = x;
            clickedy = y;
            button[x][y]->setStyleSheet("color: blue;""background-color:rgba(205,0,0,100%);""selection-background-color: blue;");

            check = 1;

        }
        else {

            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 9; j++){
                    if(savemap[i][j] == canmove){
                        button[i][j]->setStyleSheet("border: 2px solid transparent");
                    }
                }
            }

            eat(map[x][y], x, y);
            check = 0;

            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 9; j++){
                    savemap[i][j] = map[i][j];
                }
            }

         }

    }
    else if(status == 3 && whoplay == -1){
        //client
        play = -1;
        checkkingup = 1;
        checkkingdown = 1;
        for(int i = 1; i < 10 && x+i < 10; i++){
            if(map[x+i][y] != 0 && map[x+i][y] != 7 && map[x+i][y] != -7 )break;
            if( map[x+i][y] == 7 && map[x][y] != 7 && map[x][y] != -7){
                checkkingdown = 0;
            }
        }
        for(int i = 1; i < 10 && x-i >= 0; i++){
            if(map[x-i][y] != 0 && map[x-i][y] != 7 && map[x-i][y] != -7 )break;
            if( map[x-i][y] == -7 && map[x][y] != 7 && map[x][y] != -7){
                checkkingup = 0;
            }
        }
        if(clickedx == -1 && clickedy == -1){

            if(choose == 0)map[x][y] = -king;
            else if(choose == 1 || choose == 2)map[x][y] = -guard;
            else if(choose == 3 || choose == 4)map[x][y] = -bishop;
            else if(choose == 5 || choose == 6)map[x][y] = -rook;
            else if(choose == 7 || choose == 8)map[x][y] = -horse;
            else if(choose == 9 || choose == 10)map[x][y] = -cannon;
            else if(choose > 10 && choose < 16)map[x][y] = -pawn;
            else if(choose == 16)map[x][y] = king;
            else if(choose == 17 || choose == 18)map[x][y] = guard;
            else if(choose == 19 || choose == 20)map[x][y] = bishop;
            else if(choose == 21 || choose == 22)map[x][y] = rook;
            else if(choose == 23 || choose == 24)map[x][y] = horse;
            else if(choose == 25 || choose == 26)map[x][y] = cannon;
            else if(choose > 26 && choose < 32)map[x][y] = pawn;
            set[choose]->hide();
            drawmap();
            //the last time put player first play
            if(map[x][y] > 0)play = 1;
            else play = -1;
        }//&& (checkkingup || checkkingdown)
        //clickedx & clickedy are set board
        //map * play is the player to play
        else if(check == 0 && map[x][y] != 0 && map[x][y] * play > 0  && clickedx > -1 && clickedy > -1){

            if(map[x][y] == 1 || map[x][y] == -1){
                pawnmove(map[x][y], x, y);
            }
            if(map[x][y] == 2 || map[x][y] == -2){
                cannonmove(map[x][y], x, y);
            }
            if(map[x][y] == 3 || map[x][y] == -3){
                horsemove(map[x][y], x, y);
            }
            if(map[x][y] == 4 || map[x][y] == -4){
                rookmove(map[x][y], x, y);
            }
            if(map[x][y] == 5 || map[x][y] == -5){
                bishopmove(map[x][y], x, y);
            }
            if(map[x][y] == 6 || map[x][y] == -6){
                guardmove(map[x][y], x, y);
            }
            if(map[x][y] == 7 || map[x][y] == -7){
               kingmove(map[x][y], x, y);
            }
            clickedx = x;
            clickedy = y;
            button[x][y]->setStyleSheet("color: blue;""background-color:rgba(205,0,0,100%);""selection-background-color: blue;");

            check = 1;

        }
        else {

            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 9; j++){
                    if(savemap[i][j] == canmove){
                        button[i][j]->setStyleSheet("border: 2px solid transparent");
                    }
                }
            }

            eat(map[x][y], x, y);
            check = 0;

            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 9; j++){
                    savemap[i][j] = map[i][j];
                }
            }


         }



    }

}

void MainWindow::eat(int rb, int x, int y){

    if(savemap[x][y] == canmove){

        if(map[x][y] == 7 && status == 1){
            qDebug() << "black win";
            QMessageBox::information(this,"reslut:","black win！",QMessageBox::Ok);
        }
        else if(map[x][y] == -7 && status == 1){
            qDebug() << "red win";
            QMessageBox::information(this,"result：","red win！",QMessageBox::Ok);
        }
        if(status == 2){
            if(map[x][y] == 7){
                memset(sendbuff, 0, sizeof(sendbuff));
                sendbuff[0] = 'b';
                serverSocket->write(sendbuff, BUFFSIZE);
               QMessageBox::information(this,"reslut:","You lose！",QMessageBox::Ok);
            }
            if(map[x][y] == -7){
                memset(sendbuff, 0, sizeof(sendbuff));
                sendbuff[0] = 'c';
                serverSocket->write(sendbuff, BUFFSIZE);
                QMessageBox::information(this,"result：","You win！",QMessageBox::Ok);
            }
        }
        if(status == 3){
            if(map[x][y] == 7){
                memset(sendbuff, 0, sizeof(sendbuff));
                sendbuff[0] = 'c';
                serverSocket->write(sendbuff, BUFFSIZE);
                QMessageBox::information(this,"result：","You win！",QMessageBox::Ok);

            }
            if(map[x][y] == -7){
                memset(sendbuff, 0, sizeof(sendbuff));
                sendbuff[0] = 'b';
                serverSocket->write(sendbuff, BUFFSIZE);
                QMessageBox::information(this,"reslut:","You lose！",QMessageBox::Ok);
            }
        }

        button[clickedx][clickedy]->setIcon(pix[15]);
        if(map[clickedx][clickedy] > 0)button[x][y]->setIcon(pix[ map[clickedx][clickedy] ]);
        else if(map[clickedx][clickedy] < 0)button[x][y]->setIcon(pix[  7+-1*map[clickedx][clickedy] ]);
        button[x][y]->setIconSize(QSize(60,60));
        map[x][y] = map[clickedx][clickedy];
        map[clickedx][clickedy] = 0;
        //server send eat after eat
        if(status == 2 && whoplay == 1){
            memset(sendbuff, 0, sizeof(sendbuff));
            //serverSocket->write((char*)map, 90*4);
            memcpy(sendbuff + HEADERSIZE, map, 90*4);
            sendbuff[0] = 'a';
            serverSocket->write(sendbuff, BUFFSIZE);

        }
        if(status == 2 && whoplay == -1){
            memset(sendbuff, 0, sizeof(sendbuff));
            //serverSocket->write((char*)map, 90*4);
            memcpy(sendbuff + HEADERSIZE, map, 90*4);
            sendbuff[0] = 'e';
            serverSocket->write(sendbuff, BUFFSIZE);
        }
        //client send eat after eat
        if(status == 3 && whoplay == 1){
            //client->write((char*)map,90*4);
            memset(sendbuff, 0 , sizeof(sendbuff));
            memcpy(sendbuff + HEADERSIZE, map, 90*4);
            sendbuff[0] = 'a';

            client->write(sendbuff, BUFFSIZE);

        }
        if(status == 3 && whoplay == -1){
            //client->write((char*)map,90*4);
            memset(sendbuff, 0 , sizeof(sendbuff));
            memcpy(sendbuff + HEADERSIZE, map, 90*4);
            sendbuff[0] = 'e';
            client->write(sendbuff, BUFFSIZE);
        }
        //switch player
        whoplay *= -1;//turn black or red player
        if(status == 1)play *= -1;
        else if(status == 2)play = 1;//red player
        else if(status == 3)play = -1;//black player



    }
    button[clickedx][clickedy]->setStyleSheet("border-radius:60px;");
}
void MainWindow::kingmove(int rb , int x, int y){
   int checkkingleft = 1;
   int checkkingright = 1;
    if(rb > 0){
        //checkking
        for(int i = 1; i < 10 && x-i >= 0; i++){
            if(savemap[x-i][y+1] != 0  && savemap[x-i][y+1] != -7 && savemap[x-i][y+1] != 7 && y < 5)break;
                if(savemap[x-i][y+1] == -7 ){
                    checkkingright = 0;
                }
         }
        //left
        for(int i = 1; i < 10 && x-i >= 0; i++){
            if(savemap[x-i][y-1] != 0 && savemap[x-i][y-1] != -7 && savemap[x-i][y-1] != 7 && y > 3)break;
                if(savemap[x-i][y-1] == -7){
                    checkkingleft = 0;
                }
         }

        if(savemap[x+1][y] <= 0 && x < 9){
            savemap[x+1][y] = canmove;
            button[x+1][y]->setStyleSheet("border:2px solid red;");
        }

        if(savemap[x-1][y] <= 0 && x > 7){
            savemap[x-1][y] = canmove;
            button[x-1][y]->setStyleSheet("border:2px solid red;");
        }
        if(savemap[x][y+1] <= 0 && y < 5 && checkkingright){
            savemap[x][y+1] = canmove;
            button[x][y+1]->setStyleSheet("border:2px solid red;");
        }
        if(savemap[x][y-1] <= 0 && y > 3 && checkkingleft){
            savemap[x][y-1] = canmove;
            button[x][y-1]->setStyleSheet("border:2px solid red;");
        }
    }
    if(rb < 0){
        //checkkingright
        for(int i = 1; i < 10 && x+i < 10; i++){
            if(savemap[x+i][y+1] != 0 && savemap[x+i][y+1] != -7 && savemap[x+i][y+1] != 7 && y < 5)break;
                if( savemap[x+i][y+1] == 7){
                    checkkingright = 0;
                }
         }
        //left
        for(int i = 1; i < 10 && x+i < 10 ; i++){
            if(savemap[x+i][y-1] != 0 && savemap[x+i][y-1] != -7 && savemap[x+i][y-1] != 7 && y > 3)break;
                if(savemap[x+i][y-1] == 7){
                    checkkingleft = 0;
                }
         }

        if(savemap[x+1][y] >= 0 && x < 2){
            savemap[x+1][y] = canmove;
            button[x+1][y]->setStyleSheet("border:2px solid black;");
        }
        if(savemap[x-1][y] >= 0 && x > 0){
            savemap[x-1][y] = canmove;
            button[x-1][y]->setStyleSheet("border:2px solid black;");
        }
        if(savemap[x][y+1] >= 0 && y < 5 && checkkingright){
            savemap[x][y+1] = canmove;
            button[x][y+1]->setStyleSheet("border:2px solid black;");
        }
        if(savemap[x][y-1] >= 0 && y > 3 && checkkingleft){
            savemap[x][y-1] = canmove;
            button[x][y-1]->setStyleSheet("border:2px solid black;");
        }
    }


}
void MainWindow::guardmove(int rb , int x, int y ){
    if(rb > 0&& (checkkingup || checkkingdown)){
        if(savemap[x+1][y+1] <= 0 && x < 9 && y < 5 && (checkkingup || checkkingdown)){
            savemap[x+1][y+1] = canmove;
            button[x+1][y+1]->setStyleSheet("border:2px solid red;");
        }
        if(savemap[x+1][y-1] <= 0 && x < 9 && y > 3 && (checkkingup || checkkingdown)){
            savemap[x+1][y-1] = canmove;
            button[x+1][y-1]->setStyleSheet("border:2px solid red;");
        }
        if(savemap[x-1][y+1] <= 0 && y < 5 && x > 7 && (checkkingup || checkkingdown)){
            savemap[x-1][y+1] = canmove;
            button[x-1][y+1]->setStyleSheet("border:2px solid red;");
        }
        if(savemap[x-1][y-1] <= 0 && y > 3 && x > 7 && (checkkingup || checkkingdown)){
            savemap[x-1][y-1] = canmove;
            button[x-1][y-1]->setStyleSheet("border:2px solid red;");
        }
    }
    if(rb < 0&& (checkkingup || checkkingdown)){
        if(savemap[x+1][y+1] >= 0 && x < 2 && y < 5){
            savemap[x+1][y+1] = canmove;
            button[x+1][y+1]->setStyleSheet("border:2px solid black;");
        }
        if(savemap[x+1][y-1] >= 0 && x < 2 && y > 3){
            savemap[x+1][y-1] = canmove;
            button[x+1][y-1]->setStyleSheet("border:2px solid black;");
        }
        if(savemap[x-1][y+1] >= 0 && y < 5 && x > 0){
            savemap[x-1][y+1] = canmove;
            button[x-1][y+1]->setStyleSheet("border:2px solid black;");
        }
        if(savemap[x-1][y-1] >= 0 && y > 3 && x > 0){
            savemap[x-1][y-1] = canmove;
            button[x-1][y-1]->setStyleSheet("border:2px solid black;");
        }
    }
}
void MainWindow:: bishopmove(int rb , int x, int y ){
    if(rb > 0&& (checkkingup || checkkingdown)){//here
        if(savemap[x+2][y+2] <= 0 && x < 9 && y < 7 && savemap[x+1][y+1] == 0){
            savemap[x+2][y+2] = canmove;
            button[x+2][y+2]->setStyleSheet("border:2px solid red;");
        }
        if(savemap[x+2][y-2] <= 0 && x < 9 && y > 0 && savemap[x+1][y-1] == 0){
            savemap[x+2][y-2] = canmove;
            button[x+2][y-2]->setStyleSheet("border:2px solid red;");
        }
        if(savemap[x-2][y+2] <= 0 && x > 5 &&  y < 7 && savemap[x-1][y+1] == 0){
            savemap[x-2][y+2] = canmove;
            button[x-2][y+2]->setStyleSheet("border:2px solid red;");
        }
        if(savemap[x-2][y-2] <= 0 && x > 5 && y > 0 && savemap[x-1][y-1] == 0){
            savemap[x-2][y-2] = canmove;
            button[x-2][y-2]->setStyleSheet("border:2px solid red;");
        }
    }
    if(rb < 0 && (checkkingup || checkkingdown)){
        if(savemap[x+2][y+2] >= 0 && x < 4 && y < 7 && savemap[x+1][y+1] == 0){
            savemap[x+2][y+2] = canmove;
            button[x+2][y+2]->setStyleSheet("border:2px solid black;");
        }
        if(savemap[x+2][y-2] >= 0 && x < 4 && y > 0 && savemap[x+1][y-1] == 0){
            savemap[x+2][y-2] = canmove;
            button[x+2][y-2]->setStyleSheet("border:2px solid black;");
        }
        if(savemap[x-2][y+2] >= 0 && x > 0 &&  y < 7 && savemap[x-1][y+1] == 0){
            savemap[x-2][y+2] = canmove;
            button[x-2][y+2]->setStyleSheet("border:2px solid black;");
        }
        if(savemap[x-2][y-2] >= 0 && x > 0 && y > 0 && savemap[x-1][y-1] == 0){
            savemap[x-2][y-2] = canmove;
            button[x-2][y-2]->setStyleSheet("border:2px solid black;");
        }
    }
}
void MainWindow:: rookmove(int rb , int x, int y ){
    if(rb > 0){
        for(int i = 1;  i < 10; i++){
            //down
            if(x+i <= 9){
                if(savemap[x+i][y] == 0 ){
                    savemap[x+i][y] = canmove;
                    button[x+i][y]->setStyleSheet("border:2px solid red;");

                }
                else if(savemap[x+i][y] < 0){
                    savemap[x+i][y] = canmove;
                    button[x+i][y]->setStyleSheet("border:2px solid red;");
                    break;
                }
                else break;
            }
        }
        //up
        for(int i = 1; i < 10; i++){
            if(x-i >= 0){
                if(savemap[x-i][y] == 0){
                    savemap[x-i][y] = canmove;
                    button[x-i][y]->setStyleSheet("border:2px solid red;");

                }
                else if(savemap[x-i][y] < 0){
                    savemap[x-i][y] = canmove;
                    button[x-i][y]->setStyleSheet("border:2px solid red;");
                    break;
                }
                else break;
            }
        }
        for(int i = 1; i < 10; i++){
            if(y+i <= 8 && (checkkingup || checkkingdown)){
                if(savemap[x][y+i] == 0 ){
                    savemap[x][y+i] = canmove;
                    button[x][y+i]->setStyleSheet("border:2px solid red;");

                }
                else if(savemap[x][y+i] < 0){
                     savemap[x][y+i] = canmove;
                    button[x][y+i]->setStyleSheet("border:2px solid red;");
                    break;
                }
                else break;
            }
        }
        for(int i = 1; i < 10; i++){
            if(y-i >= 0&& (checkkingup || checkkingdown)){
                if(savemap[x][y-i] == 0 ){
                    savemap[x][y-i] = canmove;
                    button[x][y-i]->setStyleSheet("border:2px solid red;");

                }
                else if(savemap[x][y-i] < 0){
                    savemap[x][y-i] = canmove;
                    button[x][y-i]->setStyleSheet("border:2px solid red;");
                    break;
                }
                else break;
            }
        }

    }
    if(rb < 0){

        for(int i = 1;  i < 10; i++){
            if(x+i <= 9){
                if(savemap[x+i][y] == 0 ){
                    savemap[x+i][y] = canmove;
                    button[x+i][y]->setStyleSheet("border:2px solid black;");

                }
                else if(savemap[x+i][y] > 0){
                    savemap[x+i][y] = canmove;
                    button[x+i][y]->setStyleSheet("border:2px solid black;");
                    break;
                }
                else break;
            }
        }
        for(int i = 1; i < 10; i++){
            if(x-i >= 0){
                if(savemap[x-i][y] == 0){
                    savemap[x-i][y] = canmove;
                    button[x-i][y]->setStyleSheet("border:2px solid black;");

                }
                else if(savemap[x-i][y] > 0){
                    savemap[x-i][y] = canmove;
                    button[x-i][y]->setStyleSheet("border:2px solid black;");
                    break;
                }
                else break;
            }
        }
        for(int i = 1; i < 10; i++){
            if(y+i <= 8&& (checkkingup || checkkingdown)){
                if(savemap[x][y+i] == 0 ){
                    savemap[x][y+i] = canmove;
                    button[x][y+i]->setStyleSheet("border:2px solid black;");

                }
                else if(savemap[x][y+i] > 0){
                     savemap[x][y+i] = canmove;
                    button[x][y+i]->setStyleSheet("border:2px solid black;");
                    break;
                }
                else break;
            }
        }
        for(int i = 1; i < 10; i++){
            if(y-i >= 0&& (checkkingup || checkkingdown)){
                if(savemap[x][y-i] == 0 ){
                    savemap[x][y-i] = canmove;
                    button[x][y-i]->setStyleSheet("border:2px solid black;");

                }
                else if(savemap[x][y-i] > 0){
                    savemap[x][y-i] = canmove;
                    button[x][y-i]->setStyleSheet("border:2px solid black;");
                    break;
                }
                else break;
            }
        }
    }

}
void MainWindow:: horsemove(int rb , int x, int y ){
    if(rb > 0){
        //right up
        if( x < 9 && y < 7 && (checkkingup || checkkingdown)){
            if(savemap[x+1][y+2] <= 0 && savemap[x][y+1] == 0){
                savemap[x+1][y+2] = canmove;
                button[x+1][y+2]->setStyleSheet("border:2px solid red;");
            }
        }
        if(x < 8 && y < 8&& (checkkingup || checkkingdown)){
            if(savemap[x+2][y+1] <= 0 && savemap[x+1][y] == 0){
                savemap[x+2][y+1] = canmove;
                button[x+2][y+1]->setStyleSheet("border:2px solid red;");
            }
        }
        if( y > 0 &&  x < 8&& (checkkingup || checkkingdown)){
            if(savemap[x+2][y-1] <= 0 && savemap[x+1][y] == 0){
                savemap[x+2][y-1] = canmove;
                button[x+2][y-1]->setStyleSheet("border:2px solid red;");
            }
        }
        if( y > 1 && x < 9&& (checkkingup || checkkingdown)){
            if(savemap[x+1][y-2] <= 0 && savemap[x][y-1] == 0 ){
                savemap[x+1][y-2] = canmove;
                button[x+1][y-2]->setStyleSheet("border:2px solid red;");
            }
        }
        if(y > 1 && x > 0&& (checkkingup || checkkingdown)){
            if(savemap[x-1][y-2] <= 0 && savemap[x][y-1] == 0){
                savemap[x-1][y-2] = canmove;
                button[x-1][y-2]->setStyleSheet("border:2px solid red;");
            }
        }
        if(y > 0 && x > 1&& (checkkingup || checkkingdown)){
            if(savemap[x-2][y-1] <= 0 && savemap[x-1][y] == 0){
                savemap[x-2][y-1] = canmove;
                button[x-2][y-1]->setStyleSheet("border:2px solid red;");
            }
        }
        if(y < 8 && x > 1&& (checkkingup || checkkingdown)){
            if(savemap[x-2][y+1] <= 0 && savemap[x-1][y] == 0){
                savemap[x-2][y+1] = canmove;
                button[x-2][y+1]->setStyleSheet("border:2px solid red;");
            }
        }
        if(y < 7 && x > 0 && (checkkingup || checkkingdown)){
            if(savemap[x-1][y+2] <= 0 && savemap[x][y+1] == 0){
                savemap[x-1][y+2] = canmove;
                button[x-1][y+2]->setStyleSheet("border:2px solid red;");
            }
        }
    }
    if(rb < 0){
        //right up
        if( x < 9 && y < 7&& (checkkingup || checkkingdown)){
            if(savemap[x+1][y+2] >= 0 && savemap[x][y+1] == 0){
                savemap[x+1][y+2] = canmove;
                button[x+1][y+2]->setStyleSheet("border:2px solid black;");
            }
        }
        if(x < 8 && y < 8&& (checkkingup || checkkingdown)){
            if(savemap[x+2][y+1] >= 0 && savemap[x+1][y] == 0){
                savemap[x+2][y+1] = canmove;
                button[x+2][y+1]->setStyleSheet("border:2px solid black;");
            }
        }
        if( y > 0 &&  x < 8&& (checkkingup || checkkingdown)){
            if(savemap[x+2][y-1] >= 0 && savemap[x+1][y] == 0){
                savemap[x+2][y-1] = canmove;
                button[x+2][y-1]->setStyleSheet("border:2px solid black;");
            }
        }
        if( y > 1 && x < 9&& (checkkingup || checkkingdown)){
            if(savemap[x+1][y-2] >= 0 && savemap[x][y-1] == 0 ){
                savemap[x+1][y-2] = canmove;
                button[x+1][y-2]->setStyleSheet("border:2px solid black;");
            }
        }
        if(y > 1 && x > 0&& (checkkingup || checkkingdown)){
            if(savemap[x-1][y-2] >= 0 && savemap[x][y-1] == 0){
                savemap[x-1][y-2] = canmove;
                button[x-1][y-2]->setStyleSheet("border:2px solid black;");
            }
        }
        if(y > 0 && x > 1&& (checkkingup || checkkingdown)){
            if(savemap[x-2][y-1] >= 0 && savemap[x-1][y] == 0){
                savemap[x-2][y-1] = canmove;
                button[x-2][y-1]->setStyleSheet("border:2px solid black;");
            }
        }
        if(y < 8 && x > 1&& (checkkingup || checkkingdown)){
            if(savemap[x-2][y+1] >= 0 && savemap[x-1][y] == 0){
                savemap[x-2][y+1] = canmove;
                button[x-2][y+1]->setStyleSheet("border:2px solid black;");
            }
        }
        if(y < 7 && x > 0 && (checkkingup || checkkingdown)){
            if(savemap[x-1][y+2] >= 0 && savemap[x][y+1] == 0){
                savemap[x-1][y+2] = canmove;
                button[x-1][y+2]->setStyleSheet("border:2px solid black;");
            }
        }
    }
}
void MainWindow:: cannonmove(int rb , int x, int y ){
    if(rb > 0){
        for(int i = 1;  i < 10; i++){
            //down
            if(x+i <= 9){
                //jump
                if(savemap[x+i][y] != 0 ){
                    for(int j = 1; x+i+j <= 9 && j < 10; j++){
                        if(savemap[x+i+j][y] < 0 && (checkkingup || checkkingdown)){
                        savemap[x+i+j][y] = canmove;
                        button[x+i+j][y]->setStyleSheet("border:2px solid red;");
                        break;
                        }
                    }
                    break;

                }
                else if(savemap[x+i][y] == 0 ){
                    //eat
                    savemap[x+i][y] = canmove;
                    button[x+i][y]->setStyleSheet("border:2px solid red;");
                }
                else break;
            }
        }
        for(int i = 1; i < 10; i++){
            //up
            if(x-i >= 0){

                if(savemap[x-i][y] != 0 ){
                    for(int j = 1; x-i-j >= 0 && j < 10; j++){
                        if(savemap[x-i-j][y] < 0 && (checkkingup || checkkingdown)){
                        savemap[x-i-j][y] = canmove;
                        button[x-i-j][y]->setStyleSheet("border:2px solid red;");
                        break;
                        }
                    }
                    break;

                }
                else if(savemap[x-i][y] == 0){
                    //eat
                    savemap[x-i][y] = canmove;
                    button[x-i][y]->setStyleSheet("border:2px solid red;");
                }
                else break;
            }
        }
        for(int i = 1; i < 10; i++){
            //right
            if(y+i <= 8 && (checkkingup || checkkingdown)){
                if(savemap[x][y+i] != 0 ){
                    for(int j = 1; y+i+j <= 8 && j < 10; j++){
                        if(savemap[x][y+i+j] < 0){
                        savemap[x][y+i+j] = canmove;
                        button[x][y+i+j]->setStyleSheet("border:2px solid red;");
                        break;
                        }
                    }
                    break;
                }
                else if(savemap[x][y+i] == 0){
                    savemap[x][y+i] = canmove;
                    button[x][y+i]->setStyleSheet("border:2px solid red;");
                }
                else break;
            }
        }
        for(int i = 1; i < 10; i++){
            //left
            if(y-i >= 0 && (checkkingup || checkkingdown)){
                if(savemap[x][y-i] != 0 ){
                    for(int j = 1; y-i-j >= 0 && j < 10; j++){
                        if(savemap[x][y-i-j] < 0){
                        savemap[x][y-i-j] = canmove;
                        button[x][y-i-j]->setStyleSheet("border:2px solid red;");
                        break;
                        }
                    }
                    break;

                }
                else if(savemap[x][y-i] == 0){
                    //eat
                    savemap[x][y-i] = canmove;
                    button[x][y-i]->setStyleSheet("border:2px solid red;");
                }
                else break;
            }
        }

    }
    if(rb < 0){

        for(int i = 1;  i < 10; i++){
            //down
            if(x+i <= 9){
                if(savemap[x+i][y] != 0 ){
                    for(int j = 1; x+i+j <= 9 && j < 10; j++){
                        if(savemap[x+i+j][y] > 0&& (checkkingup || checkkingdown)){
                        savemap[x+i+j][y] = canmove;
                        button[x+i+j][y]->setStyleSheet("border:2px solid black;");
                        break;
                        }
                    }
                    break;

                }
                else if(savemap[x+i][y] == 0){
                    //eat
                    savemap[x+i][y] = canmove;
                    button[x+i][y]->setStyleSheet("border:2px solid black;");
                }
                else break;
            }
        }
        for(int i = 1; i < 10; i++){
            //up
            if(x-i >= 0){
                if(savemap[x-i][y] != 0 ){
                    for(int j = 1; x-i-j >= 0 && j < 10; j++){
                        if(savemap[x-i-j][y] > 0&& (checkkingup || checkkingdown)){
                        savemap[x-i-j][y] = canmove;
                        button[x-i-j][y]->setStyleSheet("border:2px solid black;");
                        break;
                        }
                    }
                    break;

                }
                else if(savemap[x-i][y] == 0){
                    //eat
                    savemap[x-i][y] = canmove;
                    button[x-i][y]->setStyleSheet("border:2px solid black;");
                }
                else break;
            }
        }
        for(int i = 1; i < 10; i++){
            //right
            if(y+i <= 8&& (checkkingup || checkkingdown)){
                if(savemap[x][y+i] != 0 ){
                    for(int j = 1; y+i+j <= 8 && j < 10; j++){
                        if(savemap[x][y+i+j] > 0){
                        savemap[x][y+i+j] = canmove;
                        button[x][y+i+j]->setStyleSheet("border:2px solid black;");
                        break;
                        }
                    }
                    break;
                }
                else if(savemap[x][y+i] == 0){
                    savemap[x][y+i] = canmove;
                    button[x][y+i]->setStyleSheet("border:2px solid black;");
                }
                else break;
            }
        }
        for(int i = 1; i < 10; i++){
            //left
            if(y-i >= 0&& (checkkingup || checkkingdown)){
                if(savemap[x][y-i] != 0 ){
                    for(int j = 1; y-i-j >= 0 && j < 10; j++){
                        if(savemap[x][y-i-j] > 0){
                        savemap[x][y-i-j] = canmove;
                        button[x][y-i-j]->setStyleSheet("border:2px solid black;");
                        break;
                        }
                    }
                    break;

                }
                else if(savemap[x][y-i] == 0){
                    //eat
                    savemap[x][y-i] = canmove;
                    button[x][y-i]->setStyleSheet("border:2px solid black;");
                }
                else break;
            }
        }
    }
}
void MainWindow:: pawnmove(int rb , int x, int y){
    if(rb > 0 && x > 4 && savemap[x-1][y] <= 0){
       savemap[x-1][y] = canmove;
       button[x-1][y]->setStyleSheet("border:2px solid red;");
    }
    else if(rb > 0 ){
        if(x > 0 && savemap[x-1][y] <= 0){
            savemap[x-1][y] = canmove;
            button[x-1][y]->setStyleSheet("border:2px solid red;");
        }
        if(y+1 < 9  && savemap[x][y+1] <= 0&& (checkkingup || checkkingdown) ){
            savemap[x][y+1] = canmove;
            button[x][y+1]->setStyleSheet("border:2px solid red;");
        }
        if(y-1 > 0 && savemap[x][y-1] <= 0&& (checkkingup || checkkingdown) ){
            savemap[x][y-1] = canmove;
            button[x][y-1]->setStyleSheet("border:2px solid red;");
        }
    }
    if(rb < 0 && x < 5 && savemap[x+1][y] >= 0){
        savemap[x+1][y] = canmove;
        button[x+1][y]->setStyleSheet("border: 2px solid black;");
    }
    else if(rb < 0 ){

        if(x < 9 && savemap[x+1][y] >= 0){
            savemap[x+1][y] = canmove;
            button[x+1][y]->setStyleSheet("border: 2px solid black;");
        }
        if(y+1 < 9 && savemap[x][y+1] >= 0&& (checkkingup || checkkingdown)){
            savemap[x][y+1] = canmove;
             button[x][y+1]->setStyleSheet("border: 2px solid black;");
        }
        if(y-1 > 0 && savemap[x][y-1] >= 0&& (checkkingup || checkkingdown)){
            savemap[x][y-1] = canmove;
             button[x][y-1]->setStyleSheet("border: 2px solid black;");
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_released()
{
    //set clickedx clickedy
    clickedx = 2;
    clickedy = 0;
    play = 1;
    status = 1; //normal type
    for(int i = 0; i < 32; i++){
        set[i]->hide();
    }
    MainWindow::setmap();
    MainWindow::drawmap();
}


void MainWindow::movechess(int number){
    qDebug() << number;
    choose = number;
}

void MainWindow::on_setgame_clicked()
{

    for(int i = 0; i< 32; i++){
        set[i]->show();
    }
    //if your mouse click two in one times , it will get trouble
    clickedx = -1;
    clickedy = -1;
    //red
    set[16]->setIcon(pix[7]);
    set[17]->setIcon(pix[6]);
    set[18]->setIcon(pix[6]);
    set[19]->setIcon(pix[5]);
    set[20]->setIcon(pix[5]);
    set[21]->setIcon(pix[4]);
    set[22]->setIcon(pix[4]);
    set[23]->setIcon(pix[3]);
    set[24]->setIcon(pix[3]);
    set[25]->setIcon(pix[2]);
    set[26]->setIcon(pix[2]);
    for(int i = 0; i < 5; i++){
        set[27+i]->setIcon(pix[1]);
    }
    //black
    set[0]->setIcon(pix[14]);
    set[1]->setIcon(pix[13]);
    set[2]->setIcon(pix[13]);
    set[3]->setIcon(pix[12]);
    set[4]->setIcon(pix[12]);
    set[5]->setIcon(pix[11]);
    set[6]->setIcon(pix[11]);
    set[7]->setIcon(pix[10]);
    set[8]->setIcon(pix[10]);
    set[9]->setIcon(pix[9]);
    set[10]->setIcon(pix[9]);
    for(int i = 0; i < 5; i++){
        set[11+i]->setIcon(pix[8]);
    }
    for(int i = 0; i < 32; i++){
        set[i]->setIconSize(QSize(60, 60));
    }
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 9; j++){
            map[i][j] = 0;
        }
    }
    MainWindow::drawmap();

}

void MainWindow::on_startsetgame_clicked()
{
    //change clickedx & clickedy > 0 then start play
    clickedx = 2;
    clickedy = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 9; j++){
            savemap[i][j] = map[i][j];
        }
    }
}

void MainWindow::on_server_clicked()
{
    status = 2; //server status
    //get port & cast to unsigned short
    serverport = ui->serverport->toPlainText();
    unsigned short port = serverport.toUShort();
    //change clickedx & clickedy then play
    clickedx = 2;
    clickedy = 0;
    //QTcpSocket
    //build QTcpServer
    server = new QTcpServer(this);
    //listen
    server->listen(QHostAddress::Any,port);
    //build & new socket
    connect(server,SIGNAL(newConnection()),this,SLOT(acceptConnection()));
    qDebug() << "start listening";
}
void MainWindow::acceptConnection(){

    //new socket & get client information
    serverSocket = new QTcpSocket(this);
    serverSocket = server->nextPendingConnection();
    qDebug() << "accept";

    //wait & receive paload
    //serverSocket->write((char*)map,90*4);
    /*
    //send initailized map
    memset(sendbuff, 0 , sizeof(sendbuff));
    memcpy(sendbuff + HEADERSIZE, map, 90*4);
    sendbuff[0] = 'a';
    serverSocket->write(sendbuff, BUFFSIZE);
    */
    connect(serverSocket,SIGNAL(readyRead()),this,SLOT(sendclient()));

}
void MainWindow::sendclient(){
    /*
     //接收客户端信息
    //QString msg=QString(serverSocket->readAll());
    */

    memset(recbuff, 0, sizeof(recbuff));
    serverSocket->read(recbuff, BUFFSIZE);
    //change save map
    if(recbuff[0] == 'a'){
        memcpy(map, recbuff+HEADERSIZE, 90*4);
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 9; j++){
                savemap[i][j] = map[i][j];
            }
        }
        //qDebug() << map;
        drawmap();
        whoplay = -1;//turn black player

    }
    if(recbuff[0] == 'e'){
        memcpy(map, recbuff+HEADERSIZE, 90*4);
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 9; j++){
                savemap[i][j] = map[i][j];
            }
        }
        //qDebug() << map;
        drawmap();
        whoplay = 1;//turn red player

    }
    if(recbuff[0] == 'b'){
        QMessageBox::information(this,"result：","You win！",QMessageBox::Ok);
    }
    if(recbuff[0] == 'c'){
        QMessageBox::information(this,"result：","You lose！",QMessageBox::Ok);
    }
    if(recbuff[0] == 'd'){
        QString text;
        text = (recbuff+1);
        ui->chatroom->append(text);
    }

}


void MainWindow::on_client_clicked()
{
    status = 3; //client status
    //get client ip & port
    clientip = ui->clientip->toPlainText();
    clientport = ui->clientport->toPlainText();
    //change clickedx & clickedy then play
    clickedx = 2;
    clickedy = 0;
    client = new QTcpSocket(this);
    unsigned short port = clientport.toUShort();
    client->connectToHost(QHostAddress(clientip), port);

    memset(recbuff, 0, BUFFSIZE);
    client->read(recbuff, BUFFSIZE);
    /*if(recbuff[0] == 'e'){
        memcpy(map, recbuff+HEADERSIZE, 90*4);

        //change save map
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 9; j++){
                savemap[i][j] = map[i][j];
            }
        }
        whoplay = 1;//turn red player
        drawmap();
    }*/
    if(recbuff[0] == 'a'){
        memcpy(map, recbuff+HEADERSIZE, 90*4);

        //change save map
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 9; j++){
                savemap[i][j] = map[i][j];
            }
        }
        whoplay = -1;//turn black player
        drawmap();
    }

    connect(client,SIGNAL(readyRead()),this,SLOT(getserver()));

    qDebug()<< "connect to server";

}
void MainWindow::getserver(){
    memset(recbuff, 0, BUFFSIZE);
    client->read(recbuff, BUFFSIZE);


    if(recbuff[0] == 'a'){
        memcpy(map, recbuff+HEADERSIZE, 90*4);

        //change save map
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 9; j++){
                savemap[i][j] = map[i][j];
            }
        }
        whoplay = -1;//turn black player
        drawmap();
    }
    if(recbuff[0] == 'e'){
        memcpy(map, recbuff+HEADERSIZE, 90*4);

        //change save map
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 9; j++){
                savemap[i][j] = map[i][j];
            }
        }
        whoplay = 1;//turn red player
        drawmap();
    }
    if(recbuff[0] == 'b'){
        QMessageBox::information(this,"result：","You win！",QMessageBox::Ok);
    }
    if(recbuff[0] == 'c'){
        QMessageBox::information(this,"result：","You lose！",QMessageBox::Ok);
    }
    if(recbuff[0] == 'd'){
        QString text;
        text = (recbuff+1);
        ui->chatroom->append(text);
    }
}



void MainWindow::on_enter_pressed()
{
    memset(sendbuff, 0, sizeof(sendbuff));
    QString text = ui->communication->toPlainText();
    QByteArray byteArray=text.toLocal8Bit ();
    strcpy(sendbuff+1,byteArray.data());
    ui->chatroom->append(text);
    ui->communication->setText("");
    if(status == 2){
        sendbuff[0] = 'd';
        //memcpy(sendbuff+HEADERSIZE, (char*)&text, sizeof(text));
        serverSocket->write(sendbuff, BUFFSIZE);
        //qDebug() << sendbuff;
    }
    if(status == 3){
        sendbuff[0] = 'd';
        client->write(sendbuff, BUFFSIZE);
    }

}

void MainWindow::on_sendmap_clicked()
{

    if(status == 2){
        whoplay = 1;//because readyread will emit first
        memset(sendbuff, 0, sizeof(sendbuff));
        //serverSocket->write((char*)map, 90*4);
        memcpy(sendbuff + HEADERSIZE, map, 90*4);
        sendbuff[0] = 'e';
        serverSocket->write(sendbuff, BUFFSIZE);
    }
    //client send eat after eat
    if(status == 3){
        whoplay = -1;//because readyread will emit first
        //client->write((char*)map,90*4);
        memset(sendbuff, 0 , sizeof(sendbuff));
        memcpy(sendbuff + HEADERSIZE, map, 90*4);
        sendbuff[0] = 'a';
        client->write(sendbuff, BUFFSIZE);
    }
}



void MainWindow::on_restart_clicked()
{
    //set clickedx clickedy
    clickedx = 2;
    clickedy = 0;
    play = 1;
    for(int i = 0; i < 32; i++){
        set[i]->hide();
    }
    MainWindow::setmap();
    MainWindow::drawmap();

    if(status == 2){
        whoplay = 1;//because readyread will emit first
        memset(sendbuff, 0, sizeof(sendbuff));
        //serverSocket->write((char*)map, 90*4);
        memcpy(sendbuff + HEADERSIZE, map, 90*4);
        sendbuff[0] = 'e';
        serverSocket->write(sendbuff, BUFFSIZE);

    }
    //client send eat after eat
    if(status == 3){
        //client->write((char*)map,90*4);
        whoplay = -1;//because readyread will emit first
        memset(sendbuff, 0 , sizeof(sendbuff));
        memcpy(sendbuff + HEADERSIZE, map, 90*4);
        sendbuff[0] = 'a';
        client->write(sendbuff, BUFFSIZE);
    }
}
