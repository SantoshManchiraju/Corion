#ifndef CDIALOGBOX_H
#define CDIALOGBOX_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLineEdit>

#include "CObjectDetails.h"
#include "../vision/CObjectDatabase.h"

class CDialogBox : public QDialog
{
    Q_OBJECT

private:
    QPushButton *m_btn_knownObj;
    QPushButton *m_btn_unKnownObj;
    QPushButton *m_btn_cancel;
    QPushButton *m_btn_save;
    QComboBox *m_comb_objectsList;
    QLineEdit *m_editText;

    // Layout
    QHBoxLayout *m_questionLayout;
    QHBoxLayout *m_knownLayout;
    QHBoxLayout *m_unknownLayout;
    QHBoxLayout *decisionLayout;

    // user save preferences
    bool m_isReqValid;
    bool m_isKnownObj;
    QString m_objName;

    // DB
    CObjectDatabase *m_objDB;

    void hideButtons();
    void showQuestionLayout(bool val);
    void showKnownLayout(bool val);
    void showUnknownLayout(bool val);
    QSize calculateButtonsSize();
    void initButtons();
private slots:
    void m_btn_knownObj_Clicked();
    void m_btn_unKnownObj_Clicked();
    void save_clicked();

public:
    CDialogBox(QWidget *parent = 0);
    virtual ~CDialogBox();
    void connectToDB(CObjectDatabase *db);

    CObjectDetails execute();
};

#endif // CDIALOGBOX_H
