#include "customStrings.h"
#include <iostream>



// Приватные методы

// Очистка значений полей
void String::_clear()
{
    // Удаление указателя на массив символов, если он не nullptr
    if(this->_stringSymbols != nullptr) delete[] this->_stringSymbols;

    // обнуление длины строки
    this->_stringLength = 0;
}

// 
void String::_create(const char charMas[])
{
    unsigned int strLength = 0;
    for(unsigned int i = 0; charMas[i] != '\0'; i++) strLength++;

    this->_stringSymbols = new char[strLength];

    for(unsigned int i = 0; i < strLength; i++) 
        this->_stringSymbols[i] = charMas[i];

    this->_stringLength = strLength;
}

void String::_create(unsigned int num)
{
    unsigned int strLength = 0, temp = num;
    while(temp > 0) 
    {
        strLength++;
        temp /= 10;
    }

    this->_stringSymbols = new char[strLength];

    for(unsigned int i = 0; i < strLength; i++) 
    {
        this->_stringSymbols[i] = (int)(num%10 + 48);
        num /= 10;
    }

    this->_stringLength = strLength;

    this->reverse();
}

void String::_create(const String& string)
{
    unsigned int strLength = string._stringLength;

    this->_stringSymbols = new char[strLength];

    for(unsigned int i = 0; i < strLength; i++) 
        this->_stringSymbols[i] = string._stringSymbols[i];
    
    this->_stringLength = strLength;
}





String::String() 
{
}

String::String(const char charMas[]) 
{
    this->_create(charMas);
}

String::String(unsigned int num)
{
    this->_create(num);
}

String::String(const String& string) 
{
    this->_create(string);
}

String::~String() 
{
    this->_clear();
}






unsigned int String::length()
{
    return _stringLength;
}

void String::reverse()
{
    char temp;
    for(unsigned int i = 0; i < this->_stringLength / 2; i++)
    {
        temp = this->_stringSymbols[i];
        this->_stringSymbols[i] = this->_stringSymbols[this->_stringLength - i - 1];
        this->_stringSymbols[this->_stringLength - i - 1] = temp;
    }
}




// Операторы

const String& String::operator = (const char charMas[])
{
    this->_create(charMas);
    return *this;
}

const String& String::operator = (const String& string)
{
    this->_create(string);
    return *this;
}

const String& String::operator + (const char charMas[])
{
    String tempString;
    unsigned int inputStrLength = 0;
    for(unsigned int i = 0; charMas[i] != '\0'; i++) inputStrLength++;
    unsigned int newStringLength = this->_stringLength + inputStrLength;

    tempString._stringSymbols = new char[newStringLength];

    unsigned int i = 0, j = 0;
    for(; i < this->_stringLength; i++)
        tempString._stringSymbols[i] = this->_stringSymbols[i];
    
    for(; i < newStringLength; i++, j++)
        tempString._stringSymbols[i] = charMas[j];

    tempString._stringLength = newStringLength;    

    *this = tempString;

    return *this;
}

const String& String::operator + (const String& string)
{
    String tempString;
    unsigned int newStringLength = this->_stringLength + string._stringLength;

    tempString._stringSymbols = new char[newStringLength];

    unsigned int i = 0, j = 0;
    for(; i < this->_stringLength; i++)
        tempString._stringSymbols[i] = this->_stringSymbols[i];
    
    for(; i < newStringLength; i++, j++)
        tempString._stringSymbols[i] = string._stringSymbols[j];

    tempString._stringLength = newStringLength;    

    *this = tempString;

    return *this;
}

const String& String::operator + (char symbol)
{
    String tempString;
    unsigned int newStringLength = this->_stringLength + 1;

    tempString._stringSymbols = new char[newStringLength];

    unsigned int i = 0;
    for(; i < this->_stringLength; i++)
        tempString._stringSymbols[i] = this->_stringSymbols[i];
    
    tempString._stringSymbols[i] = symbol;

    tempString._stringLength = newStringLength;    

    *this = tempString;

    return *this;
}

const char& String::operator [] (int i)
{
    return this->_stringSymbols[i];
}

bool String::operator == (const String& string)
{
    if(this->_stringLength != string._stringLength) return false;
    else
    {
        for(unsigned int i = 0; i < this->_stringLength; i++) 
            if(this->_stringSymbols[i] != string._stringSymbols[i]) return false;
        
        return true;
    }
}

bool String::operator != (const String& string)
{
    if(this->_stringLength != string._stringLength) return true;
    else
    {
        for(unsigned int i = 0; i < this->_stringLength; i++) 
            if(this->_stringSymbols[i] != string._stringSymbols[i]) return true;
        
        return false;
    }
}

std::ostream& operator << (std::ostream &out, const String& string)
{
    for(unsigned int i = 0; i < string._stringLength; i++)
    {
        out << string._stringSymbols[i];
    }
    return out;
}
