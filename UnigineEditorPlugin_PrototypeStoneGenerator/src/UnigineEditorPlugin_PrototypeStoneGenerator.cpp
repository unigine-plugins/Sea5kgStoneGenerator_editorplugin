#include <QMessageBox>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>
#include <iostream>
#include <QGuiApplication>
#include <QScreen>


#include "UnigineEditorPlugin_PrototypeStoneGenerator.h"

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
	message = QString(" >>>>>> UnigineEditorPlugin_PrototypeStoneGenerator::" + message + "\r\n");
	return message.toStdString();
}

void log_info(QString message) {
	Unigine::Log::message(log_prepare_message(message).c_str());
}

void log_error(QString message) {
	std::string sMessage = log_prepare_message(message);
	const char * pMessage = sMessage.c_str();
	Unigine::Log::error(pMessage);
}

bool UnigineEditorPlugin_PrototypeStoneGenerator::init() {
	log_info(" Initializing...");
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

	return true;
}

void UnigineEditorPlugin_PrototypeStoneGenerator::shutdown() {
	log_info("shutdown");
	// if (m_pEditScriptWindow != nullptr) {
	// 	delete m_pEditScriptWindow;
	// }
}

void UnigineEditorPlugin_PrototypeStoneGenerator::click_about() {
	QMessageBox msgBox;
    msgBox.setStyleSheet("QLabel{min-width: 700px;}");
    msgBox.setModal( true );
    msgBox.setWindowTitle("Prototype Stone Gnerator: About");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(
        "<h2>PrototypeStoneGenerator</h2> <br>"
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
	QMenu *pMenuCreate = UnigineEditor::WindowManager::findMenu(UnigineEditor::Constants::MM_CREATE);
	if (pMenuCreate == nullptr) {
		std::string sLogMsg = std::string(" Not found menu: ") + std::string(UnigineEditor::Constants::MM_CREATE);
		log_error(sLogMsg.c_str());
		return false;

	}

	if (m_pMenuCustom == nullptr) {
		m_pMenuCustom = pMenuCreate->addMenu(tr("Prototype Stone Generator"));

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

		QWidget* pMenuTools = dynamic_cast<QWidget*>(pMenuCreate);
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

// bool UnigineEditorPlugin_PrototypeStoneGenerator::loadExtensions() {
// 	if (!prepareDirectoryWithExtensions()) {
// 		return false;
// 	}
	
// 	// remove all previous
// 	for (int i = 0; i < m_vScripts.size(); i++) {
// 		delete m_vScripts[i];
// 	}
// 	m_vScripts.clear();

// 	QDir mainDir(m_sPython3ScriptingDirPath);
// 	QStringList allDirs = mainDir.entryList(QDir::NoDotAndDotDot | QDir::Dirs);
// 	for(int i = 0; i < allDirs.size(); i++) {
// 		QString sPython3ScriptJsonFilePath = m_sPython3ScriptingDirPath + "/" + allDirs[i];
// 		ModelExtension *pModel = new ModelExtension(sPython3ScriptJsonFilePath);
// 		if (pModel->loadFromDirectory()) {
// 			m_vScripts.push_back(pModel);
// 		} else {
// 			log_error(sPython3ScriptJsonFilePath + " - could not load some extension by index");
// 			delete pModel;
// 			continue;
// 		}
//     }

// 	// TODO
// 	m_sPython3ScriptingJsonFilePath = m_sPython3ScriptingDirPath + "/extensions.json";
// 	// prepareExtensionsJson();
// 	if (!safeCreateMenuCustom()) {
// 		return false;
// 	}
// 	if (!reloadMenuForSelected()) {
// 		return false;
// 	}
// 	if (!reloadMenuForExtensions()) {
// 		return false;
// 	}
// 	initMenuForCreateExtension();
// 	initMenuForManageScripts();
// 	initMenuForAbout();
// 	return true;
// }
