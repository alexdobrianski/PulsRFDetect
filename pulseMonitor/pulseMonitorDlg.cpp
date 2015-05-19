
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
#define USE_GLOBAL
#include "procXML.h"

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
    DDX_Control(pDX, IDC_STATIC_FQ1, m_Period1);
    DDX_Control(pDX, IDC_STATIC_FQ2, m_Period2);
    DDX_Control(pDX, IDC_STATIC_FQ3, m_Period3);
    DDX_Control(pDX, IDC_STATIC_FQ4, m_Period4);
    DDX_Control(pDX, IDC_STATIC_FQ5, m_Period5);
    DDX_Control(pDX, IDC_STATIC_FQ6, m_Period6);
    DDX_Control(pDX, IDC_STATIC_1_MAX, m_1_max);
    DDX_Control(pDX, IDC_STATIC_1_MID, m_1_mid);
    DDX_Control(pDX, IDC_STATIC_1_MIN, m_1_min);
    DDX_Control(pDX, IDC_STATIC_2_MAX, m_2_max);
    DDX_Control(pDX, IDC_STATIC_2_MID, m_2_mid);
    DDX_Control(pDX, IDC_STATIC_2_MIN, m_2_min);
    DDX_Control(pDX, ID_NEXT, m_Next);
    DDX_Control(pDX, IDC_BUTTONRUN, m_Run);
    DDX_Control(pDX, IDC_LIST_SCALE, m_YScale);
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
    ON_STN_CLICKED(IDC_STATIC_1_MAX, &CpulseMonitorDlg::OnStnClickedStatic1Max)
    ON_BN_CLICKED(ID_NEXT, &CpulseMonitorDlg::OnBnClickedNext)
    ON_BN_CLICKED(IDC_BUTTONRUN, &CpulseMonitorDlg::OnBnClickedButtonrun)
    ON_LBN_SELCHANGE(IDC_LIST_SCALE, &CpulseMonitorDlg::OnLbnSelchangeListScale)
END_MESSAGE_MAP()


	PCMWAVEFORMAT format;
    LPHWAVEIN m_hWaveIn;
    BOOL fInsideCallBack = FALSE;
    WAVEHDR WAVEHDRMain;
    WAVEHDR WAVEHDRMainRead;
//#define SAMPLES_PER_SEC 44100
#define SAMPLES_PER_SEC 250000
#define NUMBER_OF_CHANNELS 2
    char BUFERSND0_0[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*2];
    char BUFERSND0_1[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*2];

	char BUFERSND1_0[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*2];
    char BUFERSND1_1[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*2];

    char BUFERREAD[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*2];
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
    int g_i1Mid;
    int g_i2Mid;

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

char szOutPutREcording[_MAX_PATH]={"record.apuls"};
FILE *MyOutPutFIle = NULL;
BOOL flRecordOpenedForWrite;
int old_check_box_status = 1;
typedef struct Measurement
{
    int NearBody;
    int TypeOfmesaure;

    long double T; // time of measure
    long double TError; // time measurement error (s)
    long double px, jy, P0, P119;
    char szN[_MAX_PATH];
} MEASUREMENT, *PMEASUREMENT;

int iMaxMeasures = 0;
#define MAX_PULSARS_TO_PROCESS 20
GLOBAL_VARIABLE MEASUREMENT pulsars_over_head[MAX_PULSARS_TO_PROCESS];

typedef struct WriteStruct
{
    DWORD Signature;
    int iCountofVisiblePulsars;
    SYSTEMTIME myShowSysTime;
    MEASUREMENT pulsars_over_head[MAX_PULSARS_TO_PROCESS];
    long long llSizeOfThebuffer;
} WRITE_STRUCT, *PWRITE_STRUCT;

WRITE_STRUCT OUtPutPulseStruct;

WRITE_STRUCT ReadPulseStruct;


