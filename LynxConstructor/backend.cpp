#include "backend.h"

//-----------------------------------------------------------------
//------------------------- StructInfo ----------------------------
//-----------------------------------------------------------------

StructInfo::StructInfo(QObject *parent) : QObject(parent){};

const TextInfo& StructInfo::structName()
{
    return _structName;
}

const TextInfo& StructInfo::structId()
{
    return _structId;
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

void StructInfo::addStructMember(QString text, QString type, bool valid)
{
    _structMembers.append(TextTypeInfo(text, type, valid));
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

    bool temp = _valid;

    _valid = this->checkName();

    if(_valid ^ temp)
    {
        emit validChanged();
        // qDebug() << (valid()?"true":"false");
    }

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

//-----------------------------------------------------------------
//--------------------------- BackEnd -----------------------------
//-----------------------------------------------------------------

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
    // this->savePathSelected("../testFolder");
}

void BackEnd::outputText(QString text)
{
    if(text == _outputText)
        return;

    _outputText = text;
    emit outputTextChanged();
}

void BackEnd::setFilePathMode(E_FilePathMode mode)
{
    if(pathSelected() != bool(mode))
    {
        _filePathMode = mode;
        emit pathSelectedChanged();
    }

    _filePathMode = mode;
}

bool BackEnd::pathSelected()
{
    return bool(_filePathMode);
}

void BackEnd::savePathSelected(QString path)
{
    _filePath = path.remove("file:///") + "/";
    setFilePathMode(eFolderPath);
    outputText(_filePath);
}



void BackEnd::saveStruct(StructInfo* structInfo)
{
    QString errorMessage = "";

    if(!structInfo->structName().valid)
    {
        errorMessage += "Invalid struct name. ";
    }

    if(!structInfo->structId().valid) //!_structId.valid())
    {
        errorMessage += "Invalid struct ID. ";
    }

    QList<int> invalidMembers;

    for (int i = 0; i < structInfo->memberCount(); i++)
    {
        if(!structInfo->structMember(i)->valid)
        {
            invalidMembers.append(i);
        }
    }

    if(invalidMembers.count())
    {
        if(invalidMembers.count() > 1)
            errorMessage += "Struct members ";
        else
            errorMessage += "Struct member ";

        for (int i = 0; i < invalidMembers.count(); i++)
        {
            errorMessage += QString::number(invalidMembers.at(i));

            if(i < invalidMembers.count() - 2)
                errorMessage += ", ";
            else if(i == invalidMembers.count() - 2)
                errorMessage += " and ";
        }

        if(invalidMembers.count() > 1)
            errorMessage += " are ";
         else
            errorMessage += " is ";

        errorMessage += "invalid. ";
    }

    if(errorMessage != "")
    {
        outputText(errorMessage);
        return;
    }



    switch(_filePathMode)
    {
        case eNoPath:
        {
            outputText("No file path selected");
            return;
        }
        case eFolderPath:
        {
            _filePath += structInfo->structName().text.toLower() + "struct.h";
            setFilePathMode(eFullPath);
            break;
        }
        case eFullPath:
        {
           break;
        }
    }


    QFile file(_filePath);

    if(file.exists())
        file.remove();

    if(!file.open(QIODevice::WriteOnly))
    {
        outputText("Could not open file: " + _filePath);
        return;
    }

    QString STRUCT_NAME = structInfo->structName().text.toUpper();

    QString StructName = structInfo->structName().text.left(1).toUpper()
            + structInfo->structName().text.right(structInfo->structName().text.size() - 1);

    QString structName = structInfo->structName().text.left(1).toLower()
            + structInfo->structName().text.right(structInfo->structName().text.size() - 1);


    //-------------- define -----------------
    QString temp = "#ifndef " + STRUCT_NAME + "_STRUCT" + "\r\n#define " + STRUCT_NAME + "_STRUCT" + " " + structInfo->structId().text + "\r\n\r\n";
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

    for (int i = 0; i < structInfo->memberCount(); i++)
    {
        temp = "\t" + structInfo->structMember(i)->text + ",\r\n";
        file.write(temp.toLatin1());
    }

    temp = "\t" + structName + "Contents_EndOfList\r\n};\r\n\r\n";
    file.write(temp.toLatin1());

    //----------- structItems --------------
    temp = "static const StructItem " + structName + "Items[]\r\n{\r\n";
    file.write(temp.toLatin1());

    for (int i = 0; i < structInfo->memberCount(); i++)
    {
        temp = "\tStructItem( \"" + structInfo->structMember(i)->text + "\", e" + structInfo->structMember(i)->type + " ),\r\n";
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
    outputText("File Saved to: " + _filePath);
}


void BackEnd::openPathSelected(QString path)
{
    _filePath = path.remove("file:///");
    setFilePathMode(eFullPath);

    QFile file(_filePath);

    if(!file.exists())
    {
        outputText("File: " + _filePath + " does not exist.");
        return;
    }

    if(!file.open(QIODevice::ReadOnly))
    {
        outputText("Could not open file" + _filePath);
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
        ePushStructMembers,
        eExitLoop
        // eFailure
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

    QList<QString> structMemberNames;
    QList<int> structMemberTypes;
    bool typeListReserved = false;

    bool minorErrorFlag = false;
    bool majorErrorFlag = false;

    while(state != eExitLoop)
    {
        temp = file.readLine();

        if(temp == "")
        {
            majorErrorFlag = true;
            state = ePushStructMembers;
        }

        switch(state)
        {
            case eStructId:
            {
                currentIndex = temp.indexOf("#define");
                if(currentIndex < 0)
                    break;

                QString structID = "";
                bool numberReached = false;

                for (int i = currentIndex + int(sizeof("#define")); i < temp.count(); i++)
                {
                    if(temp[i].isNumber() || ((temp[i] == 'x') && numberReached) || ((temp[i] == 'X') && numberReached))
                    {
                        numberReached = true;
                        structID += temp[i];
                    }
                    else if(numberReached)
                        break;

                }

                state = eStructName;

                if(structID == "")
                {
                    minorErrorFlag = true;
                    break;
                }

                this->pushStructId(structID);

                break;
            }
            case eStructName:
            {
                currentIndex = temp.indexOf("Contents");
                if(currentIndex < 0)
                    break;

                structName = "";

                for (int i = currentIndex - 1; i > 0; i--)
                {
                    if((temp[i] == ' ') || (temp[i] == '_'))
                        break;
                    structName.insert(0, temp[i]);
                }

                state = eStructMemberNames;

                if(structName == "")
                {
                    structName = "0";
                    minorErrorFlag = true;
                }

                structName.replace(0, 1, structName[0].toLower());
                this->pushStructName(structName);

                break;
            }
            case eStructMemberNames:
            {
                if(temp.toLower().contains("endoflist") || temp.contains('}'))
                {
                    state = eStructMemberTypes;
                    break;
                }

                QString name = "";

                for (int i = 0; i < temp.count(); i++)
                {
                    if(temp[i].isLetterOrNumber() || (temp[i] == '_'))
                    {
                        name += temp[i];
                    }
                    else if(temp[i] == ',')
                    {
                        structMemberNames.append(name);
                        break;
                    }
                }

                break;
            }
            case eStructMemberTypes:
            {
                if(!typeListReserved)
                {
                    structMemberTypes.reserve(structMemberNames.count());
                    for (int i = 0; i < structMemberNames.count(); i++)
                    {
                        structMemberTypes.append(-1);
                    }
                    typeListReserved = true;
                }

                if(structMemberNames.count() == typeIndex)
                {
                    state = ePushStructMembers;
                    break;
                }

                currentIndex = temp.indexOf(structMemberNames.at(typeIndex));
                if(currentIndex < 0)
                    break;

                currentIndex += structMemberNames.at(typeIndex).count();

                bool startFound = false;
                QString typeName = "";

                for (int i = currentIndex; i < temp.count(); i++)
                {
                    if(startFound)
                    {
                        if(!temp[i].isLetterOrNumber())
                            break;

                        typeName += temp[i];
                    }
                    else
                    {
                        if(temp[i] == 'e')
                            startFound = true;
                    }
                }

                if(!startFound)
                    break;

                for(int i = 0; i < typeList.count(); i++)
                {
                    if(typeList.at(i) == typeName)
                    {
                        structMemberTypes[typeIndex] = i;
                        break;
                    }
                }

                if(structMemberTypes[typeIndex] < 0)
                    minorErrorFlag = true;

                typeIndex++;

                break;
            }
            case ePushStructMembers:
            {
                for (int i = 0; i < structMemberNames.count(); i++)
                {
                    if(structMemberTypes.at(i) < 0)
                        this->pushStructMember(structMemberNames.at(i), 0);
                    else
                        this->pushStructMember(structMemberNames.at(i), structMemberTypes.at(i));

                }

                state = eExitLoop;
                break;
            }
            default:
                break;
        }
    }


    if(majorErrorFlag)
    {
        outputText("Readout was incomplete, some information may be missing");
    }
    else if(minorErrorFlag)
    {
        outputText("LynxStructure \"" + structName.replace(0, 1, structName.at(0).toUpper()) + " Struct\" was loaded with errors, some information may be missing");
    }
    else
    {
        outputText("LynxStructure \"" + structName.replace(0, 1, structName.at(0).toUpper()) + " Struct\" successfully loaded");
    }

    file.close();
}

