#ifndef APPLICATIONMCR_H
#define APPLICATIONMCR_H

////----------------------------------------------------------------------------
//#define CONSOLE_APPLICATION(classname) \
//WM4_IMPLEMENT_INITIALIZE(classname); \
//\
//void classname::Initialize () \
//{ \
//    Application::Run = &ConsoleApplication::Run; \
//    TheApplication = WM4_NEW classname; \
//}

//----------------------------------------------------------------------------
#define WINDOW_APPLICATION(classname) \
IMPLEMENT_INITIALIZE(classname); \
\
void classname::Initialize () \
{ \
    Application::Run = &WindowApplication::Run; \
    TheApplication = new classname; \
}
//----------------------------------------------------------------------------

#endif