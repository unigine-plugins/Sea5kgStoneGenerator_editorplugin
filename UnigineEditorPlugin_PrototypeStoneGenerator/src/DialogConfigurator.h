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


class DialogConfigurator : public QDialog, public ISignalGun {
    Q_OBJECT

    public:
        DialogConfigurator(QWidget *parent);
        void createNode();
        void regenerateGeometry();

        // ISignalGun
        virtual void generationComplited(QString sDone) override;

    Q_SIGNALS:
        void signal_generationComplited(QString sDone);


    private slots:
        void regenerateButton_clicked();
        void sliderTriangles_valuesChanged(int nNewValue);
        void sliderRadius_valuesChanged(int nNewValue);
        void sliderRandomOffsetMin_valuesChanged(int nNewValue);
        void sliderRandomOffsetMax_valuesChanged(int nNewValue);
        void sliderScaleX_valuesChanged(int nNewValue);
        void sliderScaleY_valuesChanged(int nNewValue);
        void sliderScaleZ_valuesChanged(int nNewValue);
        void comboboxTextureResolution_Changed(int nNewValue);

        void slot_generationComplited(QString sDone);

    private:
        QString m_sRandomName;
        QPushButton *m_pRegenerateButton;
        QPushButton *m_pCloseButton;

        // number of triangles
        QLabel *m_pLabelSliderTriangles;
        QSlider *m_pSliderTriangles;
        int m_nSliderTrianglesValue;

        // radius
        QLabel *m_pLabelSliderRadius;
        QSlider *m_pSliderRadius;
        float m_nSliderRadius;

        // random min
        QLabel *m_pLabelSliderRandomOffsetMin;
        QSlider *m_pSliderRandomOffsetMin;
        float m_nSliderRandomOffsetMin;

        // random max
        QLabel *m_pLabelSliderRandomOffsetMax;
        QSlider *m_pSliderRandomOffsetMax;
        float m_nSliderRandomOffsetMax;

        // scale x
        QLabel *m_pLabelSliderScaleX;
        QSlider *m_pSliderScaleX;
        float m_nSliderScaleX;

        // scale y
        QLabel *m_pLabelSliderScaleY;
        QSlider *m_pSliderScaleY;
        float m_nSliderScaleY;

        // scale z
        QLabel *m_pLabelSliderScaleZ;
        QSlider *m_pSliderScaleZ;
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

        // Unigine::TexturePtr m_pTexture;
        bool m_bWannaUpdate;
        bool m_bInProgress;

        bool m_bRegenerateGeometry;
        bool m_bRegenerateTexture;
};

