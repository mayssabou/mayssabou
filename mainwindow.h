#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlQuery>
#include <QMainWindow>
#include <QSqlQueryModel>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
void on_pushButton_2_clicked();

    void on_pushButton_16_clicked();
QSqlQueryModel* afficher();


    void on_pushButton_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();




void  on_tabWidget_currentChanged();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_8_clicked();

    void on_textEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_9_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;
    void pdf(QWidget* widget, const QString& filename);
};

#endif // MAINWINDOW_H
