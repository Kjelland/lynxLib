#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QFile>
#include <QDebug>

struct TextHandlerLight
{
    QString text = "";
    bool valid = false;
};

struct TextHandlerType : public TextHandlerLight
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
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString indexColor READ indexColor WRITE setIndexColor NOTIFY indexColorChanged)

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
    QString color();
    QString indexColor();

signals:
    void textChanged();
    void colorChanged();
    void indexColorChanged();

public slots:
    bool valid();
    void setText(QString input);
    void setColor(QString input);
    void setValidCondition(ValidCondition condition);
    void setIndexColor(QString input);

};

class BackEnd : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString outputText READ outputText WRITE setOutputText NOTIFY outputTextChanged)
    Q_PROPERTY(bool saveFileDialog READ saveFileDialog WRITE setSaveFileDialog NOTIFY saveFileDialogChanged)

    QString _outputText = "";

    bool _saveFileDialog = false;
    QString _filePath = "";

    TextHandlerLight _structName;
    TextHandlerLight _structId;
    QList<TextHandlerType> _memberInfo;

public:

    explicit BackEnd(QObject *parent = nullptr);

    bool buttonWrite();
    QString outputText();

    bool saveFileDialog() { return _saveFileDialog; }

signals:
    void outputTextChanged();
    void saveFileDialogChanged();

    void setStructIdQml(QString text);
    void setStructNameQml(QString text);
    void addStructItemQml(int index, QString text, int typeIndex = 0);
    void setStructItemTypeQml(int index, int typeIndex);
    void resetStructItemList();

public slots:
    void buttonSaveClicked();
    void buttonBrowseClicked();
    void setSaveFileDialog(bool input) { _saveFileDialog = input; }
    void savePathSelected(QString path);

    void openPathSelected(QString path);

    void setOutputText(QString input);
    void setStructName(QString name, bool valid);
    void setStructId(QString name, bool valid);
    void setMemberName(QString name, bool valid, int index);
    void setMemberType(QString name, int index);

    void removeMember(int index);
    void moveMember(int fromIndex, int toIndex);

};

#endif // BACKEND_H
