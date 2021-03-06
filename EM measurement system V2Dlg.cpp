
// EM measurement system V2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "EM measurement system V2.h"
#include "EM measurement system V2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEMmeasurementsystemV2Dlg dialog



CEMmeasurementsystemV2Dlg::CEMmeasurementsystemV2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_EMMEASUREMENTSYSTEMV2_DIALOG, pParent)
	, m_strBaudRate1(_T(""))
	, m_strBaudRate2(_T(""))
	, m_strSendData(_T(""))
	, m_strRexvData(_T(""))
	, m_comOK1(false)
	, m_comOK2(false)
	, m_ifCli(3)
	, m_strDataBits1(_T(""))
	, m_strDataBits2(_T(""))
	, m_sampleNum(_T(""))
	, m_strRexvData2(_T(""))
	, m_strRexvData3(_T(""))
	, m_strRexvData4(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEMmeasurementsystemV2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMNUMBER1, m_ctrlComNumber1);
	DDX_Control(pDX, IDC_COMNUMBER2, m_ctrlComNumber2);
	DDX_Control(pDX, IDC_BAUDRATE1, m_ctrlBaudRate1);
	DDX_Control(pDX, IDC_BAUDRATE2, m_ctrlBaudRate2);
	DDX_Control(pDX, IDC_DATABITS1, m_ctrlDataBits1);
	DDX_Control(pDX, IDC_DATABITS2, m_ctrlDataBits2);
	DDX_CBString(pDX, IDC_BAUDRATE1, m_strBaudRate1);
	DDX_CBString(pDX, IDC_BAUDRATE2, m_strBaudRate2);
	DDX_Text(pDX, IDC_SENDDATA, m_strSendData);
	DDX_Text(pDX, IDC_REXVDATA, m_strRexvData);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlMscomm1);
	DDX_Control(pDX, IDC_MSCOMM2, m_ctrlMscomm2);
	DDX_CBString(pDX, IDC_DATABITS1, m_strDataBits1);
	DDX_CBString(pDX, IDC_DATABITS2, m_strDataBits2);
	DDX_Control(pDX, IDC_REXVDATA, m_ctrlRexvData);
	DDX_Text(pDX, IDC_SAMPLENUM, m_sampleNum);
	DDX_Control(pDX, IDC_SAMPLENUM, m_ctrlSampleNum);
	DDX_Text(pDX, IDC_REXVDATA2, m_strRexvData2);
	DDX_Text(pDX, IDC_REXVDATA3, m_strRexvData3);
	DDX_Text(pDX, IDC_REXVDATA4, m_strRexvData4);
	DDX_Control(pDX, IDC_REXVDATA2, m_ctrlRexvData2);
	DDX_Control(pDX, IDC_REXVDATA3, m_ctrlRexvData3);
	DDX_Control(pDX, IDC_REXVDATA4, m_ctrlRexvData4);
}

BEGIN_MESSAGE_MAP(CEMmeasurementsystemV2Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENBUTTON1, &CEMmeasurementsystemV2Dlg::OnBnClickedOpenbutton1)
	ON_BN_CLICKED(IDC_OPENBUTTON2, &CEMmeasurementsystemV2Dlg::OnBnClickedOpenbutton2)
	ON_BN_CLICKED(IDC_GENERATEBUTTON, &CEMmeasurementsystemV2Dlg::OnBnClickedGeneratebutton)
	ON_BN_CLICKED(IDC_CLOSEBUTTON1, &CEMmeasurementsystemV2Dlg::OnBnClickedClosebutton1)
	ON_BN_CLICKED(IDC_CLOSEBUTTON2, &CEMmeasurementsystemV2Dlg::OnBnClickedClosebutton2)
	ON_BN_CLICKED(IDC_CLEANBUTTON, &CEMmeasurementsystemV2Dlg::OnBnClickedCleanbutton)
	ON_BN_CLICKED(IDC_BUTTON1, &CEMmeasurementsystemV2Dlg::OnBnClickedCalibrate)
	ON_BN_CLICKED(IDC_MEASURE, &CEMmeasurementsystemV2Dlg::OnBnClickedMeasure)
	ON_EN_CHANGE(IDC_REXVDATA, &CEMmeasurementsystemV2Dlg::OnEnChangeRexvdata)
END_MESSAGE_MAP()


// CEMmeasurementsystemV2Dlg message handlers

