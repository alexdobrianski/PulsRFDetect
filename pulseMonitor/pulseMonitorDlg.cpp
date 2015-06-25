
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
    //DDX_Control(pDX, IDC_CHECK_DOTS_LINES, m_ShowLines);
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
    DDX_Control(pDX, IDC_EDIT_LOCAL_FILE, m_LocalFile);
    DDX_Control(pDX, IDC_LIST_ZONE, m_Zone);
    DDX_Control(pDX, IDC_STATIC_FQ1_PIC, m_PicPulse1);
    DDX_Control(pDX, IDC_STATIC_FQ2_PIC, m_PicPulse2);
    DDX_Control(pDX, IDC_STATIC_FQ3_PIC, m_PicPulse3);
    DDX_Control(pDX, IDC_STATIC_FQ4_PIC, m_PicPulse4);
    DDX_Control(pDX, IDC_STATIC_FQ5_PIC, m_PicPulse5);
    DDX_Control(pDX, IDC_STATIC_FQ6_PIC, m_PicPulse6);
    DDX_Control(pDX, IDC_CHECK_N_CH, m_NumberChan);
    //  DDX_Control(pDX, IDC_BUTTON_SET_POS, m_SetPosition);
    DDX_Control(pDX, IDC_BUTTON_SET_POS, m_SetPosition);
    DDX_Control(pDX, IDC_EDIT_OFFSET_IN_FILE, m_OffsetPosition);
    DDX_Control(pDX, IDC_EDIT_NO_LENIAR, m_TimeDelta);
    DDX_Control(pDX, IDC_EDIT_MINIMUM, m_Minimum);
    DDX_Control(pDX, IDC_EDIT_MAXIMUM, m_Maximum);
    DDX_Control(pDX, IDC_EDIT_DB, m_CountDb);
    DDX_Control(pDX, IDC_EDIT_CHN, m_ChanVis);
    DDX_Control(pDX, IDC_BUTTON_ANALIZE, m_Analize);
    DDX_Control(pDX, IDC_EDIT_FROM_P, m_From_P);
    DDX_Control(pDX, IDC_EDIT_TO_P, m_To_P);
    DDX_Control(pDX, IDC_BUTTON_ANALIZE_PULSARS_ONLY, m_AnalizePulsarsOnly);
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
    ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE, &CpulseMonitorDlg::OnBnClickedButtonSelectFile)
    ON_LBN_SELCHANGE(IDC_LIST_ZONE, &CpulseMonitorDlg::OnLbnSelchangeListZone)
    ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CpulseMonitorDlg::OnBnClickedButtonClear)
    ON_BN_CLICKED(IDC_BUTTON_CLEAN_FQ1, &CpulseMonitorDlg::OnBnClickedButtonCleanFq1)
    ON_BN_CLICKED(IDC_BUTTON_CLEAN_FQ2, &CpulseMonitorDlg::OnBnClickedButtonCleanFq2)
    ON_BN_CLICKED(IDC_BUTTON_CLEAN_FQ3, &CpulseMonitorDlg::OnBnClickedButtonCleanFq3)
    ON_BN_CLICKED(IDC_BUTTON_CLEAN_FQ4, &CpulseMonitorDlg::OnBnClickedButtonCleanFq4)
    ON_BN_CLICKED(IDC_BUTTON_CLEAN_FQ5, &CpulseMonitorDlg::OnBnClickedButtonCleanFq5)
    ON_BN_CLICKED(IDC_BUTTON_CLEAN_FQ6, &CpulseMonitorDlg::OnBnClickedButtonCleanFq6)
    ON_BN_CLICKED(IDC_CHECK_N_CH, &CpulseMonitorDlg::OnBnClickedCheckNCh)
    ON_BN_CLICKED(IDC_BUTTON_SET_POS, &CpulseMonitorDlg::OnBnClickedButtonSetPos)
    ON_BN_CLICKED(IDC_BUTTON_ANALIZE, &CpulseMonitorDlg::OnBnClickedButtonAnalize)
    ON_BN_CLICKED(IDC_BUTTON_RUN_DB, &CpulseMonitorDlg::OnBnClickedButtonRunDb)
    ON_BN_CLICKED(IDC_BUTTON_ANALIZE_PULSARS_ONLY, &CpulseMonitorDlg::OnBnClickedButtonAnalizePulsarsOnly)
END_MESSAGE_MAP()

#define NPULSARS 150
typedef struct tagPulsars
{
    int N;
    char Name[20];
    long double ELONG;
    long double ELAT;
    long double P0;
    long double S400mJy;
    long double Metrics;

} PULSARS, *PPULSARS;

    int g_j = 0;
    PULSARS Pulsars[150];
    int nPulsars;

    long g_Analize_From;
    long g_Analize_To;

    BOOL DoAnalize = FALSE;
    BOOL DoFirstdb = FALSE;

    long double g_iTimeDelta = 0;
    long g_iCountDB = 123456;
    long g_iCountDB_old = 123456;


    int g_numb_ch = 2;
	PCMWAVEFORMAT format;
    LPHWAVEIN m_hWaveIn;
    BOOL fInsideCallBack = FALSE;
    WAVEHDR WAVEHDRMain;
    WAVEHDR WAVEHDRMainRead;
//#define SAMPLES_PER_SEC 44100
#define SAMPLES_PER_SEC 250000
#define NUMBER_OF_CHANNELS 2
#define BYTES_PER_SAMPLE 2
    char BUFERSND0_0[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*BYTES_PER_SAMPLE];
    char BUFERSND0_1[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*BYTES_PER_SAMPLE];

	char BUFERSND1_0[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*BYTES_PER_SAMPLE];
    char BUFERSND1_1[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*BYTES_PER_SAMPLE];

    char BUFERREAD[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*BYTES_PER_SAMPLE];
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
unsigned char PiCRGBGreen[3] = {0x00,0xff,0x00};

#define IMAGE_W_S 512
#define IMAGE_H_S 64
#define MAX_PERIOD_IN_SEC 2
//int RGBReferenceBody = EARTH;
unsigned char bRGBImage_S1[IMAGE_W_S*IMAGE_H_S*3];
long double BUFEDETECT1[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC];
long iPosIn1;
long double Pmin1_1= 1.0e64;
long double Pmax1_1=-1.0e64;
long double Pmin2_1= 1.0e64;
long double Pmax2_1=-1.0e64;
long double omin1_1= 1.0e64;
long double omax1_1=-1.0e64;
long double omin2_1= 1.0e64;
long double omax2_1=-1.0e64;
BOOL CleanRQ1 = FALSE;
long double Fraction1 = 0.0;

unsigned char bRGBImage_S2[IMAGE_W_S*IMAGE_H_S*3];
long double BUFEDETECT2[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC];
long iPosIn2;
long double Pmin1_2= 1.0e64;
long double Pmax1_2=-1.0e64;
long double Pmin2_2= 1.0e64;
long double Pmax2_2=-1.0e64;
long double omin1_2= 1.0e64;
long double omax1_2=-1.0e64;
long double omin2_2= 1.0e64;
long double omax2_2=-1.0e64;

BOOL CleanRQ2 = FALSE;
long double Fraction2 = 0.0;

unsigned char bRGBImage_S3[IMAGE_W_S*IMAGE_H_S*3];
long double BUFEDETECT3[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC];
long iPosIn3;
long double Pmin1_3= 1.0e64;
long double Pmax1_3=-1.0e64;
long double Pmin2_3= 1.0e64;
long double Pmax2_3=-1.0e64;
long double omin1_3= 1.0e64;
long double omax1_3=-1.0e64;
long double omin2_3= 1.0e64;
long double omax2_3=-1.0e64;

BOOL CleanRQ3 = FALSE;
long double Fraction3 = 0.0;

unsigned char bRGBImage_S4[IMAGE_W_S*IMAGE_H_S*3];
long double BUFEDETECT4[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC];
long iPosIn4;
long double Pmin1_4= 1.0e64;
long double Pmax1_4=-1.0e64;
long double Pmin2_4= 1.0e64;
long double Pmax2_4=-1.0e64;
long double omin1_4= 1.0e64;
long double omax1_4=-1.0e64;
long double omin2_4= 1.0e64;
long double omax2_4=-1.0e64;

BOOL CleanRQ4 = FALSE;
long double Fraction4 = 0.0;

unsigned char bRGBImage_S5[IMAGE_W_S*IMAGE_H_S*3];
long double BUFEDETECT5[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC];
long iPosIn5;
long double Pmin1_5= 1.0e64;
long double Pmax1_5=-1.0e64;
long double Pmin2_5= 1.0e64;
long double Pmax2_5=-1.0e64;
long double omin1_5= 1.0e64;
long double omax1_5=-1.0e64;
long double omin2_5= 1.0e64;
long double omax2_5=-1.0e64;

BOOL CleanRQ5 = FALSE;
long double Fraction5 = 0.0;

unsigned char bRGBImage_S6[IMAGE_W_S*IMAGE_H_S*3];
long double BUFEDETECT6[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC];
long iPosIn6;
long double Pmin1_6= 1.0e64;
long double Pmax1_6=-1.0e64;
long double Pmin2_6= 1.0e64;
long double Pmax2_6=-1.0e64;
long double omin1_6= 1.0e64;
long double omax1_6=-1.0e64;
long double omin2_6= 1.0e64;
long double omax2_6=-1.0e64;

BOOL CleanRQ6 = FALSE;
long double Fraction6 = 0.0;

long double BUFEDETECTtmp[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC];
long double Pmin1_tmp= -12345678;
long double Pmax1_tmp;
long double Pmin2_tmp;
long double Pmax2_tmp;

long double BUFEDETECT_1db[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC];
long double BUFEDETECT_1db_last[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC];
long double Pdb1min1_tmp= -12345678;
long double Pdb1max1_tmp;
long double Pdb1min2_tmp;
long double Pdb1max2_tmp;
long idb1PosIn = 0;
long double Fraction1db = 0.0;
long double omin1_db1; 
long double omax1_db1;
long double omin2_db1;
long double omax2_db1;
long iCointdB1 = 0;

long double BUFEDETECT_2db[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC];
long double BUFEDETECT_2db_last[SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC];
long double Pdb2min1_tmp= -12345678;
long double Pdb2max1_tmp;
long double Pdb2min2_tmp;
long double Pdb2max2_tmp;
long idb2PosIn = 0;
long double Fraction2db = 0.0;
long double omin1_db2; 
long double omax1_db2;
long double omin2_db2;
long double omax2_db2;
long iCointdB2 = 0;



int bRGBImageW_S = IMAGE_W_S;
int bRGBImageH_S = IMAGE_H_S;

