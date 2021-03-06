
// EM measurement system V2Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"


// CEMmeasurementsystemV2Dlg dialog
class CEMmeasurementsystemV2Dlg : public CDialog
{
// Construction
public:
	CEMmeasurementsystemV2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EMMEASUREMENTSYSTEMV2_DIALOG };
#endif

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
public:
	CComboBox m_ctrlComNumber1;
	CComboBox m_ctrlComNumber2;
	CComboBox m_ctrlBaudRate1;
	CComboBox m_ctrlBaudRate2;
	CComboBox m_ctrlDataBits1;
	CComboBox m_ctrlDataBits2;
	CString m_strBaudRate1;
	CString m_strBaudRate2;
	CString m_strSendData;
	CString m_strRexvData;
private:
	bool m_comOK1;
	bool m_comOK2;
	int  m_ifCli;
public:
	CMscomm1 m_ctrlMscomm1;
	CMscomm1 m_ctrlMscomm2;
	afx_msg void OnBnClickedOpenbutton1();
	afx_msg void OnBnClickedOpenbutton2();
	CString m_strDataBits1;
	CString m_strDataBits2;
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	void OnCommMscomm2();
	afx_msg void OnBnClickedGeneratebutton();
	afx_msg void OnBnClickedClosebutton1();
	afx_msg void OnBnClickedClosebutton2();
	CEdit m_ctrlRexvData;
	afx_msg void OnBnClickedCleanbutton();
	afx_msg void OnBnClickedCalibrate();
	CString m_sampleNum;
	CEdit m_ctrlSampleNum;
	afx_msg void OnBnClickedMeasure();
	CString m_strRexvData2;
	afx_msg void OnEnChangeRexvdata();
	CString m_strRexvData3;
	CString m_strRexvData4;
	CEdit m_ctrlRexvData2;
	CEdit m_ctrlRexvData3;
	CEdit m_ctrlRexvData4;
};