__int64  g_reacordMAxSize;
__int64  g_reacordCurPos;
int ICOuntofOutOnScreen =0;
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
    if (!flRecordOpenedForWrite)
    {
        if (hwndC != NULL)
            return(0);
    }
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
    g_i1Mid =  i1Mid;
    g_i2Mid =  i2Mid;
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
    if (MyOutPutFIle != NULL)
    {
        if (flRecordOpenedForWrite)  // record observed period
        {
            OUtPutPulseStruct.llSizeOfThebuffer = lpWAVEHDR->dwBufferLength;
            fwrite(&OUtPutPulseStruct, sizeof(OUtPutPulseStruct), 1, MyOutPutFIle);
            fwrite(lpWAVEHDR->lpData, lpWAVEHDR->dwBufferLength, 1, MyOutPutFIle);
        }
        else                         // read observation 
        {
        }
    }

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
        
		AudioStreamCallback((HWND)-1,&WAVEHDRMain);
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

FILE *g_fInputReadUrlOrFile; 
char g_szXMLFileName[_MAX_PATH*3]={"trasimoutput.xml"};
int GetFileString(char *_szXMLFileName, char *_szLocalFileName, int FileStatusFlag, char *szString, int sizeof_szString)
{
    if (FileStatusFlag == 0) // that is OPEN operation
    {
        /*
        if (strstr(_szXMLFileName,"http://"))
        {
            // needs to copy original http file from server to a local with temporary name, than process temporary
            char szURLFileName[3*_MAX_PATH];
            char szURLServer[3*_MAX_PATH];
            char sztempFileName[3*_MAX_PATH];
            char szWebServerResp[8096];
            int UrlPort=80;
       	    CHttpConnection* m_MainHttpServer = NULL;
    	    CInternetSession  *m_MainInternetConnection = NULL;

            if (ParsURL(szURLServer, &UrlPort, szURLFileName, _szXMLFileName))
            {
                //strcpy(_szXMLFileName, _szLocalFileName);
            }
            else
            {
                printf("\n file %s was wrongly parsed",_szXMLFileName);
                return 3;
            }
            if (m_MainHttpServer == NULL)
	        {
                m_MainInternetConnection = new CInternetSession("SessionToControlServer",12,INTERNET_OPEN_TYPE_DIRECT,NULL, // proxi name
				            NULL, // proxi bypass
				            INTERNET_FLAG_DONT_CACHE|INTERNET_FLAG_TRANSFER_BINARY);
		        try
		        {
                    m_MainHttpServer = 	m_MainInternetConnection->GetHttpConnection( szURLServer, 0, UrlPort, NULL, NULL );
    		    }
	    	    catch(CInternetException *e)
		        {
                    m_MainHttpServer = NULL;
                    printf("\n file %s failure to open (no intenet connection)", _szXMLFileName);
                    return 1;
		        }
	        }
	        if (m_MainHttpServer)
	        {
                CHttpFile* myCHttpFile = NULL;
			    try
			    {
                    myCHttpFile = m_MainHttpServer->OpenRequest( CHttpConnection::HTTP_VERB_GET,
					    szURLFileName,
					    NULL,//((CGrStnApp*)AfxGetApp())->szLoginRQ,
					    NULL,//12345678,
					    NULL, 
					    NULL, 
					    INTERNET_FLAG_EXISTING_CONNECT|
					    INTERNET_FLAG_DONT_CACHE|
					    INTERNET_FLAG_RELOAD );
			    }
			    catch(CInternetException *e)
			    {
                    m_MainHttpServer->Close();
                    printf("\n file %s failure to open", _szXMLFileName);
                    return 1;
			    }

			    if (myCHttpFile !=NULL)
			    {
                    try
				    {
					    myCHttpFile->SendRequest();
					    memset(szWebServerResp, 0, sizeof(szWebServerResp));
                        DWORD dwSize;
                        CString strSize;
                        myCHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,strSize);
                        dwSize = atoi(strSize.GetString());
                        FILE *TempFile = fopen(_szLocalFileName, "wb");
                        if (TempFile)
                        {
                            if (dwSize > (sizeof(szWebServerResp)-1))
                            {
                                for (DWORD dwread=0; dwread < dwSize; dwread+= (sizeof(szWebServerResp)-1))
                                {
                                    if ((dwSize - dwread) > (sizeof(szWebServerResp)-1))
                                    {
                                        if (myCHttpFile->Read(&szWebServerResp,(sizeof(szWebServerResp)-1)))
                                        {
                                            fwrite(&szWebServerResp,(sizeof(szWebServerResp)-1),1,TempFile);
                                        }

                                    }
                                    else
                                    {
                                        if (myCHttpFile->Read(&szWebServerResp,(dwSize - dwread)))
                                        {
                                            fwrite(&szWebServerResp,(dwSize - dwread),1,TempFile);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if (myCHttpFile->Read(&szWebServerResp,dwSize))
                                {
                                    fwrite(&szWebServerResp,dwSize,1,TempFile);
                                }
                            }
                            fclose(TempFile);
                        }
                        else
                        {
                            printf("\n file %s failure to write into %s", _szXMLFileName,_szLocalFileName);
                        }
                    }
                    catch(CInternetException *e)
                    {
                        myCHttpFile->Close();
                        m_MainHttpServer->Close();
                        m_MainInternetConnection->Close();
					    //ptrApp->m_MainHttpServer = NULL;
                        printf("\n file %s failure to read", _szXMLFileName);
                        return 3;
				    }
                    myCHttpFile->Close();
				    delete myCHttpFile;
                }
                else
                {
                    m_MainHttpServer->Close();
                    m_MainInternetConnection->Close();
                    //ptrApp->m_MainHttpServer = NULL;
                    printf("\n file %s failure to read", _szXMLFileName);
                    return 3;
                }
                m_MainHttpServer->Close();
                m_MainInternetConnection->Close();
            }
            else
            {
                m_MainInternetConnection->Close();
                //ptrApp->m_MainHttpServer = NULL;
                printf("\n file %s failure to open", _szXMLFileName);
                return 3;
            }
            fInputReadUrlOrFile = fopen(_szLocalFileName, "r");
            if (fInputReadUrlOrFile != NULL)
            {
                //fclose(fInputReadUrlOrFile);
                return 0;
            }
            else
            {
                printf("\n file %s missing", _szLocalFileName);
                return 3;
            }
        }
        else*/
        {
            g_fInputReadUrlOrFile = fopen(_szXMLFileName, "r");
            if (g_fInputReadUrlOrFile != NULL)
            {
                return 0;
            }
            else
            {
                printf("\n file %s missing", _szLocalFileName);
                return 3;
            }
        }
    }
    if (FileStatusFlag == 1) // that is READ/CLOSE operation
    {
        if (g_fInputReadUrlOrFile != NULL)
        {
            if (fgets(szString, sizeof_szString-1, g_fInputReadUrlOrFile) != NULL)
            {
                return 0;
            }
            else  // end of the file reached
            {
                fclose(g_fInputReadUrlOrFile);
                return 1;
            }

        }
        else
        {
            return 2;
        }
    }
    return 66;
}

