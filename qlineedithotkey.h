#ifndef QLINEEDITHOTKEY_H
#define QLINEEDITHOTKEY_H

#include <QLineEdit>
#include <QKeyEvent>

class QLineEditHotkey : public QLineEdit
{
    Q_OBJECT
public:
    explicit QLineEditHotkey(QWidget *parent = 0);
    ~QLineEditHotkey();
protected:
     void keyPressEvent ( QKeyEvent * event );

signals:

public slots:

};

#endif // QLINEEDITHOTKEY_H
