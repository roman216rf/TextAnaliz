#include "numberword.h"
//Алгоритм для анализа распределения слов по их длиннам

QString NumberWord::run(const QString &data){
    QMap <int, int> result_map;
    QString result;
    int length = 0;

    /*
     * Проходим циклом по всей строке
     * Если очередной символ является буквой, то увеличиваем длину счетаемого слова на один
     * Иначе, если в map существует ключ соответствующий данной длине, то увеличиваем значение на один
     * Если такого ключа нет и длина не равна нулю, то создаем ключ с количеством слов равное 1.
     * После чего обнуляем длину для подсчета следующего слова.
     */
    for(const QChar c: data){
        if(c.isLetter()) // а если вместо букв будут цифры?
            ++length;   // разбить на слова можно проще qthelp://org.qt-project.qtcore.612/qtcore/qstring.html#split-2
        else{
            //сложно см. NumberChar
            if (result_map.contains(length))
                result_map.insert(length, result_map.value(length)+1);
            else if(length)
                result_map.insert(length, 1);

            length = 0;
        }
    }

    //Формируем результаты для возврата
    result = "\nРаспределение слов по их длинам:\n";
    QMapIterator<int, int>i(result_map);
    while(i.hasNext()){
        i.next();
        result = result + "Слово длиной " + QString::number(i.key()) + " символов встречается " + QString::number(i.value()) + " раз(а).\n";
    }

    return result;
}
