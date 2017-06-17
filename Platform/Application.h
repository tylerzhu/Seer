#pragma once

namespace Seer
{
    class Application
    {
	public: // methord
		virtual ~Application();

		// Extra data storage to be used for platform-specific implementations.
		void SetExtraData(int iIndex, int iSize, const void* pvData);
		void GetExtraData(int iIndex, int iSize, void* pvData) const;
		

	public: // static 
		// the unique application object
		static Application* TheApplication;
		// the unique command-line arguments object
		//static Command* TheCommand;

		// Derived classes must set this function pointer.  The int parameter is
		// the number of command line arguments.  The char** parameter is the
		// array of argument strings.
		typedef int(*EntryPoint)(int, char**);
		static EntryPoint Run;

	protected:
		Application();

		// extra data
		enum { APP_EXTRA_DATA_QUANTITY = 128 };
		char m_acExtraData[APP_EXTRA_DATA_QUANTITY];

		// support for file dialogs
		bool m_bLaunchFileDialog;
    };
}
