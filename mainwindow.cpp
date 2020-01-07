#include "mainwindow.h"
#include <QJsonArray>
#include <QStringList>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  this->socket = new QTcpSocket(this);
  connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
  connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));
  this->socket->connectToHost("localhost", 4567);
  this->loadFirstQuery();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::sockReady() {
  if (this->socket->waitForConnected(500)) {
    this->socket->waitForReadyRead(500);
    QByteArray arr = this->socket->readAll();

    //    qInfo() << "Test: " << arr;

    QJsonDocument tmp = QJsonDocument::fromBinaryData(arr);

    //    qDebug() << tmp[0].toInt();
    //    qDebug() << tmp[2][0];
    //    qDebug() << tmp[2][1];
    //    qDebug() << arr;

    if (tmp[0].toInt() == 0) {
      qDebug() << "0";
      this->requestType0 = tmp;
      this->processFirstQuery();
    }
    if (tmp[0].toInt() == 1) {
      qDebug() << "1";
      this->requestType1 = tmp;
      this->processSecondQuery();
    }
    if (tmp[0].toInt() == 2) {
      qDebug() << "2";
      this->requestType2 = tmp;
      this->processThirsQuery();
    }
    if (tmp[0].toInt() == 3) {
      qDebug() << "3";
      this->requestType3 = tmp;
      this->processFourthQuery();
    }
    if (tmp[0].toInt() == 4) {
      qDebug() << "4";
      this->requestType4 = tmp;
      this->processFivethQuery();
    }
    if (tmp[0].toInt() == 5) {
      qDebug() << "5";
      this->requestType5 = tmp;
      this->processSixthQuery();
    }

    //    qDebug() << arr;
  }
}

void MainWindow::loadFirstQuery() {
  QJsonDocument jsonDoc;
  QJsonArray jsonMainArray;
  if (this->socket->waitForConnected(500)) {
    jsonMainArray.push_back("0");
    jsonDoc.setArray(jsonMainArray);
    this->socket->write(jsonDoc.toBinaryData());
    qDebug() << "write 0";
  }
}

void MainWindow::processFirstQuery() {
  QStringList strL;
  for (int i = 0; i < this->requestType0[1].toInt(); i++) {
    strL << this->requestType0[2 + i][1].toString();
  }
  this->ui->comboBox->addItems(strL);
}

void MainWindow::loadSecondQuery() {
  int personId = -123;
  QJsonDocument jsonDoc;
  QJsonArray jsonMainArray;
  for (int i = 0; i < this->requestType0[1].toInt(); i++) {
    if (this->requestType0[2 + i][1].toString() ==
        this->ui->comboBox->currentText()) {
      personId = this->requestType0[2 + i][0].toString().toInt();
    }
  }

  if (this->socket->waitForConnected(500)) {
    jsonMainArray.push_back("1");
    jsonMainArray.push_back(QString::number(personId));
    jsonDoc.setArray(jsonMainArray);
    this->socket->write(jsonDoc.toBinaryData());
    qDebug() << "write 1";
    qDebug() << "Person ID =" << personId;
  }
}

void MainWindow::processSecondQuery() {
  QStandardItemModel *model = new QStandardItemModel;
  QStandardItem *item;

  //Заголовки столбцов
  QStringList horizontalHeader;
  horizontalHeader.append("Violation ID");
  horizontalHeader.append("Violation kind");
  horizontalHeader.append("Punish kind");
  horizontalHeader.append("Order kind");

  model->setHorizontalHeaderLabels(horizontalHeader);

  for (int var = 0; var < requestType1[1].toInt(); ++var) {
    item = new QStandardItem(requestType1[2 + var][0].toString());
    model->setItem(var, 0, item);
    item = new QStandardItem(requestType1[2 + var][1].toString());
    model->setItem(var, 1, item);
    item = new QStandardItem(requestType1[2 + var][2].toString());
    model->setItem(var, 2, item);
    item = new QStandardItem(requestType1[2 + var][3].toString());
    model->setItem(var, 3, item);
  }

  ui->tableView->setModel(model);

  ui->tableView->resizeRowsToContents();
  ui->tableView->resizeColumnsToContents();
}

void MainWindow::loadThirsQuery() {
  if (this->socket->waitForConnected(500)) {
    this->socket->write("0");
    qDebug() << "write 0";
  }
}

void MainWindow::processThirsQuery() {}

void MainWindow::loadFourthQuery() {}

void MainWindow::processFourthQuery() {}

void MainWindow::loadFivethQuery() {}

void MainWindow::processFivethQuery() {}

void MainWindow::loadSixthQuery() {}

void MainWindow::processSixthQuery() {}

void MainWindow::sockDisc() { this->socket->deleteLater(); }

void MainWindow::on_pushButton_released() { this->loadSecondQuery(); }
