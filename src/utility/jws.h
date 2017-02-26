#ifndef JWS_H
#define JWS_H

#include <QObject>
#include <QMessageAuthenticationCode>
#include <QJsonDocument>
#include <QJsonObject>
#include <QHash>

class Jws
{
public:
    Jws();
    Jws(QByteArray header, QByteArray payload, QByteArray signature);

    Jws encode(QByteArray header, QByteArray payload);
    Jws decode(QByteArray jws);

    QByteArray header();
    QByteArray payload();
    QByteArray signature();

    static QByteArray sign(QByteArray header, QByteArray payload, QByteArray secret, QString algorithm = "HS256");
    static bool verify(QByteArray jws, QByteArray secret, QString algorithm = "HS256");

    static QStringList supportedAlgorithms();

private:
    // sign using local header and payload
    QByteArray sign(QByteArray secret, QString algorithm);

    static const QHash<QString, QCryptographicHash::Algorithm> hashAlgorithms;

    QByteArray m_header;	// unencoded
    QByteArray m_payload;   // unencoded
    QByteArray m_signature; // unencoded
};

#endif // JWS_H
