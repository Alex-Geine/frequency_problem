
// frequency_problemDlg.h: файл заголовка
//

#pragma once
#include <iostream>
#include "Drawer1.h"
#include "SignalFr.h"
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
// Диалоговое окно CfrequencyproblemDlg
class CfrequencyproblemDlg : public CDialogEx
{
// Создание
public:
	CfrequencyproblemDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FREQUENCY_PROBLEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit7();
	double A1;
	double A2;
	double A3;
	double A4;
	double A5;
	double t1;
	double t2;
	double t3;
	double t4;
	double t5;
	double D1;
	double D2;
	double D3;
	double D4;
	double D5;
	double de;
	double N;
	double fd;
	double e;
	afx_msg void OnBnClickedOk2();

	Drawer GR1, GR2;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk4();
	afx_msg void OnBnClickedOk5();
	afx_msg void OnBnClickedOk3();
	afx_msg void OnBnClickedOk();
	MSG msg;
	Signal curSignal;
};
