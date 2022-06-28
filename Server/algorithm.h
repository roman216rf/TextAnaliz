#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <QString>

class Algorithm{
public:
    virtual QString run(const QString& data) = 0;
    virtual ~Algorithm(){};
};

class Factory{
public:
    virtual Algorithm* createAlgorithm() = 0;
    virtual ~Factory(){};
};
#endif // ALGORITHM_H
