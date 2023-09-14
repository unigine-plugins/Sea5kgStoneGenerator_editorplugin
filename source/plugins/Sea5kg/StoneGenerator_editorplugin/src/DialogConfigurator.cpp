#include <QtGui>
#include <iostream>

#include "DialogConfigurator.h"
#include "StoneGeneratorBasicGeometryCube.h"
#include "StoneGeneratorBasicGeometrySphere.h"

#include "DialogConfiguratorParameterSliderFloat.h"
#include "DialogConfiguratorParameterSliderInt.h"

#include <UnigineFileSystem.h>
#include <UnigineEditor.h>
#include <UnigineWorld.h>
#include <QThreadPool>
#include <QPixmap>

DialogConfigurator::DialogConfigurator(
    QWidget *parent
) : QDialog(parent) {


    m_vBasicGeometries.push_back(new StoneGeneratorBasicSphere());
    m_vBasicGeometries.push_back(new StoneGeneratorBasicCube());

    m_bWannaUpdate = false;
    m_bInProgress = false;
    m_sFilePath1 = m_temporaryDir.filePath("stone.png");
    m_sFilePathHighlighted = m_temporaryDir.filePath("stone_high.png");

    m_nBasicGeometry = StoneGeneratorBasicGeomery::SPHERE;
    m_nStoneIdName = 0;

    m_bGenerateMesh = true;
    m_bGenerateMaterial = true;

    // m_nBasicGeometry = 1;
    // m_nPointsOfAttraction = 0;
    // m_nSliderSurfaceDistortion = 0.0f;
    // m_nSliderTrianglesValue = 250;

    m_pAsyncRunGenerator = new AsyncRunGenerator(this);
    m_pAsyncRunGenerator->setAutoDelete(false);

    QVBoxLayout *verticalLayout = new QVBoxLayout;

    auto *pGeometry = new QLabel("Geometry:");
    verticalLayout->addWidget(pGeometry);

    m_pBasicGemometry = new QComboBox();
    m_pBasicGemometry->addItem(tr("Sphere"), 1);
    m_pBasicGemometry->addItem(tr("Cube"), 2);
    connect(m_pBasicGemometry, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxBasicGeometry_Changed(int)));
    verticalLayout->addWidget(m_pBasicGemometry);

    verticalLayout->addLayout(new DialogConfiguratorParameterSliderInt(
        this, IDialogConfiguratorUpdatedValue::EXPECTED_TRIANGLES,
        "Expected triangles: ", m_nextConf.getEstimatedExpectedTriangles(),
        100, 15000
    ));
    verticalLayout->addLayout(new DialogConfiguratorParameterSliderFloat(
        this, IDialogConfiguratorUpdatedValue::RADIUS,
        "Radius: ", m_nextConf.getRadius(),
        m_nextConf.getScaleMinAny(), m_nextConf.getScaleMaxAny()
    ));
    verticalLayout->addLayout(new DialogConfiguratorParameterSliderInt(
        this, IDialogConfiguratorUpdatedValue::POINDS_OF_ATTRACTION,
        "Attraction Points: ", m_nextConf.getPointsOfAttraction(),
        0, 25
    ));
    verticalLayout->addLayout(new DialogConfiguratorParameterSliderFloat(
        this, IDialogConfiguratorUpdatedValue::STRONG_OF_ATTRACTION,
        "Attraction Strong: ", m_nextConf.getStrongOfAttraction(),
        1.0, 50.0
    ));
    verticalLayout->addLayout(new DialogConfiguratorParameterSliderFloat(
        this, IDialogConfiguratorUpdatedValue::SURFACE_DISTORTION,
        "Surface distortion: ", m_nextConf.getSurfaceDistortion(),
        0.0, 2.0
    ));
    verticalLayout->addLayout(new DialogConfiguratorParameterSliderFloat(
        this, IDialogConfiguratorUpdatedValue::SCALE_X,
        "Scale X: ", m_nextConf.getScaleX(),
        m_nextConf.getScaleMinAny(), m_nextConf.getScaleMaxAny()
    ));
    verticalLayout->addLayout(new DialogConfiguratorParameterSliderFloat(
        this, IDialogConfiguratorUpdatedValue::SCALE_Y,
        "Scale Y: ", m_nextConf.getScaleY(),
        m_nextConf.getScaleMinAny(), m_nextConf.getScaleMaxAny()
    ));
    verticalLayout->addLayout(new DialogConfiguratorParameterSliderFloat(
        this, IDialogConfiguratorUpdatedValue::SCALE_Z,
        "Scale Z: ", m_nextConf.getScaleZ(),
        m_nextConf.getScaleMinAny(), m_nextConf.getScaleMaxAny()
    ));

    m_pTextureLabel = new QLabel("Texture:");
    verticalLayout->addWidget(m_pTextureLabel);

    // texture resolution
    // m_pTextureResolution = new QComboBox();
    // m_pTextureResolution->addItem(tr("128x128"), 128);
    // m_pTextureResolution->addItem(tr("256x256"), 256);
    // m_pTextureResolution->addItem(tr("512x512"), 512);
    // m_pTextureResolution->addItem(tr("1024x1024"), 1024);
    // connect(m_pTextureResolution, SIGNAL(currentIndexChanged(int)), this, SLOT(comboboxTextureResolution_Changed(int)));
    // verticalLayout->addWidget(m_pTextureResolution);

    m_pTexturesLayout = new QHBoxLayout();

    // m_pPixmapImageOrigin = new QPixmap();
    // m_pPixmapImageHiglighted = new QPixmap();
    m_pImageView = new QLabel();
    m_pImageView->setPixmap(m_pixmapImageHiglighted);
    m_pImageView->setFixedWidth(512);
    m_pImageView->setFixedHeight(512);
    m_pImageView->setScaledContents(true);
    m_pTexturesLayout->addWidget(m_pImageView);

    m_pTrianlesList = new QListWidget();
    connect(m_pTrianlesList, SIGNAL(itemSelectionChanged()),this, SLOT(triangles_itemSelectionChanged()));
    m_pTexturesLayout->addWidget(m_pTrianlesList);

    verticalLayout->addLayout(m_pTexturesLayout);

    m_pProgress = new QProgressBar(this);
    m_pProgress->setValue(0);
    m_pProgress->setMinimum(0);
    m_pProgress->setMaximum(100);
    verticalLayout->addWidget(m_pProgress);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;

    m_pRegenerateButton = new QPushButton(tr("Regenerate"));
    m_pRegenerateButton->setDefault(true);
    connect(m_pRegenerateButton, SIGNAL(clicked()),this, SLOT(regenerateButton_clicked()));
    buttonsLayout->addWidget(m_pRegenerateButton);

    m_pSaveMeshButton = new QPushButton(tr("Save Mesh"));
    connect(m_pSaveMeshButton, SIGNAL(clicked()),this, SLOT(click_saveMesh()));
    buttonsLayout->addWidget(m_pSaveMeshButton);

    buttonsLayout->addWidget(new QWidget);
    buttonsLayout->addStretch();

    m_pCloseButton = new QPushButton(tr("Close"));
    connect(m_pCloseButton, SIGNAL(clicked()),this, SLOT(close()));
    buttonsLayout->addWidget(m_pCloseButton);
    verticalLayout->addLayout(buttonsLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(verticalLayout);
    // mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);
    // setLayout(verticalLayout);
    setWindowTitle(tr("Sea5kg / Stone Generator - Configurator"));
    setFixedWidth(800);
    // setFixedHeight(sizeHint().height());

    connect(this, &DialogConfigurator::signal_generationComplited, this, &DialogConfigurator::slot_generationComplited);
}

