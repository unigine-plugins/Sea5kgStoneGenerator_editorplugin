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

    connect(m_pSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderFloat_valuesChanged(int)));
    this->addWidget(m_pSlider);
}

void DialogConfiguratorParameterSliderFloat::sliderFloat_valuesChanged(int nNewValue) {
    QObject* obj = sender();
    QSlider *pSlider = dynamic_cast<QSlider *>(obj);
    if (pSlider == nullptr) {
        std::cerr << "Could not cast" << std::endl;
        return;
    }
    m_nValue = float(nNewValue) / 100;
    m_pDialogConfigurator->updateValueFloat(m_nIdValue, m_nValue);
    m_pLabelValue->setText("(" + QString::number(m_nValue) + ")");
    // m_nextConf.setRegenerateGeometry(true);
    // this->regenerateGeometry();
}