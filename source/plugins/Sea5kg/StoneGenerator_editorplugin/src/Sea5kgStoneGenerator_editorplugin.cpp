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
        "Version: " + QString(PrototypeStoneGenerator_VERSION) + " <br>"
        "Source-code: <a href='https://github.com/unigine-plugins/unigine-editor-prototype-stone-generator'>https://github.com/unigine-plugins/unigine-editor-prototype-stone-generator</a> <br>"
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
