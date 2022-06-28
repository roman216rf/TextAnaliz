#ifndef NUMBERCHAR_H
#define NUMBERCHAR_H

#include <QObject>
#include <QMap>
#include <algorithm.h>

class NumberChar: public Algorithm{
public:
    QString run(const QString& data);
};

class NumberCharFactory: public Factory{
public:
    Algorithm* createAlgorithm(){return new NumberChar;};
};

#endif // NUMBERCHAR_H
