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

#pragma once

#include "DialogConfigurator.h"

#include <editor/UniginePlugin.h>
#include <UnigineGUID.h>
#include <UnigineNode.h>

#include <QObject>
#include <QMainWindow>
#include <QMenuBar>
#include <QJsonObject>
#include <QThread>
#include <UnigineObjects.h>

class UnigineEditorPlugin_PrototypeStoneGenerator: public QObject, public ::UnigineEditor::Plugin {
    Q_OBJECT
    Q_DISABLE_COPY(UnigineEditorPlugin_PrototypeStoneGenerator)
    Q_PLUGIN_METADATA(IID UNIGINE_EDITOR_PLUGIN_IID FILE "Sea5kgStoneGenerator_editorplugin.json")
    Q_INTERFACES(UnigineEditor::Plugin)
public:
    UnigineEditorPlugin_PrototypeStoneGenerator();
    ~UnigineEditorPlugin_PrototypeStoneGenerator() override;

    bool init() override;
    void shutdown() override;

private slots:
    void click_createMeshAndMaterial();
    void click_createOnlyMesh();
    void click_about();

    void globalSelectionChanged();

private:
    bool safeCreateMenuCustom();
    bool reloadMenuForSelected();
    bool reloadMenuForExtensions();
    bool initMenuForAbout();

    QString m_sRootPath;
    QString m_sPython3ScriptingDirPath;
    QString m_sPython3ScriptingJsonFilePath;
    QWidget *m_pMainWindow;
    QMenu *m_pMenuCustom;
    QMenu *m_pMenuCreate;
    QAction *m_pActionCreateMeshAndMaterial;
    QAction *m_pActionCreateOnlyMesh;
    QAction *m_pActionAbout;
    QAction *m_pActionEdit;

    Unigine::Vector<Unigine::NodePtr> m_vSelectedNodes;
    QVector<Unigine::ObjectMeshDynamicPtr> m_vMeshes;

    DialogConfigurator *m_pDialog;
};
