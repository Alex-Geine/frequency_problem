
// frequency_problemDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "frequency_problem.h"
#include "frequency_problemDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CfrequencyproblemDlg



CfrequencyproblemDlg::CfrequencyproblemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FREQUENCY_PROBLEM_DIALOG, pParent)
	, A1(4)
	, A2(2)
	, A3(3.5)
	, A4(2.5)
	, A5(3.5)
	, t1(150)
	, t2(380)
	, t3(600)
	, t4(800)
	, t5(920)
	, D1(4)
	, D2(2)
	, D3(3)
	, D4(2)
	, D5(3)
	, de(1.0E-6)
	, N(1024)
	, fd(1)
	, e(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfrequencyproblemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, A1);
	DDX_Text(pDX, IDC_EDIT6, A2);
	DDX_Text(pDX, IDC_EDIT11, A3);
	DDX_Text(pDX, IDC_EDIT14, A4);
	DDX_Text(pDX, IDC_EDIT15, A5);
	DDX_Text(pDX, IDC_EDIT2, t1);
	DDX_Text(pDX, IDC_EDIT5, t2);
	DDX_Text(pDX, IDC_EDIT7, t3);
	DDX_Text(pDX, IDC_EDIT8, t4);
	DDX_Text(pDX, IDC_EDIT9, t5);
	DDX_Text(pDX, IDC_EDIT3, D1);
	DDX_Text(pDX, IDC_EDIT4, D2);
	DDX_Text(pDX, IDC_EDIT10, D3);
	DDX_Text(pDX, IDC_EDIT12, D4);
	DDX_Text(pDX, IDC_EDIT13, D5);
	DDX_Text(pDX, IDC_EDIT17, de);
	DDX_Text(pDX, IDC_EDIT18, N);
	DDX_Text(pDX, IDC_EDIT16, fd);
	DDX_Text(pDX, IDC_EDIT19, e);
}

BEGIN_MESSAGE_MAP(CfrequencyproblemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()	
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_MOUSEMOVE()
	ON_WM_MBUTTONDOWN()
	ON_EN_CHANGE(IDC_EDIT7, &CfrequencyproblemDlg::OnEnChangeEdit7)
	ON_BN_CLICKED(IDOK2, &CfrequencyproblemDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDCANCEL, &CfrequencyproblemDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK4, &CfrequencyproblemDlg::OnBnClickedOk4)
	ON_BN_CLICKED(IDOK5, &CfrequencyproblemDlg::OnBnClickedOk5)
	ON_BN_CLICKED(IDOK3, &CfrequencyproblemDlg::OnBnClickedOk3)
	ON_BN_CLICKED(IDOK, &CfrequencyproblemDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CfrequencyproblemDlg

BOOL CfrequencyproblemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GR1.Create(GetDlgItem(ID_GRAPH1)->GetSafeHwnd());
	GR2.Create(GetDlgItem(ID_GRAPH2)->GetSafeHwnd());
	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CfrequencyproblemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CfrequencyproblemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		if (!curSignal.X.empty()) {
			GR1.ReDraw();
			GR2.ReDraw();
		}
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CfrequencyproblemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CfrequencyproblemDlg::OnEnChangeEdit7()
{

}

//отрисовать
void CfrequencyproblemDlg::OnBnClickedOk2()
{
	UpdateData(TRUE);

	e = 0.;

	curSignal.ClearSignal();
	curSignal.FillSignal(N, fd, A1, A2, A3, A4, A5, D1, D2, D3, D4, D5, t1, t2, t3, t4, t5, &GR1);

	GR1.DrawW();
	GR2.DrawW();

	//исходный сигнал
	GR1.DrawOne(curSignal.X, *min_element(curSignal.keys.begin(), curSignal.keys.end()), *max_element(curSignal.keys.begin(), curSignal.keys.end()),
		*min_element(curSignal.X.begin(), curSignal.X.end()), *max_element(curSignal.X.begin(), curSignal.X.end()), 't', 'A', curSignal.keys);
	//спектр
	GR2.DrawOne(curSignal.H, *min_element(curSignal.keysH.begin(), curSignal.keysH.end()), *max_element(curSignal.keysH.begin(), curSignal.keysH.end()),
		*min_element(curSignal.H.begin(), curSignal.H.end()), *max_element(curSignal.H.begin(), curSignal.H.end()), 't', 'A', curSignal.keysH);

	curSignal.Solve(msg, de, e);

	UpdateData(FALSE);
}

//Отмена
void CfrequencyproblemDlg::OnBnClickedCancel()
{	
	CDialogEx::OnCancel();
}

//посчитать
void CfrequencyproblemDlg::OnBnClickedOk4()
{
	// TODO: добавьте свой код обработчика уведомлений
	
}

//пауза
void CfrequencyproblemDlg::OnBnClickedOk5()
{
	// TODO: добавьте свой код обработчика уведомлений
}

//продолжить
void CfrequencyproblemDlg::OnBnClickedOk3()
{
	// TODO: добавьте свой код обработчика уведомлений
}

//коррекция
void CfrequencyproblemDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}