BOOL CEMmeasurementsystemV2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	int sampleNum = 1000;


	GetDlgItem(IDC_OPENBUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_OPENBUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_CLOSEBUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_CLOSEBUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEASURE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CLIBRATE)->EnableWindow(FALSE);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	m_ctrlComNumber1.AddString(_T("COM1"));
	m_ctrlComNumber1.AddString(_T("COM2"));
	m_ctrlComNumber1.AddString(_T("COM3"));
	m_ctrlComNumber1.AddString(_T("COM4"));
	m_ctrlComNumber1.AddString(_T("COM5"));
	m_ctrlComNumber1.SetCurSel(3);

	m_ctrlComNumber2.AddString(_T("COM1"));
	m_ctrlComNumber2.AddString(_T("COM2"));
	m_ctrlComNumber2.AddString(_T("COM3"));
	m_ctrlComNumber2.AddString(_T("COM4"));
	m_ctrlComNumber2.AddString(_T("COM5"));
	m_ctrlComNumber2.SetCurSel(2);

	m_ctrlBaudRate1.AddString(_T("9600"));
	m_ctrlBaudRate1.AddString(_T("4800"));
	m_ctrlBaudRate1.AddString(_T("13800"));
	SetDlgItemText(IDC_BAUDRATE1,_T("9600"));
	m_ctrlBaudRate1.UpdateData(FALSE);


	m_ctrlBaudRate2.AddString(_T("9600"));
	m_ctrlBaudRate2.AddString(_T("4800"));
	m_ctrlBaudRate2.AddString(_T("13800"));
	SetDlgItemText(IDC_BAUDRATE2, _T("9600"));
	m_ctrlBaudRate2.UpdateData(FALSE);

	m_ctrlDataBits1.AddString(_T("8"));
	m_ctrlDataBits1.AddString(_T("16"));
	m_ctrlDataBits1.SetCurSel(1);

	m_ctrlDataBits2.AddString(_T("8"));
	m_ctrlDataBits2.AddString(_T("16"));
	m_ctrlDataBits2.SetCurSel(1);

	SetDlgItemText(IDC_SAMPLENUM, _T("1000"));
	m_ctrlSampleNum.UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEMmeasurementsystemV2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEMmeasurementsystemV2Dlg::OnPaint()
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
HCURSOR CEMmeasurementsystemV2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CEMmeasurementsystemV2Dlg::OnBnClickedOpenbutton1()
{
	// TODO: Add your control notification handler code here
	int nSel1; 
	CString selComnumber1;

	if (m_ctrlMscomm1.get_PortOpen())
		m_ctrlMscomm1.put_PortOpen(FALSE);
	
	nSel1 = m_ctrlComNumber1.GetCurSel();  
	selComnumber1.Format(_T("%d"), nSel1 + 1);
	m_ctrlMscomm1.put_CommPort(nSel1 + 1);//Select COM  
	m_ctrlMscomm1.put_InputMode(1);       
	m_ctrlMscomm1.put_InBufferSize(1024); 
	m_ctrlMscomm1.put_OutBufferSize(1024); 
	
	CString str;
	int selBaudRate1 = GetDlgItemInt(IDC_BAUDRATE1);
	str.Format(_T("%d"), selBaudRate1);
	CString selDataBits1;
	GetDlgItemText(IDC_DATABITS1, selDataBits1);

	str = str + _T(",n,") + selDataBits1 + _T(",1");
	m_ctrlMscomm1.put_Settings(str);//Set parameters

	if (!m_ctrlMscomm1.get_PortOpen())
	{
		m_ctrlMscomm1.put_PortOpen(TRUE);//Open COM
		m_ctrlMscomm1.put_RThreshold(2);   
										//m_ctrlMscomm1.put_Settings(_T("9600,n,8,1"));  
		m_ctrlMscomm1.put_InputMode(1);  
		m_ctrlMscomm1.put_RThreshold(1);    
		m_ctrlMscomm1.put_InputLen(0);    
		m_ctrlMscomm1.get_Input(); 
		MessageBox(_T("COM")+selComnumber1+_T(" is opened successfully!"));
		GetDlgItem(IDC_OPENBUTTON1)->EnableWindow(FALSE);
		GetDlgItem(IDC_CLOSEBUTTON1)->EnableWindow(TRUE);
		GetDlgItem(IDC_MEASURE)->EnableWindow(TRUE);

		m_comOK1 = true;  
	}
	else
	{
		MessageBox(_T("COM") + selComnumber1 + _T(" cannot be opened!"));
		m_comOK1 = false;
	}
		

}
	   
	 


