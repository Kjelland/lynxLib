#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QFile>

struct TextHandlerLight
{
    QString text = "";
    bool valid = false;
};

struct TextHandlerType : public TextHandlerLight
{
    QString type = "";
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
    Q_PROPERTY(bool openFileDialog READ openFileDialog WRITE setOpenFileDialog NOTIFY openFileDialogChanged)

    QString _outputText = "";

    bool _openFileDialog = false;
    QString _filePath = "";

    TextHandlerLight _structName;
    TextHandlerLight _structId;
    QList<TextHandlerType> _memberInfo;

public:

    explicit BackEnd(QObject *parent = nullptr);

    bool buttonWrite();
    QString outputText();

    bool openFileDialog() { return _openFileDialog; }

signals:
    void outputTextChanged();
    void openFileDialogChanged();

public slots:
    void buttonSaveClicked();
    void buttonBrowseClicked();
    void setOpenFileDialog(bool input) { _openFileDialog = input; }
    void pathSelected(QString path);

    void setOutputText(QString input);
    void setStructName(QString name, bool valid);
    void setStructId(QString name, bool valid);
    void setMemberName(QString name, bool valid, int index);
    void setMemberType(QString name, int index);

    void removeMember(int index);
    void moveMember(int fromIndex, int toIndex);

};

#endif // BACKEND_H
