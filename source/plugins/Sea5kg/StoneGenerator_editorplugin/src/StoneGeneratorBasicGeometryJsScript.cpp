/*
MIT License

Copyright (c) 2022-2025 mrseakg@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Repository: https://github.com/unigine-plugins/Sea5kgStoneGenerator_editorplugin
*/

#include "StoneGeneratorBasicGeometryJsScript.h"

// #include <math.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

#include <StoneGeneratorConfig.h>

#include "TinyJS.h"
#include "TinyJS_Functions.h"
#include "TinyJS_MathFunctions.h"

#include <fstream>
#include <string>

// TODO: redesign
#include <QString>
#include <QDebug>

// ---------------------------------------------------------------------
// StoneGeneratorBasicJsScript

StoneGeneratorBasicJsScript::StoneGeneratorBasicJsScript(const std::string& scriptPath)  : StoneGeneratorBasicGeometry(1, "Some") {
    m_scriptPath = scriptPath;

    // read file
    std::ifstream inputFile(m_scriptPath);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return;
        // return 1; // Indicate an error
    }

    std::string content;
    std::string line;
    while (std::getline(inputFile, line)) {
        content += line + "\n";
    }

    CTinyJS *js = new CTinyJS();
    try {
        js->execute(content);
    } catch (CScriptException *e) {
        printf("ERROR: %s\n", e->text.c_str());
    }

    CScriptVar *generatorName = js->getScriptVariable("generatorName");
    if (generatorName) {
        m_sName = generatorName->getString();
        std::cout << "generatorName: " << generatorName->getString() << std::endl;
    }
    // var generatorId = 1;
    CScriptVar *generatorId = js->getScriptVariable("generatorId");
    if (generatorId) {
        m_nId = generatorId->getInt();
        std::cout << "generatorId: " << generatorId->getInt() << std::endl;
    }
}

void js_print(CScriptVar *v, void *userdata) {
    qDebug() << "tiny-js: " << QString::fromStdString(v->getParameter("text")->getString());
}

void js_Model_addPoint(CScriptVar *c, void *userdata) {
    StoneGeneratorModel *model = (StoneGeneratorModel *)userdata;
    double x = c->getParameter("x")->getDouble();
    double y = c->getParameter("y")->getDouble();
    double z = c->getParameter("z")->getDouble();

    // CScriptVar *retVar = new CScriptVar();
    CScriptVar *retVar = new CScriptVar("Point", SCRIPTVAR_OBJECT);
    retVar->setUserCustomData((void *)model->addPoint(x,y,z));
    c->setReturnVar(retVar);
}

void js_Model_addTriangle(CScriptVar *c, void *userdata) {
    StoneGeneratorModel *model = (StoneGeneratorModel *)userdata;

    CScriptVar *p0 = c->getParameter("a");
    CScriptVar *p1 = c->getParameter("b");
    CScriptVar *p2 = c->getParameter("c");

    model->addTriangle(
        (StoneGeneratorPoint *)p0->getUserCustomData(),
        (StoneGeneratorPoint *)p1->getUserCustomData(),
        (StoneGeneratorPoint *)p2->getUserCustomData()
    );
}


bool StoneGeneratorBasicJsScript::generate(StoneGeneratorModel *pModel, int nExpectedTriangles, float nRadius) {

    // read file
    std::ifstream inputFile(m_scriptPath);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return false;
        // return 1; // Indicate an error
    }

    std::string content;
    std::string line;
    while (std::getline(inputFile, line)) {
        content += line + "\n";
    }

    content += "\n generate(" + std::to_string(nExpectedTriangles) + ", " + std::to_string(nRadius) + ");";
    pModel->clear();

    CTinyJS *js = new CTinyJS();
    js->addNative("function Model.addPoint(x,y,z)", js_Model_addPoint, pModel);
    js->addNative("function Model.addTriangle(a,b,c)", js_Model_addTriangle, pModel);
    js->addNative("function print(text)", &js_print, 0);
    registerFunctions(js);
    registerMathFunctions(js);
    try {
        js->execute(content);
    } catch (CScriptException *e) {
        qDebug() << "ERROR: " << QString::fromStdString(e->text);
        printf("ERROR: %s\n", e->text.c_str());
        return false;
    }
    return true;
}

