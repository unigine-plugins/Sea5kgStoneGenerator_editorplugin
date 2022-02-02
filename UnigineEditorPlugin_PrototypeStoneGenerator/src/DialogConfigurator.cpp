#include <QtGui>
#include <iostream>

#include "DialogConfigurator.h"
#include "UnigineFileSystem.h"
#include <UnigineEditor.h>
#include <QThreadPool>
#include <QPixmap>

DialogConfigurator::DialogConfigurator(
	QWidget *parent
) : QDialog(parent) {
	// m_nSliderTrianglesValue = 80000;
	// m_nSliderTrianglesValue = 6774;
	m_bWannaUpdate = false;
	m_bInProgress = false;
	m_bRegenerateGeometry = false;
    m_bRegenerateTexture = false;
	m_nSliderTrianglesValue = 100;
	m_nSliderRadius = 2.0f;
	m_nSliderRandomOffsetMin = 0.0f;
	m_nSliderRandomOffsetMax = 0.0f;
	m_nSliderScaleX = 1.0f;
	m_nSliderScaleY = 1.0f;
	m_nSliderScaleZ = 1.0f;
	m_sFilePath1 = m_temporaryDir.filePath("stone.png");
	m_sFilePathHighlighted = m_temporaryDir.filePath("stone_high.png");
	m_nLabelSize = 120;
	m_nLabelValueSize = 50;

	m_pAsyncRunGenerator = new AsyncRunGenerator(this);
	m_pAsyncRunGenerator->setAutoDelete(false);
    

	QVBoxLayout *leftLayout = new QVBoxLayout;

	auto *pGeometry = new QLabel("Geometry:");
	leftLayout->addWidget(pGeometry);

	leftLayout->addLayout(  createIntSliderParameterUI("Expected triangles: ", &m_nSliderTrianglesValue, 100, 80000));
	leftLayout->addLayout(createFloatSliderParameterUI("Radius: ", &m_nSliderRadius, 0.1, 4.0));
	leftLayout->addLayout(createFloatSliderParameterUI("Random Offset (min): ", &m_nSliderRandomOffsetMin, -2.0, 2.0));
	leftLayout->addLayout(createFloatSliderParameterUI("Random Offset (max): ", &m_nSliderRandomOffsetMax, -2.0, 2.0));
	leftLayout->addLayout(createFloatSliderParameterUI("Scale X: ", &m_nSliderScaleX, 0.1, 10.0));
	leftLayout->addLayout(createFloatSliderParameterUI("Scale Y: ", &m_nSliderScaleY, 0.1, 10.0));
	leftLayout->addLayout(createFloatSliderParameterUI("Scale Z: ", &m_nSliderScaleZ, 0.1, 10.0));

	auto *pTexture = new QLabel("Texture:");
	leftLayout->addWidget(pTexture);

	// texture resolution
	m_pTextureResolution = new QComboBox();
	m_pTextureResolution->addItem(tr("128x128"), 128);
    m_pTextureResolution->addItem(tr("256x256"), 256);
    m_pTextureResolution->addItem(tr("512x512"), 512);
    m_pTextureResolution->addItem(tr("1024x1024"), 1024);
    connect(m_pTextureResolution, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxTextureResolution_Changed(int)));
	leftLayout->addWidget(m_pTextureResolution);

	QHBoxLayout *texturesLayout = new QHBoxLayout;

	// m_pPixmapImageOrigin = new QPixmap();
	// m_pPixmapImageHiglighted = new QPixmap();
	m_pImageView = new QLabel();
	m_pImageView->setPixmap(m_pixmapImageHiglighted);
	m_pImageView->setFixedWidth(512);
	m_pImageView->setFixedHeight(512);
	m_pImageView->setScaledContents(true);
	texturesLayout->addWidget(m_pImageView);
	
	m_pTrianlesList = new QListWidget();
	connect(m_pTrianlesList, SIGNAL(itemSelectionChanged()),this, SLOT(triangles_itemSelectionChanged()));
	texturesLayout->addWidget(m_pTrianlesList);

	leftLayout->addLayout(texturesLayout);

	m_pProgress = new QProgressBar(this);
	m_pProgress->setValue(0);
	m_pProgress->setMinimum(0);
	m_pProgress->setMaximum(100);
	leftLayout->addWidget(m_pProgress);

	QHBoxLayout *buttonsLayout = new QHBoxLayout;

	m_pRegenerateButton = new QPushButton(tr("Regenerate"));
	m_pRegenerateButton->setDefault(true);
	connect(m_pRegenerateButton, SIGNAL(clicked()),this, SLOT(regenerateButton_clicked()));
	buttonsLayout->addWidget(m_pRegenerateButton);

	buttonsLayout->addWidget(new QWidget);
	buttonsLayout->addStretch();

	m_pCloseButton = new QPushButton(tr("Close"));
	connect(m_pCloseButton, SIGNAL(clicked()),this, SLOT(close()));
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

	connect(this, &DialogConfigurator::signal_generationComplited, this, &DialogConfigurator::slot_generationComplited);
}

