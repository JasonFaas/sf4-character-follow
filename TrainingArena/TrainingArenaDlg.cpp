// TrainingArenaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrainingArena.h"
#include "TrainingArenaDlg.h"


#include "mysql_driver.h" 
#include "mysql_connection.h" 


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTrainingArenaDlg dialog




CTrainingArenaDlg::CTrainingArenaDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTrainingArenaDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrainingArenaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, BtnStart, BtnStartBtn);
	DDX_Control(pDX, IDC_CHECK1, ControllerCheckBox);
	DDX_Control(pDX, IDC_EDIT1, RecordFileName);
	DDX_Control(pDX, IDC_EDIT2, recordFrames);
}

BEGIN_MESSAGE_MAP(CTrainingArenaDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(BtnStart, &CTrainingArenaDlg::OnBnClickedBtnstart)
	ON_BN_CLICKED(IDC_CHECK1, &CTrainingArenaDlg::OnBnClickedController)
	ON_BN_CLICKED(HadokenButton, &CTrainingArenaDlg::OnBnClickedHadokenButton)
	ON_BN_CLICKED(ResetBtn, &CTrainingArenaDlg::OnBnClickedResetbtn)
END_MESSAGE_MAP()


// CTrainingArenaDlg message handlers

BOOL CTrainingArenaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTrainingArenaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTrainingArenaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTrainingArenaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTrainingArenaDlg::OnBnClickedBtnstart()
{
	// TODO: Add your control notification handler code here

	CString btnText;
	BtnStartBtn.GetWindowTextW(btnText);

	if(btnText == StrToCStr("Click Me First"))
	{
		_sfThread = NULL;
		
		TRACE("Running first video display\n");

		BtnStartBtn.SetWindowTextW((LPCTSTR)StrToCStr("Processing"));

		sf4 = new SF4Central(2);
		sf4->TestVideo();

		delete sf4;
		sf4 = NULL;

		BtnStartBtn.SetWindowTextW((LPCTSTR)StrToCStr("Unpause Game"));

		//Database stuff
		
		
		//end database stuff


	}
	else if(btnText == StrToCStr("Unpause Game"))
	{
		TRACE("Playing Game\n");
		BtnStartBtn.SetWindowTextW((LPCTSTR)StrToCStr("Processing"));

		DWORD thr_id1;
		_sfThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)StartSecondMainThread,this,0,&thr_id1);
		
		BtnStartBtn.SetWindowTextW((LPCTSTR)StrToCStr("Pause Game"));
	}
	else if(btnText == StrToCStr("Pause Game"))
	{
		
		TRACE("Pausing Game");
		BtnStartBtn.SetWindowTextW((LPCTSTR)StrToCStr("Processing"));

		if(sf4!=NULL)
			sf4->PauseGame();
		
		//TRACE("HI THERE\n:%i:\n:%i:%i:%i:\n",WaitForSingleObject(_sfThread,0),WAIT_ABANDONED,WAIT_OBJECT_0,WAIT_TIMEOUT);


	}

}


DWORD
CTrainingArenaDlg::StartSecondMainThread(void * param){
	((CTrainingArenaDlg*)param)->RunSecondMainThread();
	return 0;
}

void
CTrainingArenaDlg::RunSecondMainThread()
{
	CString fileName, frames;
	if(RecordFileName.GetWindowTextLengthW() > 0)
	{
		TRACE("Going to record stuff\n");
		RecordFileName.GetWindowTextW(fileName);
		if(recordFrames.GetWindowTextLengthW() > 0)
		{
			recordFrames.GetWindowTextW(frames);

			char * freeMe;
			char * freeMeTwo;

			sf4 = new SF4Central(2,freeMe = CStrToStr(fileName),atoi((freeMeTwo = CStrToStr(frames))));
			free(freeMe);
			free(freeMeTwo);
		}
		else
		{
			char * freeMe;

			sf4 = new SF4Central(2,freeMe = CStrToStr(fileName));

			free(freeMe);
		}

		
		


	}
	else
	{
		TRACE("Not going to record stuff\n");
		sf4 = new SF4Central(2);
	}

	
	sf4->ResumeGame();

	delete sf4;
	sf4 = NULL;

	BtnStartBtn.SetWindowTextW((LPCTSTR)StrToCStr("Unpause Game"));

}




void CTrainingArenaDlg::OnBnClickedController()
{
	// TODO: Add your control notification handler code here
	if(sf4!=NULL)
	{
		if(ControllerCheckBox.GetCheck())
			sf4->UseController(true);
		else
			sf4->UseController(false);
	}
}

void CTrainingArenaDlg::OnBnClickedHadokenButton()
{
	// TODO: Add your control notification handler code here
	if(sf4!=NULL)
	{
		sf4->ThrowHadoken();
	}
}

void CTrainingArenaDlg::OnBnClickedResetbtn()
{
	// TODO: Add your control notification handler code here
	if(sf4!=NULL)
		sf4->ResetDetect();
}
