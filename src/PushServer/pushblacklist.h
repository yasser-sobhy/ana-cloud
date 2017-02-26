#ifndef PUSHBLACKLIST_H
#define PUSHBLACKLIST_H

#include <QHostAddress>

class PushBlackList
{
public:
    PushBlackList(){}
    ~PushBlackList(){}

    void add(QHostAddress address){
        blackList.append(address.toIPv4Address());
    }

    void remove(QHostAddress address){
        blackList.removeOne(address.toIPv4Address());
    }

    bool contains(QHostAddress address){
        return blackList.contains(address.toIPv4Address());
    }

    QList<quint32> blackList;
};

#endif // PUSHBLACKLIST_H
