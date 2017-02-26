#ifndef PATTERN_H
#define PATTERN_H

#include <QByteArray>

template <class T>
class Pattern
{
public:
    Pattern(QByteArray p_path, T * p_handler){
        m_path = removeSlash(p_path);
        m_tokens = m_path.split('/');
        m_handler = p_handler;
    }

    ~Pattern(){}

    QByteArray path(){
        return m_path;
    }
    QList<QByteArray>  tokens(){
        return m_tokens;
    }
    T * handler(){
        return m_handler;
    }

    static QByteArray removeSlash(QByteArray p_path){

        if (p_path.isEmpty()) return p_path;

        int beginIndex = 0;
        while (beginIndex < p_path.length() && p_path[beginIndex] == '/') beginIndex++;
        if (beginIndex == p_path.length()) return QByteArray();

        int endIndex = p_path.length();
        if(p_path.endsWith('/')) endIndex -=1;
        while (endIndex > beginIndex && p_path[endIndex] == '/') endIndex--;

        return p_path.mid(beginIndex, endIndex);
    }

private:
    QByteArray m_path;
    QList<QByteArray> m_tokens;
    T *m_handler;

    bool m_hasTokens;
};

#endif // PATTERN_H