void DialogConfigurator::sliderInt_valuesChanged(int nNewValue) {
	QObject* obj = sender();
	CustomIntSlider *pSlider = dynamic_cast<CustomIntSlider *>(obj);
	if (pSlider == nullptr) {
	 	std::cerr << "Could not cast" << std::endl;
	 	return;
	}
	pSlider->updateValue(nNewValue);
	m_bRegenerateGeometry = true;
	this->regenerateGeometry();
}

void DialogConfigurator::sliderFloat_valuesChanged(int nNewValue) {
	QObject* obj = sender();
	CustomFloatSlider *pSlider = dynamic_cast<CustomFloatSlider *>(obj);
	if (pSlider == nullptr) {
	 	std::cerr << "Could not cast" << std::endl;
	 	return;
	}
	pSlider->updateValue(float(nNewValue) / 100);
	m_bRegenerateGeometry = true;
	this->regenerateGeometry();
}

void DialogConfigurator::comboboxTextureResolution_Changed(int nNewValue) {
	std::cout << "comboboxTextureResolution_Changed " << nNewValue << std::endl;
}

void DialogConfigurator::regenerateButton_clicked() {
	m_bRegenerateGeometry = true;
	this->regenerateGeometry();
}

void DialogConfigurator::createNode() {
	m_sRandomName = "stone_" + QString::number(std::rand() % 10000);

	m_pMesh = Unigine::ObjectMeshDynamic::create();
	// TODO select position by a camera
	m_pMesh->setWorldTransform(translate(Unigine::Math::Vec3(0.0f, 0.0f, 2.0f)));
	m_pMesh->setShowInEditorEnabledRecursive(1);
	m_pMesh->setSaveToWorldEnabledRecursive(1);
	m_pMesh->setName(QString(m_sRandomName).toStdString().c_str());
	QVector<Unigine::NodePtr> pNodes;
	pNodes.push_back(m_pMesh);
	Editor::SelectorNodes *pSelected = Editor::SelectorNodes::createObjectsSelector(pNodes);
	Editor::Selection::setSelector(pSelected);

	// m_pMaterial = Unigine::Material::create();
	auto mesh_base = Unigine::Materials::findMaterial("mesh_base");
	m_pMaterial = mesh_base->inherit();
	m_pMaterial->setParent(mesh_base);
	std::string sMaterialPath = QString(m_sRandomName + ".mat").toStdString();
	m_pMaterial->setName(QString(m_sRandomName).toStdString().c_str());
	m_pMaterial->setPath(sMaterialPath.c_str());
	m_pMaterial->save();

	Unigine::UGUID guid;
	guid.generate();
	// const char *string_id = guid.getFileSystemString();
	std::cout << "Guid: " << guid.get() << std::endl;
	// log_info("Guid: " + QString(guid.get()));

	// Unigine::FileSystem::setGUID(sMaterialPath.c_str(), guid);
	// emit Editor::AssetManager::instance()->added(guid);

	m_pMesh->setMaterial(m_pMaterial, 0);
	
	// MaterialPtr material = mesh->getMaterialInherit(0);
	

	m_pImage = Unigine::Image::create();
	// m_pImage->setName(QString(m_sRandomName + ".png").toStdString().c_str());
	// m_pTexture = Unigine::Texture::create();
	
	// on first start regenerate all
	m_bRegenerateGeometry = true;
    m_bRegenerateTexture = true;
	this->regenerateGeometry();
}

