#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QFile>
#include <QDebug>

struct TextInfo
{
    QString text = "";
    bool valid = false;
};

struct TextTypeInfo : public TextInfo
{
    QString type = "";
    QString type_t = "";

    TextTypeInfo(){}
    TextTypeInfo(QString _text, QString _type, QString _type_t, bool _valid){ text = _text; type = _type; type_t = _type_t; valid = _valid; }
};

//-----------------------------------------------------------------
//------------------------ StructInfo -----------------------------
//-----------------------------------------------------------------

class StructInfo : public QObject
{
    Q_OBJECT

    TextInfo _structName;
    TextInfo _structId;

    QList<TextTypeInfo> _structMembers;

public:
    explicit StructInfo(QObject* parent = nullptr);

    const TextInfo& structName();
    const TextInfo& structId();
    const TextTypeInfo* structMember(int index);
    int memberCount() { return _structMembers.count(); }

signals:
    // void clearMemberList();

public slots:
    void setStructName(QString text, bool valid);
    void setStructId(QString text, bool valid);
    void addStructMember(QString text, QString type, QString type_t, bool valid);
    void clear() { _structMembers.clear(); }

};

//-----------------------------------------------------------------
//----------------------- TextHandler -----------------------------
//-----------------------------------------------------------------

class TextHandler : public QObject
{
public:
    enum ValidCondition
    {
        E_Name = 0,
        E_Number
    };

    Q_ENUM(ValidCondition)

private:
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString color MEMBER _color NOTIFY colorChanged)
    Q_PROPERTY(QString indexColor MEMBER _indexColor NOTIFY indexColorChanged)
    Q_PROPERTY(bool valid READ valid NOTIFY validChanged)

    bool checkName();

    QString _text = "";
    QString _color = "black";

    QString _indexColor = "grey";

    bool _valid = false;
    ValidCondition _validCondition = E_Name;

    bool validateName();
    bool validateNumber();

public:
    explicit TextHandler(QObject *parent = nullptr);

    QString text();
    bool valid();

    void setColor(QString input);
    void setIndexColor(QString input);

signals:
    void textChanged();
    void colorChanged();
    void indexColorChanged();
    void validChanged();

public slots:
    void setText(QString input);
    void setValidCondition(ValidCondition condition);

};

//-----------------------------------------------------------------
//--------------------------- BackEnd -----------------------------
//-----------------------------------------------------------------

class BackEnd : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString outputText MEMBER _outputText NOTIFY outputTextChanged)
    Q_PROPERTY(bool pathSelected READ pathSelected NOTIFY pathSelectedChanged)

    QString _outputText = "";
    QString _filePath = "";

    enum E_FilePathMode
    {
        eNoPath = 0,
        eFolderPath,
        eFullPath
    }_filePathMode = eNoPath;

public:
    explicit BackEnd(QObject *parent = nullptr);

    void outputText(QString text);

    bool pathSelected();
    void setFilePathMode(E_FilePathMode mode);

signals:
    void outputTextChanged();
    void pathSelectedChanged();

    void pushStructName(QString text);
    void pushStructId(QString text);
    void pushStructMember(QString text, int typeIndex);

public slots:
    void saveStruct(StructInfo* structInfo);
    void savePathSelected(QString path);
    void openPathSelected(QString path);


};

#endif // BACKEND_H
