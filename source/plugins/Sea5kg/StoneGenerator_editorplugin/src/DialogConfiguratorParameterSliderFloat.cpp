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

#include "DialogConfiguratorParameterSliderFloat.h"


DialogConfiguratorParameterSliderFloat::DialogConfiguratorParameterSliderFloat(
    IDialogConfigurator *pDialogConfigurator,
    IDialogConfiguratorUpdatedValue nIdValue,
    QString sLabel,
    float nValue,
    float nMin,
    float nMax
)
: QHBoxLayout()
{
    m_pDialogConfigurator = pDialogConfigurator;
    m_nIdValue = nIdValue;

    m_nValue = nValue;

    m_pLabel = new QLabel(sLabel);
    m_pLabel->setFixedWidth(m_pDialogConfigurator->getLabelSize());
    this->addWidget(m_pLabel);

    m_pLabelValue = new QLabel("(" + QString::number(m_nValue) + ")");
    m_pLabelValue->setFixedWidth(m_pDialogConfigurator->getLabelValueSize());
    this->addWidget(m_pLabelValue);

    m_pSlider = new QSlider(Qt::Horizontal);

    m_pSlider->setRange(nMin*100, nMax*100);
    m_pSlider->setValue(m_nValue*100);

    connect(m_pSlider, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
    this->addWidget(m_pSlider);
}

void DialogConfiguratorParameterSliderFloat::valueChanged(int nNewValue) {
    m_nValue = float(nNewValue) / 100;
    m_pDialogConfigurator->updateValueFloat(m_nIdValue, m_nValue);
    m_pLabelValue->setText("(" + QString::number(m_nValue) + ")");
}