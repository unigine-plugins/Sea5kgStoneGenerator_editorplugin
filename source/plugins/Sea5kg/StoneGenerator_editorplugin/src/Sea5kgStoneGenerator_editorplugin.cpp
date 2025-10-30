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

#include <QMessageBox>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>
#include <iostream>
#include <QGuiApplication>
#include <QScreen>
#include <ctime>
#include <chrono>

#include "Sea5kgStoneGenerator_editorplugin.h"

#include <UnigineLog.h>
#include <UnigineEditor.h>
#include <UnigineObjects.h>
#include <UnigineWorld.h>
#include <UniginePrimitives.h>
#include <QCoreApplication>
#include <UnigineMaterials.h>


#include "UnigineFileSystem.h"

// ------------------------------------------------------------------------------------------
// UnigineEditorPlugin_PrototypeStoneGenerator

UnigineEditorPlugin_PrototypeStoneGenerator::UnigineEditorPlugin_PrototypeStoneGenerator()  = default;
UnigineEditorPlugin_PrototypeStoneGenerator::~UnigineEditorPlugin_PrototypeStoneGenerator() = default;

std::string log_prepare_message(QString message) {
    message = QString(" >>>>>> Sea5kgStoneGenerator_editorplugin::" + message + "\r\n");
    return message.toStdString();
}

void log_info(QString message) {
    Unigine::Log::message("%s", log_prepare_message(message).c_str());
}

void log_error(QString message) {
    std::string sMessage = log_prepare_message(message);
    const char * pMessage = sMessage.c_str();
    Unigine::Log::error("%s", pMessage);
}

bool UnigineEditorPlugin_PrototypeStoneGenerator::init() {
    log_info("Initializing...");
    m_pMenuCustom = nullptr;
    m_pMainWindow = nullptr;

    m_sRootPath = QCoreApplication::applicationDirPath(); // must be in bin

    if (!safeCreateMenuCustom()) {
        return false;
    }


    connect(
        UnigineEditor::Selection::instance(),
        &UnigineEditor::Selection::changed,
        this,
        &UnigineEditorPlugin_PrototypeStoneGenerator::globalSelectionChanged
    );
    // connect(this, &UnigineEditorPlugin_PrototypeStoneGenerator::signal_executeRunner, this, &UnigineEditorPlugin_PrototypeStoneGenerator::slot_executeRunner);

    log_info("Initialiazed");

    // auto start = std::chrono::steady_clock::now();
    // unsigned int n = 1;
    // for (int i = 0; i < 100; i++) {
    //     // std::cout << i << " " << n << std::endl;
    // }

    // auto end = std::chrono::steady_clock::now();
    // long long time_diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    // std::cout << "time_diff: " << time_diff << " ns " << std::endl;
 
    return true;
}

void UnigineEditorPlugin_PrototypeStoneGenerator::shutdown() {
    log_info("Shutdown...");
    disconnect(UnigineEditor::Selection::instance(), &UnigineEditor::Selection::changed, this, &UnigineEditorPlugin_PrototypeStoneGenerator::globalSelectionChanged);

    m_pMenuCustom->removeAction(m_pActionCreateOnlyMesh);
    m_pMenuCustom->removeAction(m_pActionCreateMeshAndMaterial);
    m_pMenuCustom->removeAction(m_pActionAbout);
    m_pMenuCreate->removeAction(m_pMenuCustom->menuAction());

    delete m_pDialog;
    log_info("Done");
}