void CEMmeasurementsystemV2Dlg::OnBnClickedOpenbutton2()
{
	// TODO: Add your control notification handler code here
	int nSel2;
	CString selComnumber2;

	if (m_ctrlMscomm2.get_PortOpen()) 
		m_ctrlMscomm2.put_PortOpen(FALSE);

	nSel2 = m_ctrlComNumber2.GetCurSel();  
	selComnumber2.Format(_T("%d"), nSel2 + 1);
	m_ctrlMscomm2.put_CommPort(nSel2 + 1);  
	m_ctrlMscomm2.put_InputMode(1);       
	m_ctrlMscomm2.put_InBufferSize(1024); 
	m_ctrlMscomm2.put_OutBufferSize(1024);

	CString str;
	int selBaudRate2 = GetDlgItemInt(IDC_BAUDRATE2);
	str.Format(_T("%d"), selBaudRate2);
	CString selDataBits2;
	GetDlgItemText(IDC_DATABITS2, selDataBits2);

	str = str + _T(",n,") + selDataBits2 + _T(",1");
	m_ctrlMscomm2.put_Settings(str);

	if (!m_ctrlMscomm2.get_PortOpen())
	{
		m_ctrlMscomm2.put_PortOpen(TRUE);  
		m_ctrlMscomm2.put_InputMode(1);     
		m_ctrlMscomm2.put_RThreshold(1);    
		m_ctrlMscomm2.put_InputLen(0);    
		m_ctrlMscomm2.get_Input(); 
		MessageBox(_T("COM") + selComnumber2 + _T(" is opened successfully!"));
		GetDlgItem(IDC_OPENBUTTON2)->EnableWindow(FALSE);
		GetDlgItem(IDC_CLOSEBUTTON2)->EnableWindow(TRUE);
		m_comOK2 = true;     
	}
	else
	{
		MessageBox(_T("COM") + selComnumber2 + _T(" cannot be opened!"));
		m_comOK2 = false;
	}

}
BEGIN_EVENTSINK_MAP(CEMmeasurementsystemV2Dlg, CDialog)
	ON_EVENT(CEMmeasurementsystemV2Dlg, IDC_MSCOMM1, 1, CEMmeasurementsystemV2Dlg::OnCommMscomm1, VTS_NONE)
	ON_EVENT(CEMmeasurementsystemV2Dlg, IDC_MSCOMM2, 1, CEMmeasurementsystemV2Dlg::OnCommMscomm2, VTS_NONE)
END_EVENTSINK_MAP()


void CEMmeasurementsystemV2Dlg::OnCommMscomm1()
{
	// TODO: Add your message handler code here
	VARIANT variant_inp;    
	COleSafeArray safearray_inp;
	LONG len, k;
	BYTE rxdata[2048]; //Set BYTE array An 8-bit integer that is not signed.       
	CString strtemp;
	unsigned char flag;

	if (m_ctrlMscomm1.get_CommEvent() == 2 && m_ifCli == 2)      
	{
		Sleep(1000);
		variant_inp = m_ctrlMscomm1.get_Input();     //Read buffer  
		safearray_inp = variant_inp;              //Transfer variant to ColeSafeArray 
		len = safearray_inp.GetOneDimSize();      //Get data length        
		for (k = 0; k<len; k++)
			safearray_inp.GetElement(&k, rxdata + k);          
		for (k = 0; k<len; k++)                          
		{
			BYTE bt = *(char*)(rxdata + k);
			strtemp.Format(_T("%c"), bt); 
			char ch = (char)bt;
			if (ch == '!')
			{
				flag = 1; continue;
			}
			if (ch == '@')
			{
				flag = 3; continue;
			}
			if (ch == '#')
			{
				flag = 2; continue;
			}
			if (ch == '%')
			{
				flag = 4; continue;
			}
			if (ch == '<')
			{
				break;
			}

			switch (flag)                //加入接收编辑框对应字符串   
			{
			case 1:    m_strRexvData += strtemp;
				break;
			case 2:    m_strRexvData2 += strtemp;
				break;
			case 3:    m_strRexvData3 += strtemp;
				break;
			case 4:    m_strRexvData4 += strtemp;
				break;
			default:break;
			}        
		}
	}
	else if (m_ctrlMscomm1.get_CommEvent() == 2 && m_ifCli == 3)
	{
		Sleep(1000);
		variant_inp = m_ctrlMscomm1.get_Input();     //Read buffer  
		safearray_inp = variant_inp;              //Transfer variant to ColeSafeArray 
		len = safearray_inp.GetOneDimSize();      //Get data length        
		for (k = 0; k<len; k++)
			safearray_inp.GetElement(&k, rxdata + k);
		for (k = 0; k<len; k++)
		{
			BYTE bt = *(char*)(rxdata + k);
			strtemp.Format(_T("%c"), bt);
			char ch = (char)bt;
			if (ch == '^')
			{
				flag = 1; continue;
			}
			if (ch == '?')
			{
				flag = 3; continue;
			}
			if (ch == '&')
			{
				flag = 2; continue;
			}
			if (ch == '*')
			{
				flag = 4; continue;
			}
			if (ch == '>')
			{
				break;
			}

			switch (flag)                //加入接收编辑框对应字符串   
			{
			case 1:    m_strRexvData += strtemp;
				break;
			case 2:    m_strRexvData2 += strtemp;
				break;
			case 3:    m_strRexvData3 += strtemp;
				break;
			case 4:    m_strRexvData4 += strtemp;
				break;
			default:break;
			}
		}
	}
	//SetDlgItemText(IDC_REXVDATA, m_strRexvData);
	UpdateData(FALSE); 
	m_ctrlRexvData.LineScroll(m_ctrlRexvData.GetLineCount());
	m_ctrlRexvData2.LineScroll(m_ctrlRexvData2.GetLineCount());
	m_ctrlRexvData3.LineScroll(m_ctrlRexvData3.GetLineCount());
	m_ctrlRexvData4.LineScroll(m_ctrlRexvData4.GetLineCount());
	//m_strRexvData.Empty();
}


