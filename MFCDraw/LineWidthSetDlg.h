#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CLineWidthSetDlg �Ի���

class CLineWidthSetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLineWidthSetDlg)

public:
	CLineWidthSetDlg(int = 5,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLineWidthSetDlg();
	BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_LW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl id_slider;
	afx_msg void OnNMCustomdrawSlider(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic id_static;
	void setLineWidth(int);
	int getLineWidth();
	int lineWidth;
};