void DialogConfigurator::setGenerateMesh(bool bGenerateMesh) {
    m_bGenerateMesh = bGenerateMesh;
}

void DialogConfigurator::setGenerateMaterial(bool bGenerateMaterial) {
    m_bGenerateMaterial = bGenerateMaterial;
    m_pTextureLabel->setVisible(m_bGenerateMaterial);
    // m_pTextureResolution->setVisible(m_bGenerateMaterial);
    m_pImageView->setVisible(m_bGenerateMaterial);
    m_pTrianlesList->setVisible(m_bGenerateMaterial);
}

void DialogConfigurator::comboboxTextureResolution_Changed(int nNewValue) {
    std::cout << "comboboxTextureResolution_Changed " << nNewValue << std::endl;
}

void DialogConfigurator::comboboxBasicGeometry_Changed(int nNewValue) {
    std::cout << "comboboxBasicGeometry_Changed " << nNewValue << std::endl;
    m_nBasicGeometry = (StoneGeneratorBasicGeomery)nNewValue;
    m_nextConf.setRegenerateGeometry(true);
    this->regenerateGeometry();
}

void DialogConfigurator::click_saveMesh() {
    // add to button - save mesh
    m_pDynamicMesh->saveMesh(QString(m_sRandomName + ".mesh").toStdString().c_str());
}

