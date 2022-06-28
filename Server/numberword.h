#ifndef NUMBERWORD_H
#define NUMBERWORD_H

#include <QObject>
#include <QMap>
#include <algorithm.h>

class NumberWord: public Algorithm{
public:
    QString run(const QString& data);
};

class NumberWordFactory: public Factory{
public:
    Algorithm* createAlgorithm(){return new NumberWord;};
};

#endif // NUMBERWORD_H
