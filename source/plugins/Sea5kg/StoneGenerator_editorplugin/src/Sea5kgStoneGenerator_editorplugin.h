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

class UnigineEditorPlugin_PrototypeStoneGenerator: public QObject, public ::UnigineEditor::Plugin
{
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
	bool initMenuForAbout();

	QString m_sRootPath;
	QString m_sPython3ScriptingDirPath;
	QString m_sPython3ScriptingJsonFilePath;
	QWidget *m_pMainWindow;
	QMenu *m_pMenuCustom;
	QAction *m_pActionCreateMeshAndMaterial;
	QAction *m_pActionCreateOnlyMesh;
	QAction *m_pActionAbout;
	QAction *m_pActionEdit;

	Unigine::Vector<Unigine::NodePtr> m_vSelectedNodes;
	QVector<Unigine::ObjectMeshDynamicPtr> m_vMeshes;

	DialogConfigurator *m_pDialog;
};
