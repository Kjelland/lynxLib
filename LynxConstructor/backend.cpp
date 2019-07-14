#include "backend.h"

TextHandler::TextHandler(QObject *parent) : QObject(parent)
{

}

const TextTypeInfo* StructInfo::structMember(int index)
{
    if(_structMembers.count() <= index)
        return nullptr;

    return &_structMembers.at(index);
}

void StructInfo::setStructName(QString text, bool valid)
{
    _structName.text = text;
    _structName.valid = valid;
}


void StructInfo::setStructId(QString text, bool valid)
{
    _structId.text = text;
    _structId.valid = valid;
}

void StructInfo::addStructMember(QString text, QString type, QString type_t, bool valid)
{
    _structMembers.append(TextTypeInfo(text, type, type_t, valid));
}


//-----------------------------------------------------------------
//------------------------ TextHandler ----------------------------
//-----------------------------------------------------------------

TextHandler::TextHandler(QObject *parent) : QObject(parent){};

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
        this->setIndexColor("steelblue");
    }
    else
    {
        this->setColor("red");
        this->setIndexColor("tomato");
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

void TextHandler::setIndexColor(QString input)
{
    if(input == _indexColor)
        return;

    _indexColor = input;
    emit indexColorChanged();
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

QString TextHandler::indexColor()
{
    return _indexColor;
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

    bool hexPrefix = _text.startsWith("0x") || _text.startsWith("0X");
    // qDebug() << hexPrefix;

    int temp;

    if(hexPrefix)
    {
        QString hexNum = "";

        for (int i = 2; i < _text.count(); i++)
        {
            hexNum += _text.at(i);
            if(!(_text.at(i).isNumber() || ((_text.at(i) >= 'a') && (_text.at(i) <= 'f')) || ((_text.at(i) >= 'A') && (_text.at(i) <= 'F'))))
                return false;
        }

        // qDebug() << hexNum;

        temp = hexNum.toInt(nullptr, 16);

        if(temp > 254)
            _text = "0xfe";
        else if(temp < 1)
            return false;
    }
    else
    {
        for (int i = 0; i < _text.count(); i++)
        {
            if(!_text.at(i).isNumber())
                return false;
        }

        temp = _text.toInt();

        if(temp > 254)
            _text = "254";
        else if(temp < 1)
            return false;
    }



    return true;
}

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
    this->savePathSelected("../testFolder");
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
        QString STRUCT_NAME = _structName.text.toUpper();
        QString StructName = _structName.text.left(1).toUpper() + _structName.text.right(_structName.text.size() - 1);
        QString structName = _structName.text.left(1).toLower() + _structName.text.right(_structName.text.size() - 1);


        //-------------- define -----------------
        QString temp = "#ifndef " + STRUCT_NAME + "_STRUCT" + "\r\n#define " + STRUCT_NAME + "_STRUCT" + " " + _structId.text + "\r\n\r\n";
        file.write(temp.toLatin1());

        //------------- include -----------------
        temp = "#include \"LynxStructure.h\"\r\n\r\n";
        file.write(temp.toLatin1());

        //--------------- using -----------------
        temp = "using namespace LynxLib;\r\n\r\n";
        file.write(temp.toLatin1());

        //--------------- enum ------------------
        temp = "enum E_" + StructName + "Contents\r\n{\r\n";
        file.write(temp.toLatin1());

        for (int i = 0; i < _memberInfo.count(); i++)
        {
            temp = "\t" +_memberInfo.at(i).text + ",\r\n";
            file.write(temp.toLatin1());
        }

        temp = "\t" + structName + "Contents_EndOfList\r\n};\r\n\r\n";
        file.write(temp.toLatin1());

        //----------- structItems --------------
        temp = "static const StructItem " + structName + "Items[]\r\n{\r\n";
        file.write(temp.toLatin1());

        for (int i = 0; i < _memberInfo.count(); i++)
        {
            temp = "\tStructItem( \"" + _memberInfo.at(i).text + "\", e" + _memberInfo.at(i).type + " ),\r\n";
            file.write(temp.toLatin1());
        }

        temp = "\tStructItem( \"\", eEndOfList )\r\n};\r\n\r\n";
        file.write(temp.toLatin1());

        //---------- structDefinition -----------
        temp = "static const StructDefinition " + structName + "Definition\r\n{\r\n";
        file.write(temp.toLatin1());

        temp = "\t\"" + StructName + " Struct\",\r\n\teStructureMode,\r\n\t" + structName + "Items\r\n};\r\n\r\n";
        file.write(temp.toLatin1());


        //--------------- end -------------------
        temp = "#endif // " + STRUCT_NAME + "_STRUCT";
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
    if(_saveFileDialog)
    {
        setOutputText("File dialog is already open in a different window");

        return;
    }

    _saveFileDialog = true;
    emit saveFileDialogChanged();
}

QString BackEnd::outputText()
{
    return _outputText;
}

    //------------- Wrapper -----------------
    temp = "struct " + StructName +  "Wrapper\r\n{\r\n";
    file.write(temp.toLatin1());

    temp = "\t" + StructName +  "Wrapper() {} \r\n";
    file.write(temp.toLatin1());

    temp = "\t" + StructName +  "Wrapper(LynxHandler* lynxHandler, const LynxID& lynxID) { this->connect(lynxHandler, lynxID); } \r\n\r\n";
    file.write(temp.toLatin1());

    temp = "\tvoid connect(LynxHandler* lynxHandler, const LynxID& lynxID)\r\n\t{\r\n";
    file.write(temp.toLatin1());

    for (int i = 0; i < structInfo->memberCount(); i++)
    {
        temp = "\t\tvar_" + structInfo->structMember(i)->text + ".connect(lynxHandler, lynxID, " + structInfo->structMember(i)->text + ");\r\n";
        file.write(temp.toLatin1());
    }

    temp = "\t}\r\n\r\n";
    file.write(temp.toLatin1());

    for (int i = 0; i < structInfo->memberCount(); i++)
    {
        temp = "\tLynxWrapperElement<" + structInfo->structMember(i)->type_t + "> var_" + structInfo->structMember(i)->text + ";\r\n";
        file.write(temp.toLatin1());
    }

    temp = "};\r\n\r\n";
    file.write(temp.toLatin1());

    //--------------- end -------------------
    temp = "#endif // " + STRUCT_NAME + "_STRUCT";
    file.write(temp.toLatin1());

void BackEnd::savePathSelected(QString path)
{
    _filePath = path.remove("file:///");
    setOutputText(_filePath + "/" + _structName.text.toLower() + "struct.h");
}

void BackEnd::openPathSelected(QString path)
{
    QString fullPath = path.remove("file:///");

    QFile file(fullPath);

    if(!file.exists())
    {
        setOutputText("File: \"" + fullPath + "\" does not exist.");
        return;
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        setOutputText("Could not open file");
        return;
    }

    QString temp = "0";

    int currentIndex = 0;

    enum E_FileReadState
    {
        eStructId = 0,
        eStructName,
        eStructMemberNames,
        eStructMemberTypes,
        eDone,
        eFailure
    }state = eStructId;

    QList<QString> typeList =
    {
        "Int8",
        "Uint8",
        "Int16",
        "Uint16",
        "Int32",
        "Uint32",
        "Int64",
        "Uint64",
        "Float",
        "Double"
    };


    // int currentItem = 0;
    int typeIndex = 0;

    QString structName = "";

    while((temp != "") && (state != eFailure) && (state != eDone))
    {
        temp = file.readLine();

        switch(state)
        {
            case eStructId:
            {
                currentIndex = temp.indexOf("#define");
                if(currentIndex < 0)
                    break;

                QString number = "";
                bool numberReached = false;

                for (int i = currentIndex + int(sizeof("#define")); i < temp.count(); i++)
                {
                    if(temp[i].isNumber() || ((temp[i] == 'x') && numberReached) || ((temp[i] == 'X') && numberReached))
                    {
                        numberReached = true;
                        number += temp[i];
                    }
                    else if(numberReached)
                        break;

                }

                if(number == "")
                {
                    state = eFailure;
                    break;
                }

                setStructIdQml(number);
                state = eStructName;

                // qDebug() << number;

                break;
            }
            case eStructName:
            {
                currentIndex = temp.indexOf("Contents");

                QString name = "";

                for (int i = currentIndex - 1; i > 0; i--)
                {
                    if((temp[i] == ' ') || (temp[i] == '_'))
                        break;
                    name.insert(0, temp[i]);
                }

                if(name != "")
                {
                    name.replace(0, 1, name[0].toLower());
                    setStructNameQml(name);
                    state = eStructMemberNames;
                    // qDebug() << _structName.text;
                }

                break;
            }
            case eStructMemberNames:
            {
                if(temp.toLower().contains("endoflist") || temp.contains('}'))
                {
                    state = eStructMemberTypes;
                    break;
                }

                if(temp.contains('{'))
                    break;

                QString name = "";

                for (int i = 0; i < temp.count(); i++)
                {
                    if(temp[i].isLetterOrNumber() || (temp[i] == '_'))
                    {
                        name += temp[i];
                    }
                    else if(temp[i] == ',')
                    {
                        if(currentItem == 0)
                        {
                            resetStructItemList();
                            _memberInfo.clear();
                        }

                        addStructItemQml(currentItem, name);
                        currentItem++;
                        // qDebug() << name;
                        break;
                    }
                }

                break;
            }
            case eStructMemberTypes:
            {

                currentIndex = temp.indexOf(_memberInfo.at(currentType).text);

                // qDebug() << currentType;
                // qDebug() << _memberInfo.at(currentType).text;

                if(currentIndex < 0)
                    break;

                bool startFound = false;
                QString typeName = "";

                for (int i = currentIndex + _memberInfo.at(currentType).text.count(); i < temp.count(); i++)
                {
                    if(startFound)
                    {
                        if((temp[i] == ' ') || (temp[i] == ')') || (temp[i] == '}'))
                            break;
                        typeName += temp[i];
                    }
                    else
                    {
                        if(temp[i] == 'e')
                            startFound = true;
                    }
                }

                // qDebug() << typeName;

                int typeIndex = -1;
                for(int i = 0; i < typeList.count(); i++)
                {
                    if(typeList.at(i) == typeName)
                    {
                        typeIndex = i;
                        break;
                    }
                }

                // qDebug() << typeIndex;

                if(typeIndex >= 0)
                {
                    setStructItemTypeQml(currentType, typeIndex);
                    currentType++;
                    if((currentType >= currentIndex) || (currentType >= _memberInfo.count()))
                    {
                        state = eDone;
                    }
                }


                break;
            }
            default:
                break;
        }
    }

    if(state == eDone)
    {
        setOutputText("LynxStructure \"" + _structName.text + "\" successfully loaded");
    }
    else
    {
        setOutputText("Readout was incomplete, some information may be missing");
    }

    file.close();
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

void BackEnd::moveMember(int fromIndex, int toIndex)
{
    _memberInfo.move(fromIndex, toIndex);
}
