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


	connect(Editor::Selection::instance(), &Editor::Selection::changed, this, &UnigineEditorPlugin_PrototypeStoneGenerator::globalSelectionChanged);
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

void UnigineEditorPlugin_PrototypeStoneGenerator::about() {
	QMessageBox msgBox;
    msgBox.setStyleSheet("QLabel{min-width: 700px;}");
    msgBox.setModal( true );
    msgBox.setWindowTitle("Python3Scripting: About");
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

void UnigineEditorPlugin_PrototypeStoneGenerator::processCreate() {
	m_pDialog->show();
	m_pDialog->createNode();
}

void UnigineEditorPlugin_PrototypeStoneGenerator::processEdit() {
	// ModelExtension *pModel = findModelExtensionByAction(sender());
	// if (pModel == nullptr) {
	// 	log_error("processSelectedNodes Could not find model for this action");
	// 	return;
	// }
}

void UnigineEditorPlugin_PrototypeStoneGenerator::processSelectedProperties() {
	// ModelExtension *pModel = findModelExtensionByAction(sender());
	// if (pModel == nullptr) {
	// 	log_error("processSelectedProperties Could not find model for this action");
	// 	return;
	// }
}

void UnigineEditorPlugin_PrototypeStoneGenerator::processSelectedRuntimes() {
	// ModelExtension *pModel = findModelExtensionByAction(sender());
	// if (pModel == nullptr) {
	// 	log_error("processSelectedRuntimes Could not find model for this action");
	// 	return;
	// }
}

void UnigineEditorPlugin_PrototypeStoneGenerator::globalSelectionChanged() {
	// using namespace std;
	// m_vSelectedGuids.clear();
	m_vSelectedNodes.clear();
	if (auto selector = Editor::Selection::getSelectorNodes()) {
		log_info("Selected nodes");
		
		m_vSelectedNodes.append(selector->getNodes());
	} else {
		log_info("Something else");
	
	}
}

bool UnigineEditorPlugin_PrototypeStoneGenerator::safeCreateMenuCustom() {
	QString sMenuName = Constants::MM_TOOLS;
	QMenu *pMenu = Editor::WindowManager::findMenu(sMenuName);
	if (pMenu == nullptr) {
		log_error(" Not found menu: " + sMenuName);
		return false;
		
	}
	// log_info(" Found menu " + sMenuName);
	// get main menu
	if (m_pMenuCustom == nullptr) {
		QWidget* pMenuTools = dynamic_cast<QWidget*>(pMenu);
		QMenuBar* pMenuBar = dynamic_cast<QMenuBar*>(pMenuTools->parentWidget());
		m_pMenuCustom = pMenuBar->addMenu(tr("Prototype Stone Generator"));
		m_pMainWindow = pMenuTools->parentWidget()->parentWidget();
		QString sClassname  = m_pMainWindow->metaObject()->className();
		log_info(" Found  " + sClassname);
		m_pDialog = new DialogConfigurator(m_pMainWindow);
		Qt::WindowFlags flags = m_pDialog->windowFlags();
		m_pDialog->setWindowFlags(flags | Qt::Tool);

		// menu create
		m_pActionCreate = new QAction("Create", this);
		connect(m_pActionCreate, &QAction::triggered, this, &UnigineEditorPlugin_PrototypeStoneGenerator::processCreate);
		m_pMenuCustom->addAction(m_pActionCreate);

		// menu edit
		// m_pActionEdit = new QAction("Edit", this);
		// connect(m_pActionEdit, &QAction::triggered, this, &UnigineEditorPlugin_PrototypeStoneGenerator::processEdit);
		// m_pMenuCustom->addAction(m_pActionEdit);
	}
	return true;
}

bool UnigineEditorPlugin_PrototypeStoneGenerator::reloadMenuForSelected() {

	return true;
}

bool UnigineEditorPlugin_PrototypeStoneGenerator::initMenuForAbout() {
	m_pActionAbout = new QAction(tr("About PrototypeStoneGenerator Plugin"), this);
	connect(m_pActionAbout, &QAction::triggered, this, &UnigineEditorPlugin_PrototypeStoneGenerator::about);
	m_pMenuCustom->addAction(m_pActionAbout);
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
