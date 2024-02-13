#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include <QStyle>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Buttons style:
    ui->pushButtonOpen->setIcon(style()->standardIcon(QStyle::SP_FileIcon));
    ui->pushButtonPrev->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->pushButtonPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButtonPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButtonStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pushButtonNext->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));

    // Player init:
    m_player = new QMediaPlayer(this);
    m_player->setVolume(70);
    ui->labelVolume->setText(QString("Volume: ").append(QString::number(m_player->volume())));
    ui->horizontalSliderVolume->setValue(m_player->volume());
    qDebug() << m_player->duration();
}
MainWindow::~MainWindow()
{
    delete m_player;
    delete ui;
}


void MainWindow::on_pushButtonOpen_clicked()
{
    QString file = QFileDialog::getOpenFileName
            (
                this,
                "Open File",
                NULL,
                "Audio files(*.mp3 *.flac);; MP-3 (*.mp3);; Flac (*.flac)"
                );

    this->ui->labelFile->setText("File: " + file);
    this->setWindowTitle("MediaPlayerPD_321 - " + file.split('/').last());
    this->m_player->setMedia(QUrl::fromLocalFile(file));
}


void MainWindow::on_horizontalSliderVolume_valueChanged(int value)
{
    m_player->setVolume(value);
    ui->labelVolume->setText(QString("Volume :").append(QString::number(m_player->volume())));
}

void MainWindow::on_pushButtonPlay_clicked()
{
    m_player->play();
}

void MainWindow::on_pushButtonPause_clicked()
{
    m_player->pause();
}


