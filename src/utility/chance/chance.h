#ifndef CHANCE_H
#define CHANCE_H

#include <QString>
#include <climits>
#include <QtMath>
#include <QVector>
#include <QStringList>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QUuid>
#include <QCryptographicHash>
#include <QByteArray>
#include <QDebug>

#include "chancedata.h"

// Constants
const QStringList  NUMBERS = {"0","1","2","3","4","5","6","7","8","9"};

const QStringList CHARS_LOWER = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
const QStringList CHARS_UPPER = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
const QStringList CHARS = CHARS_LOWER + CHARS_UPPER;

const QStringList HEX_POOL  = NUMBERS + QStringList{"a","b","c","d","e","f"};
const QStringList HEX_POOL_UPPER  = NUMBERS + QStringList{"A","B","C","D","E","F"};

const QStringList CHARS_SYMBOLS = {"!","@","#","$","%","^","&","*","(",")","[","]"};
const QStringList CHARS_ALL = CHARS_LOWER + CHARS_UPPER + CHARS_SYMBOLS;
const QStringList PUNCTUATIONS = {".","?",";","!",":"};

class Chance
{
    ChanceData chanceData;

public:
    Chance();

    // -- Basics --

    bool boolean (int likelihood = 50) {  // likelihood of success (true)

        if( likelihood < 0 || likelihood > 100) qCritical() << "Chance: likelihood accepts values from 0 to 100.";
        return random() * 100 < likelihood;
    }

    QString lowerCharacter () {
        return character(CHARS_LOWER);
    }

    QString upperCharacter () {
        return character(CHARS_UPPER);
    }

    QString symbolCharacter () {
        return character(CHARS_SYMBOLS);
    }

    QString anyCharacter () {
        return character(CHARS);
    }

    QString character (QStringList pool = CHARS_ALL) {
        return pool.at(natural(INT_MIN, pool.length() - 1) );
    }

    double doubleNumber (double min, double max, int precision = 4.0) {

        double num;
        double fixed = qPow(10, precision);

        double max_ = RAND_MAX / fixed;
        double min_ = -max;

        if(min < min_) qCritical () << "Chance: Min specified is out of range with fixed. Min should be, at least, " << min_;
        if(max > max_) qCritical () << "Chance: Max specified is out of range with fixed. Max should be, at most, " << max_;

        num = integer(min * fixed, max * fixed);
        return (num / fixed);
    }

    int integer (int min = INT_MIN, int max = INT_MAX) {

        if(min > max) qCritical() << "Chance: Min cannot be greater than Max.";

        return qFloor(random() * (max - min + 1) + min);
    }

    int natural (int min = 0, int max = INT_MAX) {

        if(min < 0) qCritical() << "Chance: Min cannot be less than zero.";
        return integer(min, max);
    }

    QString string (int len = -1, QStringList pool = CHARS_ALL) {

        if(len == -1) len = natural(5,20);

        if(len < 0) qCritical() << "Chance: Length cannot be less than zero.";

        QStringList text = n<QString>([&](){return pool[natural(1, pool.length())];}, len);

        return text.join("");
    }

    // -- End Basics --

    // -- Helpers --

    QString capitalize (QString word) {
        return word.at(0).toUpper() + word.right(1);
    }

    template<typename T, typename F>
    QList<T> unique (F&& lambda, int len) {

        auto comparator =  [](QList<T> &lst, T &value) { return lst.contains(value); };

        QList<T> lst; int count = 0; T result; int MAX_DUPLICATES = len * 50;

        while (lst.length() < len) {
            result = lambda();
            if (!comparator(lst, result)) {
                lst.append(result);
                // reset count when unique found
                count = 0;
            }

            if (++count > MAX_DUPLICATES) {
                qCritical() << "Chance: num is likely too large for sample set";
                return lst;
            }
        }

        return lst;
    }

    template <typename T, typename F>
    QList<T> n (F&& lambda, unsigned int len = 1) {

        QList<T> lst;

        if(len < 1) len = 1;
        for (int i =  0; i < len; i++) {
            lst.append(lambda());
        }
        return lst;
    }