void DialogConfigurator::regenerateButton_clicked() {
    m_nextConf.setRegenerateGeometry(true);
    this->regenerateGeometry();
}

void DialogConfigurator::createNode() {
    bool bUniqNameGenerated = false;
    while (!bUniqNameGenerated) {
        bUniqNameGenerated = true;
        m_nStoneIdName++;
        m_sRandomName = "stone_" + QString::number(m_nStoneIdName).rightJustified(6, '0');
        m_sFullPathNode = "Sea5kgStoneGenerator/" + m_sRandomName + ".node";
        m_sFullPathProp = "Sea5kgStoneGenerator/" + m_sRandomName + ".prop";
        if (UnigineEditor::AssetManager::isAsset(m_sFullPathNode.toStdString().c_str())) {
            bUniqNameGenerated = false;
        }
    }

    m_pDynamicMesh = Unigine::ObjectMeshDynamic::create();

    // find position by a camera
    auto nViewportWindowId = UnigineEditor::ViewportManager::getActiveViewportWindow();
    Unigine::PlayerPtr pPlayer = UnigineEditor::ViewportManager::getViewportWindowPlayer(nViewportWindowId);
    auto pos = pPlayer->getWorldPosition();
    auto rot = pPlayer->getWorldRotation();
    // m_pDynamicMesh->setWorldTransform(translate(Unigine::Math::Vec3(0.0f, 0.0f, 2.0f)));
    // m_pDynamicMesh->setWorldTransform(pPlayer->getTransform() * transform);
    // m_pDynamicMesh->setWorldTransform(pPlayer->getTransform());

    auto floatDirection = pPlayer->getViewDirection();
    Unigine::Math::Vec3 direction = {
        floatDirection.x,
        floatDirection.y,
        floatDirection.z
    };
    direction *= 10.0f;
    m_pDynamicMesh->setWorldPosition(pPlayer->getWorldPosition() + direction);
    m_pDynamicMesh->setWorldRotation(pPlayer->getWorldRotation());

    // Unigine::Math::Mat4 transform = pPlayer->getTransform();
    // transform.setTranslate(direction);
    // m_pDynamicMesh->setWorldTransform(pPlayer->getTransform() * transform);

    m_pDynamicMesh->setShowInEditorEnabledRecursive(true);
    m_pDynamicMesh->setSaveToWorldEnabledRecursive(true);
    m_pDynamicMesh->setName(QString(m_sRandomName).toStdString().c_str());
    Unigine::Vector<Unigine::NodePtr> pNodes;
    pNodes.push_back(m_pDynamicMesh);
    UnigineEditor::SelectorNodes *pSelected = UnigineEditor::SelectorNodes::createObjectsSelector(pNodes);
    UnigineEditor::Selection::setSelector(pSelected);

    // Unigine::World::saveNode(m_sFullPathNode.toStdString().c_str(), m_pDynamicMesh);

    // Unigine::PropertyPtr pProperty = Unigine::Properties::findProperty("node_base")->inherit("myproperty");
    // pProperty->setPath(m_sFullPathProp.toStdString().c_str());
    // m_pDynamicMesh->addProperty(pProperty);
    // pProperty->save();


    m_nextConf.setRegenerateGeometry(true);
    m_nextConf.setRegenerateTexture(false);

    if (m_bGenerateMaterial) {
        auto mesh_base = Unigine::Materials::findManualMaterial("Unigine::mesh_base");
        std::string sMaterialPath = QString(m_sRandomName + ".mat").toStdString();
        m_pMaterial = mesh_base->inherit();
        m_pMaterial->setParent(mesh_base);
        m_pMaterial->createMaterialFile(sMaterialPath.c_str());

        m_pMaterial->save();

        m_pDynamicMesh->setMaterial(m_pMaterial, 0);

        m_pImage = Unigine::Image::create();

        // on first start regenerate all
        m_nextConf.setRegenerateTexture(true);
    }

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
    m_pProgress->setMaximum(100);

    TextureStoneGeneratorConfig texConf;
    texConf.setFilepath(m_sFilePath1);
    m_pAsyncRunGenerator->setTextureStoneGeneratorConfig(texConf);

    m_nextConf.setBasicGeometry(m_nBasicGeometry);

    m_pAsyncRunGenerator->setStoneGeneratorConfig(m_nextConf);
    m_nextConf.setRegenerateGeometry(false);
    m_nextConf.setRegenerateTexture(false);

    QThreadPool::globalInstance()->start(m_pAsyncRunGenerator);
}

