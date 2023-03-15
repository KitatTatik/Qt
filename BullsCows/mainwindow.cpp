#include "mainwindow.h"
#include "./ui_mainwindow.h"

vector<int> getRandomCode();

void createSet();

void combinationRecursive(int combinationLength, int position, vector<int> &current, vector<int> &elements);

string checkCode(vector<int> guess, vector<int> code);

void removeCode(vector<vector<int>> &set, vector<int> code);

void pruneCodes(vector<vector<int>> &set, vector<int> code, string currentResponse);

vector<vector<int>> minmax();

int getMaxScore(map<string, int> inputMap);

int getMinScore(map<vector<int>, int> inputMap);

vector<int> getNextGuess(vector<vector<int>> nextGuesses);

static const int NUM_COLOURS = 6;
static const int CODE_LENGTH = 4;
vector<vector<int>> combinations; //Master set of combinations 1111 to 6666
vector<vector<int>> candidateSolutions;
vector<vector<int>> nextGuesses;
vector<int> code;
vector<int> currentGuess;
string responsePegs;
bool won;
int turn;
int rowOut;
QStandardItem *item;
QStandardItem* item2;
//QStandardItemModel *model = new QStandardItemModel;
QString qstr;

QColor WhatColorInt(int i){
    QColor outcolor;
    switch (i) {
        case 1:
            outcolor=Qt::green;
        break;
        case 2:
            outcolor=Qt::yellow;
        break;
        case 3:
            outcolor=Qt::red;
        break;
        case 4:
            outcolor=Qt::blue;
        break;
        case 5:
            outcolor=Qt::cyan;
        break;
        case 6:
            outcolor=Qt::magenta;
        break;
        default:
        break;
    }
    return(outcolor);
}
QColor ColorBW(QString ss){
    QColor outcolor;
    if (ss == "B") {
        outcolor=Qt::black;
    }else if (ss == "W"){
        outcolor=Qt::gray;
    }
    return(outcolor);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStandardItemModel *model = new QStandardItemModel (16,12);
    (ui->tableView)->setModel(model);

    for (int row = 0; row < model->rowCount(); ++row) {
            for (int column = 0; column < model->columnCount(); ++column) {
                model->setData(model->index(row, column), QVariant(""));

            }
        }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            ui->tableView->setSpan(i*2, j*2, 2, 2);
        }
    }
    (ui->tableView)->setModel(model);
    ui->tableView->show();

    turn = 1;
    rowOut = 2;
    won = false;

    code = getRandomCode();
    currentGuess = {1, 1, 2, 2}; //1122

    //set of 6^4 = 1296 variants
    createSet();
    candidateSolutions.insert(candidateSolutions.end(), combinations.begin(), combinations.end());

     for (int i = 0; i < code.size(); ++i) {
        item = new QStandardItem(QString("%1").arg(code[i]));
        item->setData(QColor(WhatColorInt(code[i])), Qt::BackgroundRole);
        item->setData(QColor(WhatColorInt(code[i])), Qt::ForegroundRole);
        model->setItem(0, 2*i, item);

     }
    // item = new QStandardItem(QString("C"));
    // model->setItem(0, 4, item);

    while (!won) {
        rowOut = rowOut+2;

        removeCode(combinations, currentGuess);
        removeCode(candidateSolutions, currentGuess);


        responsePegs = checkCode(currentGuess, code);

        cout << "STEP: " << turn << endl;
        cout << "TRY: ";
        for (int i = 0; i < currentGuess.size(); ++i) {
            item = new QStandardItem(QString("%1").arg(currentGuess[i]));
            item->setData(QColor(WhatColorInt(currentGuess[i])), Qt::BackgroundRole);
            item->setData(QColor(WhatColorInt(currentGuess[i])), Qt::ForegroundRole);
            model->setItem(rowOut, i*2, item);
        }
        cout << "= " << responsePegs << endl << endl;
        qstr = QString::fromStdString(responsePegs);
        int j = 2 * CODE_LENGTH + 1;
        item = new QStandardItem(2,2);
        for (int i = 0; i < qstr.size(); ++i) {
            QString temp = qstr.at(i);
            item = new QStandardItem(temp);
            item->setData(QColor(ColorBW(qstr.at(i))), Qt::BackgroundRole);
            item->setData(QColor(ColorBW(qstr.at(i))), Qt::ForegroundRole);
            model->setItem((rowOut+(i%2)), (9+i/2), item);

        }


        if (responsePegs == "BBBB") {
            won = true;
            cout << "Triumph!" << endl;
            break;
        }

        //Remove from candidateSolutions,
        //any code that would not give the same response if it were the code
        pruneCodes(candidateSolutions, currentGuess, responsePegs);

        nextGuesses = minmax();
        currentGuess = getNextGuess(nextGuesses);

        turn++;

    }

   ui->tableView->setModel(model);
   ui->tableView->verticalHeader()->setMinimumSectionSize(4);
   ui->tableView->horizontalHeader()->setMinimumSectionSize(4);
   ui->tableView->setModel(model);

}

