
// pulseMonitorDlg.cpp : implementation file
/*****************************************************************************
    2013 - 2015(C) Alex Dobrianski pulsar pattern recognition software
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
    Design and development by Team "Plan B" is licensed under 
    a Creative Commons Attribution-ShareAlike 3.0 Unported License.
    http://creativecommons.org/licenses/by-sa/3.0/ 
******************************************************************************/

#include "stdafx.h"
#include "pulseMonitor.h"
#include "pulseMonitorDlg.h"
#include "afxdialogex.h"
#include "mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CpulseMonitorDlg dialog




CpulseMonitorDlg::CpulseMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CpulseMonitorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpulseMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_SEC_PER_SCREEN, m_SecPerScreen);
    DDX_Control(pDX, IDC_DATETIMEPICKERTIME, m_Time);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DATA, m_Date);
    DDX_Control(pDX, IDC_CHECK_LAST, m_LastTime);
    //  DDX_Control(pDX, IDC_STATIC_MAIN_SIGNAL, m_Signal);
    //  DDX_Control(pDX, IDC_STATIC_MAIN_SIGNAL, m_Signal);
    DDX_Control(pDX, IDC_STATIC_MAIN_SIGNAL, m_SIgnal);
    DDX_Control(pDX, IDC_SLIDER_MAIN, m_SLider);
    DDX_Control(pDX, IDC_CHECK_DOTS_LINES, m_ShowLines);
}

BEGIN_MESSAGE_MAP(CpulseMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_EN_CHANGE(IDC_EDIT_SOURCE_XML, &CpulseMonitorDlg::OnEnChangeEdit1)
    ON_LBN_SELCHANGE(IDC_LIST_SEC_PER_SCREEN, &CpulseMonitorDlg::OnLbnSelchangeListSecPerScreen)
    ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MAIN, &CpulseMonitorDlg::OnNMCustomdrawSlider1)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_CHECK_LAST, &CpulseMonitorDlg::OnBnClickedCheckLast)
    ON_BN_CLICKED(IDC_CHECK_DOTS_LINES, &CpulseMonitorDlg::OnBnClickedCheckDotsLines)
END_MESSAGE_MAP()


	PCMWAVEFORMAT format;
    LPHWAVEIN m_hWaveIn;
    BOOL fInsideCallBack = FALSE;
    WAVEHDR WAVEHDRMain;
//#define SAMPLES_PER_SEC 44100
#define SAMPLES_PER_SEC 250000
#define NUMBER_OF_CHANNELS 2
    char BUFERSND0_0[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*2];
    char BUFERSND0_1[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*2];

	char BUFERSND1_0[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*2];
    char BUFERSND1_1[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*2];
	BOOL DOStop =  FALSE;
	WAVEHDR WaveHdr_0;
    WAVEHDR WaveHdr_1;
    int g_SecondsPerScreen;
    int g_FractionsPerScreen;
    int g_isecond;
    int g_i1Max = 128*256;
    int g_i2Max = 128*256;
    int g_i1Min = -128*256;
    int g_i2Min = -128*256;

// CpulseMonitorDlg message handlers
#include "JPEGLIB.H"
void
write_JPEG_file (char * filename, 
				 int quality, 
				 int SizeW, 
				 int SizeH, 
				 int SizeB, 
				 unsigned char *bArray, 
				 J_COLOR_SPACE ColorCode
				 );

//#define IMAGE_W 1280
//#define IMAGE_H 720
//#define IMAGE_W 1090
#define IMAGE_W 1024
#define IMAGE_H 150
//int RGBReferenceBody = EARTH;
unsigned char bRGBImage[IMAGE_W*IMAGE_H*3];
int bRGBImageW = IMAGE_W;
int bRGBImageH = IMAGE_H;
unsigned char PiCRGB[3] = {0x00,0x00,0x00};
unsigned char PiCRGBGray[3] = {0x80,0x80,0x80};
unsigned char PiCRGBBlue[3] = {0x00,0x00,0xFF};

