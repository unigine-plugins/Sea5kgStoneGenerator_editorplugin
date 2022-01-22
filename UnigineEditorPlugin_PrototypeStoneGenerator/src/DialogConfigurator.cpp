#include <QtGui>
#include <iostream>

#include "DialogConfigurator.h"

DialogConfigurator::DialogConfigurator(
	QWidget *parent
) : QDialog(parent) {
	// m_nSliderTrianglesValue = 80000;
	// m_nSliderTrianglesValue = 6774;
	m_nSliderTrianglesValue = 100;
	m_nSliderRadius = 2.0f;
	m_nSliderRandomOffsetMin = 0.0f;
	m_nSliderRandomOffsetMax = 0.0f;

	m_pStoneGenerator = new StoneGenerator();

    m_pRegenerateButton = new QPushButton(tr("Regenerate"));
	m_pRegenerateButton->setDefault(true);

	m_pCloseButton = new QPushButton(tr("Close"));
	
	connect(m_pRegenerateButton, SIGNAL(clicked()),this, SLOT(regenerateButton_clicked()));
	connect(m_pCloseButton, SIGNAL(clicked()),this, SLOT(close()));

	QVBoxLayout *leftLayout = new QVBoxLayout;

	// leftLayout->addWidget(m_pLineEditSearch);
	// leftLayout->addStretch();

	m_pLabelSliderTriangles = new QLabel(tr("Triangles: ") + QString::number(m_nSliderTrianglesValue));
	leftLayout->addWidget(m_pLabelSliderTriangles);

	m_pSliderTriangles = new QSlider(Qt::Horizontal);
    m_pSliderTriangles->setRange(100, 80000);
    m_pSliderTriangles->setValue(m_nSliderTrianglesValue);
	connect(m_pSliderTriangles, SIGNAL(valueChanged(int)), this, SLOT(sliderTriangles_valuesChanged(int)));
	leftLayout->addWidget(m_pSliderTriangles);

	m_pLabelSliderRadius = new QLabel(tr("Radius: ") + QString::number(m_nSliderRadius));
	leftLayout->addWidget(m_pLabelSliderRadius);

	m_pSliderRadius = new QSlider(Qt::Horizontal);
    m_pSliderRadius->setRange(0.1 * 100, 4 * 100);
    m_pSliderRadius->setValue(m_nSliderRadius*100);
	connect(m_pSliderRadius, SIGNAL(valueChanged(int)), this, SLOT(sliderRadius_valuesChanged(int)));
	leftLayout->addWidget(m_pSliderRadius);

	// random min
	m_pLabelSliderRandomOffsetMin = new QLabel(tr("Random Offset (min): ") + QString::number(m_nSliderRandomOffsetMin));
	leftLayout->addWidget(m_pLabelSliderRandomOffsetMin);
	
	m_pSliderRandomOffsetMin = new QSlider(Qt::Horizontal);
    m_pSliderRandomOffsetMin->setRange(-4 * 100, 4 * 100);
    m_pSliderRandomOffsetMin->setValue(m_nSliderRandomOffsetMin*100);
	connect(m_pSliderRandomOffsetMin, SIGNAL(valueChanged(int)), this, SLOT(sliderRandomOffsetMin_valuesChanged(int)));
	leftLayout->addWidget(m_pSliderRandomOffsetMin);

	// random max
	m_pLabelSliderRandomOffsetMax = new QLabel(tr("Random Offset (max): ") + QString::number(m_nSliderRandomOffsetMax));
	leftLayout->addWidget(m_pLabelSliderRandomOffsetMax);
	
	m_pSliderRandomOffsetMax = new QSlider(Qt::Horizontal);
    m_pSliderRandomOffsetMax->setRange(-4 * 100, 4 * 100);
    m_pSliderRandomOffsetMax->setValue(m_nSliderRandomOffsetMax*100);
	connect(m_pSliderRandomOffsetMax, SIGNAL(valueChanged(int)), this, SLOT(sliderRandomOffsetMax_valuesChanged(int)));
	leftLayout->addWidget(m_pSliderRandomOffsetMax);

	m_pProgress = new QProgressBar(this);
	m_pProgress->setValue(0);
	m_pProgress->setMinimum(0);
	m_pProgress->setMaximum(100);
	leftLayout->addWidget(m_pProgress);

	QHBoxLayout *buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(m_pRegenerateButton);
	buttonsLayout->addWidget(new QWidget);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(m_pCloseButton);
	leftLayout->addLayout(buttonsLayout);

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout);
	// mainLayout->addLayout(rightLayout);
	setLayout(mainLayout);
	// setLayout(leftLayout);
	setWindowTitle(tr("Prototype Stone Generator - Configurator"));
	setFixedWidth(800);
	setFixedHeight(sizeHint().height());
}

void DialogConfigurator::sliderTriangles_valuesChanged(int nNewValue) {
	m_nSliderTrianglesValue = nNewValue;
	m_pLabelSliderTriangles->setText(tr("Triangles: ") + QString::number(m_nSliderTrianglesValue));
	this->regenerateGeometry();
}

void DialogConfigurator::sliderRadius_valuesChanged(int nNewValue) {
	m_nSliderRadius = float(nNewValue) / 100;
	m_pLabelSliderRadius->setText(tr("Radius: ") + QString::number(m_nSliderRadius));
	this->regenerateGeometry();
}