MainWindow::~MainWindow()
{
    delete ui;
}

vector<int> getRandomCode() {

    vector<int> code;
    int max = NUM_COLOURS;
    int min = 1;
    int random;

    srand(time(0));

    for (int i = 0; i < CODE_LENGTH; ++i) {

        random = min + (rand() % (max - min + 1));
        code.push_back(random);
    }

    return code;
}

void createSet() {

    vector<int> current(CODE_LENGTH, 0);
    vector<int> elements;

    for (int i = 1; i <= NUM_COLOURS; ++i) {
        elements.push_back(i);
    }

    combinationRecursive(CODE_LENGTH, 0, current, elements);
}

void combinationRecursive(int combinationLength, int position, vector<int> &current, vector<int> &elements) {

    if (position >= combinationLength) {
        combinations.push_back(current);
        return;
    }

    for (int j = 0; j < elements.size(); ++j) {
        current[position] = elements[j];
        combinationRecursive(combinationLength, position + 1, current, elements);
    }
    return;
}

string checkCode(vector<int> guess, vector<int> code) {

    string result;

    //Get black
    for (int i = 0; i < CODE_LENGTH; ++i) {

        if (guess[i] == code[i]) {
            result.append("B");
            guess[i] *= -1;
            code[i] *= -1;
        }
    }

    //Get white
    for (int i = 0; i < CODE_LENGTH; ++i) {

        if (code[i] > 0) {

            vector<int>::iterator it = find(guess.begin(), guess.end(), code[i]);
            int index;
            if (it != guess.end()) {

                index = distance(guess.begin(), it);
                result.append("W");
                guess[index] *= -1;
            }
        }
    }

    return result;
}

void removeCode(vector<vector<int>> &set, vector<int> currentCode) {

    int index;
    for (auto it = set.begin(); it != set.end(); it++) {
        index = distance(set.begin(), it);

        if (set[index] == currentCode) {
            set.erase(set.begin() + index);
            break;
        }
    }
}

void pruneCodes(vector<vector<int>> &set, vector<int> currentCode, string currentResponse) {

    int index;
    vector<vector<int>>::iterator it = set.begin();

    while (it != set.end()) {
        index = distance(set.begin(), it);

        if (currentResponse != checkCode(currentCode, set[index])) {
            it = set.erase(set.begin() + index);
        } else {
            it++;
        }
    }
}

vector<vector<int>> minmax() {

    map<string, int> scoreCount;
    map<vector<int>, int> score;
    vector<vector<int>> nextGuesses;
    int max, min;

    for (int i = 0; i < combinations.size(); ++i) {

        for (int j = 0; j < candidateSolutions.size(); ++j) {

            string pegScore = checkCode(combinations[i], candidateSolutions[j]);
            if (scoreCount.count(pegScore) > 0) {
                scoreCount.at(pegScore)++;
            } else {
                scoreCount.emplace(pegScore, 1);
            }
        }

        max = getMaxScore(scoreCount);
        score.emplace(combinations[i], max);
        scoreCount.clear();
    }

    min = getMinScore(score);

    for (auto elem : score) {
        if (elem.second == min) {
            nextGuesses.push_back(elem.first);
        }
    }

    return nextGuesses;
}

int getMaxScore(map<string, int> inputMap) {

    int max = 0;
    for (auto elem : inputMap) {
        if (elem.second > max) {
            max = elem.second;
        }
    }

    return max;
}

int getMinScore(map<vector<int>, int> inputMap) {

    int min = numeric_limits<int>::max();
    for (auto elem : inputMap) {
        if (elem.second < min) {
            min = elem.second;
        }
    }

    return min;
}

vector<int> getNextGuess(vector<vector<int>> nextGuesses) {

    vector<int> nextGuess;

    for (int i = 0; i < nextGuesses.size(); ++i) {
        if (find(candidateSolutions.begin(), candidateSolutions.end(), nextGuesses[i]) != candidateSolutions.end()) {
            return nextGuesses[i];
        }
    }
    for (int j = 0; j < nextGuesses.size(); ++j) {
        if (find(combinations.begin(), combinations.end(), nextGuesses[j]) != combinations.end()) {
            return nextGuesses[j];
        }
    }

    return nextGuess;
}