    // H/T to SO for this one: http://vq.io/OtUrZ5
    QString pad (int number, int width = 5, QChar pad = '0') {

        QString str = QString::number(number);
        return str.length() >= width ? str : str.prepend( QString( width - str.length() + 1, pad));
    }

    // Given an array, returns a single random element
    template <typename T>
    T  pickone (QList<T> lst) {

        if (lst.length() == 0) {
            qCritical() << "Chance: Cannot pickone() from an empty string list";
            return T();
        }

        return lst[natural(0, lst.length() -1)];
    }

    // Given an array, returns a random set with "count" elements
    template <typename T>
    T pickset (QList<T> lst, int count) {

        if (count == 0) QList<T>();

        if (lst.length() == 0) {
            qCritical() << "Chance: Cannot pickset() from an empty string list";
            return  QList<T>();
        }

        if (count < 0) {
            qCritical() << "Chance: count must be positive number";
            return  QList<T>();
        }

        if (count == 1) return pickone(lst);
        else return shuffle(lst).mid(0, count);
    }

    template <typename T>
    QList<T>  shuffle (QList<T> lst) {

        QList<T>  oldlst = lst, newlst;
        int j = 0, length = oldlst.length();

        for (int i = 0; i < length; i++) {
            // Pick a random index from the list
            j = natural(0 , oldlst.length() - 1);
            // Add it to the new list
            newlst[i] = oldlst[j];
            // Remove that element from the original list
            oldlst.removeAt(j);
        }
        return newlst;
    }

    // Returns a single item from an array with relative weighting of odds
    template <typename T>
    T weighted (QList<T> lst, QList<int> weights, bool trim = false) {

        if (lst.length() != weights.length()) {
            qCritical() << "Chance: length of array and weights must match";
            return QList<T>();
        }

        // scan weights array and sum valid entries
        int sum = 0;
        int val;
        for (int weightIndex = 0; weightIndex < weights.length(); ++weightIndex) {
            val = weights[weightIndex];
            if (val > 0) {
                sum += val;
            }
        }

        if (sum == 0) {
            qCritical() << "Chance: no valid entries in array weights";
            return QList<T>();
        }

        // select a value within range
        int selected = random() * sum;

        // find array entry corresponding to selected value
        int total = 0, lastGoodIdx = -1, chosenIdx;

        for (int weightIndex = 0; weightIndex < weights.length(); ++weightIndex) {
            val = weights[weightIndex];
            total += val;
            if (val > 0) {
                if (selected <= total) {
                    chosenIdx = weightIndex;
                    break;
                }
                lastGoodIdx = weightIndex;
            }

            // handle any possible rounding error comparison to ensure something is picked
            if (weightIndex == (weights.length() - 1)) {
                chosenIdx = lastGoodIdx;
            }
        }

        T chosen = lst[chosenIdx];
        if (trim) {
            lst.removeAt(chosenIdx);
            weights.removeAt(chosenIdx);
        }

        return chosen;
    }

    // -- End Helpers --

    // -- Text --

    QString paragraph (int len = -1) {

        if(len == -1) len = natural(3,7);

        QStringList sentences = n<QString>([this](){return sentence();}, len);

        return sentences.join(" ");
    }

    // Could get smarter about this than generating random words and
    // chaining them together. Such as: http://vq.io/1a5ceOh
    QString sentence (int num_words = -1, QString punctuation = "") {

        if(num_words == -1) num_words = natural(12,18);

        QStringList wordslst = n<QString>( [this](){return word();}, num_words);
        QString text = wordslst.join(" ");

        // Capitalize first letter of sentence
        text = capitalize(text);

        // Make sure punctuation has a usable value
        if(punctuation.isEmpty() || !PUNCTUATIONS.contains(punctuation))  {
            punctuation = ".";
        }

        // Add punctuation mark
        if (!punctuation.isEmpty()) {
            text += punctuation;
        }

        return text;
    }

