#include "DialogConfiguratorParameterEditBoxUInt.h"

#include "StoneGeneratorPseudoRandom.h"

#include <QValidator>

class QUIntValidator : public QValidator {
    public:
        explicit QUIntValidator(QObject* parent= nullptr) : QValidator(parent){}

        void setRange(unsigned int nMin, unsigned int nMax) {
            m_nMin = nMin;
            m_nMax = nMax;
        }

        virtual void fixup(QString &input) const override {
            // std::cout << "fixup" << std::endl;
        }

        virtual QValidator::State validate(QString &input, int &pos) const override {
            bool bOk;
            unsigned int value = input.toLatin1().toUInt(&bOk,10);
            if (!bOk) {
                return QValidator::Invalid;
            }
            if (value < m_nMin || value > m_nMax) {
                return QValidator::Invalid;
            }
            return QValidator::Acceptable;
        }

    private:
        unsigned int m_nMin;
        unsigned int m_nMax;
};


DialogConfiguratorParameterEditBoxUInt::DialogConfiguratorParameterEditBoxUInt(
    IDialogConfigurator *pDialogConfigurator,
    IDialogConfiguratorUpdatedValue nIdValue,
    QString sLabel,
    unsigned int nValue,
    unsigned int nMin,
    unsigned int nMax
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

    m_pLineEdit = new QLineEdit();
    QUIntValidator *pValidator = new QUIntValidator(this);
    pValidator->setRange(nMin, nMax);
    m_pLineEdit->setValidator(pValidator);
    m_pLineEdit->setText(QString::number(m_nValue));
    this->addWidget(m_pLineEdit);

    m_pNextButton = new QPushButton(tr("Next Random"));
    m_pNextButton->setDefault(true);
    connect(m_pNextButton, SIGNAL(clicked()),this, SLOT(nextButton_clicked()));
    this->addWidget(m_pNextButton);

    connect(m_pLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(valueChanged(const QString &)));
}

void DialogConfiguratorParameterEditBoxUInt::valueChanged(const QString &sNewValue) {
    // std::cout << sNewValue.toStdString() << std::endl;
    bool bOk;
    unsigned int nNewValue = sNewValue.toLatin1().toUInt(&bOk,10);
    m_nValue = nNewValue;
    m_pDialogConfigurator->updateValueInt(m_nIdValue, m_nValue);
    m_pLabelValue->setText("(" + QString::number(m_nValue) + ")");
}

void DialogConfiguratorParameterEditBoxUInt::nextButton_clicked() {
    StoneGeneratorPseudoRandom r;
    r.setInitSeed(m_nValue);
    m_nValue = r.getNextRandom();
    m_pLineEdit->setText(QString::number(m_nValue));
    // m_pDialogConfigurator->updateValueInt(m_nIdValue, m_nValue);
}