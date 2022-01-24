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

#include <UnigineNode.h>
#include <UnigineMaterials.h>
#include <UnigineTextures.h>
#include <UnigineObjects.h>
#include <editor/Selector.h>
#include <editor/Selection.h>

#include "DialogConfigurator.h"

#include "StoneGenerator.h"
#include "TextureStoneGenerator.h"

class DialogConfigurator : public QDialog {
    Q_OBJECT
public:
    DialogConfigurator(QWidget *parent);
    void createNode();
    void regenerateGeometry();

signals:
    

private slots:
    void regenerateButton_clicked();
    void sliderTriangles_valuesChanged(int nNewValue);
    void sliderRadius_valuesChanged(int nNewValue);
    void sliderRandomOffsetMin_valuesChanged(int nNewValue);
    void sliderRandomOffsetMax_valuesChanged(int nNewValue);
    void sliderScaleX_valuesChanged(int nNewValue);
    void sliderScaleY_valuesChanged(int nNewValue);
    void sliderScaleZ_valuesChanged(int nNewValue);

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
    
    QProgressBar *m_pProgress;

    StoneGenerator *m_pStoneGenerator;
    Unigine::ObjectMeshDynamicPtr m_pMesh;
    Unigine::MaterialPtr m_pMaterial;
    Unigine::ImagePtr m_pImage;
    // Unigine::TexturePtr m_pTexture;
};