    QString syllable (int len = -1, bool capital = false) {

        if(len == -1) len = natural(2,3);

        const QStringList consonants = {"b","c","d","f","g","h","j","k","l","m","n","p","r","s","t","v","w","z"}; // consonants except hard to speak ones
        const QStringList vowels = {"a","e","i","o","u"}; // vowels
        const QStringList all = consonants + vowels; // all
        QString text, chr;

        // I"m sure there"s a more elegant way to do this, but this works
        // decently well.
        for (int i = 0; i < len; i++) {
            if (i == 0) {
                // First character can be anything
                chr = character(all);
            } else if (!consonants.contains(chr)) {
                // Last character was a vowel, now we want a consonant
                chr = character(consonants);
            } else {
                // Last character was a consonant, now we want a vowel
                chr = character(vowels);
            }

            text += chr;
        }

        if (capital) {
            text = capitalize(text);
        }

        return text;
    }

    QString word (int len = -1, int syllables = -1, bool capital = false) {

        if(len==-1) len = natural(4,7);
        if(syllables==-1) syllables = natural(1,3);

        QString text;

        do {
            text += syllable();
        } while (text.length() < len);

        // remove any extra characters
        text = text.left(len);

        if (capital) {
            text = capitalize(text);
        }

        return text;
    }

    // -- End Text --

    // -- Person --

    enum AgeRange { AgeRange_Child, AgeRange_Teen, AgeRange_Adult, AgeRange_Senior, AgeRange_All, AgeRange_Any};

    int age (AgeRange range = AgeRange_Any) {

        switch (range) {
        case AgeRange_Child:
            return natural(1,12);
            break;
        case AgeRange_Teen:
            return natural(13,19);
            break;
        case AgeRange_Adult:
            return natural(18,65);
            break;
        case AgeRange_Senior:
            return natural(65,100);
            break;
        case AgeRange_All:
            return natural(1,100);
            break;
        default:
            return natural(18,65);
            break;
        }
    }

    QString birthday (AgeRange range = AgeRange_Any, QString format = "dd/MM/yyyy") {

        int age_ = age(range);
        int currentYear = QDate::currentDate().year();

        return date(-1,-1,-1,-1, currentYear - age_).toString(format);
    }

    QString first (bool female) {

        if(female) return pickone( chanceData.firstNames_female);
        else return pickone( chanceData.firstNames_male);
    }

    QString gender () {
        return pickone(QStringList{"Male", "Female"});
    }

    QString last () {
        return pickone(chanceData.lastNames);
    }

    QString name (bool middle = false, bool prefix_ = false, bool suffix_ = false, bool female = false) {

        QString first_ = first(female), last_ = last(), name_;

        if (middle) {
            name_ = first_ + " " + first_ + " " + last_;
//        } else if (middle_initial) {
//            name_ = first_ + " " + upperCharacter() + " " + last_;
        } else {
            name_ = first_ + " " + last_;
        }

        if (prefix_) name_ = prefix(female) + " " + name_;

        if (suffix_) name_ = name_ + " " + suffix(false);

        return name_;
    }

    // Return the list of available name prefixes based on supplied gender.
    // @todo introduce internationalization
    QStringList name_prefixes (bool female = false, bool full = false) {

        QStringList prefixes;

        full? prefixes << "Doctor" : prefixes << "Dr.";

        if (!female) {
            full? prefixes << "Mister" : prefixes << "Mr.";
        }
        else{
            full? prefixes << "Miss" : prefixes << "Miss.";
            full? prefixes << "Misses" : prefixes << "Mrs.";
        }

        return prefixes;
    }

    // Alias for name_prefix
    QString prefix (bool female = false) {
        return name_prefix(female);
    }

    QString name_prefix (bool female = false, bool full = false) {

        return pickone(name_prefixes(female, full));
    }