// IDialogConfigurator
void DialogConfigurator::updateValueFloat(IDialogConfiguratorUpdatedValue nIdValue, float nValue) {
    switch (nIdValue) {
        case IDialogConfiguratorUpdatedValue::RADIUS:
            m_nextConf.setRadius(nValue);
            break;
        case IDialogConfiguratorUpdatedValue::STRONG_OF_ATTRACTION:
            m_nextConf.setStrongOfAttraction(nValue);
            break;
        case IDialogConfiguratorUpdatedValue::SURFACE_DISTORTION:
            m_nextConf.setSurfaceDistortion(nValue);
            break;
        case IDialogConfiguratorUpdatedValue::SCALE_X:
            m_nextConf.setScaleX(nValue);
            break;
        case IDialogConfiguratorUpdatedValue::SCALE_Y:
            m_nextConf.setScaleY(nValue);
            break;
        case IDialogConfiguratorUpdatedValue::SCALE_Z:
            m_nextConf.setScaleZ(nValue);
            break;
        default:
            break; // nothing
    };
    m_nextConf.setRegenerateGeometry(true);
    this->regenerateGeometry();
};

void DialogConfigurator::updateValueInt(IDialogConfiguratorUpdatedValue nIdValue, int nValue) {
    switch (nIdValue) {
        case IDialogConfiguratorUpdatedValue::POINDS_OF_ATTRACTION:
            m_nextConf.setPointsOfAttraction(nValue);
            break;
        case IDialogConfiguratorUpdatedValue::EXPECTED_TRIANGLES:
            m_nextConf.setEstimatedExpectedTriangles(nValue);
            break;
        default:
            break; // nothing
    };
    m_nextConf.setRegenerateGeometry(true);
    this->regenerateGeometry();
}


int DialogConfigurator::getLabelSize() {
    return 130;
}

int DialogConfigurator::getLabelValueSize() {
    return 50;
}

void DialogConfigurator::generationComplited(QString sDone) {
    emit signal_generationComplited(sDone);
}

