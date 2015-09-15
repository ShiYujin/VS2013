
// MFCDrawView.h : interface of the CMFCDrawView class
//

#pragma once
#include <vector>


class CMFCDrawView : public CView
{
protected: // create from serialization only
	CMFCDrawView();
	DECLARE_DYNCREATE(CMFCDrawView)

// Attributes
public:
	CMFCDrawDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMFCDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

private:
	void WuLine(int x1, int y1, int x2, int y2, double w);
	CPoint m_ptOrigin;
	CPoint m_ptlast;
	UINT m_nDrawType;
	bool m_bfree;
	int m_LineWidth;
	bool antialiased;
	int lastspeed;
public:
	afx_msg void OnFreedraw();
	afx_msg void OnLine();
	afx_msg void OnLinewidth();
	//afx_msg void OnAntia();
	afx_msg void OnUpdate32779(CCmdUI *pCmdUI);
	afx_msg void On32779();
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFreedraw(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLinewidth(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in MFCDrawView.cpp
inline CMFCDrawDoc* CMFCDrawView::GetDocument() const
   { return reinterpret_cast<CMFCDrawDoc*>(m_pDocument); }
#endif

