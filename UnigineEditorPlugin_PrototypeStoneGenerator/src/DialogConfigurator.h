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

#include <UnigineNode.h>
#include <UnigineObjects.h>
#include <editor/Selector.h>
#include <editor/Selection.h>

#include "DialogConfigurator.h"
#include "StoneGenerator.h"

class DialogConfigurator : public QDialog {
    Q_OBJECT
public:
    DialogConfigurator(QWidget *parent);
    void createNode();
    void regenerateGeometry();

signals:
    

private slots:
    void removeClicked();
    void sliderTriangles_valuesChanged(int nNewValue);
    void sliderRadius_valuesChanged(int nNewValue);
    void sliderRandom_valuesChanged(int nNewValue);

private:
    QPushButton *m_pRemoveButton;
    QPushButton *m_pCloseButton;

    // number of triangles
    QLabel *m_pLabelSliderTriangles;
    QSlider *m_pSliderTriangles;
    int m_nSliderTrianglesValue;

    // radius
    QLabel *m_pLabelSliderRadius;
    QSlider *m_pSliderRadius;
    float m_nSliderRadius;

    // random
    QLabel *m_pLabelSliderRandom;
    QSlider *m_pSliderRandom;
    float m_nSliderRandom;
    

    StoneGenerator *m_pStoneGenerator;
    Unigine::ObjectMeshDynamicPtr m_pMesh;
};