void UnigineEditorPlugin_PrototypeStoneGenerator::click_about() {
    QMessageBox msgBox;
    msgBox.setStyleSheet("QLabel{min-width: 700px;}");
    msgBox.setModal( true );
    msgBox.setWindowTitle("Sea5kg Stone Gnerator: About");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(
        "<h2>Sea5kg Stone Generator</h2> <br>"
        "UnigineEditor Plugin for generation of meshes representing stones of various sizes and shapes.<br>"
        "Version: " + QString(CURRENT_PROJECT_VERSION) + " <br>"
        "Source-code: <a href='https://github.com/unigine-plugins/Sea5kgStoneGenerator_editorplugin'>https://github.com/unigine-plugins/Sea5kgStoneGenerator_editorplugin</a> <br>"
        "Unigine Store: <a href='https://store.unigine.com/add-on/1ee2ef39-4458-6124-aefe-dbe1b97903ce/description'>https://store.unigine.com/add-on/1ee2ef39-4458-6124-aefe-dbe1b97903ce/description</a> <br>"
        "Telegram: <a href='https://t.me/sea5kg_stonegenerator'>https://t.me/sea5kg_stonegenerator</a> <br>"
        "Youtube Playlist: <a href='https://youtube.com/playlist?list=PL-Ky59xTi1WRCFocly-FhrFLLKwdbqEkO&feature=shared'>https://youtube.com/playlist?list=PL-Ky59xTi1WRCFocly-FhrFLLKwdbqEkO&feature=shared</a> <br>"

        "<hr/>"
        "Components and author(s):<ul>"
        "  <li>Evgenii Sopov (mrseakg@gmail.com) </li>"
        "</ul><hr>"
        // + sFileLicenseContent
    );
    msgBox.exec();
}

void UnigineEditorPlugin_PrototypeStoneGenerator::click_createMeshAndMaterial() {
    m_pDialog->setGenerateMesh(true);
    m_pDialog->setGenerateMaterial(true);
    m_pDialog->show();
    m_pDialog->createNode();
}

void UnigineEditorPlugin_PrototypeStoneGenerator::click_createOnlyMesh() {
    m_pDialog->setGenerateMesh(true);
    m_pDialog->setGenerateMaterial(false);
    m_pDialog->show();
    m_pDialog->createNode();
}

void UnigineEditorPlugin_PrototypeStoneGenerator::globalSelectionChanged() {
    // using namespace std;
    // m_vSelectedGuids.clear();
    m_vSelectedNodes.clear();
    if (auto selector = UnigineEditor::Selection::getSelectorNodes()) {
        log_info("Selected nodes");
        m_vSelectedNodes.append(selector->getNodes());
    } else {
        log_info("Something else");
    }
}

bool UnigineEditorPlugin_PrototypeStoneGenerator::safeCreateMenuCustom() {
    m_pMenuCreate = UnigineEditor::WindowManager::findMenu(UnigineEditor::Constants::MM_CREATE);
    if (m_pMenuCreate == nullptr) {
        std::string sLogMsg = std::string(" Not found menu: ") + std::string(UnigineEditor::Constants::MM_CREATE);
        log_error(sLogMsg.c_str());
        return false;

    }

    if (m_pMenuCustom == nullptr) {
        m_pMenuCustom = m_pMenuCreate->addMenu(tr("Sea5kg / Stone Generator"));

        // menu create
        m_pActionCreateOnlyMesh = new QAction("Create Only Mesh", this);
        connect(m_pActionCreateOnlyMesh, &QAction::triggered, this, &UnigineEditorPlugin_PrototypeStoneGenerator::click_createOnlyMesh);
        m_pMenuCustom->addAction(m_pActionCreateOnlyMesh);

        m_pActionCreateMeshAndMaterial = new QAction("Create Mesh And Material", this);
        connect(m_pActionCreateMeshAndMaterial, &QAction::triggered, this, &UnigineEditorPlugin_PrototypeStoneGenerator::click_createMeshAndMaterial);
        m_pMenuCustom->addAction(m_pActionCreateMeshAndMaterial);

        m_pActionAbout = new QAction(tr("About PrototypeStoneGenerator Plugin"), this);
        connect(m_pActionAbout, &QAction::triggered, this, &UnigineEditorPlugin_PrototypeStoneGenerator::click_about);
        m_pMenuCustom->addAction(m_pActionAbout);

        QWidget* pMenuTools = dynamic_cast<QWidget*>(m_pMenuCreate);
        m_pMainWindow = pMenuTools->parentWidget()->parentWidget();
        QString sClassname  = m_pMainWindow->metaObject()->className();
        log_info(" Found  " + sClassname);
        m_pDialog = new DialogConfigurator(m_pMainWindow);
        Qt::WindowFlags flags = m_pDialog->windowFlags();
        m_pDialog->setWindowFlags(flags | Qt::Tool);
    }

    return true;
}

bool UnigineEditorPlugin_PrototypeStoneGenerator::reloadMenuForSelected() {

    return true;
}
