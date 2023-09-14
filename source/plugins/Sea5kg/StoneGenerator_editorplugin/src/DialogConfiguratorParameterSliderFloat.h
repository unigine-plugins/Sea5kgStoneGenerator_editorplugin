#pragma once

#include <QString>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>

#include <iostream>

#include "IDialogConfigurator.h"

class DialogConfiguratorParameterSliderFloat : public QHBoxLayout {
    Q_OBJECT
    public:
        DialogConfiguratorParameterSliderFloat(IDialogConfigurator *pDialogConfigurator, IDialogConfiguratorUpdatedValue nIdValue, QString sLabel, float nValue, float nMin, float nMax);

    private slots:
        void sliderFloat_valuesChanged(int nNewValue);

    private:
        IDialogConfiguratorUpdatedValue m_nIdValue;
        QLabel *m_pLabel;
        QLabel *m_pLabelValue;
        QSlider *m_pSlider;
        float m_nValue;
        IDialogConfigurator *m_pDialogConfigurator;
};
