
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
}

BEGIN_MESSAGE_MAP(CpulseMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_EN_CHANGE(IDC_EDIT_SOURCE_XML, &CpulseMonitorDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


	PCMWAVEFORMAT format;
    LPHWAVEIN m_hWaveIn;
    BOOL fInsideCallBack = FALSE;
    WAVEHDR WAVEHDRMain;
    char BUFERSND0[8000];
	char BUFERSND1[8000];
	BOOL DOStop =  FALSE;
	WAVEHDR WaveHdr;
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

#define IMAGE_W 1280
#define IMAGE_H 720
//int RGBReferenceBody = EARTH;
unsigned char bRGBImage[IMAGE_W*IMAGE_H*3];
int bRGBImageW = IMAGE_W;
int bRGBImageH = IMAGE_H;
unsigned char PiCRGB[3] = {0x00,0x00,0x00};
unsigned char PiCRGBBlue[3] = {0x00,0x00,0xFF};

void putpixel(unsigned char *bRGB, int X, int Y)
{
    int iRow = (X) + (bRGBImageH - (Y))*bRGBImageW;
    if ((iRow*3 >=0) && (iRow*3 < (sizeof(bRGBImage) -3)))
    {
        memcpy(&bRGBImage[iRow*3],bRGB, 3);
    }
}

LRESULT CALLBACK AudioStreamCallback(HWND hwndC,LPWAVEHDR lpWAVEHDR)
{
    for (int i = 0; i < lpWAVEHDR->dwBufferLength; i++)
    {
        signed char iVal = lpWAVEHDR->lpData[i];

    }
    /*
	int i,j, k, StoringLength;
	char szAudioFN[_MAX_PATH];
	(MyCCgApp->CountCaptureCurrent)++;

	StoringLength = lpWAVEHDR->dwBufferLength;

	if (iAudioBegin + StoringLength < iAudioEnd)
	{
		memcpy(&bAudioFrame[iAudioBegin], lpWAVEHDR->lpData, lpWAVEHDR->dwBufferLength);

		iAudioBegin += lpWAVEHDR->dwBufferLength;
		
	}
	else
	{
		int iLastCopyBeforSave = (iAudioEnd - iAudioBegin) &0xfffffff0;
		int iLastCopyAfterSave = lpWAVEHDR->dwBufferLength - iLastCopyBeforSave;

			memcpy(&bAudioFrame[iAudioBegin], lpWAVEHDR->lpData, iLastCopyBeforSave);
			iAudioBegin += iLastCopyBeforSave;

		// if we transmitting now this file then skip save to it and save to next one;
		if (TransmitAudioFile == AudioFileNumber)
		{
			IncAudio(AudioFileNumber);
		}
		strcpy(szAudioFN, MyCCgApp->m_HTMLPath);
		strcat(szAudioFN, "\\");
		strcat(szAudioFN,AudioFileNames[AudioFileNumber]);

		int iIFN = ImageFileNumber;
		DecImage(iIFN);
		AudioToImageTo[AudioFileNumber] = ImageFileNumber;

		if (AudioFilesNow == 0)
		{
			AudioToImageFrom[AudioFileNumber] = 0;
			AudioTimeStamp[AudioFileNumber] = TimeTick - //timeGetTime() - StartTime -
				iAudioBegin /8;
		}

		*(DWORD*)&(AudioStmp[AudioFileNumber].dwAudioTimeCurent) = 
			AudioTimeStamp[AudioFileNumber];

		*(__int64*)&(AudioStmp[AudioFileNumber].dwAudioTimeCurent64) = 
			(__int64)(AudioTimeStamp[AudioFileNumber]) + StartTime64;

		DWORD NextT = TimeTick;//timeGetTime() - StartTime;// - lpWAVEHDR->dwBufferLength/8;
		*(DWORD*)&(AudioStmp[AudioFileNumber].dwAudioTimeNext) = NextT;
		int ist = AudioToImageFrom[AudioFileNumber];
		int iFl =0;
		while(ist != AudioToImageTo[AudioFileNumber] && iFl <16)
		{
			*(DWORD*)&(AudioStmp[AudioFileNumber].dwImageTime[iFl++]) = ImageTimeStamp[ist];
			IncImage(ist);
		}
		AudioStmp[AudioFileNumber].bNImages = iFl;

		SaveWavFile(szAudioFN ,AudioTimeStamp[AudioFileNumber],&AudioStmp[AudioFileNumber]);

		if (++AudioFilesNow >= _MAX_NUMBER_OF_AUDIO_FILES)
			AudioFilesNow = _MAX_NUMBER_OF_AUDIO_FILES;
		
		IncAudio(AudioFileNumber);
		AudioToImageFrom[AudioFileNumber] = ImageFileNumber;
		AudioTimeStamp[AudioFileNumber] = NextT;
		
		memcpy(&bAudioFrame[iAudioBegin], ((BYTE*)lpWAVEHDR->lpData)+iLastCopyBeforSave, iLastCopyAfterSave);
		iAudioBegin += iLastCopyAfterSave;
		MyCCgApp->fSwitch2K4KAudio = FALSE;
	}
	LPWAVEHDR a = lpWAVEHDR;
    */
	return(0);
}
void CALLBACK waveInProc(  HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2 )
{
	if (WIM_DATA == uMsg)
	{
		fInsideCallBack = TRUE;
		WAVEHDRMain.dwBufferLength = 8000;
		WAVEHDRMain.lpData = BUFERSND1;
		memcpy(BUFERSND1,BUFERSND0,sizeof(BUFERSND1));
		waveInUnprepareHeader( (HWAVEIN)m_hWaveIn,(LPWAVEHDR)&WaveHdr,sizeof(WAVEHDR)  );
		if (DOStop ==  FALSE)
		{
			waveInPrepareHeader( (HWAVEIN)m_hWaveIn, (LPWAVEHDR)&WaveHdr, sizeof(WAVEHDR) );
			waveInAddBuffer( (HWAVEIN)	m_hWaveIn,(LPWAVEHDR)&WaveHdr, sizeof(WAVEHDR));
			waveInStart((HWAVEIN)m_hWaveIn);
		}
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
		format.wf.nChannels = 1;
		format.wf.nSamplesPerSec = 8000;
		format.wf.nAvgBytesPerSec = 8000;
		format.wf.nBlockAlign = 1;
		format.wBitsPerSample = 8;

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
			 
		WaveHdr.lpData=BUFERSND0;
		WaveHdr.dwBufferLength = sizeof(BUFERSND0);
		WaveHdr.dwBytesRecorded = 0L;
		WaveHdr.dwFlags = 0L;
		WaveHdr.dwLoops = 0L;
		WaveHdr.dwUser = 0x1234;
		if (waveInPrepareHeader( (HWAVEIN)m_hWaveIn,
							  (LPWAVEHDR)&WaveHdr,
							  sizeof(WAVEHDR) )	)
		{
		}
		if (waveInAddBuffer( (HWAVEIN)	m_hWaveIn,
						 (LPWAVEHDR)&WaveHdr,
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

		Mres = waveInStop((HWAVEIN)m_hWaveIn);
		Mres = waveInReset((HWAVEIN)m_hWaveIn);
		Mres = waveInUnprepareHeader( (HWAVEIN)m_hWaveIn,
								(LPWAVEHDR)&WaveHdr,
								sizeof(WAVEHDR)  );
		Mres = waveInClose((HWAVEIN)m_hWaveIn);
		m_hWaveIn=0;
	}
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
    StopWAVCapture();
    return CDialogEx::DestroyWindow();
}
