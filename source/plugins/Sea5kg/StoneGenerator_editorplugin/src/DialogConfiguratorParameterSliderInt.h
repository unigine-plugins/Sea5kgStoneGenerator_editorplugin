#pragma once

#include <QString>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>

#include <iostream>

#include "IDialogConfigurator.h"

class DialogConfiguratorParameterSliderInt : public QHBoxLayout {
    Q_OBJECT
    public:
        DialogConfiguratorParameterSliderInt(
            IDialogConfigurator *pDialogConfigurator,
            IDialogConfiguratorUpdatedValue nIdValue,
            QString sLabel,
            int nValue,
            int nMin,
            int nMax
        );

    private slots:
        void sliderInt_valuesChanged(int nNewValue);

    private:
        IDialogConfiguratorUpdatedValue m_nIdValue;
        QLabel *m_pLabel;
        QLabel *m_pLabelValue;
        QSlider *m_pSlider;
        int m_nValue;
        IDialogConfigurator *m_pDialogConfigurator;
};
