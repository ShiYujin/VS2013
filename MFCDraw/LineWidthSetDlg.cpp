// LineWidthSetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCDraw.h"
#include "LineWidthSetDlg.h"
#include "afxdialogex.h"


// CLineWidthSetDlg 对话框

IMPLEMENT_DYNAMIC(CLineWidthSetDlg, CDialogEx)

CLineWidthSetDlg::CLineWidthSetDlg(int i, CWnd* pParent /*=NULL*/)
	: CDialogEx(CLineWidthSetDlg::IDD, pParent)
{
	lineWidth = i;
}

CLineWidthSetDlg::~CLineWidthSetDlg()
{
}

void CLineWidthSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER, id_slider);
	DDX_Control(pDX, IDC_STATIC2, id_static);
}

BOOL CLineWidthSetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

	id_slider.SetRange(1, 10);
	id_slider.SetPos(lineWidth);
	//lineWidth = 5;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CLineWidthSetDlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER, &CLineWidthSetDlg::OnNMCustomdrawSlider)
END_MESSAGE_MAP()


// CLineWidthSetDlg 消息处理程序


void CLineWidthSetDlg::OnNMCustomdrawSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	lineWidth = id_slider.GetPos();
	char string[3];
	_itoa_s(lineWidth, string, 10);
	size_t converted = 0;
	wchar_t *WStr;
	WStr = (wchar_t*)malloc(3 * sizeof(wchar_t));
	mbstowcs_s(&converted, WStr, 3, string, _TRUNCATE);

	GetDlgItem(IDC_STATIC2)->SetWindowText(WStr);
	*pResult = 0;
}

void CLineWidthSetDlg::setLineWidth(int i)
{
	//id_slider.SetPos(i);
}

int CLineWidthSetDlg::getLineWidth()
{
	return lineWidth;
}
