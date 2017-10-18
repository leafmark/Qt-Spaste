#include "./unix/ShortCut.h"

MyGlobalShortCut::MyGlobalShortCut(QString key)
{
    this->m_key = QKeySequence(key);
    registerHotKey();
}

MyGlobalShortCut::~MyGlobalShortCut()
{
    unregisterHotKey();
}

bool  MyGlobalShortCut::registerHotKey()
{
   Qt::KeyboardModifiers allMods = Qt::ShiftModifier | Qt::ControlModifier|
                                   Qt::AltModifier | Qt::MetaModifier;
   this->key  = this->m_key.isEmpty() ? Qt::Key(0) :
                                        Qt::Key((this->m_key[0] ^ allMods) & this->m_key[0]);
   this->mods = this->m_key.isEmpty() ? Qt::KeyboardModifiers(0) :
                                        Qt::KeyboardModifiers(this->m_key[0] & allMods);
   const quint32 nativeKey  = nativeKeycode(this->key);
   const quint32 nativeMods = nativeModifiers(this->mods);

   Display* display = QX11Info::display();
   Window window = QX11Info::appRootWindow();
   Bool owner = True;
   int pointer  = GrabModeAsync;
   int keyboard = GrabModeAsync;

   XGrabKey(display, nativeKey, nativeMods, window, owner, pointer, keyboard);
   XGrabKey(display, nativeKey, nativeMods | Mod2Mask, window, owner, pointer, keyboard); // allow numlock
   XSync(display, False);

   original_x_errhandler = XSetErrorHandler(qxt_x_errhandler);
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
{
    this->m_shortcut = shortcut;
}

MyWinEventFilter::~MyWinEventFilter()
{
}

bool MyWinEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
   if (eventType == "xcb_generic_event_t")
   {
       xcb_generic_event_t* event = static_cast<xcb_generic_event_t *>(message);

       if ( (event->response_type & ~0x80)==XCB_KEY_PRESS )
       {
            qDebug() << "XCB_HOTKEY" <<endl;

            xcb_button_press_event_t *press = (xcb_button_press_event_t *)event;

            const quint32 keycode = press->detail;
            const quint32 modifiers = press->state;
            if( m_shortcut->shortcuts.value(qMakePair(keycode, modifiers)) )
            {
                screenshot *n_screenshot = new screenshot;
                n_screenshot->shot();
                return true;
            }
            return true;
       }
   }
// XK_Tab
   return false;
}

//==============================================
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
