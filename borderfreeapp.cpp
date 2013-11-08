#include "borderfreeapp.h"

#include <QDesktopWidget>

BorderFreeApp::BorderFreeApp ( int & argc, char ** argv ) :
    QApplication(argc, argv),
    tIcon(new QIcon(QString::fromWCharArray(L":/images/Crystal_Clear_action_view_remove_with_NO.png"))),
    trayIcon(new QSystemTrayIcon(this))
{
    trayIcon->setIcon((*tIcon));
    trayIcon->setVisible(true);
    if (RegisterHotKey(0, 1, MOD_ALT, VK_VOLUME_MUTE)) {
        trayIcon->showMessage(QString::fromWCharArray(L"BorderFree"),
                              QString::fromWCharArray(L"The program will keep running in the "
                                 "system tray. To terminate the program, "
                                 "choose Exit in the context menu "
                                 "of the system tray entry."),
                              QSystemTrayIcon::Information,
                              10000);
    }
    if (RegisterHotKey(0, 2, MOD_ALT, VK_VOLUME_UP)) {

    }
    if (RegisterHotKey(0, 3, MOD_ALT, VK_VOLUME_DOWN)) {

    }
    QAbstractEventDispatcher::instance()->installNativeEventFilter(this);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(tActivated(QSystemTrayIcon::ActivationReason)));
}


BorderFreeApp::~BorderFreeApp () {
    UnregisterHotKey(0, 1);
    UnregisterHotKey(0, 2);
    UnregisterHotKey(0, 3);
    delete trayIcon;
    delete tIcon;
}

void BorderFreeApp::tActivated(QSystemTrayIcon::ActivationReason reason) {
     switch (reason) {
     case QSystemTrayIcon::Trigger :
         break;
     case QSystemTrayIcon::Context :
         break;
     default:
         break;
     }
}

bool BorderFreeApp::nativeEventFilter(const QByteArray &eventType, void *message, long *) {
    if (eventType == "windows_generic_MSG") {
        MSG* m = (MSG*)message;
        if (m->message == WM_HOTKEY) {
            wprintf(L"Hotkey %d event received!\n", m->wParam);
            switch (m->wParam) {
            case 1:
                QApplication::exit();
                break;
            case 2:
                cleanActiveWindow();
                break;
            case 3:
                restoreActiveWindow();
                break;
            }
            return true;
        }
    }
    return false;
}


void BorderFreeApp::cleanActiveWindow() {
    WCHAR win_text[MAX_WIN_TEXT_LEN];
    RECT c_rect;
    QDesktopWidget* qdw = this->desktop();
    QRect r = qdw->screenGeometry(qdw->primaryScreen());

    HWND win = GetForegroundWindow();
    wprintf(L"Clean window!");
    if (!IsWindow(win)) {
        wprintf(L"Active Windows is not a window\n");
        return;
    }
    if (changedWindows.contains(win)) return;

    TWindowData* wps_p = new TWindowData;
    GetWindowText(win, (LPTSTR)win_text, MAX_WIN_TEXT_LEN);
    wps_p->hwnd = win;
    wps_p->style = GetWindowLongPtr(win, GWL_STYLE);
    GetWindowRect(win, &wps_p->rect);
    GetClientRect(win, &c_rect);
    SetWindowLongPtr(win, GWL_STYLE, STRIPPED_STYLE);
    SetWindowPos(win,
                 HWND_TOP,
                 c_rect.left,                   /* default horizontal position */
                 c_rect.top,                    /* default vertical position   */
                 c_rect.right  - c_rect.left,  /* default width               */
                 c_rect.bottom - c_rect.top,   /* default height              */
                 //SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE);
                 //SWP_FRAMECHANGED | SWP_NOSIZE);
                 SWP_NOZORDER | SWP_FRAMECHANGED);
    SetWindowPos(win,
                 HWND_TOP,
                 r.left(),                   /* default horizontal position */
                 r.top(),                    /* default vertical position   */
                 r.right() + 1,  /* default width               */
                 r.bottom() + 1,   /* default height              */
                 //SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE);
                 //SWP_FRAMECHANGED | SWP_NOSIZE);
                 SWP_NOZORDER | SWP_FRAMECHANGED);
    wprintf(L"Changed size to %dx%d\n", r.right() + 1 ,  r.bottom() + 1);
    changedWindows.insert(win, wps_p);
}

void BorderFreeApp::restoreActiveWindow() {

    HWND win = GetForegroundWindow();
    if (!IsWindow(win)) {
        wprintf(L"Active Windows is not a window\n");
        return;
    }
    if (!changedWindows.contains(win)) {
        wprintf(L"Active Windows is not a in the list\n");
        return;
    }
    TWindowData* wps_p = changedWindows.take(win);

    wprintf(L"Returning window to normal\n");

    SetWindowLongPtr(wps_p->hwnd, GWL_STYLE, wps_p->style);
    SetWindowPos(wps_p->hwnd,
                 HWND_TOP,
                 wps_p->rect.left,                   /* default horizontal position */
                 wps_p->rect.top,                    /* default vertical position   */
                 wps_p->rect.right  - wps_p->rect.left,  /* default width               */
                 wps_p->rect.bottom - wps_p->rect.top,   /* default height              */
                 //SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOZORDER | SWP_NOMOVE);
                 //SWP_FRAMECHANGED | SWP_NOSIZE);
                 SWP_NOZORDER | SWP_FRAMECHANGED);
    delete wps_p;
}