void ParamCommon(char *szString)
{
    XML_BEGIN;
    XML_SECTION(pulsars_over_head)
	//<hPULSARmeasure>
	// <M>2</M>
	//	<T>+2.45716069811568270e+006</T>
	//	<N>B1133+16</N>
	//	<px>+1.18791306593600000e+000</px>
	//	<jy>257.000000</jy>
	//	<P0>+1.18801646317793200E+000</P0>
	//	<P119>+1.42561976218221530E+002</P119>
	// <E>+1.00000000000000000e+000</E>
	//</hPULSARmeasure>

    XML_SECTION_GROUP_SEPARATOR
    
    XML_GROUP(hPULSARmeasure)
        IF_XML_ELEMENT(T)
        {
            if (++iMaxMeasures>MAX_PULSARS_TO_PROCESS)
                iMaxMeasures--;
            pulsars_over_head[iMaxMeasures-1].T = atof(pszQuo);;
        }
        IF_XML_ELEMENT(N)
        {
            strcpy(pulsars_over_head[iMaxMeasures-1].szN,pszQuo);
            if (strchr(pulsars_over_head[iMaxMeasures-1].szN, '<'))
                *strchr(pulsars_over_head[iMaxMeasures-1].szN, '<')=0;
        }
        IF_XML_ELEMENT(px)
        {
            pulsars_over_head[iMaxMeasures-1].px =atof(pszQuo);
        }
        IF_XML_ELEMENT(jy)
        {
            pulsars_over_head[iMaxMeasures-1].jy =atof(pszQuo);
        }
        IF_XML_ELEMENT(P0)
        {
            pulsars_over_head[iMaxMeasures-1].P0 =atof(pszQuo);
        }
        IF_XML_ELEMENT(P119)
        {
            pulsars_over_head[iMaxMeasures-1].P119 =atof(pszQuo);
        }
    XML_GROUP_END

    XML_SECTION_END;

    XML_END;
}
void ParamDoAll(FILE *fInput)
{
    char szString[1024];
    char *pszQuo;
    char *pszQuo2;
    // default section:
    strcpy(szSection, "pulsars_over_head");
    while(fgets(szString, sizeof(szString) -1, fInput))
    {
        if (strstr(szString, "TRA:section") != NULL)
        {
            if ((pszQuo = strstr(szString, "name=\"")) != NULL)
            {
                strcpy(szSection, pszQuo + sizeof("name=\"") - 1);
                if ((pszQuo2 = strchr(szSection, '\"')) != 0)
                    *pszQuo2 = 0;
            }
        }
        ParamCommon(szString);
    }
}

