#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QByteArray>
#include <QJsonDocument>
#include <QMainWindow>
#include <QTcpSocket>
#include "QStandardItem"
#include "QStandardItemModel"

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  QTcpSocket *socket;

  void loadFirstQuery();
  void processFirstQuery();

  void loadSecondQuery();
  void processSecondQuery();

  void loadThirsQuery();
  void processThirsQuery();

  void loadFourthQuery();
  void processFourthQuery();

  void loadFivethQuery();
  void processFivethQuery();

  void loadSixthQuery();
  void processSixthQuery();

 public slots:
  void sockReady();
  void sockDisc();

 private slots:
  void on_pushButton_released();

  void on_tabWidget_currentChanged(int index);

  void on_pushButton_2_released();

  void on_pushButton_3_released();

 private:
  QJsonDocument requestType0;
  QJsonDocument requestType1;
  QJsonDocument requestType2;
  QJsonDocument requestType3;
  QJsonDocument requestType4;
  QJsonDocument requestType5;

  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
