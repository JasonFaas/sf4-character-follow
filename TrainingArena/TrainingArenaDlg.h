// TrainingArenaDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <stdio.h>
#include <winsock2.h>

#include <iostream>

#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
#include <odbcinst.h>

#include "afxdb.h"
#include <windows.h>




#include "..\..\..\..\GenericFunctions\FaasStringFunctions.h"
;
#include "SF4Central.h"
;


// CTrainingArenaDlg dialog
class CTrainingArenaDlg : public CDialog
{
// Construction
public:
	CTrainingArenaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TRAININGARENA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


	SF4Central * sf4;
	HANDLE _sfThread;
	static DWORD StartSecondMainThread(void * param);
	void RunSecondMainThread();

public:
	afx_msg void OnBnClickedBtnstart();
	CButton BtnStartBtn;


	
	afx_msg void OnBnClickedController();
	CButton ControllerCheckBox;
	afx_msg void OnBnClickedHadokenButton();
	CEdit RecordFileName;
	CEdit recordFrames;
	afx_msg void OnBnClickedResetbtn();
};
