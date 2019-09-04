#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
       ui(new Ui::MainWindow)
   {
       QString path = QDir::currentPath();

       QStringList list = path.split("/");
       QString Path = "";
       for(int i{0}; i < list.size()-1; i++) {
            Path += list[i] + "/";
       }

       qDebug() << Path;

       ui->setupUi(this);
       LoadData(Path + "Dictionary/L4_P1_input.csv");
       button = ui->searchButton;
       connect(button, SIGNAL(clicked()), this, SLOT(SearchMeaning()));
}


void MainWindow::LoadData(QString filename) {
    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "could not open file";
        return;
    }
    QTextStream in(&file);
    QString text;

    while((text = in.readLine()) != "") {
        QStringList query = text.split(",");
        QString second;
        for (int i = 1; i < query.size(); ++i){
                 second.append(query[i]);
                 if (i != query.size()-1)
                     second.append(", ");
        }
        trie.insert(query[0], second);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SearchMeaning() {
    QString word = ui->inputText->toPlainText();
    word = word.trimmed().toUpper();
    ui->meaning->clear();
    ui->meaning->setText(trie.getMeaning(word));
}
