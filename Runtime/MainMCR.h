#pragma once

#ifndef MAINMCR_H
#define MAINMCR_H

#include "Object/Main.h"

//----------------------------------------------------------------------------
#define DECLARE_INITIALIZE \
public: \
    static bool RegisterInitialize (); \
    static void Initialize (); \
private: \
    static bool ms_bInitializeRegistered
//----------------------------------------------------------------------------
#define IMPLEMENT_INITIALIZE(classname) \
bool classname::ms_bInitializeRegistered = false; \
bool classname::RegisterInitialize () \
{ \
    if (!ms_bInitializeRegistered) \
    { \
        Main::AddInitializer(classname::Initialize); \
        ms_bInitializeRegistered = true; \
    } \
    return ms_bInitializeRegistered; \
}
//----------------------------------------------------------------------------
#define REGISTER_INITIALIZE(classname) \
static bool gs_bInitializeRegistered_##classname = \
    classname::RegisterInitialize ()
//----------------------------------------------------------------------------
#define DECLARE_TERMINATE \
public: \
    static bool RegisterTerminate (); \
    static void Terminate (); \
private: \
    static bool ms_bTerminateRegistered
//----------------------------------------------------------------------------
#define IMPLEMENT_TERMINATE(classname) \
bool classname::ms_bTerminateRegistered = false; \
bool classname::RegisterTerminate () \
{ \
    if (!ms_bTerminateRegistered) \
    { \
        Main::AddTerminator(classname::Terminate); \
        ms_bTerminateRegistered = true; \
    } \
    return ms_bTerminateRegistered; \
}
//----------------------------------------------------------------------------
#define REGISTER_TERMINATE(classname) \
static bool gs_bTerminateRegistered_##classname = \
    classname::RegisterTerminate ()
//----------------------------------------------------------------------------

#endif