void GetCurentPulsarsData(void)
{
    g_fInputReadUrlOrFile = NULL;
    iMaxMeasures = 0;
    if (GetFileString(g_szXMLFileName, "_trasimoutput_.xml", 0, NULL, 0) == 0) // open was successfull fInputReadUrlOrFile is a handler
    {
        ParamDoAll(g_fInputReadUrlOrFile);
        fclose(g_fInputReadUrlOrFile);
        g_fInputReadUrlOrFile = NULL;
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

    m_YScale.AddString("avrg");
    m_YScale.AddString("1024");
    m_YScale.AddString("512");
    m_YScale.AddString("256");
    m_YScale.AddString("128");
    m_YScale.AddString("64");
    m_YScale.AddString("32");

    m_YScale.SetCurSel(0);
    memset(&OUtPutPulseStruct, 0, sizeof(OUtPutPulseStruct));
    memset(&pulsars_over_head, 0, sizeof(pulsars_over_head));
    OUtPutPulseStruct.Signature = 0x01020304;
    OUtPutPulseStruct.iCountofVisiblePulsars = 0;
    flRunningRecording = FALSE;
    //
    GetCurentPulsarsData();
    if (iMaxMeasures)
    {
        char szText[_MAX_PATH];
        
        // pulsars on top of head
        OUtPutPulseStruct.iCountofVisiblePulsars = iMaxMeasures;
        for (int i = 0; i < OUtPutPulseStruct.iCountofVisiblePulsars; i++)
        {
            OUtPutPulseStruct.pulsars_over_head[i].NearBody = pulsars_over_head[i].NearBody;
            OUtPutPulseStruct.pulsars_over_head[i].T = pulsars_over_head[i].T;
            OUtPutPulseStruct.pulsars_over_head[i].px = pulsars_over_head[i].px;
            OUtPutPulseStruct.pulsars_over_head[i].jy = pulsars_over_head[i].jy;
            strcpy(OUtPutPulseStruct.pulsars_over_head[i].szN, pulsars_over_head[i].szN);
            OUtPutPulseStruct.pulsars_over_head[i].P0 = pulsars_over_head[i].P0;
            OUtPutPulseStruct.pulsars_over_head[i].P119 = pulsars_over_head[i].P119;
            switch(i)
            {
            case 0: sprintf(szText, "%s %1.3f (%d)",OUtPutPulseStruct.pulsars_over_head[i].szN, 
                        OUtPutPulseStruct.pulsars_over_head[i].px, (int)OUtPutPulseStruct.pulsars_over_head[i].jy);
                m_Period1.SetWindowTextA(szText);break;
            case 1: sprintf(szText, "%s %1.3f (%d)",OUtPutPulseStruct.pulsars_over_head[i].szN, 
                        OUtPutPulseStruct.pulsars_over_head[i].px, (int)OUtPutPulseStruct.pulsars_over_head[i].jy);
                m_Period2.SetWindowTextA(szText);break;
            case 2: sprintf(szText, "%s %1.3f (%d)",OUtPutPulseStruct.pulsars_over_head[i].szN, 
                        OUtPutPulseStruct.pulsars_over_head[i].px, (int)OUtPutPulseStruct.pulsars_over_head[i].jy); 
                m_Period3.SetWindowTextA(szText);break;

            case 3: sprintf(szText, "%s %1.3f (%d)",OUtPutPulseStruct.pulsars_over_head[i].szN, 
                        OUtPutPulseStruct.pulsars_over_head[i].px, (int)OUtPutPulseStruct.pulsars_over_head[i].jy); 
                m_Period4.SetWindowTextA(szText);break;
            case 4: sprintf(szText, "%s %1.3f (%d)",OUtPutPulseStruct.pulsars_over_head[i].szN, 
                        OUtPutPulseStruct.pulsars_over_head[i].px, (int)OUtPutPulseStruct.pulsars_over_head[i].jy); 
                m_Period5.SetWindowTextA(szText);break;
            case 5: sprintf(szText, "%s %1.3f (%d)",OUtPutPulseStruct.pulsars_over_head[i].szN, 
                        OUtPutPulseStruct.pulsars_over_head[i].px, (int)OUtPutPulseStruct.pulsars_over_head[i].jy); 
                m_Period6.SetWindowTextA(szText);break;

            }
        }
    }
    {
        char szText[_MAX_PATH];
        sprintf(szText, "%d", g_i1Max); m_1_max.SetWindowTextA(szText);
        sprintf(szText, "%d", g_i1Min); m_1_min.SetWindowTextA(szText);
        sprintf(szText, "%d", g_i1Mid); m_1_mid.SetWindowTextA(szText);
        sprintf(szText, "%d", g_i2Max); m_2_max.SetWindowTextA(szText);
        sprintf(szText, "%d", g_i2Min); m_2_min.SetWindowTextA(szText);
        sprintf(szText, "%d", g_i2Mid); m_2_mid.SetWindowTextA(szText);
    }
    m_FractionsPerScreen = 1;
    g_FractionsPerScreen = m_FractionsPerScreen;
    m_SecondsPerScreen = 1;
    g_SecondsPerScreen = m_SecondsPerScreen;
    g_isecond = 0;
    hBmpMainSignal = NULL;
    memset(bRGBImage, 0xff, sizeof(bRGBImage));
    //SYSTEMTIME mySYsTime;
    GetLocalTime(&mySYsTime);
    memcpy(&OUtPutPulseStruct.myShowSysTime, &mySYsTime, sizeof(OUtPutPulseStruct.myShowSysTime));
    
    CTime MyTime = CTime(mySYsTime);

    m_Time.SetTime(&MyTime);
    m_Date.SetTime(&MyTime);

    old_check_box_status = 1;
    m_LastTime.SetCheck(1);

    if (m_LastTime.GetCheck()) // that is record operation
    {
        MyOutPutFIle = fopen(szOutPutREcording, "ab");
        if (MyOutPutFIle!=NULL)
        {
            flRecordOpenedForWrite = TRUE;
        }
    }
    else                       //that is view recording
    {
        MyOutPutFIle = fopen(szOutPutREcording, "rb");
        if (MyOutPutFIle!=NULL)
        {
            flRecordOpenedForWrite = FALSE;
        }
    }

    m_ShowLines.SetCheck(0);
    SetTimer(901, 1000,NULL);
    SetTimer(902,60500,NULL);

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
    KillTimer(902);
    if (hBmpMainSignal!=NULL)
        DeleteObject(hBmpMainSignal);

    StopWAVCapture();
    if (MyOutPutFIle != NULL)
        fclose(MyOutPutFIle);
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
    g_isecond = 1024;
    ICOuntofOutOnScreen = 0;
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
            memcpy(&OUtPutPulseStruct.myShowSysTime,&myShowSysTime, sizeof(OUtPutPulseStruct.myShowSysTime));

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
        {
            char szText[_MAX_PATH];
            sprintf(szText, "%d", g_i1Max); m_1_max.SetWindowTextA(szText);
            sprintf(szText, "%d", g_i1Min); m_1_min.SetWindowTextA(szText);
            sprintf(szText, "%d", g_i1Mid); m_1_mid.SetWindowTextA(szText);
            sprintf(szText, "%d", g_i2Max); m_2_max.SetWindowTextA(szText);
            sprintf(szText, "%d", g_i2Min); m_2_min.SetWindowTextA(szText);
            sprintf(szText, "%d", g_i2Mid); m_2_mid.SetWindowTextA(szText);
        }
        if (flRecordOpenedForWrite == FALSE) // that is tickingt timer and needs to show all switch of the data on the screen
        {
            if (MyOutPutFIle != NULL)
            {
                if (flRunningRecording)
                {
                    if (ICOuntofOutOnScreen >= g_SecondsPerScreen)
                        ICOuntofOutOnScreen = 0;
                }
                while (ICOuntofOutOnScreen++ < g_SecondsPerScreen)
                {
                    ReadPulseStruct.Signature = 0;
                    while(ReadPulseStruct.Signature != 0x01020304)
                    {
                        __int64  reacordCurPos = _ftelli64(MyOutPutFIle);
                        if (sizeof(ReadPulseStruct) == fread(&ReadPulseStruct, sizeof(ReadPulseStruct), 1, MyOutPutFIle))
                        {
                            break;
                        }
                        if (ReadPulseStruct.Signature == 0x01020304)
                            break;
                        reacordCurPos +=1;
                        _fseeki64(MyOutPutFIle, reacordCurPos, SEEK_SET);
                    }
                    if (ReadPulseStruct.Signature == 0x01020304)
                    {
                        if (ReadPulseStruct.llSizeOfThebuffer == sizeof(BUFERREAD))
                        {
                            WAVEHDRMainRead.dwBufferLength = sizeof(BUFERREAD);
                            WAVEHDRMainRead.lpData = BUFERREAD; // is it first buffer?
                            size_t imySize = fread(&BUFERREAD, WAVEHDRMainRead.dwBufferLength, 1, MyOutPutFIle);
                            if (1 == imySize)
                            {
                                AudioStreamCallback(NULL,&WAVEHDRMainRead);
                                g_reacordCurPos = _ftelli64(MyOutPutFIle);
                                CTime MyTime = CTime(ReadPulseStruct.myShowSysTime);
                                m_Time.SetTime(&MyTime);
                                m_Date.SetTime(&MyTime);
                                m_SLider.SetPos((m_SLider.GetRangeMax()* g_reacordCurPos)/g_reacordMAxSize);
                            }
                        }
                    }
                }
            }
        }
    }
    else if (nIDEvent== 902)
    {
        GetCurentPulsarsData();
        if (iMaxMeasures)
        {
            // pulsars on top of head
            OUtPutPulseStruct.iCountofVisiblePulsars = iMaxMeasures;
            for (int i = 0; i < OUtPutPulseStruct.iCountofVisiblePulsars; i++)
            {
                OUtPutPulseStruct.pulsars_over_head[i].NearBody = pulsars_over_head[i].NearBody;
                OUtPutPulseStruct.pulsars_over_head[i].T = pulsars_over_head[i].T;
                OUtPutPulseStruct.pulsars_over_head[i].px = pulsars_over_head[i].px;
                strcpy(OUtPutPulseStruct.pulsars_over_head[i].szN, pulsars_over_head[i].szN);
                OUtPutPulseStruct.pulsars_over_head[i].P0 = pulsars_over_head[i].P0;
                OUtPutPulseStruct.pulsars_over_head[i].P119 = pulsars_over_head[i].P119;
            }
        }

    }
    CDialogEx::OnTimer(nIDEvent);
}


