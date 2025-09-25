/*
MIT License

Copyright (c) 2022-2025 mrseakg@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Repository: https://github.com/unigine-plugins/Sea5kgStoneGenerator_editorplugin
*/

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
