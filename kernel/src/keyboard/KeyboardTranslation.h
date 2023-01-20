#pragma once
#include "../BitOSUtilities.h"
struct NormalKeyboardKey{
    char key;
    char keyType;
};

const char _qwerty[] = "qwertyuiop[]";
const char _asdfg[] = "asdfghjkl;'";
const char _zxcv[] = "zxcvbnm,./";
const char _dash_equal[] = "-=";
const char _0 = '0';
const char _numbers[] = "123456789";
const char _backslash = '\\';

#define shiftableLength 21

const char shiftable[] = "1234567890-=[]\\;',./`";
const char shifted[] = "!@#$%^&*()_+{}|:\"<>?~";

static char shiftChar(char c){
        if(isAlpha(c)){
                return toUpper(c);
        }
        for(int i = 0; i < shiftableLength; i++){
                if(shiftable[i] == c){
                        return shifted[i];
                }
        }
        return c;
}

static NormalKeyboardKey scancode2normal(char c){
        NormalKeyboardKey convertedKey;
        convertedKey.keyType = 255;
        if(c == 1){
                convertedKey.keyType=(char)0;//control character
                convertedKey.key=0;
        }
        else if(c>=59 && c<=68){//f1-f10
                convertedKey.keyType=(char)1;//function key
                convertedKey.key=(char)(c-58+48);
        }
        else if(c>=2 && c<=10){//1-9
                convertedKey.keyType=(char)2;//ascii character
                convertedKey.key=_numbers[c-2];
        }
        else if(c==11){//0
                convertedKey.keyType=(char)2;//ascii character
                convertedKey.key=_0;
        }
        else if(c>=16 && c<=27){//qwerty...]
                convertedKey.keyType=(char)2;//ascii character
                convertedKey.key=_qwerty[c-16];
        }
        else if(c == 43){
                convertedKey.keyType=(char)2;//ascii character
                convertedKey.key=_backslash;
        }
        else if(c>=30 && c<=40){//qwerty...]
                convertedKey.keyType=(char)2;//ascii character
                convertedKey.key=_asdfg[c-30];
        }
        else if(c>=44 && c<=53){
                convertedKey.keyType=(char)2;//ascii character
                convertedKey.key=_zxcv[c-44];
        }
        else if(c==28){
                convertedKey.keyType=(char)2;//ascii character
                convertedKey.key='\n';
        }
        else if(c>=12 && c<=13){
                convertedKey.keyType=(char)2;//ascii character
                convertedKey.key=_dash_equal[c-12];
        }
        else if(c == 57){
                convertedKey.keyType=(char)2;//ascii character
                convertedKey.key=' ';
        }
        else if(c==75){//left arrow
                convertedKey.keyType=(char)3;//arrow key
                convertedKey.key=0;
        }
        else if(c==72){//up arrow
                convertedKey.keyType=(char)3;//arrow key
                convertedKey.key=1;
        }
        else if(c==77){//right arrow
                convertedKey.keyType=(char)3;//arrow key
                convertedKey.key=3;
        }
        else if(c==80){//down arrow
                convertedKey.keyType=(char)3;//arrow key
                convertedKey.key=3;
        }
        else if(c==14){
                convertedKey.keyType=(char)0;//control character
                convertedKey.key=1;
        }
        else if(c==29){
                convertedKey.keyType=(char)0;//control character
                convertedKey.key=2;
        }
        else if(c==56){
                convertedKey.keyType=(char)0;//control character
                convertedKey.key=3;
        }
        else if(c==42){
                convertedKey.keyType=(char)0;//control character
                convertedKey.key=4;
        }
        else if(c == 83){
                convertedKey.keyType=(char)0;
                convertedKey.key=5;
        }
        return convertedKey;
}