void DialogConfigurator::sliderRandomOffsetMin_valuesChanged(int nNewValue) {
	m_nSliderRandomOffsetMin = float(nNewValue) / 100;
	m_pLabelSliderRandomOffsetMin->setText(tr("Random Offset (min): ") + QString::number(m_nSliderRandomOffsetMin));
	this->regenerateGeometry();
}

void DialogConfigurator::sliderRandomOffsetMax_valuesChanged(int nNewValue) {
	m_nSliderRandomOffsetMax = float(nNewValue) / 100;
	m_pLabelSliderRandomOffsetMax->setText(tr("Random Offset (max): ") + QString::number(m_nSliderRandomOffsetMax));
	this->regenerateGeometry();
}

void DialogConfigurator::regenerateButton_clicked() {
	this->regenerateGeometry();
}

void DialogConfigurator::createNode() {
	m_pMesh = Unigine::ObjectMeshDynamic::create();
	// TODO select position by a camera
	m_pMesh->setWorldTransform(translate(Unigine::Math::Vec3(0.0f, 0.0f, 2.0f)));
	m_pMesh->setShowInEditorEnabledRecursive(1);
	m_pMesh->setSaveToWorldEnabledRecursive(1);
	QVector<Unigine::NodePtr> pNodes;
	pNodes.push_back(m_pMesh);
	Editor::SelectorNodes *pSelected = Editor::SelectorNodes::createObjectsSelector(pNodes);
	Editor::Selection::setSelector(pSelected);

	this->regenerateGeometry();
}

void DialogConfigurator::regenerateGeometry() {
	Unigine::Log::message("DialogConfigurator::regenerateGeometry start\n");
	m_pProgress->setValue(0);
	m_pProgress->setMinimum(0);
	m_pProgress->setMaximum(m_nSliderTrianglesValue);

	m_pStoneGenerator->clear();

	m_pStoneGenerator->setRaidus(m_nSliderRadius);
	m_pStoneGenerator->setEstimatedExpectedTriangles(m_nSliderTrianglesValue);
	m_pStoneGenerator->setRandomOffsetMin(m_nSliderRandomOffsetMin);
	m_pStoneGenerator->setRandomOffsetMax(m_nSliderRandomOffsetMax);
	m_pStoneGenerator->generate();

	m_pMesh->clearVertex();
	m_pMesh->clearIndices(); // here triangles like some one
	m_pMesh->flushIndices();
	m_pMesh->flushVertex();

	const std::vector<StoneTriangle *> &v = m_pStoneGenerator->triangles();
	m_pMesh->addTriangles(v.size());
	for (int i = 0; i < v.size(); i++) {
		StoneTriangle *pTriangle = v[i];

		m_pMesh->addVertex(Unigine::Math::vec3(
			pTriangle->p1()->x(),
			pTriangle->p1()->y(),
			pTriangle->p1()->z()
		));
		m_pMesh->addTexCoord(Unigine::Math::vec4(0, 0, 0, 0));
		// m_pMesh->addColor(Unigine::Math::vec4(0, 1, 1, 1));
		m_pMesh->addVertex(Unigine::Math::vec3(
			pTriangle->p2()->x(),
			pTriangle->p2()->y(),
			pTriangle->p2()->z()
		));
		m_pMesh->addTexCoord(Unigine::Math::vec4(1, 0, 0, 0));
		// m_pMesh->addColor(Unigine::Math::vec4(1, 0, 1, 1));

		m_pMesh->addVertex(Unigine::Math::vec3(
			pTriangle->p3()->x(),
			pTriangle->p3()->y(),
			pTriangle->p3()->z()
		));
		m_pMesh->addTexCoord(Unigine::Math::vec4(1, 1, 0, 0));
		// m_pMesh->addColor(Unigine::Math::vec4(1, 1, 0, 1));
	}

	m_pMesh->updateTangents();
	// // optimize vertex and index buffers, if necessary
	// m_pMesh->updateIndices(); 

	// // calculate a mesh bounding box
	m_pMesh->updateBounds();

	m_pMesh->flushIndices();
	m_pMesh->flushVertex();

	// I expect an approximate number of triangles 

	// Unigine::UGUID guid;
	// guid.generate();
	// const char *string_id = guid.getFileSystemString();
	// log_info("Guid: " + QString(guid.get()));
	// auto size = Unigine::Math::vec3(1.0f, 1.0f, 1.0f);

	// Unigine::ObjectMeshDynamicPtr mesh1 = Unigine::Primitives::createBox(size);
	// mesh1->setMaterial("mesh_base", "*");
	// mesh1->setEnabled(1);
	
	// mesh1->setShowInEditorEnabledRecursive(1);
	// mesh1->setSaveToWorldEnabledRecursive(1);
	
	// mesh1->setWorldTransform(translate(Unigine::Math::Vec3(1.0f, 1.0f, 1.0f)));
	// // set the name of the mesh
	// mesh1->setName("Dynamic Mesh");
	// mesh1->saveMesh("box_24567.mesh");
	// Unigine::FileSystem::setGUID("box_24567.mesh", guid);
	// emit Editor::AssetManager::instance()->added(guid);

	Unigine::Log::message("DialogConfigurator::regenerateGeometry end\n");
}