int DialogConfigurator::showNormal(int nLastIndex, int nIndex, StoneGeneratorPoint *p1, int nSurface) {

    Unigine::Math::vec3 vp0(
        p1->x(),
        p1->y(),
        p1->z()
    );

    Unigine::Math::vec3 np(p1->getNormalX(), p1->getNormalY(), p1->getNormalZ());
    // np = np.normalize();

    Unigine::Math::vec3 np0( 1.0f * 0.0f,  1.0f * np.z, -1.0f * np.x);
    Unigine::Math::vec3 np1( 1.0f * 0.0f, -1.0f * np.z,  1.0f * np.x);
    Unigine::Math::vec3 np2( 1.0f * np.y, -1.0f * np.x,  1.0f * 0.0f);
    Unigine::Math::vec3 np3(-1.0f * np.y,  1.0f * np.x,  1.0f * 0.0f);
    Unigine::Math::vec3 np4( 1.0f * np.z,  1.0f * 0.0f, -1.0f * np.x);
    Unigine::Math::vec3 np5(-1.0f * np.z,  1.0f * 0.0f,  1.0f * np.x);

    // Unigine::Math::vec3 vp1 = ((np0 + np3) / 2.0).normalize() * 0.1 + vp0;
    // Unigine::Math::vec3 vp2 = ((np1 + np4) / 2.0).normalize() * 0.1 + vp0;
    // Unigine::Math::vec3 vp3 = ((np2 + np5) / 2.0).normalize() * 0.1 + vp0;

    Unigine::Math::vec3 vp1 = np0.normalize() * 0.1 + np + vp0;
    Unigine::Math::vec3 vp2 = np2.normalize() * 0.1 + np + vp0;
    Unigine::Math::vec3 vp3 = np4.normalize() * 0.1 + np + vp0;

    std::vector<Unigine::Math::vec3> vPoints;

    // t1
    vPoints.push_back(vp0);
    vPoints.push_back(vp2);
    vPoints.push_back(vp1);

    vPoints.push_back(vp0);
    vPoints.push_back(vp3);
    vPoints.push_back(vp2);

    vPoints.push_back(vp0);
    vPoints.push_back(vp1);
    vPoints.push_back(vp3);

    vPoints.push_back(vp1);
    vPoints.push_back(vp2);
    vPoints.push_back(vp3);

    for (int i = 0; i < vPoints.size(); i++) {
        m_pMeshTemp->addVertex(vPoints[i], nSurface);
        m_pMeshTemp->addNormal(Unigine::Math::vec3(0.0, 0.0, 0.0), nSurface);
        m_pMeshTemp->addIndex(nLastIndex, nSurface);
        nLastIndex++;
    }
    return nLastIndex;
}

void DialogConfigurator::addPointOfTriangle(int nIndex, StoneGeneratorPoint *p1, StoneGeneratorTexturePoint &t1, int nSurface) {
    m_pMeshTemp->addVertex(Unigine::Math::vec3(
        p1->x(),
        p1->y(),
        p1->z()
    ), nSurface);
    m_pMeshTemp->addTexCoord0(Unigine::Math::vec2(
        t1.x(),
        t1.y()
    ), nSurface);
    // m_pMeshTemp->addColor(Unigine::Math::vec4(0,0,0,255), nSurface);
    Unigine::Math::vec3 nr(
        p1->getNormalX(),
        p1->getNormalY(),
        p1->getNormalZ()
    );
    m_pMeshTemp->addNormal(nr, nSurface);
    // Unigine::Math::quat t(
    //     p1->getTangentX(),
    //     p1->getTangentY(),
    //     p1->getTangentZ(),
    //     p1->getTangentW()
    // );
    // m_pMeshTemp->addTangent(t, nSurface);
    m_pMeshTemp->addIndex(nIndex, nSurface);
}

