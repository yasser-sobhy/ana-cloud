/****************************************************************************
**
** Copyright (C) 2016 Yasser Sobhy Saleh.
** Contact: yasser.sobhy.net@gmail.com
**          www.yasser-sobhy.com
**
** This file is part of the Core module of AnaCloud.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
****************************************************************************/

#ifndef RULE_H
#define RULE_H

#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "schemaerror.h"

class Rule
{
public:
    Rule(){}

    virtual bool apply(QJsonObject &obj, QJsonValue &value, QString valuename, SchemaError *error){ return false;}
    virtual bool apply(QJsonArray &array, QJsonValue &value, QString valuename, SchemaError *error){ return false;}

    virtual QString message(){}

protected:
    bool optional = false;
    QString errorMessage;
};


#endif // RULE_H
