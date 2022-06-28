#include "numberchar.h"
//Алгоритм подсчета повторений каждого символа

QString NumberChar::run(const QString &data){
    QMap<QChar, int>result;
    QString str_result = "";

    /* Проходим циклом по всей строке
     * Если в Map отсутствует ключ, соответствующий символу, то создаём такой ключ и записываем в него количество вхождений символа.
     */
    for(const QChar c: data){
        //сложно и не эффективно
        //проще result[c]++;
        if (!result.contains(c) && c != '\n'){
            result[c] = data.count(c);
        }
    }

    //Формируем вывод результатов
    str_result = "\nКоличество повторений символов:\n";
    QMapIterator<QChar, int>i(result);
    while(i.hasNext()){
        i.next();
        str_result = str_result + "Символ '" + QString(i.key()) + "' повторяется " + QString::number(i.value()) + " раз(а).\n";
    }

    return str_result;
}