void DialogConfigurator::slot_generationComplited(QString sDone) {
    Unigine::Log::message("DialogConfigurator::generationComplited start\n");

    if (QThread::currentThread() != QCoreApplication::instance()->thread()) {
        Unigine::Log::error("UnigineEditorPlugin_Python3Scripting::slot_executeRunner Not main thread!!!");
    }
    std::cout << sDone.toStdString() << std::endl;

    m_pDynamicMesh->clearVertex();
    m_pDynamicMesh->clearIndices(); // here triangles like some one
    m_pDynamicMesh->flushIndices();
    m_pDynamicMesh->flushVertex();
    auto *pStoneGenerator = m_pAsyncRunGenerator->getStoneGenerator();
    const StoneGeneratorConfig &conf = m_pAsyncRunGenerator->getConf();

    const std::vector<StoneGeneratorTriangle *> &vTriangles = pStoneGenerator->triangles();
    m_pMeshTemp = Unigine::Mesh::create();
    // int nSurface = m_pMeshTemp->addEmptySurface("0", vTriangles.size()*3, vTriangles.size()*3);
    int nSurface = m_pMeshTemp->addSurface("0");
    // m_pDynamicMesh->addTriangles(vTriangles.size());
    // m_pDynamicMesh->allocateIndices(vTriangles.size()*3);
    std::cout << "Got triangles: " << vTriangles.size() << std::endl;
    int nLastIndex = 0;
    for (int i = 0; i < vTriangles.size(); i++) {
        StoneGeneratorTriangle *pTriangle = vTriangles[i];
        this->addPointOfTriangle(i*3 + 0, pTriangle->p1(), pTriangle->t1(), nSurface);
        this->addPointOfTriangle(i*3 + 1, pTriangle->p2(), pTriangle->t2(), nSurface);
        this->addPointOfTriangle(i*3 + 2, pTriangle->p3(), pTriangle->t3(), nSurface);
        nLastIndex = i*3 + 2;
    }

    // show normals
    if (conf.getShowNormales()) {
        nLastIndex = nLastIndex + 1;
        const std::vector<StoneGeneratorPoint *> &vPoints = pStoneGenerator->points();
        for (int i = 0; i < vPoints.size(); i++) {
            StoneGeneratorPoint *p1 = vPoints[i];
            nLastIndex = this->showNormal(nLastIndex, i, vPoints[i], nSurface);
        }
    }

    // m_pMeshTemp->save("tmp.mesh");

    m_pMeshTemp->createTangents(); // without nice


    // // optimize vertex and index buffers, if necessary
    Unigine::MaterialPtr pPrevMeterial = m_pDynamicMesh->getMaterial(0);

    m_pDynamicMesh->setMesh(m_pMeshTemp);
    // return material
    m_pDynamicMesh->setMaterial(pPrevMeterial, 0);

    m_pDynamicMesh->flushIndices();
    m_pDynamicMesh->flushVertex();

    // m_pDynamicMesh->updateIndices();
    // calculate a mesh bounding box for editor I guess
    m_pDynamicMesh->updateBounds();

    // lighting
    // m_pDynamicMesh->updateTangents();

    if (m_pAsyncRunGenerator->getConf().getRegenerateTexture()) {
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
        // m_pMaterial->fl
    }

    if (m_bGenerateMaterial) {
        // reload preview texture image
        this->updateTextureImageView("");
    }

    Unigine::Log::message("DialogConfigurator::generationComplited end\n");
    m_bInProgress = false;
    if (m_bWannaUpdate) {
        Unigine::Log::message("regenerate geometry again\n");
        this->regenerateGeometry();
    }
    m_pMeshTemp = nullptr;

    Unigine::World::saveNode(m_sFullPathNode.toStdString().c_str(), m_pDynamicMesh);
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
    const std::vector<StoneGeneratorTriangle *> &vTriangles = pStoneGenerator->triangles();

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
        StoneGeneratorTriangle *pTriangle = vTriangles[i];
        int nX0 = normalizeTextureCoordinates(nImageHeight, pTriangle->t1().x());
        int nY0 = normalizeTextureCoordinates(nImageWidth,  pTriangle->t1().y());
        int nX1 = normalizeTextureCoordinates(nImageHeight, pTriangle->t2().x());
        int nY1 = normalizeTextureCoordinates(nImageWidth,  pTriangle->t2().y());
        int nX2 = normalizeTextureCoordinates(nImageHeight, pTriangle->t3().x());
        int nY2 = normalizeTextureCoordinates(nImageWidth,  pTriangle->t3().y());

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