    //Hungarian ID number
    QString HIDN (){

        //Hungarian ID nuber structure: XXXXXXYY (X=number,Y=Capital Latin letter)
        const QStringList idn_pool= {"0","1","2","3","4","5","6","7","8","9"};
        const QStringList idn_chrs= {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","X","Z"};

        QString idn= "";

        idn+= string(6, idn_pool);
        idn+= string(2, idn_chrs);

        return idn;
    }

    QString ssn (bool lastFour = false, bool noDash = false) {

        QStringList ssn_pool = {"1","2","3","4","5","6","7","8","9","0"};
        QString dash = noDash ? "-" : "";

        if(!lastFour)
            return string(4, ssn_pool);

        else {
            return string(3, ssn_pool) + dash + string(2, ssn_pool) + dash + string(4, ssn_pool);
        }
    }

    // Alias for name_suffix
    QString suffix (bool full = false) {
        return name_suffix(full);
    }

    QString name_suffix (bool full = false) {

        ChanceData::Suffix s = pickone( chanceData.suffixes);

        if(full) return s.suffix;
        else return s.abbr;
    }

    // Generate random nationality based on json list
    QString nationality () {
        return pickone(chanceData.nationalities);
    }

    // -- End Person --

    // -- Mobile --
    // Android GCM Registration ID
    QString android_id () {
        QStringList lst = {"0","1","2","3","4","5","6","7","8","9","a","b","c","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","-","_"};
        return "APA91" + string(178, lst);
    }

    // Apple Push Token
    QString apple_token () {
        return string(64, {"a","b","c","d","e","f","1","2","3","4","5","6","7","8","9","0"});
    }

    // Windows Phone 8 ANID2
    QString wp8_anid2 () {
        return QByteArray().append(hash(32)).toBase64();
    }

    // Windows Phone 7 ANID
    QString wp7_anid () {
        return "A=" + guid().replace("-", "").toUpper() + "&E=" + hash(3) + "&W=" + QString::number( integer(0,9) );
    }

    // BlackBerry Device PIN
    QString bb_pin () {
        return hash(8);
    }

    // -- End Mobile --

    // -- Web --
    QString avatar (QString protocol = "", QString fileExtension = "", QString email_ = "", QString fallback = "", QString rating = "", int size = -1) {

        // Set to a random email
        if(email_.isEmpty()) email_ = email();

        QString url, URL_BASE = "//www.gravatar.com/avatar/";
        QStringList PROTOCOLS = {"http","https"};
        QStringList FILE_TYPES = {"bmp","gif","jpg","png"};
        QStringList FALLBACKS = {
            "404", /* Return 404 if not found */
            "mm", /*  Mystery man */
            "identicon", /*  Geometric pattern based on hash */
            "monsterid", /*  A generated monster icon */
            "wavatar", /*  A generated face */
            "retro", /*  8-bit icon */
            "blank" /*  A transparent png */
        };
        QStringList RATINGS = { "g", "pg", "r", "x"};

        // Safe checking for params
        protocol = PROTOCOLS.contains(protocol)? protocol + ":" : "";
        rating = RATINGS.contains(rating)? rating : "";
        fallback = FALLBACKS.contains(fallback) ? fallback : "";
        fileExtension = FILE_TYPES.contains(fileExtension) ? fileExtension : "";

        url =   protocol + URL_BASE + md5(email_);

        if(!fileExtension.isEmpty()) url.append( "." + fileExtension);
        if(size != -1 || !rating.isEmpty() || !fallback.isEmpty()) url.append("?");
        if(size != -1) url.append("&s=" + QString::number(size));
        if(!rating.isEmpty()) url.append( "&r=" + rating );
        if(!fallback.isEmpty()) url.append("&d=" + fallback);

        return url;
    }

    QString color (QString format = "", bool grayscale = false, bool upper = false) {

        auto _gray = [] (QString value, QString delimiter = "") {
            return QStringList {value, value, value}.join(delimiter);
        };

        auto _rgb = [&](bool hasAlpha) {

            QString rgbValue    = hasAlpha ? "rgba" : "rgb";
            QString alphaChanal = hasAlpha ? "," + QString::number( doubleNumber(0,1)) : "";
            QString colorValue  = grayscale ? _gray(QString::number(natural(0, 255)), ",") : QString::number(natural(0,255)) + "," + QString::number(natural(0,255)) + "," + QString::number(natural(0,255));

            return rgbValue + "(" + colorValue + alphaChanal + ")";
        };

        auto _hex = [&](int start, int end, bool withHash = false) {

            QString simbol = withHash ? "#" : "";
            QString expression  = grayscale ? _gray(hash(start)) : hash(end);
            return simbol + expression;
        };

        QStringList formats = {"hex", "shorthex", "rgb", "rgba", "0x", "name"};

        if(format.isEmpty() || !formats.contains(format)) format = pickone(formats);

        QString colorValue;

        if (format == "hex") {
            colorValue =  _hex(2, 6, true);
        }
        else if (format == "shorthex") {
            colorValue = _hex(1, 3, true);
        }
        else if (format == "rgb") {
            colorValue = _rgb(false);
        }
        else if (format == "rgba") {
            colorValue = _rgb(true);
        }
        else if (format == "0x") {
            colorValue = "0x" + _hex(2, 6);
        }
        else if(format == "name") {
            return pickone(chanceData.colorNames);
        }

        if (upper) {
            colorValue = colorValue.toUpper();
        }

        return colorValue;
    }

    QString domain (QString tld_ = "") {

        if(tld_.isEmpty()) tld_ = tld();
        return word() + "." + tld_;
    }

    QString email (QString domain_ = "", int len = -1) {

        if(domain_.isEmpty()) domain_ = domain();
        if(len == -1) len = natural(5,15);

        return word(len) + "@" + domain_;
    }

    QString fbid () {
        return QString::number(natural(0, 100000000000)).prepend("10000");
    }

    QString google_analytics () {
        QString account = pad(natural(-1, 999999), 6);
        QString property = pad(natural(-1, 99), 2);

        return "UA-" + account + "-" + property;
    }

    QString hashtag () {
        return "#" + word();
    }

    QString ip () {
        // Todo: This could return some reserved IPs. See http://vq.io/137dgYy
        // this should probably be updated to account for that rare as it may be
        return  QString::number( natural(1, 254)) + "." +
                QString::number( natural(0, 255)) + "." +
                QString::number( natural(0, 255)) + "." +
                QString::number( natural(1, 254));
    }

    QString ipv6 () {

        QStringList ip_addr = n<QString>([this](){return hash(8);}, 4);

        return ip_addr.join(":");
    }

    QString klout () {
        return QString::number( natural(1, 99) );
    }

    QString tld () {
        return pickone(chanceData.tlds);
    }

    QString twitter () {
        return "@" + word();
    }

    QString url (QString protocol = "http", QString domain_ = "", QString domain_prefix = "", QString path = "", QStringList  extensions = {}){

        domain_ = domain(domain_);

        QString extension;

        if(protocol.isEmpty()) protocol = "http";
        if(path.isEmpty()) path = word();
        if(!extensions.isEmpty()) extension =  "." + pickone(extensions);
        if(!domain_prefix.isEmpty()) domain_ = domain_prefix + "." + domain_;

        return protocol + "://" + domain_ + "/" + path + extension;
    }

    QString port (){
        return QString::number( integer(0, 65535) );
    }

    // -- End Web --

    // -- Location --

    QString address (bool short_suffix = false) {
        return natural(5, 2000) + " " + street(short_suffix);
    }

    QString areacode (bool parens = false) {

        // Don"t want area codes to start with 1, or have a 9 as the second digit
        QString area_code =
                QString::number(natural(2,9)) +
                QString::number(natural(0,8)) +
                QString::number(natural(0,9));

        return parens ? "(" + area_code + ")" : area_code;
    }

    QString city () {
        return capitalize(word(3, 10));
    }

    QString country (bool full = false) {
        ChanceData::Country c = pickone(chanceData.countries);
        return full ? c.name : c.abbreviation;
    }

    double depth (int min = -10994, int max = 0, int fixed = 5) {

        return doubleNumber(min, max, fixed);
    }

    QString geohash (int len = 7) {
        return string(len, {"0","1","2","3","4","5","6","7","8","9","b","c","d","e","f","g","h","j","k","m","n","p","q","r","s","t","u","v","w","x","y","z"});
    }

    QString geojson (int min = -90, int max = 90, int fixed = 5) {

        return QString::number( latitude(min, max, fixed) ).append(", ")
                .append(QString::number( longitude(min, max, fixed))).append(", ")
                .append(QString::number( altitude(min, max, fixed)));
    }

    double altitude (int fixed = 5, int min = 5, int max = 8848) {

        return doubleNumber(min, max, fixed);
    }

    double latitude (int fixed = 5, int min = -90, int max = 90 ) {
        return doubleNumber(min, max, fixed);
    }

    double longitude (int fixed = 5, int min = -180, int max = 180) {
        return doubleNumber(min, max, fixed);
    }

    QString coordinates (int fixed = 5) {
        return QString::number( latitude(fixed) ) + ", " + QString::number( longitude(fixed) );
    }

    /////////**********************************************************
    ///
    /// ///////////////

    QString postal () {
        // Postal District
        QString pd = character( {"X","V","T","S","R","P","N","K","L","M","H","J","G","E","C","B","A"} );
        // Forward Sortation Area (FSA)
        QString fsa = pd + natural(-1, 9) + upperCharacter();
        // Local Delivery Unut (LDU)
        QString ldu = natural(-1,9) + upperCharacter() + natural(-1, 9);

        return fsa + " " + ldu;
    }

    QString county () {
        return pickone(chanceData.counties);
    }

    QString province (bool full = true) {

        ChanceData::Province pro = pickone(chanceData.provinces);

        if(full) return pro.name;
        else return pro.abbreviation;
    }

    QString state (bool full = true) {

        ChanceData::State st = pickone(chanceData.states);
        if(full) return st.name;
        else return st.abbreviation;
    }


    QString street (bool short_suffix = false, int syllables = 2) {

        QString street =  word(-1, syllables);

        street = capitalize(street) + " ";
        street += street_suffix(short_suffix);

        return street;
    }

    QString street_suffix (bool short_suffix = false) {

        ChanceData::StreetSuffix ss = pickone(chanceData.street_suffixes);
        if(short_suffix) return ss.abbreviation;
        else return ss.name;
    }

    // Note: only returning US zip codes, internationalization will be a whole
    // other beast to tackle at some point.
    QString zip (bool plusfour = false) {

        QStringList zip = n<QString>([this](){ return QString::number(natural(0,9));}, 5);

        if (plusfour) {
            zip.append("-");
            zip.append(n<QString>([this](){ return QString::number(natural(0,9));}, 4));
        }

        return zip.join("");
    }

    // -- End Location --

    // -- Time

    QString ampm () {
        return boolean() ? "am" : "pm";
    }

    int day(unsigned int min = 1, unsigned int max = 31){

        if(min > max) qCritical () <<  "Chance: Min cannot be greater than Max.";
        return integer(min, max);
    }

    QString dayString(unsigned int min = 1, unsigned int max = 31){

        return QString::number( day(min, max) );
    }


    long hammertime () {
        return QDateTime( date() ).toMSecsSinceEpoch();
    }

    int hour (unsigned int min = 0, unsigned int max = 23, bool twentyfour = true) {

        if( twentyfour && max > 23) qCritical() << "Chance: Max cannot be greater than 23 for twentyfour option.";
        if(!twentyfour && max > 12) qCritical() << "Chance: Max cannot be greater than 12.";
        if(min > max) qCritical () <<  "Chance: Min cannot be greater than Max.";

        return natural(min, max);
    }

    int millisecond () {
        return natural(0, 999);
    }

    int second (unsigned int min = 0, unsigned int max = 59) {

        if( max > 59) qCritical() << "Chance: Max cannot be greater than 59.";
        if(min > max) qCritical () <<  "Chance: Min cannot be greater than Max.";

        return natural(min, max);
    }

    int minute (unsigned int min = 0, unsigned int max = 59){
        return second(min, max);
    }

    QString weekday (bool weekday_only = false) {

        QStringList weekdays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
        if (!weekday_only) {
            weekdays.append("Saturday");
            weekdays.append("Sunday");
        }

        return pickone(weekdays);
    }

    int month (unsigned int min = 1, unsigned int max = 12) {

        if(min < 1) qCritical() << "Chance: Min cannot be less than 1.";
        if(max > 12) qCritical() << "Chance: Max cannot be greater than 12.";
        if(min > max) qCritical() << "Chance: Min cannot be greater than Max.";

        ChanceData::Month month = pickone(chanceData.months);
        return month.numeric.toInt();
    }

    QString monthName (unsigned int min = 1, unsigned int max = 12) {

        if(min < 1) qCritical() << "Chance: Min cannot be less than 1.";
        if(max > 12) qCritical() << "Chance: Max cannot be greater than 12.";
        if(min > max) qCritical() << "Chance: Min cannot be greater than Max.";

        ChanceData::Month month = pickone(chanceData.months);
        return month.name;
    }

    int year (int min = -1, int max = -1) {
        // Default to current year as min if none specified
        if(min == -1) min = QDate::currentDate().year();
        // Default to one century after current year as max if none specified
        if(max == -1) max = min  + 100;

        return natural(min,max);
    }

    QString yearString (unsigned int min = -1, unsigned int max = -1) {

        return QString::number( year(min,max) );
    }

    int timestamp () {
        return natural(1, QDateTime::currentDateTime().currentMSecsSinceEpoch() / 1000);
    }

    // max: 100,000,000 days measured relative to midnight at the beginning of 01 January, 1970 UTC. http://es5.github.io/#x15.9.1.1
    QDate date (int min = 1, long max = 8640000000000000, int day_ = -1, int month_ = -1, int year_ = -1) {

        // if min or max was specified use it
        if(min != -1 || max != -1)
            return QDateTime::fromMSecsSinceEpoch(natural(min, max)).date();
        else {

            if(day_ == -1) day_ = day();
            if(month_ == -1) month_ = month();
            if(year_ == -1) year_ = year();

            return QDate(year_, month_, day_);
        }
    }

    // -- End Time

    // -- Finance --


    QString cc (ChanceData::CCTypes type = ChanceData::AnyCard) {

        ChanceData::CreditCard card = cc_type(type);

        QStringList number = card.prefix.split("");
        int to_generate = card.length - card.prefix.length() - 1;

        // Generates n - 1 digits
        number.append(  n<QString>([this](){return QString::number( integer(0,9) );}, to_generate) );

        // Generates the last digit according to Luhn algorithm
        number.append( QString::number( luhn_calculate(number.join(""))));

        return number.join("");
    }

    ChanceData::CreditCard cc_type (ChanceData::CCTypes type = ChanceData::AnyCard) {

        if( type == ChanceData::AnyCard)
            return pickone(chanceData.cc_types);
        else {

            for(ChanceData::CreditCard c : chanceData.cc_types){
                if(c._type == type) return c;
            }
        }
    }

    QString cc_typeString (ChanceData::CCTypes type = ChanceData::AnyCard) {

        ChanceData::CreditCard card = cc_type(type);
        return card.type;
    }

    //return random world currency by ISO 4217
    QString currency () {
        return pickone(chanceData.currency_types).code;
    }

    //return random timezone
    QString timezone () {
        return pickone(chanceData.timezones).name;
    }

    //Return random correct currency exchange pair (e.g. EUR/USD) or array of currency code
    QString currency_pair () {

        QList<QString> currencies = unique<QString>([this](){return currency();}, 2 );
        return currencies.join("/");
    }

    QString dollar (double min = 0.0, double max = 10000.0) {

        double dollar = qAbs(doubleNumber(min, max, 2));

        QString dollar_string = QString::number(dollar);

        QStringList l = dollar_string.split(".");

        if(l.size() == 1) // if no cents
            dollar_string += ".00";
        return dollar_string.prepend("$");
    }

    QString euro (double min = 0.0, double max = 10000.0) {
        return dollar(min, max).replace("$", "").append("€");
    }

    QString exp () {

        int year = exp_year(), month;

        // If the year is this year, need to ensure month is greater than the
        // current month or this expiration will not be valid
        if (year == QDate::currentDate().year()) {
            month = exp_month();
        } else {
            month = exp_month(false);
        }

        return QString::number(month) + "/" + QString::number(year);
    }

    int exp_month (bool future = true) {

        int month_, current_month = QDate::currentDate().month();

        if (future && (current_month != 12)) {
            do {
                month_ = month();
            } while (month_ <= current_month);
        }
        else {
            month_ = month();
        }

        return month_;
    }

    int exp_year () {

        int current_month = QDate::currentDate().month(), current_year = QDate::currentDate().year();

        if(current_month == 12) current_year += 1;
        return year(current_year, current_year + 10);
    }

    // -- End Finance

    // -- Regional


    // -- End Regional

    // -- Miscellaneous --

    // Dice - For all the board game geeks out there, myself included ;)
    int diceFn (int min, int max) {
        return natural(min, max);
    }

    int d4() {return diceFn(1, 4);}
    int d6() {return  diceFn(1,6);}
    int d8() {return  diceFn(1, 8);}
    int d10() {return  diceFn(1, 10);}
    int d12() {return  diceFn(1, 12);}
    int d20() {return  diceFn(1, 20);}
    int d30() {return  diceFn(1, 30);}
    int d100() {return  diceFn(1,100);}

    // Guid
    QString guid () {
        return QUuid::createUuid().toString();
    }

    // Hash
    QString hash (int len = 40, bool upper = false) {

        QStringList pool = upper? HEX_POOL_UPPER : HEX_POOL;
        return string(len, pool);
    }

    bool luhn_check (QString num) {
        int checkDigit = num.right(1).toInt();
        return checkDigit == luhn_calculate( num.left(num.length() - 1));
    }

    //https://github.com/gil9red/LuhnAlgorithm/blob/master/luhnalgorithm.cpp
    int luhn_calculate (QString num) {

        QString numberCard = num.remove( " " );
        QVector < qint16 > array;
        const qint32 length = numberCard.length();

        for( qint32 i = 0; i < length; i++ )
        {
            qint16 digit = numberCard.at(i).digitValue();
            if ( i % 2 == 0 )
            {
                digit *= 2;
                digit = (digit > 9 ? digit - 9 : digit);
            }
            array << digit;
        }

        int sum = 0;
        foreach ( qint16 n, array )
            sum += n;

        return (sum * 9) % 10;
    }

    // MD5 Hash
    QString md5 (QString str) {

        if(str.isEmpty()) str = string();

        return QCryptographicHash::hash(QByteArray().append(str), QCryptographicHash::Md5).toHex();
    }

    QString file (int length = -1, QStringList extentions = QStringList()) {

        if(length == -1) length = natural(5,25);

        // Generate random file name
        QString fileName = word(length);

        // Generate file by specific extention provided by the user
        if(extentions.length() == 1) {
            return fileName + "." + extentions.at(0);
        }

        // Generate file by specific extention collection
        QString fileExtention = pickone(extentions);
        return fileName + "." + fileExtention;
    }

    QString file_raster (int length = -1, QString extension = "") {
        return file(length, QStringList(extension));
    }

    QString file_raster (int length = -1) {
        return file(length, chanceData.fileExtension_raster);
    }

    QString file_3d (int length = -1) {
        return file(length, chanceData.fileExtension_3d);
    }

    QString file_document (int length = -1) {
        return file(length, chanceData.fileExtension_document);
    }

    QString file_vector (int length = -1) {
        return file(length, chanceData.fileExtension_vector);
    }

    // Mac Address
    QString mac_address (QString separator = ":", bool networkVersion = false){
        // typically mac addresses are separated by ":"
        // however they can also be separated by "-"
        // the network variant uses a dot every fourth byte

        if(networkVersion) separator = ".";

        QStringList mac_pool= {"A","B","C","D","E","F","1","2","3","4","5","6","7","8","9","0"};
        QString mac;

        if(!networkVersion)
            mac = n<QString>([&](){return string(2, mac_pool);}, 6).join(separator);
        else
            mac = n<QString>([&](){return string(4, mac_pool);},3).join(separator);

        return mac;
    }

    enum RadioSides
    {
        WEST, EAST, ANY
    };

    QString radio (RadioSides side = ANY) {

        // Initial Letter (Typically Designated by Side of Mississippi River)

        QString fl = "";

        switch (side) {
            case EAST:
                fl = "W";
                break;
            case WEST:
                fl = "K";
                break;
            default:
                fl = character({"K","W"});
                break;
        }

        return fl + upperCharacter() + upperCharacter() + upperCharacter();
    }

    QString tv (RadioSides side = ANY) {
        return radio(side);
    }

    // -- End Miscellaneous --
};

#endif // CHANCE_H
