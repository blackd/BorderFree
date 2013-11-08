#ifndef BORDERFREEAPP_H
#define BORDERFREEAPP_H

#include <QApplication>
#include <QtGui>
#include <QSystemTrayIcon>
#include <windows.h>

#define MAX_WIN_TEXT_LEN 512
#define STRIPPED_STYLE   (WS_POPUP|WS_VISIBLE)

typedef struct TWindowDataStruct
{
  HWND hwnd;
  RECT rect;
  long style;
} TWindowData;


class BorderFreeApp : public QApplication, QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    explicit BorderFreeApp ( int & argc, char ** argv );
    ~BorderFreeApp ();
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *);

private:
    const QIcon *tIcon;
    QSystemTrayIcon *trayIcon;
    //QMenu *contextMenu;
    QHash<HWND, TWindowData*> changedWindows;

    void cleanActiveWindow();
    void restoreActiveWindow();

protected:

private slots:
    void tActivated(QSystemTrayIcon::ActivationReason reason);

signals:

public slots:

};

#endif // BORDERFREEAPP_H
