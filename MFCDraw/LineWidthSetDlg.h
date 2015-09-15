#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CLineWidthSetDlg 对话框

class CLineWidthSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLineWidthSetDlg)

public:
	CLineWidthSetDlg(int = 5,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLineWidthSetDlg();
	BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_LW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl id_slider;
	afx_msg void OnNMCustomdrawSlider(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic id_static;
	void setLineWidth(int);
	int getLineWidth();
	int lineWidth;
};
