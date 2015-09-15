
// MFCDraw.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MFCDraw.h"
#include "MainFrm.h"

#include "MFCDrawDoc.h"
#include "MFCDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCDrawApp

BEGIN_MESSAGE_MAP(CMFCDrawApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMFCDrawApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_FREEDRAW, &CMFCDrawApp::OnFreedraw)
	ON_COMMAND(ID_LINE, &CMFCDrawApp::OnLine)
	ON_COMMAND(ID_CLEAR, &CMFCDrawApp::OnClear)
	//ON_COMMAND(ID_ANTIA, &CMFCDrawApp::OnAntia)
END_MESSAGE_MAP()


// CMFCDrawApp construction

CMFCDrawApp::CMFCDrawApp()
{
	m_bHiColorIcons = TRUE;

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MFCDraw.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CMFCDrawApp object

CMFCDrawApp theApp;


// CMFCDrawApp initialization

BOOL CMFCDrawApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMFCDrawDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMFCDrawView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	//AfxGetMainWnd()->GetMenu()->CheckMenuItem(ID_ANTIA, MF_UNCHECKED);

	return TRUE;
}

// CMFCDrawApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CMFCDrawApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMFCDrawApp customization load/save methods

void CMFCDrawApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CMFCDrawApp::LoadCustomState()
{
}

void CMFCDrawApp::SaveCustomState()
{
}

// CMFCDrawApp message handlers

void CMFCDrawApp::OnFreedraw()
{
	// TODO:  �ڴ���������������
	//m_nDrawType = 0;
}


void CMFCDrawApp::OnLine()
{
	// TODO:  �ڴ���������������
	//m_nDrawType = 1;
}


void CMFCDrawApp::OnClear()
{
	// TODO:  �ڴ���������������
	//OnDraw();
}


//void CMFCDrawApp::OnAntia()
//{
//	// TODO:  �ڴ���������������
//	AfxGetMainWnd()->GetMenu()->GetSubMenu(5)->GetMenuState(ID_ANTIA, MF_CHECKED)
//		? AfxGetMainWnd()->GetMenu()->GetSubMenu(5)->CheckMenuItem(ID_ANTIA, MF_UNCHECKED)
//		: AfxGetMainWnd()->GetMenu()->GetSubMenu(5)->CheckMenuItem(ID_ANTIA, MF_CHECKED);
//}