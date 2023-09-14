#pragma once

#include <QDialog>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QListView>
#include <QStringList>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QComboBox>
#include <QSlider>
#include <QProgressBar>
#include <QTemporaryDir>
#include <QListWidget>

#include <UnigineNode.h>
#include <UnigineMaterials.h>
#include <UnigineTextures.h>
#include <UnigineObjects.h>
#include <editor/UnigineSelector.h>
#include <editor/UnigineSelection.h>

#include "DialogConfigurator.h"
#include "AsyncRunGenerator.h"
#include "StoneGenerator.h"

#include "TextureStoneGenerator.h"
#include "ISignalGun.h"
#include "IDialogConfigurator.h"

class DialogConfigurator : public QDialog, public ISignalGun, public IDialogConfigurator {
    Q_OBJECT

    public:
        DialogConfigurator(QWidget *parent);
        void setGenerateMesh(bool bGenerateMesh);
        void setGenerateMaterial(bool bGenerateMaterial);
        void createNode();
        void regenerateGeometry();

        // ISignalGun
        virtual void generationComplited(QString sDone) override;

        // IDialogConfigurator
        virtual void updateValueFloat(IDialogConfiguratorUpdatedValue nIdValue, float nValue) override;
        virtual void updateValueInt(IDialogConfiguratorUpdatedValue nIdValue, int nValue) override;
        virtual int getLabelSize() override;
        virtual int getLabelValueSize() override;

    Q_SIGNALS:
        void signal_generationComplited(QString sDone);


    private slots:
        void regenerateButton_clicked();
        void click_saveMesh();

        void comboboxTextureResolution_Changed(int nNewValue);
        void comboboxBasicGeometry_Changed(int nNewValue);

        void slot_generationComplited(QString sDone);

        void triangles_itemSelectionChanged();

    private:

        int normalizeTextureCoordinates(int nWidth, float nVal);
        void updateTextureImageView(const QString &sHeighlightTriangle = "");

        void addPointOfTriangle(int nIndex, StoneGeneratorPoint *p1, StoneGeneratorTexturePoint &t1, int nSurface);
        int showNormal(int nLastIndex, int nIndex, StoneGeneratorPoint *p1, int nSurface);

        int m_nStoneIdName;

        QString m_sRandomName;
        QString m_sFullPathNode;
        QString m_sFullPathProp;
        QComboBox *m_pBasicGemometry;

        QLabel *m_pTextureLabel;
        QHBoxLayout *m_pTexturesLayout;
        QLabel *m_pImageView;
        QListWidget *m_pTrianlesList;
        QPixmap m_pixmapImageOrigin;
        QPixmap m_pixmapImageHiglighted;

        QPushButton *m_pRegenerateButton;
        QPushButton *m_pSaveMeshButton;
        QPushButton *m_pCloseButton;

        std::vector<StoneGeneratorBasicGeometry *> m_vBasicGeometries;
        StoneGeneratorBasicGeomery m_nBasicGeometry;

        QComboBox *m_pTextureResolution;

        StoneGeneratorConfig m_nextConf;

        QProgressBar *m_pProgress;
        AsyncRunGenerator *m_pAsyncRunGenerator;
        Unigine::ObjectMeshDynamicPtr m_pDynamicMesh;
        Unigine::MeshPtr m_pMeshTemp;
        Unigine::MaterialPtr m_pMaterial;
        Unigine::ImagePtr m_pImage;

        QTemporaryDir m_temporaryDir;
        QString m_sFilePath1;
        QString m_sFilePathHighlighted;

        // Unigine::TexturePtr m_pTexture;
        bool m_bWannaUpdate;
        bool m_bInProgress;

        bool m_bGenerateMesh;
        bool m_bGenerateMaterial;
};

