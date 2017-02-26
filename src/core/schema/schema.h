#ifndef SCHEMA_H
#define SCHEMA_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QHash>
#include "rule.h"

// Rule may be a schema
// async, deffered for the next version
// negate a Rule, defered for the next version or may not be supported

class Schema
{
public:
    Schema(){}

    /*
    // apply this schema on a JSON document
    virtual bool apply(QJsonDocument &json){

        if (json.isObject()) apply(json.object());
        else apply(json.array());
    }

    // apply this schema on a JSON object
    virtual bool apply(QJsonObject &obj){

        for (Rule r: rule_values.keys()){
            r.apply(obj, obj.value(rule_values.value(r)));
        }

        for (QString str: value_rules.keys()){
            Rule r = value_rules.value(str);
            r.apply(obj, obj.value(str));
        }
    }

    // apply this schema on a JSON object
    virtual bool apply(QJsonArray &array){

        for (Rule r: rule_values.keys()){
            r.apply(array, obj.value(rule_values.value(r)));
        }
    }

    // append rule and a list of values to be applied on
    void append(Rule rule, QStringList values){
        rule_values.insert(rule, values);
    }

    // append value and a list of rules to be applied to
    void append(QString value, QList<Rule> rules){
        value_rules.insert(value, rules);
    }

    // same as append(Rule, QStringList);
    void operator << ( QHash<Rule, QStringList> hash){
        rule_values.unite(hash);
    }

    // same as append(QString, QList<Rule>);
    void operator << (QHash<QString, QList<Rule>> hash){
        value_rules.unite(hash);
    }

*/

private:
    QHash<Rule, QStringList> rule_values;
    QHash<QString, QList<Rule>> value_rules;

    QHash<Rule, QStringList> moderates;
};

#endif // SCHEMA_H
