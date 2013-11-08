#include "qlineedithotkey.h"


QLineEditHotkey::QLineEditHotkey(QWidget* pParent):QLineEdit(pParent)
{
}

QLineEditHotkey::~QLineEditHotkey() {

}

void QLineEditHotkey::keyPressEvent( QKeyEvent * event )
{
    int keyInt = event->key();
    Qt::Key key = static_cast<Qt::Key>(keyInt);

    // Handle unknown keys
    if( key == Qt::Key_unknown )
        return;

    // Pressing Esc or Backspace will clear the content
    if( key == Qt::Key_Escape || key == Qt::Key_Backspace )
    {
        setText(NULL);
        return;
    }

    // Empty means a special key like F5, Delete, Home etc
    if( event->text().isEmpty() )
        return;

    // Checking for key combinations
    Qt::KeyboardModifiers modifiers = event->modifiers();

    if(modifiers.testFlag(Qt::NoModifier))
        return;
    if(modifiers.testFlag(Qt::ShiftModifier))
        keyInt += Qt::SHIFT;
    if(modifiers.testFlag(Qt::ControlModifier))
        keyInt += Qt::CTRL;
    if(modifiers.testFlag(Qt::AltModifier))
        keyInt += Qt::ALT;

    setText( QKeySequence(keyInt).toString(QKeySequence::NativeText) );
}