void putpixel(unsigned char *bRGB, int X, int Y)
{
    int iRow = (X) + (bRGBImageH - (Y))*bRGBImageW-1;
    if ((iRow*3 >=0) && (iRow*3 < (sizeof(bRGBImage) -3)))
    {
        memcpy(&bRGBImage[iRow*3],bRGB, 3);
    }
}
// should be no longer than 1 sec 
LRESULT CALLBACK AudioStreamCallback(HWND hwndC,LPWAVEHDR lpWAVEHDR)
{

    int iSize = format.wf.nBlockAlign;
    int iPoints = bRGBImageW/g_SecondsPerScreen;
    int i1SecRep = lpWAVEHDR->dwBufferLength/ iPoints;
    int iCurmsc = 0;
    if (g_isecond >= g_SecondsPerScreen)
    {
        g_isecond = 0;
        memset(bRGBImage, 0xff, sizeof(bRGBImage));
    }
    int i1Max = -128*256;
    int i2Max = -128*256;
    int i1Min = 128*256;
    int i2Min = 128*256;
    for (int i = 0; i < lpWAVEHDR->dwBufferLength; i+=iSize)
    {
        signed short iVal1 = *(signed short *)&lpWAVEHDR->lpData[i];
        signed short iVal2 = *(signed short *)&lpWAVEHDR->lpData[i+2];
        if (iVal1 > i1Max)
            i1Max = iVal1;
        if (iVal1 < i1Min)
            i1Min = iVal1;
        if (iVal2 > i2Max)
            i2Max = iVal2;
        if (iVal2 < i2Min)
            i2Min = iVal2;
    }
    for (int j = 1; j <bRGBImageH; j++)
    {
        putpixel(PiCRGBGray, g_isecond*iPoints+1, j);
    }
    g_i1Max = (g_i1Max*9 + i1Max)/10;
    g_i1Min = (g_i1Min*9 + i1Min)/10;
    g_i2Max = (g_i2Max*9 + i2Max)/10;
    g_i2Min = (g_i2Min*9 + i2Min)/10;

    int i1Mid = (g_i1Min+g_i1Max)/2;
    int i2Mid = (g_i2Min+g_i2Max)/2;
    int i1M = (g_i1Max-g_i1Min);
    int i2M = (g_i2Max-g_i2Min);

    for (int i = 0; i < lpWAVEHDR->dwBufferLength; i+=i1SecRep)
    {
        signed short iVal1 = *(signed short *)&lpWAVEHDR->lpData[i];
        signed short iVal2 = *(signed short *)&lpWAVEHDR->lpData[i+2];
        int iiVal1 = iVal1;
        int iiVal2 = iVal2;
        putpixel(PiCRGBGray, g_isecond*iPoints+iCurmsc, bRGBImageH/4);
        //putpixel(PiCRGBBlue, g_isecond*iPoints+iCurmsc, bRGBImageH/4 + (((bRGBImageH*(iiVal1-i1Mid))/4)/256)/128 );
        putpixel(PiCRGBBlue, g_isecond*iPoints+iCurmsc, bRGBImageH/4 + ((bRGBImageH*(iiVal1-i1Mid))/4)/i1M );
        putpixel(PiCRGBGray, g_isecond*iPoints+iCurmsc, (bRGBImageH*3)/4);
        //putpixel(PiCRGBBlue, g_isecond*iPoints+iCurmsc, (bRGBImageH*3)/4 + (((bRGBImageH*(iiVal2-i2Mid))/4)/256)/128 );
        putpixel(PiCRGBBlue, g_isecond*iPoints+iCurmsc, (bRGBImageH*3)/4 + ((bRGBImageH*(iiVal2-i2Mid))/4)/i2M);
        iCurmsc++;
        //if (iCurmsc >= iPoints)
        //    break;
    }
    g_isecond++;
	return(0);
}
SYSTEMTIME mySYsTime;
void CALLBACK waveInProc(  HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2 )
{
    WAVEHDR *pWaveHdr = (WAVEHDR *)dwParam1;
    GetLocalTime(&mySYsTime);
	if (WIM_DATA == uMsg)
	{
		fInsideCallBack = TRUE;
        WAVEHDRMain.dwBufferLength = pWaveHdr->dwBufferLength;
        if ((void*)(pWaveHdr->lpData) == (void*)&BUFERSND0_0) // is it first buffer?
        {
            memcpy(BUFERSND1_0,BUFERSND0_0,sizeof(BUFERSND1_0));
            WAVEHDRMain.lpData = BUFERSND1_0;
    		waveInUnprepareHeader( (HWAVEIN)m_hWaveIn,(LPWAVEHDR)&WaveHdr_0,sizeof(WAVEHDR)  );
	    	if (DOStop ==  FALSE)
		    {
			    waveInPrepareHeader( (HWAVEIN)m_hWaveIn, (LPWAVEHDR)&WaveHdr_0, sizeof(WAVEHDR) );
			    waveInAddBuffer( (HWAVEIN)	m_hWaveIn,(LPWAVEHDR)&WaveHdr_0, sizeof(WAVEHDR));
		    }

        }
        else if ((void*)(pWaveHdr->lpData) == (void*)&BUFERSND0_1) // is it first buffer?
        {
            memcpy(BUFERSND1_1,BUFERSND0_1,sizeof(BUFERSND1_1));
            WAVEHDRMain.lpData = BUFERSND1_1;
    		waveInUnprepareHeader( (HWAVEIN)m_hWaveIn,(LPWAVEHDR)&WaveHdr_1,sizeof(WAVEHDR)  );
	    	if (DOStop ==  FALSE)
		    {
			    waveInPrepareHeader( (HWAVEIN)m_hWaveIn, (LPWAVEHDR)&WaveHdr_1, sizeof(WAVEHDR) );
			    waveInAddBuffer( (HWAVEIN)	m_hWaveIn,(LPWAVEHDR)&WaveHdr_1, sizeof(WAVEHDR));
		    }

        }

        WAVEHDRMain.dwBytesRecorded = pWaveHdr->dwBytesRecorded;
        WAVEHDRMain.dwFlags = pWaveHdr->dwFlags;
        WAVEHDRMain.dwLoops = pWaveHdr->dwLoops;
        WAVEHDRMain.reserved =pWaveHdr->reserved;
        
		AudioStreamCallback(NULL,&WAVEHDRMain);
		fInsideCallBack = FALSE;
	}
}
void StartWAVCapture(void)
{
	MMRESULT Mres;
	if (m_hWaveIn==0)
	{
		format.wf.wFormatTag =  WAVE_FORMAT_PCM;
        
		format.wf.nChannels = NUMBER_OF_CHANNELS;
		format.wf.nSamplesPerSec = SAMPLES_PER_SEC;//441000;
        format.wBitsPerSample = 16;
        if (format.wBitsPerSample  == 8)
		    format.wf.nAvgBytesPerSec = format.wf.nSamplesPerSec*format.wf.nChannels;//441000;
        else
            format.wf.nAvgBytesPerSec = format.wf.nSamplesPerSec*format.wf.nChannels*2;//441000;
		format.wf.nBlockAlign =  (short)((format.wf.nChannels * format.wBitsPerSample) / 8);


		// open the device, have message come back to frame window
		Mres = waveInOpen(
						  (LPHWAVEIN) &m_hWaveIn,
							0,
							(LPWAVEFORMATEX)(&format),
							(DWORD)waveInProc,
							(DWORD) 0,
							(DWORD) CALLBACK_FUNCTION 
							);
		if (Mres !=	MMSYSERR_NOERROR  )
			 return;
			 
		WaveHdr_0.lpData=BUFERSND0_0;
        //WaveHdr_0.lpNext=WaveHdr_1;
		WaveHdr_0.dwBufferLength = sizeof(BUFERSND0_0);
		WaveHdr_0.dwBytesRecorded = 0L;
		WaveHdr_0.dwFlags = 0L;
		WaveHdr_0.dwLoops = 0L;
		WaveHdr_0.dwUser = 0x1234;
		if (waveInPrepareHeader( (HWAVEIN)m_hWaveIn,
							  (LPWAVEHDR)&WaveHdr_0,
							  sizeof(WAVEHDR) )	)
		{
		}
		if (waveInAddBuffer( (HWAVEIN)	m_hWaveIn,
						 (LPWAVEHDR)&WaveHdr_0,
						 sizeof(WAVEHDR))  )
		{
		}
        // second buffer
        WaveHdr_1.lpData=BUFERSND0_1;
        //WaveHdr_1.lpNext=WaveHdr_0;
		WaveHdr_1.dwBufferLength = sizeof(BUFERSND0_1);
		WaveHdr_1.dwBytesRecorded = 0L;
		WaveHdr_1.dwFlags = 0L;
		WaveHdr_1.dwLoops = 0L;
		WaveHdr_1.dwUser = 0x1234;
		if (waveInPrepareHeader( (HWAVEIN)m_hWaveIn,
							  (LPWAVEHDR)&WaveHdr_1,
							  sizeof(WAVEHDR) )	)
		{
		}
		if (waveInAddBuffer( (HWAVEIN)	m_hWaveIn,
						 (LPWAVEHDR)&WaveHdr_1,
						 sizeof(WAVEHDR))  )
		{
		}

		if (waveInStart((HWAVEIN)m_hWaveIn))
		{
		}
		DOStop =  FALSE;
	}
}
void StopWAVCapture(void)
{
	MMRESULT Mres;
	DOStop =  TRUE;
	if (m_hWaveIn)
	{
        DOStop = TRUE;
        for (int i = 0; i < 15; i++)
        {
            Sleep(200);
        }
		Mres = waveInStop((HWAVEIN)m_hWaveIn);
       
		Mres = waveInReset((HWAVEIN)m_hWaveIn);
		Mres = waveInUnprepareHeader( (HWAVEIN)m_hWaveIn,
								(LPWAVEHDR)&WaveHdr_0,
								sizeof(WAVEHDR)  );
   		Mres = waveInUnprepareHeader( (HWAVEIN)m_hWaveIn,
								(LPWAVEHDR)&WaveHdr_1,
								sizeof(WAVEHDR)  );

		Mres = waveInClose((HWAVEIN)m_hWaveIn);
		m_hWaveIn=0;
	}
    memset(bRGBImage, 0xff, sizeof(bRGBImage));
}