void CEMmeasurementsystemV2Dlg::OnCommMscomm2()
{
	// TODO: Add your message handler code here

}


void CEMmeasurementsystemV2Dlg::OnBnClickedGeneratebutton()
{
	// TODO: Add your control notification handler code here
	if (m_comOK2 == true)      
	{
		UpdateData(TRUE);  
		CString strSend = COleVariant(m_strSendData);
		int sendData = _ttoi(strSend);
		if (sendData >= 800000 && sendData <= 2700000)
		{
			m_ctrlMscomm2.put_Output(COleVariant(m_strSendData)); //Send data
			MessageBox(_T("Frequency is successfully set as ")+strSend+_T(" KHz"));
		}
		else
		{
			MessageBox(_T("Invalid frequency!"));
		}
	}
	else
	{
		MessageBox(_T("Please open a COM!"));
	}
}


void CEMmeasurementsystemV2Dlg::OnBnClickedClosebutton1()
{
	// TODO: Add your control notification handler code here
	m_comOK1 = false;
	m_ctrlMscomm1.put_PortOpen(FALSE);//Close COM
	GetDlgItem(IDC_OPENBUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_CLOSEBUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_MEASURE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CLIBRATE)->EnableWindow(FALSE);

}


void CEMmeasurementsystemV2Dlg::OnBnClickedClosebutton2()
{
	// TODO: Add your control notification handler code here
	m_comOK2 = false;
	m_ctrlMscomm2.put_PortOpen(FALSE);//Close COM
	GetDlgItem(IDC_OPENBUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_CLOSEBUTTON2)->EnableWindow(FALSE);
}


void CEMmeasurementsystemV2Dlg::OnBnClickedCleanbutton()
{
	// TODO: Add your control notification handler code here
	SetDlgItemText(IDC_REXVDATA, NULL);
	SetDlgItemText(IDC_REXVDATA2, NULL);
	SetDlgItemText(IDC_REXVDATA3, NULL);
	SetDlgItemText(IDC_REXVDATA4, NULL);

}


void CEMmeasurementsystemV2Dlg::OnBnClickedCalibrate()
{
	// TODO: Add your control notification handler code here
	m_ifCli = 3;
	m_ctrlMscomm1.put_PortOpen(FALSE);
	m_ctrlMscomm1.put_Settings(_T("9600,n,8,1"));
	m_ctrlMscomm1.put_PortOpen(TRUE);//Open COM
	m_ctrlMscomm1.put_RThreshold(2);
	//m_ctrlMscomm1.put_Settings(_T("9600,n,8,1"));  
	m_ctrlMscomm1.put_InputMode(1);
	m_ctrlMscomm1.put_RThreshold(1);
	m_ctrlMscomm1.put_InputLen(0);
	m_ctrlMscomm1.get_Input();
	GetDlgItem(IDC_MEASURE)->EnableWindow(TRUE);
	GetDlgItem(IDC_CLIBRATE)->EnableWindow(FALSE);


}


void CEMmeasurementsystemV2Dlg::OnBnClickedMeasure()
{
	// TODO: Add your control notification handler code here
	m_ifCli = 2;
	m_ctrlMscomm1.put_PortOpen(FALSE);
	m_ctrlMscomm1.put_Settings(_T("9600,n,8,1"));
	m_ctrlMscomm1.put_PortOpen(TRUE);//Open COM
	m_ctrlMscomm1.put_RThreshold(2);
	//m_ctrlMscomm1.put_Settings(_T("9600,n,8,1"));  
	m_ctrlMscomm1.put_InputMode(1);
	m_ctrlMscomm1.put_RThreshold(1);
	m_ctrlMscomm1.put_InputLen(0);
	m_ctrlMscomm1.get_Input();
	GetDlgItem(IDC_MEASURE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CLIBRATE)->EnableWindow(TRUE);
}


void CEMmeasurementsystemV2Dlg::OnEnChangeRexvdata()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