char szModule[3*_MAX_PATH];
char szOutPutREcording[3*_MAX_PATH]={"record.apuls"};
FILE *MyOutPutFIle = NULL;
BOOL flRecordOpenedForWrite;
int old_check_box_status = 1;
TIME_ZONE_INFORMATION tmzone;
int iZoneBias = 0;


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
BOOL FirstRead = TRUE;
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
void putpixelS(unsigned char *bRGBImageS,unsigned char *bRGB, int X, int Y)
{
    int iRow = (X) + (bRGBImageH_S - (Y))*bRGBImageW_S-1;
    if ((iRow*3 >=0) && (iRow*3 < (sizeof(bRGBImage_S1) -3)))
    {
        memcpy(&bRGBImageS[iRow*3],bRGB, 3);
    }
}
// should be no longer than 1 sec 
LRESULT CALLBACK AudioStreamCallback(HWND hwndC,LPWAVEHDR lpWAVEHDR, BOOL flProcessPulsars)
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
    if (flProcessPulsars)
    {
        if (DoAnalize)
        {
            long double dLenOfPuls = /*SAMPLES_PER_SEC * (pulsars_over_head[g_j].px) +*/ g_iTimeDelta;
            long iLenOfPuls = dLenOfPuls;
            long double FraDbl = dLenOfPuls - (long double)iLenOfPuls;
            long double *pFraction = NULL;
                
            long iStart = 0;
            long double *dIntegralVal = NULL;
            long double *dIntegralVal0 = NULL;
            long double *data_last = NULL;
            long double ldMin1=1.0e+64;
            long double ldMax1=-1.0e+64;
            long double ldMin2=1.0e+64;
            long double ldMax2=-1.0e+64;
            long double *oMin1 = NULL;
            long double *oMax1 = NULL;
            long double *oMin2 = NULL;
            long double *oMax2 = NULL;
            long *iCointdB;

            int iTemp = 0;
            if (DoFirstdb)
            {
                iStart = idb1PosIn; ldMin1 = Pdb1min1_tmp; ldMax1 = Pdb1max1_tmp; ldMin2 = Pdb1min2_tmp; ldMax2 = Pdb1max2_tmp; 
                pFraction = &Fraction1db; oMin1 = &omin1_db1; oMax1 = &omax1_db1; oMin2 = &omin2_db1; oMax2 = &omax2_db1; iCointdB = &iCointdB1;
                dIntegralVal0 = &BUFEDETECT_1db[0];dIntegralVal = &BUFEDETECT_1db[iStart*2];
                data_last = &BUFEDETECT_1db_last[0];
            }
            else
            {
                iStart = idb2PosIn; ldMin1 = Pdb2min1_tmp; ldMax1 = Pdb2max1_tmp; ldMin2 = Pdb2min2_tmp; ldMax2 = Pdb2max2_tmp; 
                pFraction = &Fraction2db; oMin1 = &omin1_db2; oMax1 = &omax1_db2; oMin2 = &omin2_db2; oMax2 = &omax2_db2; iCointdB = &iCointdB2;
                dIntegralVal0 = &BUFEDETECT_2db[0];dIntegralVal = &BUFEDETECT_2db[iStart*2];
                data_last = &BUFEDETECT_2db_last[0];
            }
            *pFraction += FraDbl; iTemp = *pFraction; 
            for (long i = 0; i < lpWAVEHDR->dwBufferLength; i+=NUMBER_OF_CHANNELS*2)
            {
                signed short iVal1 = *(signed short *)&lpWAVEHDR->lpData[i];
                signed short iVal2 = *(signed short *)&lpWAVEHDR->lpData[i+2];
                *(dIntegralVal) +=iVal1;
                if (g_numb_ch == 1)
                {
                    *(dIntegralVal) -=iVal2;
                    if (*(dIntegralVal) < ldMin1)
                        ldMin1 = *(dIntegralVal);
                    if (*(dIntegralVal) >= ldMax1)
                        ldMax1 = *(dIntegralVal);
                    dIntegralVal++;
                    dIntegralVal++;
                }
                else
                {
                    if (*(dIntegralVal) < ldMin1)
                        ldMin1 = *(dIntegralVal);
                    if (*(dIntegralVal) >= ldMax1)
                        ldMax1 = *(dIntegralVal);
                    
                    dIntegralVal++;
                    *(dIntegralVal) +=iVal2;
                    if (*(dIntegralVal) < ldMin2)
                        ldMin2 = *(dIntegralVal);
                    if (*(dIntegralVal) >= ldMax2)
                        ldMax2 = *(dIntegralVal);
                    dIntegralVal++;
                }

                if (++iStart > iLenOfPuls)
                {
                    (*iCointdB)++;
                    int iiTemp = iTemp;
                    while(iiTemp--)
                    {
                        dIntegralVal++;dIntegralVal++;
                    }
                    if (g_iCountDB < 4)
                        memcpy(data_last, dIntegralVal0, iLenOfPuls*NUMBER_OF_CHANNELS*sizeof(long double));
                    *pFraction -= (long double) iTemp;
                    *oMin1 = ldMin1; *oMax1 = ldMax1; *oMin2 = ldMin2; *oMax2 = ldMax2;
                    *pFraction += FraDbl; iTemp = *pFraction;// *pFraction -= (long double) iTemp;
                    iStart = 0;
                    dIntegralVal = dIntegralVal0;
                    ldMin1 = 1.0e64; ldMax1 = -1.0e64; ldMin2 = 1.0e64; ldMax2 = -1.0e64;
                }
            }
            if (DoFirstdb)
            {
                idb1PosIn = iStart; Pdb1min1_tmp = ldMin1; Pdb1max1_tmp = ldMax1; Pdb1min2_tmp = ldMin2; Pdb1max2_tmp = ldMax2; 
            }
            else
            {
                idb2PosIn = iStart; Pdb2min1_tmp = ldMin1; Pdb2max1_tmp = ldMax1; Pdb2min2_tmp = ldMin2; Pdb2max2_tmp = ldMax2; 
            }
        }
        else if (iMaxMeasures)
        {
            int iiMaxMeasures = iMaxMeasures;
            if (iiMaxMeasures >= 6)
                iiMaxMeasures = 6;
                                        // pulsars on top of head
            for (int j = 0; j < iiMaxMeasures; j++)
            {
                BOOL WasProcessed = FALSE;
                long double dLenOfPuls = SAMPLES_PER_SEC * (pulsars_over_head[j].px) + g_iTimeDelta;
                long iLenOfPuls = dLenOfPuls;
                long double FraDbl = dLenOfPuls - (long double)iLenOfPuls;
                long double *pFraction = NULL;
                
                long iStart = 0;
                long double *dIntegralVal = NULL;
                long double *dIntegralVal0 = NULL;
                long double ldMin1=1.0e+64;
                long double ldMax1=-1.0e+64;
                long double ldMin2=1.0e+64;
                long double ldMax2=-1.0e+64;
                unsigned char *bRGBImage_S= NULL;
                long iTemp;
                BOOL *CleanREQ = NULL;
                long double *oMin1 = NULL;
                long double *oMax1 = NULL;
                long double *oMin2 = NULL;
                long double *oMax2 = NULL;


                switch (j)
                {
                case 0: iStart = iPosIn1; ldMin1 = Pmin1_1; ldMax1 = Pmax1_1; ldMin2 = Pmin2_1; ldMax2 = Pmax2_1; CleanREQ= &CleanRQ1;
                        pFraction = &Fraction1;oMin1 = &omin1_1; oMax1 = &omax1_1; oMin2 = &omin2_1; oMax2 = &omax2_1;
                        dIntegralVal0 = &BUFEDETECT1[0];dIntegralVal = &BUFEDETECT1[iStart*2];bRGBImage_S = &bRGBImage_S1[0];break;
                case 1: iStart = iPosIn2; ldMin1 = Pmin1_2; ldMax1 = Pmax1_2; ldMin2 = Pmin2_2; ldMax2 = Pmax2_2;CleanREQ= &CleanRQ2;
                        pFraction = &Fraction2; oMin1 = &omin1_2; oMax1 = &omax1_2; oMin2 = &omin2_2; oMax2 = &omax2_2;
                        dIntegralVal0 = &BUFEDETECT2[0];dIntegralVal = &BUFEDETECT2[iStart*2];bRGBImage_S = &bRGBImage_S2[0];break;
                case 2: iStart = iPosIn3; ldMin1 = Pmin1_3; ldMax1 = Pmax1_3; ldMin2 = Pmin2_3; ldMax2 = Pmax2_3;CleanREQ= &CleanRQ3;
                        pFraction = &Fraction3; oMin1 = &omin1_3; oMax1 = &omax1_3; oMin2 = &omin2_3; oMax2 = &omax2_3;
                        dIntegralVal0 = &BUFEDETECT3[0];dIntegralVal = &BUFEDETECT3[iStart*2];bRGBImage_S = &bRGBImage_S3[0];break;
                case 3: iStart = iPosIn4; ldMin1 = Pmin1_4; ldMax1 = Pmax1_4; ldMin2 = Pmin2_4; ldMax2 = Pmax2_4;CleanREQ= &CleanRQ4;
                        pFraction = &Fraction4;oMin1 = &omin1_4; oMax1 = &omax1_4; oMin2 = &omin2_4; oMax2 = &omax2_4;
                        dIntegralVal0 = &BUFEDETECT4[0];dIntegralVal = &BUFEDETECT4[iStart*2];bRGBImage_S = &bRGBImage_S4[0];break;
                case 4: iStart = iPosIn5; ldMin1 = Pmin1_5; ldMax1 = Pmax1_5; ldMin2 = Pmin2_5; ldMax2 = Pmax2_5;CleanREQ= &CleanRQ5;
                        pFraction = &Fraction5;oMin1 = &omin1_5; oMax1 = &omax1_5; oMin2 = &omin2_5; oMax2 = &omax2_5;
                        dIntegralVal0 = &BUFEDETECT5[0];dIntegralVal = &BUFEDETECT5[iStart*2];bRGBImage_S = &bRGBImage_S5[0];break;
                case 5: iStart = iPosIn6; ldMin1 = Pmin1_6; ldMax1 = Pmax1_6; ldMin2 = Pmin2_6; ldMax2 = Pmax2_6;CleanREQ= &CleanRQ6;
                        pFraction = &Fraction6;oMin1 = &omin1_6; oMax1 = &omax1_6; oMin2 = &omin2_6; oMax2 = &omax2_6;
                        dIntegralVal0 = &BUFEDETECT6[0];dIntegralVal = &BUFEDETECT6[iStart*2];bRGBImage_S = &bRGBImage_S6[0];break;
                }
                *pFraction += FraDbl; iTemp = *pFraction; 
                for (long i = 0; i < lpWAVEHDR->dwBufferLength; i+=NUMBER_OF_CHANNELS*2)
                {
                    signed short iVal1 = *(signed short *)&lpWAVEHDR->lpData[i];
                    signed short iVal2 = *(signed short *)&lpWAVEHDR->lpData[i+2];
                    *(dIntegralVal) +=iVal1;
                    if (g_numb_ch == 1)
                    {
                        *(dIntegralVal) -=iVal2;
                        if (*(dIntegralVal) < ldMin1)
                            ldMin1 = *(dIntegralVal);
                        if (*(dIntegralVal) >= ldMax1)
                            ldMax1 = *(dIntegralVal);
                        dIntegralVal++;
                        dIntegralVal++;
                    }
                    else
                    {
                        if (*(dIntegralVal) < ldMin1)
                            ldMin1 = *(dIntegralVal);
                        if (*(dIntegralVal) >= ldMax1)
                            ldMax1 = *(dIntegralVal);
                    
                        dIntegralVal++;
                        *(dIntegralVal) +=iVal2;
                        if (*(dIntegralVal) < ldMin2)
                            ldMin2 = *(dIntegralVal);
                        if (*(dIntegralVal) >= ldMax2)
                            ldMax2 = *(dIntegralVal);
                        dIntegralVal++;
                    }

                    if (++iStart > iLenOfPuls)
                    {
                        int iiTemp = iTemp;
                        while(iiTemp--)
                        {
                            dIntegralVal++;dIntegralVal++;
                        }
                        *pFraction -= (long double) iTemp;

                        memcpy(BUFEDETECTtmp, dIntegralVal0, sizeof(BUFEDETECTtmp));
                        *oMin1 = ldMin1; *oMax1 = ldMax1; *oMin2 = ldMin2; *oMax2 = ldMax2;
                        Pmin1_tmp= ldMin1; Pmax1_tmp = ldMax1; Pmin2_tmp = ldMin2; Pmax2_tmp = ldMax2;
                        *pFraction += FraDbl; iTemp = *pFraction;// *pFraction -= (long double) iTemp;
                        iStart = 0;
                        dIntegralVal = dIntegralVal0;
                        ldMin1 = 1.0e64; ldMax1 = -1.0e64; ldMin2 = 1.0e64; ldMax2 = -1.0e64;
                        WasProcessed = TRUE;
                        if (*CleanREQ)
                        {
                            for (long il = 0; il < SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC; il++)
                            {
                                dIntegralVal[il] = 0;
                            }
                            *CleanREQ = FALSE;
                        }
                    }
                }
                if (WasProcessed)
                {
                    dIntegralVal = BUFEDETECTtmp;
                    long double ldDifs1 = Pmax1_tmp - Pmin1_tmp;
                    long double ldDifs2 = Pmax2_tmp - Pmin2_tmp;
                    memset(bRGBImage_S, 0xff, sizeof(bRGBImage_S1));
                    for (long io = 0; io < iLenOfPuls; io++)
                    {
                        int iX = bRGBImageW_S * (long double) io / (long double)iLenOfPuls;
                        if (g_numb_ch == 1)
                        {
                            int iY = (*dIntegralVal - Pmin1_tmp)/ ldDifs1*bRGBImageH_S;
                            if (*dIntegralVal == Pmin1_tmp)
                                putpixelS(bRGBImage_S,PiCRGBBlue, iX, bRGBImageH_S - iY);
                            else if  (*dIntegralVal == Pmax1_tmp)
                                putpixelS(bRGBImage_S,PiCRGBBlue, iX, bRGBImageH_S - iY+1);
                            else
                                putpixelS(bRGBImage_S,PiCRGBGreen, iX, bRGBImageH_S - iY);
                            dIntegralVal++;
                            dIntegralVal++;
                        }
                        else
                        {
                            int iY = (*dIntegralVal - Pmin1_tmp)/ ldDifs1*bRGBImageH_S/2;
                            putpixelS(bRGBImage_S,PiCRGBGreen, iX, bRGBImageH_S/2 - iY);
                            dIntegralVal++;
                            int iiY = (*dIntegralVal - Pmin2_tmp)/ ldDifs2*bRGBImageH_S/2;
                            putpixelS(bRGBImage_S,PiCRGBGreen, iX, bRGBImageH_S - iiY);
                            dIntegralVal++;
                        }
                    }
                }
                switch(j)
                {
                case 0:iPosIn1 = iStart;Pmin1_1 = ldMin1; Pmax1_1 = ldMax1; Pmin2_1 = ldMin2; Pmax2_1 = ldMax2;break;
                case 1:iPosIn2 = iStart;Pmin1_2 = ldMin1; Pmax1_2 = ldMax1; Pmin2_2 = ldMin2; Pmax2_2 = ldMax2;break;
                case 2:iPosIn3 = iStart;Pmin1_3 = ldMin1; Pmax1_3 = ldMax1; Pmin2_3 = ldMin2; Pmax2_3 = ldMax2;break;
                case 3:iPosIn4 = iStart;Pmin1_4 = ldMin1; Pmax1_4 = ldMax1; Pmin2_4 = ldMin2; Pmax2_4 = ldMax2;break;
                case 4:iPosIn5 = iStart;Pmin1_5 = ldMin1; Pmax1_5 = ldMax1; Pmin2_5 = ldMin2; Pmax2_5 = ldMax2;break;
                case 5:iPosIn6 = iStart;Pmin1_6 = ldMin1; Pmax1_6 = ldMax1; Pmin2_6 = ldMin2; Pmax2_6 = ldMax2;break;
                }
            }
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
        
		AudioStreamCallback((HWND)-1,&WAVEHDRMain, FALSE);
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
void ParamCommonPulsars(char *szString)
{
    XML_BEGIN;
        XML_SECTION(pulsars);
        IF_XML_READ(N)
        {
            Pulsars[nPulsars].N = atoi(pszQuo);
            Pulsars[nPulsars].Metrics = 0.0;
            strcpy(Pulsars[nPulsars].Name," ");
            Pulsars[nPulsars].ELONG = 0.0;
            Pulsars[nPulsars].ELAT = 0.0;
            Pulsars[nPulsars].P0 = 0.0;
            Pulsars[nPulsars].S400mJy = 0.0;
        }
        IF_XML_READ(Name)
        {
            strcpy(Pulsars[nPulsars].Name,pszQuo);
            char * iQuot = strstr(Pulsars[nPulsars].Name,"\"");
            if (iQuot)
                *iQuot=0;
        }
        IF_XML_READ(ELONG)
        {
            Pulsars[nPulsars].ELONG = atof(pszQuo);
        }
        IF_XML_READ(ELAT)
        {
            Pulsars[nPulsars].ELAT = atof(pszQuo);
        }
        IF_XML_READ(P0)
        {
            Pulsars[nPulsars].P0 = atof(pszQuo);
        }
        IF_XML_READ(S400mJy)
        {
            Pulsars[nPulsars].S400mJy = atof(pszQuo);
        }
        IF_XML_READ(RAJD)
        {
            Pulsars[nPulsars].ELONG = atof(pszQuo);
        }
        IF_XML_READ(DECJD)
        {
            Pulsars[nPulsars].ELAT = atof(pszQuo);
        }
        IF_XML_READ(RAJ)
        {
            long double fRajH = atoi(pszQuo);
            long double fRajM = atoi(pszQuo+3);
            long double fRajS = atoi(pszQuo+6);
            long double fRajMS = atoi(pszQuo+9);
            int iLen = strlen(pszQuo+9);
            int iLenQ = 0;
            if (strchr(pszQuo+9,'\"') != NULL)
            {
                iLenQ = strlen(strchr(pszQuo+9,'\"'));
            }
            long double fLen = pow(10.0, iLen-iLenQ);
            long double fsec = (fRajH * 60.0 + fRajM) * 60.0 + fRajS + fRajMS/fLen;
            Pulsars[nPulsars].ELONG = 360.0*fsec/ (24*60*60); 

        }
        IF_XML_READ(DECJ)
        {
            BOOL flNegative = FALSE;
            if (pszQuo[0] == '-')
                flNegative = TRUE;
            long double fDecjDeg =atoi(pszQuo);
            long double fDecjMin =atoi(pszQuo+4);
            long double fDecjSec =atoi(pszQuo+7);
            long double fDecjMS =atoi(pszQuo+10);
            int iLen = strlen(pszQuo+10);
            int iLenQ = 0;
            if (strchr(pszQuo+10,'\"') != NULL)
            {
                iLenQ = strlen(strchr(pszQuo+10,'\"'));
            }
            long double fLen = pow(10.0, iLen-iLenQ);
            long double fDec = 0;
            if (flNegative)
                fDec = fDecjDeg - fDecjMin/60 - (fDecjSec+fDecjMS/fLen)/(60*60);
            else
                fDec = fDecjDeg + fDecjMin/60 + (fDecjSec+fDecjMS/fLen)/(60*60);
            Pulsars[nPulsars].ELAT =fDec;
            if (++nPulsars >= NPULSARS)
                nPulsars = NPULSARS-1;
        }
        XML_SECTION_END;
    XML_END;
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
        IF_XML_ELEMENT(na)
        {
            pulsars_over_head[iMaxMeasures-1].TError =atof(pszQuo);
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
void ParamDoAllPulsars(FILE *fInput)
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
        ParamCommonPulsars(szString);
    }
}

int iDayOfTheYearZeroBase(int iDay, int iMonth, int iYear)
{
	int iDays = iDay-1;
	switch(iMonth-1)
	{
	case 11:// november
		iDays+=30;
	case 10:// october
		iDays+=31;
	case 9:// september
		iDays+=30;
	case 8://august
		iDays+=31;
	case 7:// july
		iDays+=31;
	case 6:// june
		iDays+=30;
	case 5:// may
		iDays+=31;
	case 4:// april
		iDays+=30;
	case 3:// march
		iDays+=31;
	case 2:// february
		if ((iYear %4) ==0) // leap year
			iDays+=29;
		else
			iDays+=28;
	case 1:iDays+=31; // january
	case 0:iDays+=0;
		break;
	}
	return iDays;
}
double ConvertDateTimeToTLEEpoch(int iDay, int iMonth, int iYear, int iHour, int iMin, int iSec, int iMills)
{
    // An epoch of 98001.00000000 corresponds to 0000 UT on 1998 January 01—in other words, 
    // midnight between 1997 December 31 and 1998 January 01. 
    // An epoch of 98000.00000000 would actually correspond to the beginning of 1997 December 31—strange as that might seem. 
    // Note that the epoch day starts at UT midnight (not noon) and that all times are measured mean solar rather than sidereal time units.
    int mYear = iYear-2000;
    int mDays = iDayOfTheYearZeroBase(iDay, iMonth, iYear)+1;
	long mCurSec = iHour * 60*60;
    mCurSec += iMin *60;
    mCurSec += iSec;
	double dEpoch = mYear *1000.0 + mDays;
	dEpoch += (((double)mCurSec)+ ((double)iMills/1000.))/ (24.0*60.0*60.0);
    return dEpoch;
}
long double ConverTLEEpochDate2JulianDay(long double KeplerDate)
{
    // TLE elements is 1 day based - needs to minus at the end one day
    int iYear = (int)(KeplerDate /1000);
    // date as it is = 2000/01/01     2451544.5, 2451910.5, 2452275.5, 2452640.5, 2453005.5, 2453371.5, 2453736.5, 2013-2456293.5
    // 
    double t2000_01_01_01 = 2451544.5;
    switch(iYear)
    {
        // add years = if you still alive !!! or just put formula if ((iYear-1)%4 == 0) t2000_01_01_01+=366; else t2000_01_01_01+=365;
    case 24:t2000_01_01_01+=365;
    case 23:t2000_01_01_01+=365;
    case 22:t2000_01_01_01+=365;
    case 21:t2000_01_01_01+=366;
    case 20:t2000_01_01_01+=365;
    case 19:t2000_01_01_01+=365;
    case 18:t2000_01_01_01+=365;
    case 17:t2000_01_01_01+=366;
    case 16:t2000_01_01_01+=365;
    case 15:t2000_01_01_01+=365;
    case 14:t2000_01_01_01+=365;
    case 13:t2000_01_01_01+=366;
    case 12:t2000_01_01_01+=365;
    case 11:t2000_01_01_01+=365;
    case 10:t2000_01_01_01+=365;
    case  9:t2000_01_01_01+=366;
    case  8:t2000_01_01_01+=365;
    case  7:t2000_01_01_01+=365;
    case  6:t2000_01_01_01+=365;
    case  5:t2000_01_01_01+=366;
    case  4:t2000_01_01_01+=365;
    case  3:t2000_01_01_01+=365;
    case  2:t2000_01_01_01+=365;
    case  1:t2000_01_01_01+=366;
    case  0:;
        // minus years = add if you interesting in anything from last century or use formala!!
    }
    //long it2000_01_01_01 = t2000_01_01_01;
    //double RestOfTheDay = t2000_01_01_01 - (double)it2000_01_01_01;
    return t2000_01_01_01// - RestOfTheDay 
            + KeplerDate - ((long double)(iYear*1000))
            -1; // epoch date is 1== 1 Jan - needs to adjust one day.
}

BOOL CallTraToConfirmation(void)
{
    BOOL bret = FALSE;
    char szXMLLine[1024];
    // open @TRA.XML
    FILE * MyTRAsetFIle = fopen("@TRA.XML", "r");
    if (MyTRAsetFIle!=NULL)    // reading old recordings
    {
        FILE * MyTRAOutFIle = fopen("TRA.XML", "w");
        if (MyTRAOutFIle!=NULL)    // reading old recordings
        {
            while(fgets(szXMLLine,sizeof(szXMLLine),MyTRAsetFIle))
            {
                char *myxmlline = strstr(szXMLLine, "<TRA:setting name=\"SimulationOutputTime\" value=\"0\" />");
                if (myxmlline != NULL)
                {
                    // change date of the observation. Pposition and type of calculation ("Mode" value="SIM", "SimulationType" value="PULSAR") must be set correctly
                    CTime MyTime = CTime(ReadPulseStruct.myShowSysTime);
                    CTimeSpan timeBias(0,iZoneBias,0,0);
                    CTime MySysTime = MyTime + timeBias;
                    SYSTEMTIME mystime;

                    MySysTime.GetAsSystemTime(mystime);
                    long double TLEdt = ConvertDateTimeToTLEEpoch(mystime.wDay, mystime.wMonth, mystime.wYear, mystime.wHour, mystime.wMinute, mystime.wSecond, 0);
                    //long double ld_dStartJD = ConverTLEEpochDate2JulianDay(Jdt);

                    fprintf(MyTRAOutFIle, "<TRA:setting name=\"SimulationOutputTime\" value=\"%.11f\" />\n", TLEdt);
                }
                else
                {
                    fprintf(MyTRAOutFIle, "%s", szXMLLine);
                }
            }
            fclose(MyTRAOutFIle);
        }
        fclose(MyTRAsetFIle);
    }
    // now needs to execute TRA to get pulsars data
    STARTUPINFO stinfo = { 0 };
    stinfo.cb = sizeof( stinfo );
    char szSourceFile[3*MAX_PATH];
    char szTragetFile[3*MAX_PATH];
    char CmdPath[3*_MAX_PATH];
    PROCESS_INFORMATION ProcInfo;
    strcpy(CmdPath, szModule);
    strcat(CmdPath, "\\tra.exe");
    char DirPath[3*_MAX_PATH];
    strcpy(DirPath, szModule);
    strcat(DirPath, "\\");

    BOOL fRC = CreateProcessA( CmdPath,       // name of executable module
                         NULL,    // command-line string
                         0,             // SD
                         0,             // SD
                         FALSE,         // inheritance option
                         IDLE_PRIORITY_CLASS | CREATE_UNICODE_ENVIRONMENT | CREATE_NO_WINDOW, // creation flags
                         0,             // new environment block
                         NULL,           // current directory name
                         &stinfo,       // startup information
                         &ProcInfo );   // process information

    DWORD err = GetLastError();
    if ( fRC )
    {
        WaitForSingleObject(ProcInfo.hProcess, 10000);
        bret = TRUE;
        CloseHandle( ProcInfo.hProcess );
        CloseHandle( ProcInfo.hThread );
        strcpy(szSourceFile, szModule);
        strcat(szSourceFile, "\\@trasimoutput.xml");
        strcpy(szTragetFile, szModule);
        strcat(szTragetFile, "\\trasimoutput.xml");
        bret = CopyFile(szSourceFile, szTragetFile, FALSE);
        err = GetLastError();
    }


    return bret;
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

void GetAllPulsarsData(void)
{
    g_fInputReadUrlOrFile = NULL;
    nPulsars = 0;;

    if (GetFileString("@tra.xml", "_tra_.xml", 0, NULL, 0) == 0) // open was successfull fInputReadUrlOrFile is a handler
    {
        ParamDoAllPulsars(g_fInputReadUrlOrFile);
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

    int Iret = GetTimeZoneInformation(&tmzone);

    GetLocalTime(&mySYsTime);
    m_Zone.AddString("-12");
    m_Zone.AddString("-11");
    m_Zone.AddString("-10");
    m_Zone.AddString("-9");
    m_Zone.AddString("-8");
    m_Zone.AddString("-7");
    m_Zone.AddString("-6");
    m_Zone.AddString("-5");
    m_Zone.AddString("-4");
    m_Zone.AddString("-3");
    m_Zone.AddString("-2");
    m_Zone.AddString("-1");
    m_Zone.AddString("0");
    m_Zone.AddString("+1");
    m_Zone.AddString("+2");
    m_Zone.AddString("+3");
    m_Zone.AddString("+4");
    m_Zone.AddString("+5");
    m_Zone.AddString("+6");
    m_Zone.AddString("+7");
    m_Zone.AddString("+8");
    m_Zone.AddString("+9");
    m_Zone.AddString("+10");
    m_Zone.AddString("+11");
    m_Zone.AddString("+12");
    for (int ip = 0 ; ip < m_Zone.GetCount(); ip++)
    {
        CString MyString0;
        m_Zone.GetText(ip, MyString0);
        int iVal = atoi(MyString0.GetString());
        if ((iVal * 60) == (tmzone.Bias + tmzone.DaylightBias))
        {
            m_Zone.SetCurSel(ip);
            iZoneBias = iVal;
            break;
        }
    }

    SYSTEMTIME MyTime1;
    GetSystemTime(&MyTime1);

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
    hBmpPicPulsar1 = NULL;
    hBmpPicPulsar2 = NULL;
    hBmpPicPulsar3 = NULL;
    hBmpPicPulsar4 = NULL;
    hBmpPicPulsar5 = NULL;
    hBmpPicPulsar6 = NULL;
    memset(bRGBImage, 0xff, sizeof(bRGBImage));
    CleanAllPictures();
    //SYSTEMTIME mySYsTime;
    GetLocalTime(&mySYsTime);
    memcpy(&OUtPutPulseStruct.myShowSysTime, &mySYsTime, sizeof(OUtPutPulseStruct.myShowSysTime));
    
    CTime MyTime = CTime(mySYsTime);

    m_Time.SetTime(&MyTime);
    m_Date.SetTime(&MyTime);

    old_check_box_status = 0;
    m_LastTime.SetCheck(old_check_box_status);

    if (m_LastTime.GetCheck()) // that is record operation
    {
        m_LastTime.SetWindowTextA("stop");
        MyOutPutFIle = fopen(szOutPutREcording, "ab");
        if (MyOutPutFIle!=NULL)
        {
            flRecordOpenedForWrite = TRUE;
        }
    }
    else                       //that is view recording
    {
        m_LastTime.SetWindowTextA("record");
        MyOutPutFIle = fopen(szOutPutREcording, "rb");
        if (MyOutPutFIle!=NULL)
        {
            flRecordOpenedForWrite = FALSE;
        }
    }

    //m_ShowLines.SetCheck(0);
    SetTimer(901, 1000,NULL);
    SetTimer(902,60500,NULL);
    m_LocalFile.SetWindowTextA(szOutPutREcording);

    m_NumberChan.SetCheck(1);
    g_numb_ch = 2;

    m_TimeDelta.SetWindowTextA("0");
    m_CountDb.SetWindowTextA("123456");
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
    if (hBmpPicPulsar1!=NULL)
        DeleteObject(hBmpPicPulsar1);
    if (hBmpPicPulsar2!=NULL)
        DeleteObject(hBmpPicPulsar2);
    if (hBmpPicPulsar3!=NULL)
        DeleteObject(hBmpPicPulsar3);
    if (hBmpPicPulsar4!=NULL)
        DeleteObject(hBmpPicPulsar4);
    if (hBmpPicPulsar5!=NULL)
        DeleteObject(hBmpPicPulsar5);
    if (hBmpPicPulsar6!=NULL)
        DeleteObject(hBmpPicPulsar6);

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
    int iPosSlide = m_SLider.GetPos();
    int iMaxSlide = m_SLider.GetRangeMax();
    if (flRecordOpenedForWrite == FALSE)
    {
        if (MyOutPutFIle != NULL)
        {
            /*
            g_reacordCurPos = g_reacordMAxSize*iPosSlide;
            g_reacordCurPos /=iMaxSlide;
             _fseeki64( MyOutPutFIle, g_reacordCurPos, SEEK_SET);
            for (long il = 0; il < SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC; il++)
            {
                BUFEDETECT1[il] = 0.0; BUFEDETECT2[il] = 0.0; BUFEDETECT3[il] = 0.0;
                BUFEDETECT4[il] = 0.0; BUFEDETECT5[il] = 0.0; BUFEDETECT6[il] = 0.0;
            }
            iPosIn1 = 0; Pmin1_1 = 1.0e64; Pmax1_1=-1.0e64; Pmin2_1 = 1.0e64; Pmax2_1=-1.0e64;
            iPosIn2 = 0; Pmin1_2 = 1.0e64; Pmax1_2=-1.0e64; Pmin2_2 = 1.0e64; Pmax2_2=-1.0e64;
            iPosIn3 = 0;  Pmin1_3 = 1.0e64; Pmax1_3=-1.0e64; Pmin2_3 = 1.0e64; Pmax2_3=-1.0e64;
            iPosIn4 = 0; Pmin1_4 = 1.0e64; Pmax1_4=-1.0e64; Pmin2_4 = 1.0e64; Pmax2_4=-1.0e64;
            iPosIn5 = 0; Pmin1_5 = 1.0e64; Pmax1_5=-1.0e64; Pmin2_5 = 1.0e64; Pmax2_5=-1.0e64;
            iPosIn6 = 0; Pmin1_6 = 1.0e64; Pmax1_6=-1.0e64; Pmin2_6 = 1.0e64; Pmax2_6=-1.0e64;
            */
        }
    }
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
        if (flRecordOpenedForWrite == FALSE) // that is ticking timer, and needs to show all switch of the data on the screen
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
                    if (g_iCountDB != 123456)
                    {
                        if (--g_iCountDB < 0)
                        {
                            if (flRecordOpenedForWrite == FALSE)
                            {
                                if (MyOutPutFIle!=NULL)    // reading old recordings
                                {
                                    if (DoAnalize)
                                    {
                                        if (DoFirstdb)
                                        {
                                            DoFirstdb = FALSE;
                                            g_iCountDB = g_iCountDB_old;
                                        }
                                        else
                                        {
                                            CString MyPos64;
                                            m_OffsetPosition.GetWindowTextA(MyPos64);
                                            char szText[64];
                                            strcpy(szText, MyPos64.GetString());
                                            __int64  recordCurPos =0;
                                            sscanf(szText, "%I64d",&recordCurPos);
                                            _fseeki64(MyOutPutFIle, recordCurPos, SEEK_SET);
                                            FILE *AnalizeLog = fopen("Analize.txt","a");
                                            if (AnalizeLog != NULL)
                                            {
                                                char szPulsar[_MAX_PATH]={"        "};

                                                // 1. find medum value => Medium1
                                                // 2. find medim for top-to-medium =>MediumT
                                                // 3. find medium from medul-to-bottom =>MediumB
                                                // 4. output max,min, medium1, mediumT, MediumB
                                                // 5. find metrix from FerstdB and seconddB (V1-V2)^2
                                                long double Medium1= 0;
                                                long double Medium2= 0;
                                                for (int ik = 0 ; ik < g_iTimeDelta; ik++)
                                                {
                                                    Medium1+=BUFEDETECT_1db_last[ik*2];
                                                    Medium2+=BUFEDETECT_2db_last[ik*2];
                                                }
                                                Medium1/=(long double)g_iTimeDelta*(long double)iCointdB1;
                                                Medium2/=(long double)g_iTimeDelta*(long double)iCointdB2;

                                                long double MediumT1= 0;
                                                long double MediumT2= 0;
                                                long double MediumB1= 0;
                                                long double MediumB2= 0;

                                                long iMediumT1= 0;
                                                long iMediumT2= 0;
                                                long iMediumB1= 0;
                                                long iMediumB2= 0;

                                                for (int ik = 0 ; ik < g_iTimeDelta; ik++)
                                                {
                                                    if (BUFEDETECT_1db_last[ik*2] > (Medium1*(long double)iCointdB1))
                                                    {
                                                        MediumT1+=BUFEDETECT_1db_last[ik*2];
                                                        iMediumT1++;
                                                    }
                                                    else
                                                    {
                                                        MediumB1+=BUFEDETECT_1db_last[ik*2];
                                                        iMediumB1++;
                                                    }
                                                    if (BUFEDETECT_2db_last[ik*2] > (Medium2*(long double)iCointdB2))
                                                    {
                                                        MediumT2+=BUFEDETECT_2db_last[ik*2];
                                                        iMediumT2++;
                                                    }
                                                    else
                                                    {
                                                        MediumB2+=BUFEDETECT_2db_last[ik*2];
                                                        iMediumB2++;
                                                    }
                                                }
                                                MediumT1/=(long double)iMediumT1*(long double)iCointdB1;
                                                MediumT2/=(long double)iMediumT2*(long double)iCointdB2;
                                                MediumB1/=(long double)iMediumB1*(long double)iCointdB1;
                                                MediumB2/=(long double)iMediumB2*(long double)iCointdB2;

                                                long double Metrix=0.0;
                                                for (int ik = 0 ; ik < g_iTimeDelta; ik++)
                                                {
                                                    Metrix+= (BUFEDETECT_1db_last[ik*2]-BUFEDETECT_2db_last[ik*2])*(BUFEDETECT_1db_last[ik*2]-BUFEDETECT_2db_last[ik*2]);
                                                }
                                                Metrix = sqrt(Metrix)/(g_iTimeDelta*(long double)iCointdB1);
                                                for (int ipu = 0; ipu < nPulsars; ipu++)
                                                {
                                                    if (((long)g_iTimeDelta) == ((long)(Pulsars[ipu].P0*SAMPLES_PER_SEC)))
                                                    {
                                                        strcpy(szPulsar, Pulsars[ipu].Name);
                                                        break;
                                                    }
                                                }
                                                fprintf(AnalizeLog,"\n%8s Period = %7.0f, Metrix=%13.7f Min1_Max1=%10.2f Min2_Max2=%10.2f MedT1_MedB1 =%13.3f MedT2_MedB2 =%13.3f",
                                                   szPulsar, g_iTimeDelta, Metrix, -omin1_db1/(long double)iCointdB1 + omax1_db1/(long double)iCointdB1, 

                                                   -omin1_db2/(long double)iCointdB2 + omax1_db2/(long double)iCointdB1, MediumT1 -MediumB1, MediumT2-MediumB2);

                                                fclose(AnalizeLog);
                                                iCointdB1 = 0; iCointdB2 = 0;
                                                omin1_db1 = 0.0; omax1_db1 = 0.0; omin2_db1 = 0.0; omax2_db1 = 0.0;
                                                for (long il = 0; il < SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC; il++)
                                                {
                                                    BUFEDETECT_1db[il] = 0.0; BUFEDETECT_2db[il] = 0.0;
                                                }
                                                Pdb1min1_tmp= 1.0e64; Pdb1max1_tmp =-1.0e64; Pdb1min2_tmp = 1.0e64; Pdb1max2_tmp =-1.0e64;
                                                Pdb2min1_tmp= 1.0e64; Pdb2max1_tmp =-1.0e64; Pdb2min2_tmp = 1.0e64; Pdb2max2_tmp =-1.0e64;
                                                idb1PosIn = 0; idb2PosIn = 0;
                                                Fraction1db = 0.0; Fraction2db = 0.0;
                                            }

                                            DoFirstdb = TRUE;
                                            g_iCountDB = g_iCountDB_old;
                                            g_iTimeDelta +=1;
                                            if (g_iTimeDelta > g_Analize_To)
                                            {
                                                flRunningRecording = FALSE;
                                                DoAnalize = FALSE;
                                                m_Analize.SetWindowTextA("Analize");
                                                KillTimer(901);
                                                SetTimer(901, 1000,NULL);
                                                g_SecondsPerScreen = 1;
                                                break;
                                            }
                                            {
                                                char szAnalizeFQ[_MAX_PATH];
                                                sprintf(szAnalizeFQ,"%13.3f",g_iTimeDelta);
                                                m_TimeDelta.SetWindowTextA(szAnalizeFQ);
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (flRunningRecording == TRUE)
                                        {
                                            flRunningRecording = FALSE;
                                            m_Run.SetWindowTextA("run");
                                            CString mystr;
                                            m_ChanVis.GetWindowTextA(mystr);
                                            char szmystr[64];
                                            char szmystrmin[64];
                                            char szmystrmax[64];
                                            strcpy(szmystr, mystr.GetString());
                                            int iCh = atoi(szmystr);
                                            switch(iCh)
                                            {
                                            case 0: sprintf(szmystrmin, "%f", omin1_1); sprintf(szmystrmax, "%f", omax1_1); break;
                                            case 1: sprintf(szmystrmin, "%f", omin1_2); sprintf(szmystrmax, "%f", omax1_2); break;
                                            case 2: sprintf(szmystrmin, "%f", omin1_3); sprintf(szmystrmax, "%f", omax1_3); break;
                                            case 3: sprintf(szmystrmin, "%f", omin1_4); sprintf(szmystrmax, "%f", omax1_4); break;
                                            case 4: sprintf(szmystrmin, "%f", omin1_5); sprintf(szmystrmax, "%f", omax1_5); break;
                                            case 5: sprintf(szmystrmin, "%f", omin1_6); sprintf(szmystrmax, "%f", omax1_6); break;
                                            }
                                            m_Minimum.SetWindowTextA(szmystrmin);
                                            m_Maximum.SetWindowTextA(szmystrmax);
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
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
                                if (DoAnalize)
                                {
                                    AudioStreamCallback(NULL,&WAVEHDRMainRead, TRUE);
                                    g_reacordCurPos = _ftelli64(MyOutPutFIle);
                                    CTime MyTime = CTime(ReadPulseStruct.myShowSysTime);
                                    m_Time.SetTime(&MyTime);
                                    m_Date.SetTime(&MyTime);
                                    m_SLider.SetPos((m_SLider.GetRangeMax()* g_reacordCurPos)/g_reacordMAxSize);
                                }
                                else
                                {
                                    if (FirstRead==FALSE)
                                    {
                                        FirstRead = TRUE;
                                        for (long il = 0; il < SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC; il++)
                                        {
                                            BUFEDETECT1[il] = 0.0;
                                            BUFEDETECT2[il] = 0.0;
                                            BUFEDETECT3[il] = 0.0;
                                            BUFEDETECT4[il] = 0.0;
                                            BUFEDETECT5[il] = 0.0;
                                            BUFEDETECT6[il] = 0.0;
                                        }
                                        iPosIn1 = 0; iPosIn2 = 0; iPosIn3 = 0; iPosIn4 = 0; iPosIn5 = 0; iPosIn6 = 0;
                                        Fraction1 = 0.0; Fraction2 = 0.0; Fraction3 = 0.0; Fraction4 = 0.0; Fraction5 = 0.0; Fraction6 = 0.0;
                                        Pmin1_1 = 1.0e64; Pmax1_1=-1.0e64; Pmin2_1 = 1.0e64; Pmax2_1=-1.0e64;
                                        Pmin1_2 = 1.0e64; Pmax1_2=-1.0e64; Pmin2_2 = 1.0e64; Pmax2_2=-1.0e64;
                                        Pmin1_3 = 1.0e64; Pmax1_3=-1.0e64; Pmin2_3 = 1.0e64; Pmax2_3=-1.0e64;
                                        Pmin1_4 = 1.0e64; Pmax1_4=-1.0e64; Pmin2_4 = 1.0e64; Pmax2_4=-1.0e64;
                                        Pmin1_5 = 1.0e64; Pmax1_5=-1.0e64; Pmin2_5 = 1.0e64; Pmax2_5=-1.0e64;
                                        Pmin1_6 = 1.0e64; Pmax1_6=-1.0e64; Pmin2_6 = 1.0e64; Pmax2_6=-1.0e64;
                                    }
                                    if (CallTraToConfirmation())
                                    {
                                        //FirstRead = TRUE;
                                        GetCurentPulsarsData();
                                        if (iMaxMeasures)
                                        {
                                            // pulsars on top of head
                                            OUtPutPulseStruct.iCountofVisiblePulsars = iMaxMeasures;
                                            ReadPulseStruct.iCountofVisiblePulsars = iMaxMeasures;
                                            for (int i = 0; i < OUtPutPulseStruct.iCountofVisiblePulsars; i++)
                                            {
                                                OUtPutPulseStruct.pulsars_over_head[i].NearBody = pulsars_over_head[i].NearBody;
                                                OUtPutPulseStruct.pulsars_over_head[i].T = pulsars_over_head[i].T;
                                                OUtPutPulseStruct.pulsars_over_head[i].px = pulsars_over_head[i].px;
                                                //strcpy(OUtPutPulseStruct.pulsars_over_head[i].szN, pulsars_over_head[i].szN);
                                                OUtPutPulseStruct.pulsars_over_head[i].P0 = pulsars_over_head[i].P0;
                                                OUtPutPulseStruct.pulsars_over_head[i].P119 = pulsars_over_head[i].P119;
                                                OUtPutPulseStruct.pulsars_over_head[i].jy = pulsars_over_head[i].jy;
                                                OUtPutPulseStruct.pulsars_over_head[i].TError = pulsars_over_head[i].TError;

                                                ReadPulseStruct.pulsars_over_head[i].NearBody = pulsars_over_head[i].NearBody;
                                                ReadPulseStruct.pulsars_over_head[i].T = pulsars_over_head[i].T;
                                                ReadPulseStruct.pulsars_over_head[i].px = pulsars_over_head[i].px;
                                                if (strcmp(OUtPutPulseStruct.pulsars_over_head[i].szN, pulsars_over_head[i].szN) != 0)
                                                {
                                                    switch(i)
                                                    {
                                                    case 0:
                                                        for (long il = 0; il < SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC; il++)
                                                            BUFEDETECT1[il] = 0.0;
                                                        iPosIn1 = 0; Pmin1_1 = 1.0e64; Pmax1_1=-1.0e64; Pmin2_1 = 1.0e64; Pmax2_1=-1.0e64;
                                                        Fraction1 = 0.0;
                                                        break;
                                                    case 1:
                                                        for (long il = 0; il < SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC; il++)
                                                            BUFEDETECT2[il] = 0.0;
                                                        iPosIn2 = 0; Pmin1_2 = 1.0e64; Pmax1_2=-1.0e64; Pmin2_2 = 1.0e64; Pmax2_2=-1.0e64;
                                                        Fraction2 = 0.0;
                                                        break;
                                                    case 2:
                                                        for (long il = 0; il < SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC; il++)
                                                            BUFEDETECT3[il] = 0.0;
                                                        iPosIn3 = 0;  Pmin1_3 = 1.0e64; Pmax1_3=-1.0e64; Pmin2_3 = 1.0e64; Pmax2_3=-1.0e64;
                                                        Fraction3 = 0.0;
                                                        break;
                                                    case 3:
                                                        for (long il = 0; il < SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC; il++)
                                                            BUFEDETECT4[il] = 0.0;
                                                        iPosIn4 = 0; Pmin1_4 = 1.0e64; Pmax1_4=-1.0e64; Pmin2_4 = 1.0e64; Pmax2_4=-1.0e64;
                                                        Fraction4 = 0.0;
                                                        break;
                                                    case 4:
                                                        for (long il = 0; il < SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC; il++)
                                                            BUFEDETECT5[il] = 0.0;
                                                        iPosIn5 = 0; Pmin1_5 = 1.0e64; Pmax1_5=-1.0e64; Pmin2_5 = 1.0e64; Pmax2_5=-1.0e64;
                                                        Fraction5 = 0.0;
                                                        break;
                                                    case 5:
                                                        for (long il = 0; il < SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC; il++)
                                                            BUFEDETECT6[il] = 0.0;
                                                        iPosIn6 = 0; Pmin1_6 = 1.0e64; Pmax1_6=-1.0e64; Pmin2_6 = 1.0e64; Pmax2_6=-1.0e64;
                                                        Fraction6 = 0.0;
                                                        break;
                                                    }
                                                }
                                                strcpy(OUtPutPulseStruct.pulsars_over_head[i].szN, pulsars_over_head[i].szN);
                                                ReadPulseStruct.pulsars_over_head[i].P0 = pulsars_over_head[i].P0;
                                                ReadPulseStruct.pulsars_over_head[i].P119 = pulsars_over_head[i].P119;
                                                ReadPulseStruct.pulsars_over_head[i].jy = pulsars_over_head[i].jy;
                                                BITMAPINFO binfPicPulsar;
       	                                        memset((void*)&binfPicPulsar,0,sizeof(binfPicPulsar));
                                                RECT myRect;

                                                HDC         hDC;                    
                                                hDC = ::GetDC(NULL); 
 		                                        // create bitmap from DIB info. and bits 
                                                switch(i)
                                                {
                                                case 0:  if (hBmpPicPulsar1!=NULL) DeleteObject(hBmpPicPulsar1); m_PicPulse1.GetWindowRect(&myRect);break;
                                                case 1:  if (hBmpPicPulsar2!=NULL) DeleteObject(hBmpPicPulsar2); m_PicPulse2.GetWindowRect(&myRect);break;
                                                case 2:  if (hBmpPicPulsar3!=NULL) DeleteObject(hBmpPicPulsar3); m_PicPulse3.GetWindowRect(&myRect);break;
                                                case 3:  if (hBmpPicPulsar4!=NULL) DeleteObject(hBmpPicPulsar4); m_PicPulse4.GetWindowRect(&myRect);break;
                                                case 4:  if (hBmpPicPulsar5!=NULL) DeleteObject(hBmpPicPulsar5); m_PicPulse5.GetWindowRect(&myRect);break;
                                                case 5:  if (hBmpPicPulsar6!=NULL) DeleteObject(hBmpPicPulsar6); m_PicPulse6.GetWindowRect(&myRect);break;
                                                }

    		                                    binfPicPulsar.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
                                                binfPicPulsar.bmiHeader.biWidth = bRGBImageW_S;//read_image_width; 
                                                binfPicPulsar.bmiHeader.biHeight = bRGBImageH_S;//read_image_height; 
		                                        binfPicPulsar.bmiHeader.biPlanes = 1; 
		                                        binfPicPulsar.bmiHeader.biBitCount = 24; 
		                                        binfPicPulsar.bmiHeader.biCompression = BI_RGB; 
		                                        binfPicPulsar.bmiHeader.biSizeImage = 0; 
		                                        binfPicPulsar.bmiHeader.biXPelsPerMeter = 0; 
		                                        binfPicPulsar.bmiHeader.biYPelsPerMeter = 0; 
		                                        binfPicPulsar.bmiHeader.biClrUsed = 0; 
		                                        binfPicPulsar.bmiHeader.biClrImportant = 0; 
                                                char szText[3*MAX_PATH];
                                                sprintf(szText, "%s %1.3f (%d)%3.2f",OUtPutPulseStruct.pulsars_over_head[i].szN, 
                                                    OUtPutPulseStruct.pulsars_over_head[i].px, (int)OUtPutPulseStruct.pulsars_over_head[i].jy,OUtPutPulseStruct.pulsars_over_head[i].TError);

                                                switch(i)
                                                {
                                                case 0: 
                                                    hBmpPicPulsar1 = CreateDIBitmap(hDC, &(binfPicPulsar.bmiHeader), CBM_INIT, bRGBImage_S1, &binfPicPulsar, DIB_RGB_COLORS); 
                                                    m_PicPulse1.SetBitmap(hBmpPicPulsar1); m_PicPulse1.GetWindowRect(&myRect); m_PicPulse1.ValidateRect(&myRect);
                                                    m_PicPulse1.UpdateWindow();
                                                    m_Period1.SetWindowTextA(szText);
                                                    break;
                                                case 1: 
                                                    hBmpPicPulsar2 = CreateDIBitmap(hDC, &(binfPicPulsar.bmiHeader), CBM_INIT, bRGBImage_S2, &binfPicPulsar, DIB_RGB_COLORS); 
                                                    m_PicPulse2.SetBitmap(hBmpPicPulsar2); m_PicPulse2.GetWindowRect(&myRect); m_PicPulse2.ValidateRect(&myRect);
                                                    m_PicPulse2.UpdateWindow();
                                                    m_Period2.SetWindowTextA(szText);
                                                    break;
                                                case 2: 
                                                    hBmpPicPulsar3 = CreateDIBitmap(hDC, &(binfPicPulsar.bmiHeader), CBM_INIT, bRGBImage_S3, &binfPicPulsar, DIB_RGB_COLORS); 
                                                    m_PicPulse3.SetBitmap(hBmpPicPulsar3); m_PicPulse3.GetWindowRect(&myRect); m_PicPulse3.ValidateRect(&myRect);
                                                    m_PicPulse3.UpdateWindow();
                                                    m_Period3.SetWindowTextA(szText);
                                                    break;
                                                case 3: 
                                                    hBmpPicPulsar4 = CreateDIBitmap(hDC, &(binfPicPulsar.bmiHeader), CBM_INIT, bRGBImage_S4, &binfPicPulsar, DIB_RGB_COLORS); 
                                                    m_PicPulse4.SetBitmap(hBmpPicPulsar4); m_PicPulse4.GetWindowRect(&myRect); m_PicPulse4.ValidateRect(&myRect);
                                                    m_PicPulse4.UpdateWindow();
                                                    m_Period4.SetWindowTextA(szText);
                                                    break;
                                                case 4: 
                                                    hBmpPicPulsar5 = CreateDIBitmap(hDC, &(binfPicPulsar.bmiHeader), CBM_INIT, bRGBImage_S5, &binfPicPulsar, DIB_RGB_COLORS); 
                                                    m_PicPulse5.SetBitmap(hBmpPicPulsar5); m_PicPulse5.GetWindowRect(&myRect); m_PicPulse5.ValidateRect(&myRect);
                                                    m_PicPulse5.UpdateWindow();
                                                    m_Period5.SetWindowTextA(szText);
                                                    break;
                                                case 5: 
                                                    hBmpPicPulsar6 = CreateDIBitmap(hDC, &(binfPicPulsar.bmiHeader), CBM_INIT, bRGBImage_S6, &binfPicPulsar, DIB_RGB_COLORS); 
                                                    m_PicPulse6.SetBitmap(hBmpPicPulsar6); m_PicPulse6.GetWindowRect(&myRect); m_PicPulse6.ValidateRect(&myRect);
                                                    m_PicPulse6.UpdateWindow();
                                                    m_Period6.SetWindowTextA(szText);
                                                    break;
                                                }
		                                        ::ReleaseDC(NULL, hDC); 
                                            }
                                        }
                                    }
                                    else
                                    {
                                        ReadPulseStruct.iCountofVisiblePulsars = iMaxMeasures;
                                        for (int i = 0; i < ReadPulseStruct.iCountofVisiblePulsars; i++)
                                        {
                                            ReadPulseStruct.pulsars_over_head[i].NearBody = pulsars_over_head[i].NearBody;
                                            ReadPulseStruct.pulsars_over_head[i].T = pulsars_over_head[i].T;
                                            ReadPulseStruct.pulsars_over_head[i].px = pulsars_over_head[i].px;
                                            strcpy(ReadPulseStruct.pulsars_over_head[i].szN, pulsars_over_head[i].szN);
                                            ReadPulseStruct.pulsars_over_head[i].P0 = pulsars_over_head[i].P0;
                                            ReadPulseStruct.pulsars_over_head[i].P119 = pulsars_over_head[i].P119;
                                        }
                                    }
                                    AudioStreamCallback(NULL,&WAVEHDRMainRead, TRUE);
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
    }
    else if (nIDEvent== 902)
    {
        if (flRecordOpenedForWrite == FALSE) // that is ticking timer, and needs to show all switch of the data on the screen
        {
            if (MyOutPutFIle != NULL)
            {
                // needs to confirm position of a pulsars
                //if (CallTraToConfirmation())
                //{
                //    GetCurentPulsarsData();
                //}
            }
        }
        else
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
                    OUtPutPulseStruct.pulsars_over_head[i].jy = pulsars_over_head[i].jy;
                }
            }
        }

    }
    CDialogEx::OnTimer(nIDEvent);
}

void CpulseMonitorDlg::SetRead()
{
            while(fInsideCallBack)
            {
                Sleep(100);
            }
            if (MyOutPutFIle)
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
            m_LastTime.SetWindowTextA("record");
}
void CpulseMonitorDlg::SetWrite()
{
        {
            if (MyOutPutFIle)
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
            m_LastTime.SetWindowTextA("stop");
        }

}

void CpulseMonitorDlg::OnBnClickedCheckLast()
{
    // TODO: Add your control notification handler code here

    int iCheckBoxnow = m_LastTime.GetCheck();
    if (iCheckBoxnow != old_check_box_status)
    {
        if (old_check_box_status == 1) // was recording
        {
            SetRead();
        }
        else // was reading
        {
            SetWrite();
        }
        old_check_box_status = iCheckBoxnow;
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
        if (flRecordOpenedForWrite == FALSE)
        {
            if (MyOutPutFIle!=NULL)    // reading old recordings
            {
                __int64  recordCurPos = _ftelli64(MyOutPutFIle);
                char szOffset[64];
                sprintf(szOffset, "%I64d", recordCurPos);
                m_OffsetPosition.SetWindowTextA(szOffset);
                g_iCountDB = 123456;
            }
        }
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


void CpulseMonitorDlg::OnBnClickedButtonSelectFile()
{
    // TODO: Add your control notification handler code here
    CFileDialog dlg(FALSE, _T("apuls"), _T("*.apuls"), 0);//OFN_OVERWRITEPROMPT);
    if(dlg.DoModal() == IDOK)
    {
        CString KeyFileName;
        CStringA KeyFileNameA;
        POSITION fileNamesPosition  = dlg.GetStartPosition();
        if (fileNamesPosition != NULL)
        {
            KeyFileName = dlg.GetNextPathName(fileNamesPosition);
            KeyFileNameA = (CStringA)KeyFileName;
            strcpy(szOutPutREcording, KeyFileNameA.GetString());
            m_LocalFile.SetWindowTextA(szOutPutREcording);
            if (old_check_box_status == 1) // was recording
            {
                SetWrite();
            }
            else // was reading
            {
                SetRead();
            }
        }
    }

}


void CpulseMonitorDlg::OnLbnSelchangeListZone()
{
    // TODO: Add your control notification handler code here
    int isel = m_Zone.GetCurSel();
    CString MyString0;
    m_Zone.GetText(isel, MyString0);
    iZoneBias = atoi(MyString0.GetString());

}


void CpulseMonitorDlg::OnBnClickedButtonClear()
{
    // TODO: Add your control notification handler code here
    CleanRQ1 = TRUE; CleanRQ2 = TRUE; CleanRQ3 = TRUE; CleanRQ4 = TRUE; CleanRQ5 = TRUE; CleanRQ6 = TRUE;
    /*
    for (long il = 0; il < SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*2; il++)
    {
        BUFEDETECT1[il] = 0.0; BUFEDETECT2[il] = 0.0; BUFEDETECT3[il] = 0.0;
        BUFEDETECT4[il] = 0.0; BUFEDETECT5[il] = 0.0; BUFEDETECT6[il] = 0.0;
    }
    iPosIn1 = 0; Pmin1_1 = 1.0e64; Pmax1_1=-1.0e64; Pmin2_1 = 1.0e64; Pmax2_1=-1.0e64;
    iPosIn2 = 0; Pmin1_2 = 1.0e64; Pmax1_2=-1.0e64; Pmin2_2 = 1.0e64; Pmax2_2=-1.0e64;
    iPosIn3 = 0;  Pmin1_3 = 1.0e64; Pmax1_3=-1.0e64; Pmin2_3 = 1.0e64; Pmax2_3=-1.0e64;
    iPosIn4 = 0; Pmin1_4 = 1.0e64; Pmax1_4=-1.0e64; Pmin2_4 = 1.0e64; Pmax2_4=-1.0e64;
    iPosIn5 = 0; Pmin1_5 = 1.0e64; Pmax1_5=-1.0e64; Pmin2_5 = 1.0e64; Pmax2_5=-1.0e64;
    iPosIn6 = 0; Pmin1_6 = 1.0e64; Pmax1_6=-1.0e64; Pmin2_6 = 1.0e64; Pmax2_6=-1.0e64;
    */
}


void CpulseMonitorDlg::OnBnClickedButtonCleanFq1()
{
    // TODO: Add your control notification handler code here
    CleanRQ1 = TRUE;
}


void CpulseMonitorDlg::OnBnClickedButtonCleanFq2()
{
    // TODO: Add your control notification handler code here
    CleanRQ2 = TRUE;
}


void CpulseMonitorDlg::OnBnClickedButtonCleanFq3()
{
    // TODO: Add your control notification handler code here
    CleanRQ3 = TRUE;
}


void CpulseMonitorDlg::OnBnClickedButtonCleanFq4()
{
    // TODO: Add your control notification handler code here
    CleanRQ4 = TRUE;
}


void CpulseMonitorDlg::OnBnClickedButtonCleanFq5()
{
    // TODO: Add your control notification handler code here
    CleanRQ5 = TRUE;
}


void CpulseMonitorDlg::OnBnClickedButtonCleanFq6()
{
    // TODO: Add your control notification handler code here
    CleanRQ6 = TRUE;
}


void CpulseMonitorDlg::OnBnClickedCheckNCh()
{
    // TODO: Add your control notification handler code here
    if (m_NumberChan.GetCheck())
    {
        g_numb_ch = 2;
        m_NumberChan.SetWindowTextA("2ch");
    }
    else
    {
        g_numb_ch = 1;
        m_NumberChan.SetWindowTextA("Dif");
    }
}


void CpulseMonitorDlg::OnBnClickedButtonSetPos()
{
    // TODO: Add your control notification handler code here
    if (flRecordOpenedForWrite == FALSE)
    {
        if (MyOutPutFIle!=NULL)    // reading old recordings
        {
            CString MyPos64;
            m_OffsetPosition.GetWindowTextA(MyPos64);
            char szText[64];
            strcpy(szText, MyPos64.GetString());
            __int64  recordCurPos =0;
            sscanf(szText, "%I64d",&recordCurPos);
            for (long il = 0; il < SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC; il++)
            {
                BUFEDETECT1[il] = 0.0; BUFEDETECT2[il] = 0.0; BUFEDETECT3[il] = 0.0;
                BUFEDETECT4[il] = 0.0; BUFEDETECT5[il] = 0.0; BUFEDETECT6[il] = 0.0;
            }
            iPosIn1 = 0; iPosIn2 = 0; iPosIn3 = 0; iPosIn4 = 0; iPosIn5 = 0; iPosIn6 = 0;
            Fraction1 = 0.0; Fraction2 = 0.0; Fraction3 = 0.0; Fraction4 = 0.0; Fraction5 = 0.0; Fraction6 = 0.0;
            Pmin1_1 = 1.0e64; Pmax1_1=-1.0e64; Pmin2_1 = 1.0e64; Pmax2_1=-1.0e64;
            Pmin1_2 = 1.0e64; Pmax1_2=-1.0e64; Pmin2_2 = 1.0e64; Pmax2_2=-1.0e64;
            Pmin1_3 = 1.0e64; Pmax1_3=-1.0e64; Pmin2_3 = 1.0e64; Pmax2_3=-1.0e64;
            Pmin1_4 = 1.0e64; Pmax1_4=-1.0e64; Pmin2_4 = 1.0e64; Pmax2_4=-1.0e64;
            Pmin1_5 = 1.0e64; Pmax1_5=-1.0e64; Pmin2_5 = 1.0e64; Pmax2_5=-1.0e64;
            Pmin1_6 = 1.0e64; Pmax1_6=-1.0e64; Pmin2_6 = 1.0e64; Pmax2_6=-1.0e64;
            _fseeki64(MyOutPutFIle, recordCurPos, SEEK_SET);
        }
    }
}


void CpulseMonitorDlg::OnBnClickedButtonAnalize()
{
    // TODO: Add your control notification handler code here
    if (DoAnalize)
    {
        DoAnalize = FALSE;
        m_Analize.SetWindowTextA("Analize");
        KillTimer(901);
        SetTimer(901, 1000,NULL);
    }
    else
    {
        KillTimer(901);
        DoAnalize = TRUE;
        DoFirstdb = TRUE;
        CleanAllPictures();
        CString MyPos64;
        m_OffsetPosition.GetWindowTextA(MyPos64);
        char szText[64];
        strcpy(szText, MyPos64.GetString());
        __int64  recordCurPos =0;
        sscanf(szText, "%I64d",&recordCurPos);

        _fseeki64(MyOutPutFIle, recordCurPos, SEEK_SET);
        m_TimeDelta.GetWindowTextA(MyPos64);
        strcpy(szText, MyPos64.GetString());
        //g_iTimeDelta = atof(szText);

        m_CountDb.GetWindowTextA(MyPos64);
        strcpy(szText, MyPos64.GetString());
        g_iCountDB = atoi(szText);
        g_iCountDB_old = g_iCountDB;

        m_From_P.GetWindowTextA(MyPos64);
        strcpy(szText, MyPos64.GetString());
        g_Analize_From = atol(szText);
        g_iTimeDelta = g_Analize_From;
        m_TimeDelta.SetWindowTextA(szText);

        m_To_P.GetWindowTextA(MyPos64);
        strcpy(szText, MyPos64.GetString());
        g_Analize_To = atol(szText);

        GetAllPulsarsData();
        m_Analize.SetWindowTextA("Analizing");
        g_j = 0;
        if (flRunningRecording == FALSE)
        {
            flRunningRecording = TRUE;
        }
        SetTimer(901, 100,NULL);
    }
}


void CpulseMonitorDlg::OnBnClickedButtonRunDb()
{
    // TODO: Add your control notification handler code here
    if (flRunningRecording == FALSE)
    {
        flRunningRecording = TRUE;
        m_Run.SetWindowTextA("stp");
        if (flRecordOpenedForWrite == FALSE)
        {
            if (MyOutPutFIle!=NULL)    // reading old recordings
            {
                CString MyPos64;
                m_OffsetPosition.GetWindowTextA(MyPos64);
                char szText[64];
                strcpy(szText, MyPos64.GetString());
                __int64  recordCurPos =0;
                sscanf(szText, "%I64d",&recordCurPos);
                
                CleanAllPictures();

                _fseeki64(MyOutPutFIle, recordCurPos, SEEK_SET);
                m_TimeDelta.GetWindowTextA(MyPos64);
                strcpy(szText, MyPos64.GetString());
                g_iTimeDelta = atof(szText);

                m_CountDb.GetWindowTextA(MyPos64);
                strcpy(szText, MyPos64.GetString());
                g_iCountDB = atoi(szText);

            }
        }
    }
    else
    {
        flRunningRecording = FALSE;
        m_Run.SetWindowTextA("run");
        if (flRecordOpenedForWrite == FALSE)
        {
            if (MyOutPutFIle!=NULL)    // reading old recordings
            {
                __int64  recordCurPos = _ftelli64(MyOutPutFIle);
                char szOffset[64];
                sprintf(szOffset, "%I64d", recordCurPos);
                m_OffsetPosition.SetWindowTextA(szOffset);


            }
        }
    }

}
void CpulseMonitorDlg::CleanAllPictures(void)
{
    memset(bRGBImage_S1, 0xff, sizeof(bRGBImage_S1));
    memset(bRGBImage_S2, 0xff, sizeof(bRGBImage_S2));
    memset(bRGBImage_S3, 0xff, sizeof(bRGBImage_S3));
    memset(bRGBImage_S4, 0xff, sizeof(bRGBImage_S4));
    memset(bRGBImage_S5, 0xff, sizeof(bRGBImage_S5));
    memset(bRGBImage_S6, 0xff, sizeof(bRGBImage_S6));
    for (long il = 0; il < SAMPLES_PER_SEC*NUMBER_OF_CHANNELS*MAX_PERIOD_IN_SEC; il++)
    {
        BUFEDETECT1[il] = 0.0;    BUFEDETECT2[il] = 0.0;    BUFEDETECT3[il] = 0.0;
        BUFEDETECT4[il] = 0.0;    BUFEDETECT5[il] = 0.0;    BUFEDETECT6[il] = 0.0;
        BUFEDETECT_1db[il] = 0.0; BUFEDETECT_2db[il] = 0.0;
    }
    Pdb1min1_tmp= 1.0e64; Pdb1max1_tmp =-1.0e64; Pdb1min2_tmp = 1.0e64; Pdb1max2_tmp =-1.0e64;
    Pdb2min1_tmp= 1.0e64; Pdb2max1_tmp =-1.0e64; Pdb2min2_tmp = 1.0e64; Pdb2max2_tmp =-1.0e64;
    idb1PosIn = 0; idb2PosIn = 0;
    Fraction1db = 0.0; Fraction2db = 0.0;

    iPosIn1 = 0; iPosIn2 = 0; iPosIn3 = 0; iPosIn4 = 0; iPosIn5 = 0; iPosIn6 = 0;
    Fraction1 = 0.0; Fraction2 = 0.0; Fraction3 = 0.0; Fraction4 = 0.0; Fraction5 = 0.0; Fraction6 = 0.0;
    iCointdB1 = 0; iCointdB2 = 0;
    omin1_db1 = 0.0; omax1_db1 = 0.0; omin2_db1 = 0.0; omax2_db1 = 0.0;
    omin1_db2 = 0.0; omax1_db2 = 0.0; omin2_db2 = 0.0; omax2_db2 = 0.0;

    Pmin1_1 = 1.0e64; Pmax1_1=-1.0e64; Pmin2_1 = 1.0e64; Pmax2_1=-1.0e64;
    Pmin1_2 = 1.0e64; Pmax1_2=-1.0e64; Pmin2_2 = 1.0e64; Pmax2_2=-1.0e64;
    Pmin1_3 = 1.0e64; Pmax1_3=-1.0e64; Pmin2_3 = 1.0e64; Pmax2_3=-1.0e64;
    Pmin1_4 = 1.0e64; Pmax1_4=-1.0e64; Pmin2_4 = 1.0e64; Pmax2_4=-1.0e64;
    Pmin1_5 = 1.0e64; Pmax1_5=-1.0e64; Pmin2_5 = 1.0e64; Pmax2_5=-1.0e64;
    Pmin1_6 = 1.0e64; Pmax1_6=-1.0e64; Pmin2_6 = 1.0e64; Pmax2_6=-1.0e64;

    omin1_1 = 0.0; omax1_1=0.0; omin2_1 = 0.0; omax2_1=0.0;
    omin1_2 = 0.0; omax1_2=0.0; omin2_2 = 0.0; omax2_2=0.0;
    omin1_3 = 0.0; omax1_3=0.0; omin2_3 = 0.0; omax2_3=0.0;
    omin1_4 = 0.0; omax1_4=0.0; omin2_4 = 0.0; omax2_4=0.0;
    omin1_5 = 0.0; omax1_5=0.0; omin2_5 = 0.0; omax2_5=0.0;
    omin1_6 = 0.0; omax1_6=0.0; omin2_6 = 0.0; omax2_6=0.0;
    for (int i =0; i < 6; i++)
    {
        BITMAPINFO binfPicPulsar;
        memset((void*)&binfPicPulsar,0,sizeof(binfPicPulsar));
        RECT myRect;
        HDC         hDC;                    
        hDC = ::GetDC(NULL); 
 		// create bitmap from DIB info. and bits 
        switch(i)
        {
        case 0:  if (hBmpPicPulsar1!=NULL) DeleteObject(hBmpPicPulsar1); m_PicPulse1.GetWindowRect(&myRect);break;
        case 1:  if (hBmpPicPulsar2!=NULL) DeleteObject(hBmpPicPulsar2); m_PicPulse2.GetWindowRect(&myRect);break;
        case 2:  if (hBmpPicPulsar3!=NULL) DeleteObject(hBmpPicPulsar3); m_PicPulse3.GetWindowRect(&myRect);break;
        case 3:  if (hBmpPicPulsar4!=NULL) DeleteObject(hBmpPicPulsar4); m_PicPulse4.GetWindowRect(&myRect);break;
        case 4:  if (hBmpPicPulsar5!=NULL) DeleteObject(hBmpPicPulsar5); m_PicPulse5.GetWindowRect(&myRect);break;
        case 5:  if (hBmpPicPulsar6!=NULL) DeleteObject(hBmpPicPulsar6); m_PicPulse6.GetWindowRect(&myRect);break;
        }

    	binfPicPulsar.bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
        binfPicPulsar.bmiHeader.biWidth = bRGBImageW_S;//read_image_width; 
        binfPicPulsar.bmiHeader.biHeight = bRGBImageH_S;//read_image_height; 
		binfPicPulsar.bmiHeader.biPlanes = 1; 
		binfPicPulsar.bmiHeader.biBitCount = 24; 
		binfPicPulsar.bmiHeader.biCompression = BI_RGB; 
		binfPicPulsar.bmiHeader.biSizeImage = 0; 
		binfPicPulsar.bmiHeader.biXPelsPerMeter = 0; 
		binfPicPulsar.bmiHeader.biYPelsPerMeter = 0; 
		binfPicPulsar.bmiHeader.biClrUsed = 0; 
		binfPicPulsar.bmiHeader.biClrImportant = 0; 
        char szText[3*MAX_PATH] = {"                "};
        switch(i)
        {
        case 0: 
            hBmpPicPulsar1 = CreateDIBitmap(hDC, &(binfPicPulsar.bmiHeader), CBM_INIT, bRGBImage_S1, &binfPicPulsar, DIB_RGB_COLORS); 
            m_PicPulse1.SetBitmap(hBmpPicPulsar1); m_PicPulse1.GetWindowRect(&myRect); m_PicPulse1.ValidateRect(&myRect);
            m_PicPulse1.UpdateWindow();
            m_Period1.SetWindowTextA(szText);
            break;
        case 1: 
            hBmpPicPulsar2 = CreateDIBitmap(hDC, &(binfPicPulsar.bmiHeader), CBM_INIT, bRGBImage_S2, &binfPicPulsar, DIB_RGB_COLORS); 
            m_PicPulse2.SetBitmap(hBmpPicPulsar2); m_PicPulse2.GetWindowRect(&myRect); m_PicPulse2.ValidateRect(&myRect);
            m_PicPulse2.UpdateWindow();
            m_Period2.SetWindowTextA(szText);
            break;
        case 2: 
            hBmpPicPulsar3 = CreateDIBitmap(hDC, &(binfPicPulsar.bmiHeader), CBM_INIT, bRGBImage_S3, &binfPicPulsar, DIB_RGB_COLORS); 
            m_PicPulse3.SetBitmap(hBmpPicPulsar3); m_PicPulse3.GetWindowRect(&myRect); m_PicPulse3.ValidateRect(&myRect);
            m_PicPulse3.UpdateWindow();
            m_Period3.SetWindowTextA(szText);
            break;
        case 3: 
            hBmpPicPulsar4 = CreateDIBitmap(hDC, &(binfPicPulsar.bmiHeader), CBM_INIT, bRGBImage_S4, &binfPicPulsar, DIB_RGB_COLORS); 
            m_PicPulse4.SetBitmap(hBmpPicPulsar4); m_PicPulse4.GetWindowRect(&myRect); m_PicPulse4.ValidateRect(&myRect);
            m_PicPulse4.UpdateWindow();
            m_Period4.SetWindowTextA(szText);
            break;
        case 4: 
            hBmpPicPulsar5 = CreateDIBitmap(hDC, &(binfPicPulsar.bmiHeader), CBM_INIT, bRGBImage_S5, &binfPicPulsar, DIB_RGB_COLORS); 
            m_PicPulse5.SetBitmap(hBmpPicPulsar5); m_PicPulse5.GetWindowRect(&myRect); m_PicPulse5.ValidateRect(&myRect);
            m_PicPulse5.UpdateWindow();
            m_Period5.SetWindowTextA(szText);
            break;
        case 5: 
            hBmpPicPulsar6 = CreateDIBitmap(hDC, &(binfPicPulsar.bmiHeader), CBM_INIT, bRGBImage_S6, &binfPicPulsar, DIB_RGB_COLORS); 
            m_PicPulse6.SetBitmap(hBmpPicPulsar6); m_PicPulse6.GetWindowRect(&myRect); m_PicPulse6.ValidateRect(&myRect);
            m_PicPulse6.UpdateWindow();
            m_Period6.SetWindowTextA(szText);
            break;
        }
		::ReleaseDC(NULL, hDC); 
    }
}

void CpulseMonitorDlg::OnBnClickedButtonAnalizePulsarsOnly()
{
    // TODO: Add your control notification handler code here
    if (DoAnalize)
    {
        DoAnalize = FALSE;
        m_Analize.SetWindowTextA("Analize");
        KillTimer(901);
        SetTimer(901, 1000,NULL);
    }
    else
    {
        KillTimer(901);
        DoAnalize = TRUE;
        DoFirstdb = TRUE;
        CleanAllPictures();
        CString MyPos64;
        m_OffsetPosition.GetWindowTextA(MyPos64);
        char szText[64];
        strcpy(szText, MyPos64.GetString());
        __int64  recordCurPos =0;
        sscanf(szText, "%I64d",&recordCurPos);

        _fseeki64(MyOutPutFIle, recordCurPos, SEEK_SET);
        m_TimeDelta.GetWindowTextA(MyPos64);
        strcpy(szText, MyPos64.GetString());
        //g_iTimeDelta = atof(szText);

        m_CountDb.GetWindowTextA(MyPos64);
        strcpy(szText, MyPos64.GetString());
        g_iCountDB = atoi(szText);
        g_iCountDB_old = g_iCountDB;

        m_From_P.GetWindowTextA(MyPos64);
        strcpy(szText, MyPos64.GetString());
        g_Analize_From = atol(szText);
        g_iTimeDelta = g_Analize_From;
        m_TimeDelta.SetWindowTextA(szText);

        m_To_P.GetWindowTextA(MyPos64);
        strcpy(szText, MyPos64.GetString());
        g_Analize_To = atol(szText);

        GetAllPulsarsData();
        m_Analize.SetWindowTextA("Analizing");
        g_j = 0;
        if (flRunningRecording == FALSE)
        {
            flRunningRecording = TRUE;
        }
        SetTimer(901, 100,NULL);
    }
}