void CpulseMonitorDlg::OnBnClickedCheckLast()
{
    // TODO: Add your control notification handler code here

    int iCheckBoxnow = m_LastTime.GetCheck();
    if (iCheckBoxnow != old_check_box_status)
    {
        if (old_check_box_status == 1) // was recording
        {
            while(fInsideCallBack)
            {
                Sleep(100);
            }
            fclose(MyOutPutFIle);
            MyOutPutFIle = NULL;
            {
                MyOutPutFIle = fopen(szOutPutREcording, "rb");
                if (MyOutPutFIle!=NULL)    // reading old recordings
                {
                    flRecordOpenedForWrite = FALSE;
                    _fseeki64( MyOutPutFIle, 0, SEEK_END);
                    g_reacordMAxSize = _ftelli64(MyOutPutFIle);
                    g_reacordCurPos = 0;
                    _fseeki64( MyOutPutFIle, g_reacordCurPos, SEEK_SET);
                    m_Next.EnableWindow(1);
                    m_Run.EnableWindow(1);
                    g_isecond = 1024;
                    ICOuntofOutOnScreen =0;
                    
                    m_SLider.SetPos((m_SLider.GetRangeMax()* g_reacordCurPos)/g_reacordMAxSize);
                }
            }
        }
        else // was reading
        {
            fclose(MyOutPutFIle);
            MyOutPutFIle = NULL;
            if (m_LastTime.GetCheck()) // that is record operation
            {
                MyOutPutFIle = fopen(szOutPutREcording, "ab");
                if (MyOutPutFIle!=NULL)    // continue read
                {
                    flRecordOpenedForWrite = TRUE;
                    m_Next.EnableWindow(1);
                    m_Run.EnableWindow(1);
                }
            }
        }
    }
}