BOOL CpulseMonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
    StartWAVCapture();
    m_SecPerScreen.AddString("0.9765625 ms");
    m_SecPerScreen.AddString("1.953125 ms");
    m_SecPerScreen.AddString("3.90625 ms");
    m_SecPerScreen.AddString("7.8125 ms");
    m_SecPerScreen.AddString("15.625 ms");
    m_SecPerScreen.AddString("31.25 ms");
    m_SecPerScreen.AddString("62.5 ms");
    m_SecPerScreen.AddString("125 sec");
    m_SecPerScreen.AddString("250 ms");
    m_SecPerScreen.AddString("500 ms");

    m_SecPerScreen.AddString("1 sec");
    m_SecPerScreen.AddString("2 sec");
    m_SecPerScreen.AddString("4 sec");
    m_SecPerScreen.AddString("8 sec");
    m_SecPerScreen.AddString("16 sec");
    m_SecPerScreen.AddString("32 sec");
    m_SecPerScreen.AddString("64 sec");
    m_SecPerScreen.AddString("128 sec");
    m_SecPerScreen.AddString("256 sec");
    m_SecPerScreen.AddString("512 sec");
    m_SecPerScreen.SetCurSel(10);
    m_FractionsPerScreen = 1;
    g_FractionsPerScreen = m_FractionsPerScreen;
    m_SecondsPerScreen = 1;
    g_SecondsPerScreen = m_SecondsPerScreen;
    g_isecond = 0;
    hBmpMainSignal = NULL;
    memset(bRGBImage, 0xff, sizeof(bRGBImage));
    //SYSTEMTIME mySYsTime;
    GetLocalTime(&mySYsTime);
    
    CTime MyTime = CTime(mySYsTime);

    m_Time.SetTime(&MyTime);
    m_Date.SetTime(&MyTime);
    m_LastTime.SetCheck(1);
    m_ShowLines.SetCheck(0);
    SetTimer(901,1000,NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CpulseMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CpulseMonitorDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CpulseMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CpulseMonitorDlg::OnEnChangeEdit1()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialogEx::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}


