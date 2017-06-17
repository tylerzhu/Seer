#include "Application.h"

#include <string>

#include "Object/Main.h"

using namespace Seer;

Application::EntryPoint Application::Run = 0;
//Command* Application::TheCommand = 0;
Application* Application::TheApplication = 0;

Application::Application()
{
	memset(m_acExtraData, 0, APP_EXTRA_DATA_QUANTITY*sizeof(char));
	m_bLaunchFileDialog = false;
}

Seer::Application::~Application()
{

}

void Seer::Application::SetExtraData(int iIndex, int iSize, const void* pvData)
{

}

void Seer::Application::GetExtraData(int iIndex, int iSize, void* pvData) const
{

}


/**
  *  @brief  Thisis a brief description.
  *  @param[in]  inArgName input argument description.type name:purpose(Range)
  *  @param[out] outArgName output argument description.
  *  @Return:    int:description of the return value
  *  - TRUE
  *  - FALSE
  *
  *  @note   matters needing attention
  *  @see    other functions  
  */
int main(int iQuantity, char* apcArgument[])
{
	
	Main::Initialize();

	int iExitCode = 0;
	if (Application::Run)
	{		
		//Application::TheCommand = WM4_NEW Command(iQuantity, apcArgument);
		iExitCode = Application::Run(iQuantity, apcArgument);
//		WM4_DELETE Application::TheCommand;
//		Application::TheCommand = 0;
	
	}
	else
	{
		iExitCode = INT_MAX;
	}		

//	WM4_DELETE Application::TheApplication;
//	Application::TheApplication = 0;

	

//#ifdef WM4_MEMORY_MANAGER
//#ifdef _DEBUG
//	Memory::GenerateReport("MemoryReportDebug.txt");
//#else
//	Memory::GenerateReport("MemoryReportRelease.txt");
//#endif
//#endif

	return iExitCode;
}