void CpulseMonitorDlg::OnBnClickedCheckDotsLines()
{
    // TODO: Add your control notification handler code here

}


void CpulseMonitorDlg::OnStnClickedStatic1Max()
{
    // TODO: Add your control notification handler code here
}


void CpulseMonitorDlg::OnBnClickedNext()
{
    // TODO: Add your control notification handler code here
    ICOuntofOutOnScreen = 0;
}


void CpulseMonitorDlg::OnBnClickedButtonrun()
{
    // TODO: Add your control notification handler code here
    if (flRunningRecording == FALSE)
    {
        flRunningRecording = TRUE;
        m_Run.SetWindowTextA("stp");
    }
    else
    {
        flRunningRecording = FALSE;
        m_Run.SetWindowTextA("run");
    }
    
}


void CpulseMonitorDlg::OnLbnSelchangeListScale()
{
    // TODO: Add your control notification handler code here
    switch(m_YScale.GetCurSel())
    {
    case 0:break;
    case 1:  g_i1Max = g_i1Mid + 1024; g_i2Max = g_i2Mid + 1024; g_i1Min = g_i1Mid - 1024; g_i2Min = g_i2Mid - 1024;break;
    case 2:  g_i1Max = g_i1Mid + 512;  g_i2Max = g_i2Mid + 512;  g_i1Min = g_i1Mid - 512;  g_i2Min = g_i2Mid - 512;break;
    case 3:  g_i1Max = g_i1Mid + 256;  g_i2Max = g_i2Mid + 256;  g_i1Min = g_i1Mid - 256;  g_i2Min = g_i2Mid - 256;break;
    case 4:  g_i1Max = g_i1Mid + 128;  g_i2Max = g_i2Mid + 128;  g_i1Min = g_i1Mid - 128;  g_i2Min = g_i2Mid - 128;break;
    case 5:  g_i1Max = g_i1Mid + 64;   g_i2Max = g_i2Mid + 64;   g_i1Min = g_i1Mid - 64;   g_i2Min = g_i2Mid - 64;break;
    case 6:  g_i1Max = g_i1Mid + 32;   g_i2Max = g_i2Mid + 21;   g_i1Min = g_i1Mid - 32;   g_i2Min = g_i2Mid - 32;break;
    }
    if (flRunningRecording)
        ICOuntofOutOnScreen = 0;
}
