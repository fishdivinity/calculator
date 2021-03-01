#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icon/calc.ico"));
    this->setWindowTitle("calculator");

    //数字
    connect(ui->zeroButton, SIGNAL(clicked()), this, SLOT(on_number_pushButton_clicked()));
    connect(ui->oneButton, SIGNAL(clicked()), this, SLOT(on_number_pushButton_clicked()));
    connect(ui->twoButton, SIGNAL(clicked()), this, SLOT(on_number_pushButton_clicked()));
    connect(ui->threeButton, SIGNAL(clicked()), this, SLOT(on_number_pushButton_clicked()));
    connect(ui->fourButton, SIGNAL(clicked()), this, SLOT(on_number_pushButton_clicked()));
    connect(ui->fiveButton, SIGNAL(clicked()), this, SLOT(on_number_pushButton_clicked()));
    connect(ui->sixButton, SIGNAL(clicked()), this, SLOT(on_number_pushButton_clicked()));
    connect(ui->sevenButton, SIGNAL(clicked()), this, SLOT(on_number_pushButton_clicked()));
    connect(ui->eightButton, SIGNAL(clicked()), this, SLOT(on_number_pushButton_clicked()));
    connect(ui->nineButton, SIGNAL(clicked()), this, SLOT(on_number_pushButton_clicked()));
    connect(ui->dotButton, SIGNAL(clicked()), this, SLOT(on_number_pushButton_clicked()));

    //运算
    connect(ui->complementationButton, SIGNAL(clicked()), this, SLOT(on_operator_pushButton_clicked()));
    connect(ui->pushOrMinusButton, SIGNAL(clicked()), this, SLOT(on_operator_pushButton_clicked()));
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(on_operator_pushButton_clicked()));
    connect(ui->minusButton, SIGNAL(clicked()), this, SLOT(on_operator_pushButton_clicked()));
    connect(ui->multiplyButton, SIGNAL(clicked()), this, SLOT(on_operator_pushButton_clicked()));
    connect(ui->divideButton, SIGNAL(clicked()), this, SLOT(on_operator_pushButton_clicked()));
    connect(ui->complementationButton, SIGNAL(clicked()), this, SLOT(on_operator_pushButton_clicked()));

    //优先级
    connect(ui->leftBracketButton, SIGNAL(clicked()), this, SLOT(on_priority_pushButton_clicked()));
    connect(ui->rightBracketButton, SIGNAL(clicked()), this, SLOT(on_priority_pushButton_clicked()));

    //结果
    connect(ui->equalButton, SIGNAL(clicked()), this, SLOT(on_result_pushButton_clicked()));

    //退格与清除
    connect(ui->backspaceButton, SIGNAL(clicked()), this, SLOT(on_backspace_pushButton_clicked()));
    connect(ui->cleanButton, SIGNAL(clicked()), this, SLOT(on_clean_pushButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_number_pushButton_clicked()
{
    if(resultFlag)
        on_clean_pushButton_clicked();
    temp = ((QPushButton *)sender())->text();
    leftBracketFlag=true;
    rightBracketFlag=false;
    if (temp == ".")
    {
        if (!dotFlag)
        {
            dotFlag = true;
            outputBrowserString += temp;
            ui->outputBrowser->setText(outputBrowserString);
            figure += temp;
        }
        else
            return;
    }
    else
    {
        outputBrowserString += temp;
        ui->outputBrowser->setText(outputBrowserString);
        figure += temp;
        return;
    }
    return;
}

void MainWindow::on_operator_pushButton_clicked()
{
    temp = ((QPushButton *)sender())->text();
    leftBracketFlag=false;
    rightBracketFlag=true;
    if (temp.size() == 1)
    {
        dotFlag = false;
        if(figure.isEmpty())
        {
            operatorDeque.pop_back();
            outputBrowserString=outputBrowserString.left(outputBrowserString.length()-1);
            ui->outputBrowser->setText(outputBrowserString);
        }
        outputBrowserString+=temp;
        ui->outputBrowser->setText(outputBrowserString);
        operatorDeque.push_back(operator_QString(temp));
        figureDeque.push_back(figure.toDouble());
        figure.clear();
    }
    else
    {
        //转换正负
        return;
    }
}

void MainWindow::on_result_pushButton_clicked()
{
    resultFlag=true;
    if(figure.isEmpty())
    {
        if(figureDeque.empty())
        {
            ui->outputBrowser->setText("FALSE");
            return;
        }
        if(*(operatorDeque.end())!=')')
        {
            operatorDeque.pop_back();
            outputBrowserString=outputBrowserString.left(outputBrowserString.length()-1);
            ui->outputBrowser->setText(outputBrowserString);
        }

    }
    else
    {
        figureDeque.push_back(figure.toDouble());
    }
outputBrowserString+='=';
ui->outputBrowser->setText(outputBrowserString);
    if(figureDeque.size()==1)
    {
        outputBrowserString += QString::number(*(figureDeque.begin()));
        ui->outputBrowser->setText(outputBrowserString);
        return;
    }

    std::deque<double>::iterator figureDequeIterator1,figureDequeIterator2;
    std::deque<char>::iterator operatorDequeIterator1,operatorDequeIterator2;

    figureDequeIterator2=figureDequeIterator1=figureDeque.begin();
    figureDequeIterator2++;
    operatorDequeIterator2=operatorDequeIterator1=operatorDeque.begin();
//    //优先级设置...
//    for(figureDequeIterator2=figureDequeIterator1=figureDeque.begin(),figureDequeIterator2++,operatorDequeIterator2=operatorDequeIterator1=operatorDeque.begin(),operatorDequeIterator2++;figureDequeIterator2!=figureDeque.end();figureDequeIterator2++)
//    {
//        if(*operatorDequeIterator1 == '(' )
//        {
//            bracketPair++;
//            operatorDequeIterator1++;
//            operatorDequeIterator2++;
//        }
//    }
//    if(bracketPair)

    for (;figureDequeIterator1!=figureDeque.end(); )
    {
        if(*operatorDequeIterator1 == '*')
        {
            *figureDequeIterator2 *= *figureDequeIterator1;
            figureDeque.erase(figureDequeIterator1);
            figureDequeIterator1=figureDequeIterator2;
            if(figureDequeIterator2!=figureDeque.end())
            {
                figureDequeIterator2++;
                operatorDequeIterator2++;
            }
            operatorDeque.erase(operatorDequeIterator1);
            operatorDequeIterator1=operatorDequeIterator2;
        }
        else if(*operatorDequeIterator1 == '/')
        {
            *figureDequeIterator2 = (*figureDequeIterator1)/(*figureDequeIterator2);
            figureDeque.erase(figureDequeIterator1);
            figureDequeIterator1=figureDequeIterator2;
            if(figureDequeIterator2!=figureDeque.end())
            {
                figureDequeIterator2++;
                operatorDequeIterator2++;
            }
            operatorDeque.erase(operatorDequeIterator1);
            operatorDequeIterator1=operatorDequeIterator2;
        }
        else if(*operatorDequeIterator1 == '%')
        {
            DEBUG
            *figureDequeIterator2 = ((int)(*figureDequeIterator1)) % ((int)(*figureDequeIterator2));
            DEBUG
            figureDeque.erase(figureDequeIterator1);
            figureDequeIterator1=figureDequeIterator2;
            if(figureDequeIterator2!=figureDeque.end())
            {
                figureDequeIterator2++;
                operatorDequeIterator2++;
            }
            operatorDeque.erase(operatorDequeIterator1);
            operatorDequeIterator1=operatorDequeIterator2;
        }
        else
        {
            figureDequeIterator1=figureDequeIterator2;
            if(figureDequeIterator2!=figureDeque.end())
            {
                figureDequeIterator2++;
                operatorDequeIterator2++;
                operatorDequeIterator1=operatorDequeIterator2;
            }
            operatorDequeIterator1++;
        }
    }
    if(!(operatorDeque.empty()))
    {
        figureDequeIterator2=figureDequeIterator1=figureDeque.begin();
        figureDequeIterator2++;
        operatorDequeIterator2=operatorDequeIterator1=operatorDeque.begin();

        for(;figureDequeIterator1!=figureDeque.end();)
        {
            if(*operatorDequeIterator1 == '+')
            {
                *figureDequeIterator2 += *figureDequeIterator1;
                figureDeque.erase(figureDequeIterator1);
                figureDequeIterator1=figureDequeIterator2;
                if(figureDequeIterator2!=figureDeque.end())
                {
                    figureDequeIterator2++;
                    operatorDequeIterator2++;
                }
                operatorDeque.erase(operatorDequeIterator1);
                operatorDequeIterator1=operatorDequeIterator2;
            }
            else if(*operatorDequeIterator1 == '-')
            {
                *figureDequeIterator2 = (*figureDequeIterator1)-(*figureDequeIterator2);
                figureDeque.erase(figureDequeIterator1);
                figureDequeIterator1=figureDequeIterator2;
                if(figureDequeIterator2!=figureDeque.end())
                {
                    figureDequeIterator2++;
                    operatorDequeIterator2++;
                }
                operatorDeque.erase(operatorDequeIterator1);
                operatorDequeIterator1=operatorDequeIterator2;
            }
            else
            {
                figureDequeIterator1=figureDequeIterator2;
                if(figureDequeIterator2!=figureDeque.end())
                {
                    figureDequeIterator2++;
                    operatorDequeIterator2++;
                    operatorDequeIterator1=operatorDequeIterator2;
                }
                operatorDequeIterator1++;
            }
        }
    }
    outputBrowserString+=QString::number(*(figureDeque.begin()));
    ui->outputBrowser->setText(outputBrowserString);
    return;
}

void MainWindow::on_backspace_pushButton_clicked()
{
    if (!resultFlag)
    {
    }
    else
    {
        on_clean_pushButton_clicked();
        return;
    }
}

void MainWindow::on_clean_pushButton_clicked()
{
    outputBrowserString.clear();
    ui->outputBrowser->clear();
    figure.clear();
    figureDeque.clear();
    operatorDeque.clear();
    dotFlag = false;
    resultFlag = false;
    leftBracketFlag=false;
    rightBracketFlag=true;
    bracketPair=0;
}

void MainWindow::on_priority_pushButton_clicked()
{
    temp = ((QPushButton *)sender())->text();
    if((!leftBracketFlag) && temp=="(")
    {
        outputBrowserString+=temp;
        ui->outputBrowser->setText(outputBrowserString);
        operatorDeque.push_back(operator_QString(temp));
        bracketPair++;
        return;
    }
    if((!rightBracketFlag) && bracketPair &&temp==")")
    {
        outputBrowserString+=temp;
        ui->outputBrowser->setText(outputBrowserString);
        operatorDeque.push_back(operator_QString(temp));
        bracketPair--;
        return;
    }
    return;
}