void DialogConfigurator::regenerateGeometry() {
	if (m_bInProgress) {
		m_bWannaUpdate = true;
		return;
	}
	m_bInProgress = true;
	m_bWannaUpdate = false;
	
	// TODO update process
	m_pProgress->setValue(0);
	m_pProgress->setMinimum(0);
	m_pProgress->setMaximum(m_nSliderTrianglesValue);

	TextureStoneGeneratorConfig texConf;
	texConf.setFilepath(m_sFilePath1);
	m_pAsyncRunGenerator->setTextureStoneGeneratorConfig(texConf);

	StoneGeneratorConfig newConf;
	newConf.setEstimatedExpectedTriangles(m_nSliderTrianglesValue);
	newConf.setRadius(m_nSliderRadius);
	newConf.setRandomOffsetMin(m_nSliderRandomOffsetMin);
	newConf.setRandomOffsetMax(m_nSliderRandomOffsetMax);
	newConf.setScaleX(m_nSliderScaleX);
	newConf.setScaleY(m_nSliderScaleY);
	newConf.setScaleZ(m_nSliderScaleZ);
	
	m_pAsyncRunGenerator->setStoneGeneratorConfig(newConf);
	m_pAsyncRunGenerator->setRegenerateGeometry(m_bRegenerateGeometry);
	m_pAsyncRunGenerator->setRegenerateTexture(m_bRegenerateTexture);
	m_bRegenerateGeometry = false;
    m_bRegenerateTexture = false;

	QThreadPool::globalInstance()->start(m_pAsyncRunGenerator);
}

void DialogConfigurator::generationComplited(QString sDone) {
	emit signal_generationComplited(sDone);
}

void DialogConfigurator::slot_generationComplited(QString sDone) {
	Unigine::Log::message("DialogConfigurator::generationComplited start\n");

	if (QThread::currentThread() != QCoreApplication::instance()->thread()) {
		Unigine::Log::error("UnigineEditorPlugin_Python3Scripting::slot_executeRunner Not main thread!!!");
	}
	std::cout << sDone.toStdString() << std::endl;

	m_pMesh->clearVertex();
	m_pMesh->clearIndices(); // here triangles like some one
	m_pMesh->flushIndices();
	m_pMesh->flushVertex();
	auto *pStoneGenerator = m_pAsyncRunGenerator->getStoneGenerator();

	const std::vector<StonePoint *> &vPoints = pStoneGenerator->points();
	for (int i = 0; i < vPoints.size(); i++) {
		m_pMesh->addVertex(Unigine::Math::vec3(
			vPoints[i]->x(),
			vPoints[i]->y(),
			vPoints[i]->z()
		));
		// m_pMesh->addTexCoord(Unigine::Math::vec4(float(std::rand() % 100) / 100, float(std::rand() % 100) / 100, 0, 0));
		// std::cout << "tx coord uv: " <<
		// 	vPoints[i]->getTextureCoordinateU()
		// 	<< " " << 
		// 	vPoints[i]->getTextureCoordinateV()
		// 	<< std::endl;
		m_pMesh->addTexCoord(Unigine::Math::vec4(
			vPoints[i]->getTextureCoordinateU(),
			vPoints[i]->getTextureCoordinateV(),
			0,
			0
		));
	}

	const std::vector<StoneTriangle *> &vTriangles = pStoneGenerator->triangles();
	m_pMesh->addTriangles(vTriangles.size());
	m_pMesh->allocateIndices(vTriangles.size()*3);
	for (int i = 0; i < vTriangles.size(); i++) {
		StoneTriangle *pTriangle = vTriangles[i];
		m_pMesh->setIndex(i*3 + 0, pTriangle->p1()->getIndex());
		m_pMesh->setIndex(i*3 + 1, pTriangle->p2()->getIndex());
		m_pMesh->setIndex(i*3 + 2, pTriangle->p3()->getIndex());
	}

	// // optimize vertex and index buffers, if necessary
	// m_pMesh->updateIndices();

	// calculate a mesh bounding box for editor I guess
	m_pMesh->updateBounds();

	// 
	m_pMesh->updateTangents();

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
	// Unigine::UGUID guid;
	// guid.generate();
	// const char *string_id = guid.getFileSystemString();
	// log_info("Guid: " + QString(guid.get()));
	// Unigine::FileSystem::setGUID("box_24567.mesh", guid);
	// emit Editor::AssetManager::instance()->added(guid);

	// TextureStoneGeneratorConfig texConf;
	// texConf.setFilepath(m_sFilePath1);

	// TextureStoneGenerator tex;
	// tex.generate(texConf);
	if (m_pAsyncRunGenerator->getRegenerateTexture()) {
		m_pImage->clear();
		m_pImage->load(m_sFilePath1.toStdString().c_str());
		m_pixmapImageOrigin.load(m_sFilePath1);
		if (m_pImage->isLoaded()) {
			std::cout << "Image loaded" << std::endl;
			// add to button - save texture
			m_pImage->save(QString(m_sRandomName + ".png").toStdString().c_str());
			// m_pImageView->setScaledContents(true);
		}
		// m_pTexture->clear();
		// m_pTexture->setImage(m_pImage);

		int num = m_pMaterial->findTexture("albedo");
		if (num != -1) {
			std::cout << "Set albedo" << std::endl;
			m_pMaterial->setTexturePath(num, QString(m_sRandomName + ".png").toStdString().c_str());

			// m_pMaterial->setTextureImage(num, m_pImage);
		}
	}

	// reload preview texture image
	
	this->updateTextureImageView("");

	// m_pMesh->setMaterial(m_pMaterial, 0);
	// add to button - save mesh
	// m_pMesh->saveMesh(QString(m_sRandomName + ".mesh").toStdString().c_str());

	Unigine::Log::message("DialogConfigurator::generationComplited end\n");
	m_bInProgress = false;
	if (m_bWannaUpdate) {
		Unigine::Log::message("regenerate geometry again\n");
		this->regenerateGeometry();
	}
}