BOOL CpulseMonitorDlg::DestroyWindow()
{
    // TODO: Add your specialized code here and/or call the base class
    KillTimer(901);
    if (hBmpMainSignal!=NULL)
        DeleteObject(hBmpMainSignal);

    StopWAVCapture();
    return CDialogEx::DestroyWindow();
}


void CpulseMonitorDlg::OnLbnSelchangeListSecPerScreen()
{
    // TODO: Add your control notification handler code here
    switch(m_SecPerScreen.GetCurSel())
    {
    case 0:  m_SecondsPerScreen = 1; m_FractionsPerScreen =512;break;
    case 1:  m_SecondsPerScreen = 1; m_FractionsPerScreen =256;break;
    case 2:  m_SecondsPerScreen = 1; m_FractionsPerScreen =128;break;
    case 3:  m_SecondsPerScreen = 1; m_FractionsPerScreen =64;break;
    case 4:  m_SecondsPerScreen = 1; m_FractionsPerScreen =32;break;
    case 5:  m_SecondsPerScreen = 1; m_FractionsPerScreen =16;break;
    case 6:  m_SecondsPerScreen = 1; m_FractionsPerScreen =8;break;
    case 7:  m_SecondsPerScreen = 1; m_FractionsPerScreen =4;break;
    case 8:  m_SecondsPerScreen = 1; m_FractionsPerScreen =2;break;
    case 9:  m_SecondsPerScreen = 1; m_FractionsPerScreen =1;break;
    case 10:  m_SecondsPerScreen = 1; m_FractionsPerScreen =1;break;
    case 11:  m_SecondsPerScreen = 2; m_FractionsPerScreen =1;break;
    case 12:  m_SecondsPerScreen = 4; m_FractionsPerScreen =1;break;
    case 13:  m_SecondsPerScreen = 8; m_FractionsPerScreen =1;break;
    case 14:  m_SecondsPerScreen = 16; m_FractionsPerScreen =1;break;
    case 15:  m_SecondsPerScreen = 32; m_FractionsPerScreen =1;break;
    case 16:  m_SecondsPerScreen = 64; m_FractionsPerScreen =1;break;
    case 17:  m_SecondsPerScreen = 128; m_FractionsPerScreen =1;break;
    case 18:  m_SecondsPerScreen = 256; m_FractionsPerScreen =1;break;
    case 19:  m_SecondsPerScreen = 512; m_FractionsPerScreen =1;break;
    }
    g_SecondsPerScreen = m_SecondsPerScreen;
    g_FractionsPerScreen = m_FractionsPerScreen;
}


void CpulseMonitorDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
    // TODO: Add your control notification handler code here
    *pResult = 0;
}


void CpulseMonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    if (nIDEvent== 901)
    {
        //SYSTEMTIME mySYsTime;
        //GetLocalTime(&mySYsTime);
        if (m_LastTime.GetCheck() == 1)
        {
            myShowSysTime = mySYsTime;
            CTime MyTime = CTime(myShowSysTime);

            m_Time.SetTime(&MyTime);
            m_Date.SetTime(&MyTime);
        }
        BITMAPINFO binfMainLogo;
       	memset((void*)&binfMainLogo,0,sizeof(binfMainLogo));

        if (hBmpMainSignal!=NULL)
    		DeleteObject(hBmpMainSignal);



        // get a DC  
        HDC         hDC;                    
        hDC = ::GetDC(NULL); 
 		// create bitmap from DIB info. and bits 
        RECT myRect;
        m_SIgnal.GetWindowRect(&myRect);
        RECT MainRect;
        GetWindowRect(&MainRect);
        RECT SliderRect;
        m_SLider.GetWindowRect(&SliderRect);

        

		binfMainLogo.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
        binfMainLogo.bmiHeader.biWidth = bRGBImageW;//read_image_width; 
        binfMainLogo.bmiHeader.biHeight = bRGBImageH;//read_image_height; 
		binfMainLogo.bmiHeader.biPlanes = 1; 
		binfMainLogo.bmiHeader.biBitCount = 24; 
		binfMainLogo.bmiHeader.biCompression = BI_RGB; 
		binfMainLogo.bmiHeader.biSizeImage = 0; 
		binfMainLogo.bmiHeader.biXPelsPerMeter = 0; 
		binfMainLogo.bmiHeader.biYPelsPerMeter = 0; 
		binfMainLogo.bmiHeader.biClrUsed = 0; 
		binfMainLogo.bmiHeader.biClrImportant = 0; 
		hBmpMainSignal = CreateDIBitmap(hDC, &(binfMainLogo.bmiHeader), CBM_INIT, bRGBImage, &binfMainLogo, DIB_RGB_COLORS); 
		::ReleaseDC(NULL, hDC); 
        //((CStatic*)GetDlgItem(IDC_STATIC_MAIN_SIGNAL))->SetBitmap(hBmpMainSignal);
        //GetDlgItem(IDC_STATIC_MAIN_SIGNAL)->UpdateWindow();
        m_SIgnal.SetBitmap(hBmpMainSignal);
        //RECT myRect;
        m_SIgnal.GetWindowRect(&myRect);
        m_SIgnal.ValidateRect(&myRect);
        m_SIgnal.UpdateWindow();
    }
    CDialogEx::OnTimer(nIDEvent);
}


void CpulseMonitorDlg::OnBnClickedCheckLast()
{
    // TODO: Add your control notification handler code here

    //m_LastTime.SetCheck(0)
}


void CpulseMonitorDlg::OnBnClickedCheckDotsLines()
{
    // TODO: Add your control notification handler code here
}
