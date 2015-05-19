
// pulseMonitorDlg.h : header file
/*****************************************************************************
    2013 (C) Alex Dobrianski pulsar pattern recognition software
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

#pragma once


// CpulseMonitorDlg dialog
class CpulseMonitorDlg : public CDialogEx
{
// Construction
public:
	CpulseMonitorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PULSEMONITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

    int m_SecondsPerScreen;
    int m_FractionsPerScreen;
    SYSTEMTIME myShowSysTime;
    HBITMAP hBmpMainSignal ;
    BOOL flRunningRecording;

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
    afx_msg void OnEnChangeEdit1();
    virtual BOOL DestroyWindow();
    CListBox m_SecPerScreen;
    afx_msg void OnLbnSelchangeListSecPerScreen();
    afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    CDateTimeCtrl m_Time;
    CDateTimeCtrl m_Date;
    CButton m_LastTime;
    afx_msg void OnBnClickedCheckLast();
//    CStatic m_Signal;
//    CStatic m_Signal;
    CStatic m_SIgnal;
    CSliderCtrl m_SLider;
    CButton m_ShowLines;
    afx_msg void OnBnClickedCheckDotsLines();
    CStatic m_Period1;
    CStatic m_Period2;
    CStatic m_Period3;
    CStatic m_Period4;
    CStatic m_Period5;
    CStatic m_Period6;
    afx_msg void OnStnClickedStatic1Max();
    CStatic m_1_max;
    CStatic m_1_mid;
    CStatic m_1_min;
    CStatic m_2_max;
    CStatic m_2_mid;
    CStatic m_2_min;
    CButton m_Next;
    afx_msg void OnBnClickedNext();
    CButton m_Run;
    afx_msg void OnBnClickedButtonrun();
    CListBox m_YScale;
    afx_msg void OnLbnSelchangeListScale();
};