void DialogConfigurator::triangles_itemSelectionChanged() {
	std::cout << "triangles_itemSelectionChanged" << std::endl;
	QList<QListWidgetItem *> listItems = m_pTrianlesList->selectedItems();

	// auto *pStoneGenerator = m_pAsyncRunGenerator->getStoneGenerator();
	QStringList highllightTriangles;
	for (int i = 0; i < listItems.size(); i++) {
		QListWidgetItem *pItem = listItems.at(i);
		std::cout << pItem->text().toStdString() << std::endl;
		highllightTriangles.append(pItem->text());
		updateTextureImageView(pItem->text());
		return;
	}
}

int DialogConfigurator::normalizeTextureCoordinates(int nWidth, float nVal) {
	int nRet = nWidth * nVal;
	if (nRet > nWidth) {
		nRet = nWidth;
	}
	if (nRet < 0) {
		nRet = 0;
	}
	return nRet;
}

void DialogConfigurator::updateTextureImageView(const QString &sHeighlightTriangle) {
	// reload preview texture image
	m_pixmapImageHiglighted = m_pixmapImageOrigin;

	auto *pStoneGenerator = m_pAsyncRunGenerator->getStoneGenerator();
	const std::vector<StoneTriangle *> &vTriangles = pStoneGenerator->triangles();

	// print uv map
	QPainter painter(&m_pixmapImageHiglighted);
	QBrush brush( 0xffff00 /*Qt::white*/, Qt::SolidPattern);
	QPen pen(0xffff00 /*Qt::white*/);
	painter.setPen(pen);
	painter.setBrush(brush);
	int nImageHeight = m_pixmapImageHiglighted.height();
	int nImageWidth = m_pixmapImageHiglighted.width();
	if (sHeighlightTriangle == "") {
		m_pTrianlesList->clear();
	}
	bool bSaveImage = false;
	for (int i = 0; i < vTriangles.size(); i++) {
		StoneTriangle *pTriangle = vTriangles[i];
		int nX0 = normalizeTextureCoordinates(nImageHeight, pTriangle->p1()->getTextureCoordinateU());
		int nY0 = normalizeTextureCoordinates(nImageWidth, pTriangle->p1()->getTextureCoordinateV());
		int nX1 = normalizeTextureCoordinates(nImageHeight, pTriangle->p2()->getTextureCoordinateU());
		int nY1 = normalizeTextureCoordinates(nImageWidth, pTriangle->p2()->getTextureCoordinateV());
		int nX2 = normalizeTextureCoordinates(nImageHeight, pTriangle->p3()->getTextureCoordinateU());
		int nY2 = normalizeTextureCoordinates(nImageWidth, pTriangle->p3()->getTextureCoordinateV());

		painter.drawLine(nX0, nY0, nX1, nY1);
		painter.drawLine(nX1, nY1, nX2, nY2);
		painter.drawLine(nX2, nY2, nX0, nY0);
		QString sTrianle = 
			"(" + QString::number(nX0) + "," + QString::number(nY0) + ")"
			+ "(" + QString::number(nX1) + "," + QString::number(nY1) + ")"
			+ "(" + QString::number(nX2) + "," + QString::number(nY2) + ")";
		if (sHeighlightTriangle == "") {
			m_pTrianlesList->addItem(sTrianle);
		} else {
			if (sTrianle == sHeighlightTriangle) {
				QPainterPath path;
				// Set pen to this point.
				path.moveTo (nX0, nY0);
				// Draw line from pen point to this point.
				path.lineTo (nX1, nY1);
				// path.moveTo (endPointX1, endPointY1); // <- no need to move
				path.lineTo (nX2, nY2);
				// path.moveTo (endPointX2,   endPointY2); // <- no need to move
				path.lineTo (nX0, nY0);
				// painter.setPen (Qt :: NoPen);
				painter.fillPath (path, QBrush (QColor ("blue")));
				// TODO draw higlighted triangul
				bSaveImage = true;
			}
		}
		
	}
	m_pImageView->setPixmap(m_pixmapImageHiglighted);
	if (bSaveImage) {
		m_pixmapImageHiglighted.save(m_sFilePathHighlighted);
		m_pImage->load(m_sFilePathHighlighted.toStdString().c_str());
		if (m_pImage->isLoaded()) {
			std::cout << "Image loaded" << std::endl;
			// add to button - save texture
			// m_pImage->save(QString(m_sRandomName + ".png").toStdString().c_str());

			int num = m_pMaterial->findTexture("albedo");
			if (num != -1) {
				std::cout << "Set albedo" << std::endl;
				// set runtime
				m_pMaterial->setTextureImage(num, m_pImage);

				// m_pMaterial->setTextureImage(num, m_pImage);
			}
		}
	} else {
		m_pImage->load(m_sFilePath1.toStdString().c_str());
		if (m_pImage->isLoaded()) {
			std::cout << "Image loaded" << std::endl;
			// add to button - save texture
			// m_pImage->save(QString(m_sRandomName + ".png").toStdString().c_str());
			// m_pImageView->setScaledContents(true);
			int num = m_pMaterial->findTexture("albedo");
			if (num != -1) {
				std::cout << "Set albedo (reset picture)" << std::endl;
				// NOT work here
				m_pMaterial->setTexturePath(num, QString(m_sRandomName + ".png").toStdString().c_str());

				// m_pMaterial->setTextureImage(num, m_pImage);
			}
		}
		// m_pTexture->clear();
		// m_pTexture->setImage(m_pImage);
	}

}

