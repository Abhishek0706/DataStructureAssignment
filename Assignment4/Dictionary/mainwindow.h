#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegExp>
#include <QPushButton>
#include <QDir>

namespace Ui {
class MainWindow;
}

struct TrieNode {
  public:
    bool isEndOfWord;
    QHash<QChar, TrieNode*> map;
    QString meaning;

    TrieNode(){
        isEndOfWord = false;
    }
};



class Trie{
public:
        TrieNode *root;

        Trie() {
            root = nullptr;
        }

        void insert(QString str, QString meaning){

            if (root == nullptr)
                root = new TrieNode();

            TrieNode* temp = root;
            for (int i = 0; i < str.length(); i++) {
                QChar x = str[i];


                if (temp->map.find(x) == temp->map.end())
                    temp->map[x] = new TrieNode();

                temp = temp->map[x];
            }

            temp->isEndOfWord = true;
            temp->meaning = meaning;
        }


        QString getMeaning(QString word){

            if (root == nullptr)
                return "";

            TrieNode* temp = root;

            for (int i = 0; i < word.length(); i++) {
                temp = temp->map[word[i]];
                if (temp == nullptr)
                    return "";
            }

            if (temp->isEndOfWord)
                return temp->meaning;
            return "";
        }
};


class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void LoadData(QString filename);
        Trie trie;
    public slots:
            void SearchMeaning();

private:
    Ui::MainWindow *ui;
    QPushButton *button;
};


#endif // MAINWINDOW_H
