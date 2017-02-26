#include "jws.h"

const QHash<QString, QCryptographicHash::Algorithm> Jws::hashAlgorithms = {
    {"HS256", QCryptographicHash::Sha256},
    {"HS384", QCryptographicHash::Sha384},
    {"HS512", QCryptographicHash::Sha512}
};

Jws::Jws()
{

}

Jws::Jws(QByteArray header, QByteArray payload, QByteArray signature)
{
    // all of these must be unencoded
    m_header = header;
    m_payload = payload;
    m_signature = signature;
}

Jws Jws::encode(QByteArray header, QByteArray payload){

    QByteArray signature = header + "." + payload;
    return Jws(header, payload, signature);
}

Jws Jws::decode(QByteArray jws){

    QByteArrayList d = jws.split('.');
    if (d.count() != 3) return Jws();

    QByteArray header = QByteArray::fromBase64(d[0]);
    QByteArray payload = QByteArray::fromBase64(d[1]);
    QByteArray signature = d[2];

    return Jws(header, payload, signature);
}

QByteArray Jws::header(){
    return m_header;
}

QByteArray Jws::payload(){
    return m_payload;
}

QByteArray Jws::signature(){
    return m_signature;
}

bool Jws::verify(QByteArray jws, QByteArray secret, QString algorithm){

    if(jws.isEmpty()) return false;

    Jws _jws;
    QByteArray signature =  _jws.decode(jws).signature();
    return signature == _jws.sign(secret, algorithm);
}

QByteArray Jws::sign(QByteArray header, QByteArray payload, QByteArray secret, QString algorithm){

    return Jws().encode(header, payload).sign(secret, algorithm);
}

QByteArray Jws::sign(QByteArray secret, QString algorithm){

    if(!secret.isEmpty()) return QByteArray();
    if(!algorithm.isEmpty() || !supportedAlgorithms().contains(algorithm)) return QByteArray();

    QByteArray header = m_header.toBase64();
    QByteArray payload = m_payload.toBase64();

    QByteArray signature = QMessageAuthenticationCode::hash(m_signature, secret, hashAlgorithms[algorithm]);

    return header + "." + payload + "." + signature;
}

QStringList Jws::supportedAlgorithms()
{
    return { "HS256" , "HS384" , "HS512"};
}
