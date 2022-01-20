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

#

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

// void UnigineEditorPlugin_PrototypeStoneGenerator::slot_executeRunner(Python3Runner *pRunner) {
// 	// std::cout << "slot_executeRunner, QThread::currentThreadId(): " << QThread::currentThread() << std::endl;
// 	// std::cout << "slot_executeRunner, QCoreApplication::instance()->thread(): " << QCoreApplication::instance()->thread() << std::endl;
// 	if (QThread::currentThread() != QCoreApplication::instance()->thread()) {
// 		log_error("UnigineEditorPlugin_PrototypeStoneGenerator::slot_executeRunner Not main thread!!!");
// 	}
// 	pRunner->run();
// 	pRunner->mutexAsync.unlock();
// }

void UnigineEditorPlugin_PrototypeStoneGenerator::editExtension() {
	QObject* obj = sender();
	QAction *pAction = dynamic_cast<QAction *>(obj);
	if (pAction == nullptr) {
		log_error("editExtension. Could not cast to QAction");
		return;
	}
	QVariant userData = pAction->data();
	QString sExtensionId = userData.toString();
	log_info("editExtension. sExtensionId == " + sExtensionId);

	// ModelExtension *pModel = nullptr;
	// for (int i = 0; i < m_vScripts.size(); i++) {
	// 	if (m_vScripts[i]->getId() == sExtensionId) {
	// 		pModel = m_vScripts[i];
	// 		break;
	// 	}
	// }
	// if (pModel == nullptr) {
	// 	log_error("UnigineEditorPlugin_PrototypeStoneGenerator::editExtension(), Not found model");
	// 	return;
	// }

	// auto *pEdit = getEditDialog();
	// pEdit->setModelExtension(pModel);
	// pEdit->show();
    // sd.setModal(true);
    /*if (sd.exec() == QDialog::Accepted) {

    }*/
}

/*
void UnigineEditorPlugin_PrototypeStoneGenerator::createNewExtension() {
	// QString strPaths = listRemove.join("\n");
	// QWidget *pWin = QApplication::activeWindow();
	QString strPaths = "";
    CreateExtensionDialog sd(m_pMainWindow, strPaths);
    sd.setModal(true);
    if (sd.exec() == QDialog::Accepted){
		QString sName = sd.getExtensionName();
		QString sFor = sd.getExtensionFor();
		log_info("createNewExtension. Next with " + sFor + ": " + sName);

		// normalize extension id
		QString sExtensionId = sFor + "_";
		for (int i = 0; i < sName.length(); i++) {
			if (sName[i].isNumber()
				|| (sName[i] >= 'a' && sName[i] <= 'z')
				|| (sName[i] >= 'A' && sName[i] <= 'Z')
			) {
				sExtensionId += sName[i].toLower(); 
			} else {
				sExtensionId += '_';
			}
		}
		log_info("createNewExtension. Next sExtensionId == " + sExtensionId);

		// preapre extension folder
		QDir newExtDir(m_sPython3ScriptingDirPath + "/" + sExtensionId);
		int num = 0;
		while (newExtDir.exists()) {
			newExtDir = QDir(m_sPython3ScriptingDirPath + "/" + sExtensionId + "_" + QString::number(num));
		}
		sExtensionId = newExtDir.dirName();
		QDir(m_sPython3ScriptingDirPath).mkdir(sExtensionId);
		
		QString sPython3ScriptingMainPyPath = newExtDir.absolutePath() + "/main.py";
		QFile fileMainPy(sPython3ScriptingMainPyPath);
		if (!fileMainPy.exists()) {
			fileMainPy.open(QFile::WriteOnly);
			fileMainPy.write(
				"import unigine\r\n"
				"print('￼Disable shadows')\r\n"
				"for mat in LIST_MATERIALS:\r\n"
				"    print(mat.get_name())\r\n"
				"    mat.set_shadow_mask(￼0x00000000)\r\n"
			);
			fileMainPy.close();
		}
		auto pModel = new ModelExtension(newExtDir.absolutePath());
		pModel->setId(sExtensionId);
		pModel->setName(sName);
		pModel->setFor(sFor);
		pModel->setEnabled(true);
		m_vScripts.push_back(pModel);
		// saveAndReloadExtensions();

		// auto *pEdit = getEditDialog();
		// pEdit->setModelExtension(pModel);
		// pEdit->show();
    }
}*/

void UnigineEditorPlugin_PrototypeStoneGenerator::manageScripts() {
	QString strPaths = "";
    // ManageScriptsDialog sd(m_pMainWindow, &m_vScripts);
    // sd.setModal(true);
    // if (sd.exec() == QDialog::Accepted) {
	// 	// QString sName = sd.getExtensionName();
	// 	
	// 	// saveAndReloadExtensions();
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
        "Source-code: <a href='https://github.com/unigine-plugins/unigine-editor-commands-from-outside'>https://github.com/unigine-plugins/unigine-editor-commands-from-outside</a> <br>"
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
