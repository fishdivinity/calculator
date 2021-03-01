#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <deque>
#include <iterator>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

#define DEBUG qDebug()<<__LINE__;
inline char operator_QString(QString& character)
{
    if (character == "×")
        return '*';
    else if (character == "÷")
        return '/';
    else if (character == "+")
        return '+';
    else if (character == "-")
        return '-';
    else if (character == "%")
        return '%';
    else if (character == "(")
        return '(';
    else if (character == ")")
        return ')';
    return 0;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_number_pushButton_clicked();
    void on_operator_pushButton_clicked();
    void on_result_pushButton_clicked();
    void on_backspace_pushButton_clicked();
    void on_clean_pushButton_clicked();
    void on_priority_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QString temp;
    QString outputBrowserString;
    QString figure;

    std::deque<double> figureDeque;
    std::deque<char> operatorDeque;

    bool dotFlag = false;
    bool resultFlag = false;
    bool leftBracketFlag=false;
    bool rightBracketFlag=true;
    short bracketPair=0;
};
#endif // MAINWINDOW_H
