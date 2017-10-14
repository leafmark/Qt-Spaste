
#include "./unix/ShortCut.h"

static int (*original_x_errhandler)(Display* display, XErrorEvent* event);

static int qxt_x_errhandler(Display* display, XErrorEvent *event)
{
    Q_UNUSED(display);
    switch (event->error_code)
    {
        case BadAccess:
        case BadValue:
        case BadWindow:
            if (event->request_code == 33 /* X_GrabKey */ ||
                event->request_code == 34 /* X_UngrabKey */)
            {
                //TODO:
                //char errstr[256];
                //XGetErrorText(dpy, err->error_code, errstr, 256);
            }
        default:
            return 0;
    }
}

MyGlobalShortCut::MyGlobalShortCut(QString key, screenshot *shot)
{
    Q_UNUSED(shot);
    m_key = QKeySequence(key);
    m_filter = new MyWinEventFilter(this);
    m_app->installNativeEventFilter(m_filter);

    registerHotKey();
}

MyGlobalShortCut::~MyGlobalShortCut()
{
    unregisterHotKey();
}

void MyGlobalShortCut::activateShortcut()
{
   shot.cut();
}

bool  MyGlobalShortCut::registerHotKey()
{
   Qt::KeyboardModifiers allMods = Qt::ShiftModifier | Qt::ControlModifier|
                                   Qt::AltModifier | Qt::MetaModifier;
   key  = m_key.isEmpty() ? Qt::Key(0) : Qt::Key((m_key[0] ^ allMods) & m_key[0]);
   mods = m_key.isEmpty() ? Qt::KeyboardModifiers(0) : Qt::KeyboardModifiers(m_key[0] & allMods);
   const quint32 nativeKey  = nativeKeycode(key);
   const quint32 nativeMods = nativeModifiers(mods);

   Display* display = QX11Info::display();
   Window window = QX11Info::appRootWindow();
   Bool owner = True;
   int pointer = GrabModeAsync;
   int keyboard = GrabModeAsync;

   original_x_errhandler = XSetErrorHandler(qxt_x_errhandler);
   XGrabKey(display, nativeKey, nativeMods, window, owner, pointer, keyboard);
   XGrabKey(display, nativeKey, nativeMods | Mod2Mask, window, owner, pointer, keyboard); // allow numlock
   XSync(display, False);
   XSetErrorHandler(original_x_errhandler);

   shortcuts.insert(qMakePair(nativeKey, nativeMods),this);

   return 0;
}

bool  MyGlobalShortCut::unregisterHotKey()
{
    Display* display = QX11Info::display();
    Window window = QX11Info::appRootWindow();
    original_x_errhandler = XSetErrorHandler(qxt_x_errhandler);

    const quint32 nativeKey  = nativeKeycode(key);
    const quint32 nativeMods = nativeModifiers(mods);

    XUngrabKey(display, nativeKey, nativeMods, window);
    XUngrabKey(display, nativeKey, nativeMods | Mod2Mask, window); // allow numlock
    XSync(display, False);
    XSetErrorHandler(original_x_errhandler);
    return 0;
}

quint32 MyGlobalShortCut::nativeKeycode(Qt::Key key)
{
    Display* display = QX11Info::display();
    return XKeysymToKeycode(display, XStringToKeysym(QKeySequence(key).toString().toLatin1().data()));
}

quint32 MyGlobalShortCut::nativeModifiers(Qt::KeyboardModifiers modifiers)
{
    // ShiftMask, LockMask, ControlMask, Mod1Mask, Mod2Mask, Mod3Mask, Mod4Mask, and Mod5Mask
    quint32 native = 0;
    if (modifiers & Qt::ShiftModifier)
        native |= ShiftMask;
    if (modifiers & Qt::ControlModifier)
        native |= ControlMask;
    if (modifiers & Qt::AltModifier)
        native |= Mod1Mask;
    if (modifiers & Qt::MetaModifier)
        native |= Mod4Mask;

    // TODO: resolve these?
    //if (modifiers & Qt::MetaModifier)
    //if (modifiers & Qt::KeypadModifier)
    //if (modifiers & Qt::GroupSwitchModifier)
    return native;
}
//==============================================
MyWinEventFilter::MyWinEventFilter(MyGlobalShortCut *shortcut)
    : m_shortcut(shortcut)
{
}

MyWinEventFilter::~MyWinEventFilter()
{
}

bool MyWinEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
   if (eventType == "xcb_generic_event_t") {
       XEvent* msg = static_cast<XEvent*>(message);

       m_shortcut ->activateShortcut();
       qDebug() << "test" << msg <<endl;
       return true;
   }
   return false;
}