QHBoxLayout *DialogConfigurator::createIntSliderParameterUI(QString sLabel, int *nValue, int nMin, int nMax) {
	CustomIntSlider *pSlider = new CustomIntSlider(Qt::Horizontal);

	QHBoxLayout *pLayout = new QHBoxLayout();

	QLabel *pLabel = new QLabel(sLabel);
	pLabel->setFixedWidth(m_nLabelSize);
	pLayout->addWidget(pLabel);

	QLabel *pLabelValue = new QLabel("(" + QString::number(*nValue) + ")");
	pLabelValue->setFixedWidth(m_nLabelValueSize);
	pSlider->setLabelValue(pLabelValue);
	pLayout->addWidget(pLabelValue);
    pSlider->setRange(nMin, nMax);
	pSlider->setValue(*nValue);
    pSlider->setPoiterValue(nValue);
	connect(pSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderInt_valuesChanged(int)));
	pLayout->addWidget(pSlider);
	
	return pLayout;
}

QHBoxLayout *DialogConfigurator::createFloatSliderParameterUI(QString sLabel, float *nValue, float nMin, float nMax) {
	CustomFloatSlider *pSlider = new CustomFloatSlider(Qt::Horizontal);

	QHBoxLayout *pLayout = new QHBoxLayout();

	QLabel *pLabel = new QLabel(sLabel);
	pLabel->setFixedWidth(m_nLabelSize);
	pLayout->addWidget(pLabel);

	QLabel *pLabelValue = new QLabel("(" + QString::number(*nValue) + ")");
	pLabelValue->setFixedWidth(m_nLabelValueSize);
	pSlider->setLabelValue(pLabelValue);
	pLayout->addWidget(pLabelValue);
    pSlider->setRange(nMin*100, nMax*100);
	pSlider->setValue((*nValue)*100);
    pSlider->setPoiterValue(nValue);

	connect(pSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderFloat_valuesChanged(int)));
	pLayout->addWidget(pSlider);
	
	return pLayout;
}