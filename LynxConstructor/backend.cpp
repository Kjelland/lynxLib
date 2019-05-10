#include "backend.h"

TextHandler::TextHandler(QObject *parent) : QObject(parent)
{

}

void TextHandler::setText(QString input)
{
    if(input == _text)
        return;

    while(input.count() > 20)
    {
        input.chop(1);
    }

    _text = input;
    _valid = this->checkName();

    if(_valid)
    {
        this->setColor("blue");
    }
    else
    {
        this->setColor("red");
    }

    emit textChanged();
}

void TextHandler::setColor(QString input)
{
    if(input == _color)
        return;

    _color = input;
    emit colorChanged();
}

void TextHandler::setValidCondition(ValidCondition condition)
{
    _validCondition = condition;
}

void TextHandler::setIndex(int index)
{
    if(index == _index)
        return;

    _index = index;
    emit indexChanged();
}

bool TextHandler::valid()
{
    return _valid;
}

QString TextHandler::text()
{
    return _text;
}

QString TextHandler::color()
{
    return _color;
}

int TextHandler::index()
{
    return _index;
}

bool TextHandler::checkName()
{
    switch(_validCondition)
    {
    case E_Name:
        return this->validateName();
    case E_Number:
        return this->validateNumber();
    }

    return false;
}

bool TextHandler::validateName()
{
    if(_text.count() < 1)
        return false;

    QChar temp = _text.at(0);

    if(!(temp == '_'))
    {
        if((temp < 'A') || (temp > 'z'))
            return false;

        if((temp < 'a') && (temp > 'Z'))
            return false;
    }


    for (int i = 1; i < _text.count(); i++)
    {
        temp = _text.at(i);

        if(!(temp == '_'))
        {
            if((temp < '0') || (temp > 'z'))
                return false;
            else if((temp > '9') && (temp < 'a'))
            {
                if((temp < 'A') || (temp > 'Z'))
                    return false;
            }
        }
    }

    return true;
}

bool TextHandler::validateNumber()
{
    if(_text.count() < 1)
        return false;

    for (int i = 0; i < _text.count(); i++)
    {
        if(!_text.at(i).isNumber())
            return false;
    }

    float temp = _text.toFloat();

    if(temp > 254)
        this->setText("254");
    else if(temp < 1)
        this->setText("1");

    return true;
}

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
    this->pathSelected("../testFolder");
}

void BackEnd::buttonSaveClicked()
{
    if(!_structName.valid) //!_className.valid())
    {
        setOutputText("Invalid name");
        return;
    }

    if(!_structId.valid) //!_structId.valid())
    {
        setOutputText("Invalid struct ID");
        return;
    }

    for (int i = 0; i < _memberInfo.count(); i++)
    {
        if(!_memberInfo.at(i).valid)
        {
            setOutputText("One or more members are invalid");
            return;
        }
    }

    QString fullPath = _filePath + "/" + _structName.text.toLower() + "struct" + ".h";
    QFile file(fullPath);

    if(file.exists())
        file.remove();

    if(file.open(QIODevice::WriteOnly))
    {
        //-------------- define -----------------
        QString temp = "#ifndef " + _structName.text.toUpper() + "_STRUCT" + "\r\n#define " + _structName.text.toUpper() + "_STRUCT" + " " + _structId.text + "\r\n\r\n";
        file.write(temp.toLatin1());

        //------------- include -----------------
        temp = "#include \"LynxStructure.h\"\r\n\r\n";
        file.write(temp.toLatin1());

        //--------------- using -----------------
        temp = "using namespace LynxLib;\r\n\r\n";
        file.write(temp.toLatin1());

        //--------------- enum ------------------
        temp = "enum E_" + _structName.text + "Contents\r\n{\r\n";
        file.write(temp.toLatin1());

        for (int i = 0; i < _memberInfo.count(); i++)
        {
            temp = "\t" +_memberInfo.at(i).text + ",\r\n";
            file.write(temp.toLatin1());
        }

        temp = "\t" + _structName.text + "Contents_EndOfList\r\n};\r\n\r\n";
        file.write(temp.toLatin1());

        //----------- structItems --------------
        temp = "static const StructItem " + _structName.text + "Items[]\r\n{\r\n";
        file.write(temp.toLatin1());

        for (int i = 0; i < _memberInfo.count(); i++)
        {
            temp = "\t{ \"" + _memberInfo.at(i).text + "\", e" + _memberInfo.at(i).type + " },\r\n";
            file.write(temp.toLatin1());
        }

        temp = "\t{ \"\", eEndOfList };\r\n}\r\n\r\n";
        file.write(temp.toLatin1());

        //---------- structDefinition -----------
        temp = "static const StructDefinition " + _structName.text + "Definition\r\n";
        file.write(temp.toLatin1());

        temp = "\t\"" + _structName.text + " Struct\",\r\n\teStructureMode,\r\n\t" + _structName.text + "Items\r\n};\r\n\r\n";
        file.write(temp.toLatin1());


        //--------------- end -------------------
        temp = "#endif // " + _structName.text.toUpper() + "_STRUCT";
        file.write(temp.toLatin1());

        file.close();
        setOutputText("File Saved to: " + fullPath);
    }
    else
    {
        setOutputText("Could not open file");
    }
}

void BackEnd::buttonBrowseClicked()
{
    if(_openFileDialog)
    {
        setOutputText("File dialog is already open in a different window");

        return;
    }

    _openFileDialog = true;
    emit openFileDialogChanged();
}

QString BackEnd::outputText()
{
    return _outputText;
}


void BackEnd::pathSelected(QString path)
{
    _filePath = path.remove("file:///");
    setOutputText(_filePath + "/" + _structName.text.toLower() + "struct.h");
}

void BackEnd::setOutputText(QString input)
{
    if(input == _outputText)
        return;

    _outputText = input;
    emit outputTextChanged();
}

void BackEnd::setStructName(QString name, bool valid)
{
    _structName.text = name;
    _structName.valid = valid;
}

void BackEnd::setStructId(QString name, bool valid)
{
    _structId.text = name;
    _structId.valid = valid;
}

void BackEnd::setMemberName(QString name, bool valid, int index)
{
    if(index >= _memberInfo.count())
    {
        TextHandlerType temp;

        while(index >= _memberInfo.count())
        {
            _memberInfo.append(temp);
        }
    }

    _memberInfo[index].text = name;
    _memberInfo[index].valid = valid;
}

void BackEnd::setMemberType(QString type, int index)
{
    if(index >= _memberInfo.count())
    {
        TextHandlerType temp;

        while(index >= _memberInfo.count())
        {
            _memberInfo.append(temp);
        }
    }

    _memberInfo[index].type = type;
}

void BackEnd::removeMember(int index)
{
    _memberInfo.removeAt(index);
}
