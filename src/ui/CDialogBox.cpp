#include "CDialogBox.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>
#include <map>

#include "../logger/Logger.h"

CDialogBox::CDialogBox(QWidget *parent)
    :QDialog(parent)
{
    QRect monitorGeometry(QApplication::desktop()->availableGeometry());

    setMinimumSize(0.4*monitorGeometry.width(),0.2*monitorGeometry.height());
    this->setWindowTitle("Save picture");

    QLabel *title = new QLabel(this);
    title->setText("Save this picture to learn as a?");

    initButtons();
    //    m_btn_cancel->setContentsMargins();

    m_comb_objectsList = new QComboBox;
//    m_comb_objectsList->addItem("One");
//    m_comb_objectsList->addItem("Two");
//    m_comb_objectsList->addItem("Three");

    m_editText = new QLineEdit;

    m_questionLayout = new QHBoxLayout;
    m_knownLayout = new QHBoxLayout;
    m_unknownLayout = new QHBoxLayout;
    decisionLayout = new QHBoxLayout;

    m_questionLayout->addWidget(m_btn_knownObj);
    m_questionLayout->addWidget(m_btn_unKnownObj);
    m_knownLayout->addWidget(m_comb_objectsList);
    m_unknownLayout->addWidget(m_editText);
    decisionLayout->addWidget(m_btn_save);
    decisionLayout->addWidget(m_btn_cancel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(title);
    mainLayout->addLayout(m_questionLayout);
    mainLayout->addLayout(m_knownLayout);
    mainLayout->addLayout(m_unknownLayout);
    mainLayout->addLayout(decisionLayout);

    setLayout(mainLayout);
    //    hideButtons();
    showKnownLayout(false);
    showUnknownLayout(false);
    m_btn_save->setDisabled(true);

    // user save prefs
    m_isReqValid = false;
}

CDialogBox::~CDialogBox()
{

}

void CDialogBox::connectToDB(CObjectDatabase *db)
{
    m_objDB = db;
    Logger::INFO("DB connection level 2");
}

CObjectDetails CDialogBox::execute()
{
    this->exec();

    return CObjectDetails(m_objName,m_isKnownObj,m_isReqValid);
}

void CDialogBox::hideButtons()
{
    m_btn_knownObj->hide();
    m_btn_unKnownObj->hide();
}

void CDialogBox::showQuestionLayout(bool val)
{
    m_btn_knownObj->setVisible(val);
    m_btn_unKnownObj->setVisible(val);
}

void CDialogBox::showKnownLayout(bool val)
{
    m_comb_objectsList->setVisible(val);
    m_btn_save->setDisabled(false);
}

void CDialogBox::showUnknownLayout(bool val)
{
    m_editText->setVisible(val);
    m_btn_save->setDisabled(false);
}

QSize CDialogBox::calculateButtonsSize()
{
    QRect monitorGeometry(QApplication::desktop()->availableGeometry());

    return QSize(0.08*monitorGeometry.width(),0.07*monitorGeometry.height());
}

void CDialogBox::initButtons()
{
    m_btn_knownObj = new QPushButton();
    m_btn_unKnownObj = new QPushButton;
    m_btn_cancel = new QPushButton;
    m_btn_save = new QPushButton;

    QSize buttonSize = calculateButtonsSize();

    m_btn_knownObj->setFixedSize(buttonSize);
    m_btn_unKnownObj->setFixedSize(buttonSize);
    m_btn_cancel->setFixedSize(buttonSize);
    m_btn_save->setFixedSize(buttonSize);
    m_btn_knownObj->setText(tr("Known Object"));
    m_btn_unKnownObj->setText(tr("New Object"));
    m_btn_save->setText(tr("Save"));
    m_btn_cancel->setText(tr("Cancel"));

    // connect to slots
    connect(m_btn_knownObj, SIGNAL (clicked()),this, SLOT (m_btn_knownObj_Clicked()));
    connect(m_btn_unKnownObj, SIGNAL (clicked()),this, SLOT (m_btn_unKnownObj_Clicked()));
    connect(m_btn_cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_btn_save, SIGNAL(clicked()), this, SLOT(save_clicked()));
}

void CDialogBox::m_btn_knownObj_Clicked()
{
    showQuestionLayout(false);
    // load data to combo
        auto data = m_objDB->getData();
        for (auto &i : data) {
            m_comb_objectsList->addItem(QString((i.name).c_str()));
        }

    showKnownLayout(true);
    m_isKnownObj = true;
}

void CDialogBox::m_btn_unKnownObj_Clicked()
{
    showQuestionLayout(false);
    showUnknownLayout(true);
    m_isKnownObj = false;
}

void CDialogBox::save_clicked()
{
    if(m_isKnownObj){
        m_objName = m_comb_objectsList->currentText();
    }else{
        m_objName = m_editText->text();
    }
    m_isReqValid = true;
    this->close();
}
