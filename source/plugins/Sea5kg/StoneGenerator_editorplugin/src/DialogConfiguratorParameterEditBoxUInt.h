#pragma once

#include <QString>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include <iostream>

#include "IDialogConfigurator.h"

class DialogConfiguratorParameterEditBoxUInt : public QHBoxLayout {
    Q_OBJECT
    public:
        DialogConfiguratorParameterEditBoxUInt(
            IDialogConfigurator *pDialogConfigurator,
            IDialogConfiguratorUpdatedValue nIdValue,
            QString sLabel,
            unsigned int nValue,
            unsigned int nMin,
            unsigned int nMax
        );

    private slots:
        void valueChanged(const QString &sNewValue);
        void nextButton_clicked();

    private:
        IDialogConfiguratorUpdatedValue m_nIdValue;
        QLabel *m_pLabel;
        QLabel *m_pLabelValue;
        QLineEdit *m_pLineEdit;
        QPushButton *m_pNextButton;
        unsigned int m_nValue;
        IDialogConfigurator *m_pDialogConfigurator;
};
