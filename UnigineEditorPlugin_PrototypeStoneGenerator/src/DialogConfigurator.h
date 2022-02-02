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
#include <editor/Selector.h>
#include <editor/Selection.h>

#include "DialogConfigurator.h"
#include "AsyncRunGenerator.h"
#include "StoneGenerator.h"
#include "TextureStoneGenerator.h"
#include "ISignalGun.h"

class CustomIntSlider : public QSlider {
    public:
        CustomIntSlider(Qt::Orientation orientation) : QSlider(orientation) {};
        void setPoiterValue(int *pValue) { m_pValue = pValue; };
        void updateValue(int nValue) {
            *m_pValue = nValue;
            m_pLabelValue->setText("(" + QString::number(nValue) + ")");
        };
        
        void setLabelValue(QLabel *pLabelValue) { m_pLabelValue = pLabelValue; };
    private:
        QLabel *m_pLabelValue;
        int *m_pValue;
};

class CustomFloatSlider : public QSlider {
    public:
        CustomFloatSlider(Qt::Orientation orientation) : QSlider(orientation) {};
        void setPoiterValue(float *pValue) { m_pValue = pValue; };
        void updateValue(float nValue) {
            *m_pValue = nValue;
            m_pLabelValue->setText("(" + QString::number(nValue) + ")");
        };
        
        void setLabelValue(QLabel *pLabelValue) { m_pLabelValue = pLabelValue; };
    private:
        QLabel *m_pLabelValue;
        float *m_pValue;
};

class DialogConfigurator : public QDialog, public ISignalGun {
    Q_OBJECT

    public:
        DialogConfigurator(QWidget *parent);
        void setGenerateMesh(bool bGenerateMesh);
        void setGenerateMaterial(bool bGenerateMaterial);
        void createNode();
        void regenerateGeometry();

        // ISignalGun
        virtual void generationComplited(QString sDone) override;

    Q_SIGNALS:
        void signal_generationComplited(QString sDone);


    private slots:
        void regenerateButton_clicked();
        void click_saveMesh();
        
        void sliderInt_valuesChanged(int nNewValue);
        void sliderFloat_valuesChanged(int nNewValue);

        void comboboxTextureResolution_Changed(int nNewValue);

        void slot_generationComplited(QString sDone);

        void triangles_itemSelectionChanged();


    private:

        QHBoxLayout *createIntSliderParameterUI(QString sLabel, int *nValue, int nMin, int nMax);
        QHBoxLayout *createFloatSliderParameterUI(QString sLabel, float *nValue, float nMin, float nMax);

        int normalizeTextureCoordinates(int nWidth, float nVal);
        void updateTextureImageView(const QString &sHeighlightTriangle = "");

        int m_nLabelSize;
        int m_nLabelValueSize;

        QString m_sRandomName;
        QLabel *m_pImageView;
        QListWidget *m_pTrianlesList;
        QPixmap m_pixmapImageOrigin;
        QPixmap m_pixmapImageHiglighted;
        QPushButton *m_pRegenerateButton;
        QPushButton *m_pSaveMeshButton;
        QPushButton *m_pCloseButton;
        QLabel *m_pTextureLabel;
        QHBoxLayout *m_pTexturesLayout;
        
        
        int m_nSliderTrianglesValue;
        float m_nSliderRadius;
        float m_nSliderRandomOffsetMin;
        float m_nSliderRandomOffsetMax;
        float m_nSliderScaleX;
        float m_nSliderScaleY;
        float m_nSliderScaleZ;
        
        //
        QComboBox *m_pTextureResolution;


        QProgressBar *m_pProgress;
        AsyncRunGenerator *m_pAsyncRunGenerator;
        Unigine::ObjectMeshDynamicPtr m_pMesh;
        Unigine::MaterialPtr m_pMaterial;
        Unigine::ImagePtr m_pImage;

        QTemporaryDir m_temporaryDir;
        QString m_sFilePath1;
        QString m_sFilePathHighlighted;

        // Unigine::TexturePtr m_pTexture;
        bool m_bWannaUpdate;
        bool m_bInProgress;

        bool m_bRegenerateGeometry;
        bool m_bRegenerateTexture;

        bool m_bGenerateMesh;
        bool m_bGenerateMaterial;
};

