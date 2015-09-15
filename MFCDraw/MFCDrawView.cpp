
// MFCDrawView.cpp : implementation of the CMFCDrawView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCDraw.h"
#endif

#include "MFCDrawDoc.h"
#include "MFCDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "LineWidthSetDlg.h"


// CMFCDrawView

IMPLEMENT_DYNCREATE(CMFCDrawView, CView)

BEGIN_MESSAGE_MAP(CMFCDrawView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_FREEDRAW, &CMFCDrawView::OnFreedraw)
	ON_COMMAND(ID_LINE, &CMFCDrawView::OnLine)
	ON_COMMAND(ID_LINEWIDTH, &CMFCDrawView::OnLinewidth)
	//ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER, &CMFCDrawView::OnNMCustomdrawSlider)
	//ON_COMMAND(ID_ANTIA, &CMFCDrawView::OnAntia)
	ON_UPDATE_COMMAND_UI(32779, &CMFCDrawView::OnUpdate32779)
	ON_COMMAND(32779, &CMFCDrawView::On32779)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CMFCDrawView::OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_FREEDRAW, &CMFCDrawView::OnUpdateFreedraw)
	ON_UPDATE_COMMAND_UI(ID_LINEWIDTH, &CMFCDrawView::OnUpdateLinewidth)
END_MESSAGE_MAP()

// CMFCDrawView construction/destruction

CMFCDrawView::CMFCDrawView()
{
	// TODO: add construction code here
	m_ptOrigin = CPoint(0, 0);
	m_ptlast = m_ptOrigin;
	m_nDrawType = 0;
	m_bfree = 0;
	m_LineWidth = 5;
	antialiased = 0;
	lastspeed = -1;
}

CMFCDrawView::~CMFCDrawView()
{
}

BOOL CMFCDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCDrawView drawing

void CMFCDrawView::OnDraw(CDC* /*pDC*/)
{
	CMFCDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	//Invalidate();
}

void CMFCDrawView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CMFCDrawView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCDrawView diagnostics

#ifdef _DEBUG
void CMFCDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDrawDoc* CMFCDrawView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDrawDoc)));
	return (CMFCDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCDrawView message handlers


void CMFCDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	//创建一个画笔
	CPen pen(PS_SOLID, m_LineWidth, RGB(0, 0, 0));
	//将创建的画笔选入设备描述表
	CPen *pOldPen = dc.SelectObject(&pen);
	if (m_bfree)
	{
		switch (m_nDrawType)
		{
		case 0:
			if (antialiased)
			{
				//double speed = sqrt((double(m_ptOrigin.x) - double(point.x))
				//	* (double(m_ptOrigin.x) - double(point.x))
				//	+ (double(m_ptOrigin.y) - double(point.y))
				//	* (double(m_ptOrigin.y) - double(point.y)));
				double speed = abs(m_ptOrigin.x - point.x) + abs(m_ptOrigin.y - point.y);
				speed = 10 - speed / 5;
				if (speed > 10)speed = 10;
				else if (speed < 1)speed = 1;
				if (lastspeed == -1) lastspeed = speed;
				else if (lastspeed - speed > 1) speed = lastspeed - 1;
				else if (speed - lastspeed > 1) speed = lastspeed + 1;
				lastspeed = speed;
				WuLine(m_ptOrigin.x, m_ptOrigin.y, point.x, point.y, speed);
				m_ptOrigin = point;
			}
			else
			{
				dc.MoveTo(m_ptOrigin);
				dc.LineTo(point);
				m_ptOrigin = point;
			}
			break;
		case 1:
			dc.SetROP2(R2_NOT);
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(m_ptlast);
			
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(point);
			m_ptlast = point;
			//dc.SetROP2(R2_COPYPEN );
			break;
		}
	}

	CView::OnMouseMove(nFlags, point);
}


void CMFCDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (m_nDrawType)
	{
	case 0:
		m_ptOrigin = point;
		m_bfree = 1;
		break;
	case 1:
		m_ptOrigin = point;
		m_ptlast = point;
		m_bfree = 1;
		break;
	}

	CView::OnLButtonDown(nFlags, point);
}


void CMFCDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	//创建一个画笔
	CPen pen(PS_SOLID, m_LineWidth, RGB(0, 0, 0));
	//将创建的画笔选入设备描述表
	CPen *pOldPen = dc.SelectObject(&pen);
	switch (m_nDrawType)
	{
	case 0:
		if (antialiased)
		{
			//double speed = sqrt((double(m_ptOrigin.x) - double(point.x))
			//	* (double(m_ptOrigin.x) - double(point.x))
			//	+ (double(m_ptOrigin.y) - double(point.y))
			//	* (double(m_ptOrigin.y) - double(point.y)));
			int speed = abs(m_ptOrigin.x - point.x) + abs(m_ptOrigin.y - point.y);
			speed = 10 - speed / 5;
			if (speed > 10)speed = 10;
			else if(speed < 1)speed = 1;
			if (lastspeed == -1) lastspeed = speed;
			else if (lastspeed - speed > 1) speed = lastspeed - 1;
			else if (speed - lastspeed > 1) speed = lastspeed + 1;
			lastspeed = speed;
			WuLine(m_ptOrigin.x, m_ptOrigin.y, point.x, point.y, 1);//warning!
			m_bfree = 0;
		}
		else
		{
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(point);

			m_bfree = 0;
		}
		break;
	case 1:
		if (antialiased)
		{
			dc.SetROP2(R2_NOT);
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(m_ptlast);
			dc.SetROP2(R2_COPYPEN);
			WuLine(m_ptOrigin.x, m_ptOrigin.y, point.x, point.y, m_LineWidth);
			m_bfree = 0;
		}
		else
		{
			dc.SetROP2(R2_NOT);
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(m_ptlast);

			dc.SetROP2(R2_COPYPEN);
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(point);
			m_bfree = 0;
		}
		break;
	}

	CView::OnLButtonUp(nFlags, point);
}


void CMFCDrawView::OnFreedraw()
{
	// TODO:  在此添加命令处理程序代码
	m_nDrawType = 0;
}


void CMFCDrawView::OnLine()
{
	// TODO:  在此添加命令处理程序代码
	m_nDrawType = 1;
}


void CMFCDrawView::OnLinewidth()
{
	// TODO:  在此添加命令处理程序代码
	CLineWidthSetDlg dlg(m_LineWidth,this);
	//dlg.setLineWidth(m_LineWidth);
	if (dlg.DoModal() == IDOK)
		m_LineWidth = dlg.getLineWidth();
}

void CMFCDrawView::OnUpdateLinewidth(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
}

//http://bbs.csdn.net/topics/390171688#quote
//#3
void CMFCDrawView::OnUpdate32779(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(antialiased);
}


void CMFCDrawView::On32779()
{
	// TODO:  在此添加命令处理程序代码
	antialiased = !antialiased;
}

//http://dev.gameres.com/Program/Visual/Effects/WuLine.htm
void CMFCDrawView::WuLine(int x1, int y1, int x2, int y2, double w)
{
	CClientDC dc(this);
	CPen pen(PS_SOLID, m_LineWidth, RGB(0, 0, 0));
	CPen *pOldPen = dc.SelectObject(&pen);

	int dx = x1 - x2;
	int dy = y1 - y2;
	//if (w > dx && dx == dy && dx == 1) w = 1;
	double k = 0;
	if (dx == 0)
		k = DBL_MAX;
	else
		k = double(dy) / double(dx);

	if (abs(dy) < abs(dx))
	{
		double wh = (w - 1) / 2;/*(w - 1) / 2 * sqrt(k * k + 1)*/;
		if (x1 > x2)//ensure that x1 < x2
		{
			int tem = x1;
			x1 = x2;
			x2 = tem;
			tem = y1;
			y1 = y2;
			y2 = tem;
			dx = -dx;
			dy = -dy;
		}
		for (int x = x1 - 1; x < x2 + 2; x++)
		{
			double y = k * (x - x1) + y1;
			int y0 = y;
			dc.SetPixel(x, y0, RGB(0, 0, 0));
			while (1)
			{
				y0++;
				if (y0 - y < wh)
				{
					dc.SetPixel(x, y0, RGB(0, 0, 0));
					continue;
				}
				else if (y0 - y < wh + 1)
				{
					double delta = y0 - y - wh;
					int lightness = 255 * delta;
					COLORREF color_o = GetPixel(dc, x, y0);
					COLORREF color_n = color_o & RGB(lightness, lightness, lightness);
					dc.SetPixel(x, y0, color_n);
					continue;
				}
				else
					break;
			}
			y0 = y;
			while (1)
			{
				y0--;
				if (y - y0 < wh)
				{
					dc.SetPixel(x, y0, RGB(0, 0, 0));
					continue;
				}
				else if (y - y0 < wh + 1)
				{
					double delta = y - y0 - wh;
					int lightness = 255 * delta;
					COLORREF color_o = GetPixel(dc, x, y0);
					COLORREF color_n = color_o & RGB(lightness, lightness, lightness);
					dc.SetPixel(x, y0, color_n);
					continue;
				}
				else
					break;
			}
		}
		//
		/*int x = x1 - 2;
		double y = k * (x - x1) + y1;
		int y0 = y;
		dc.SetPixel(x, y0, RGB(128, 128, 128));
		for (y0 = y; y0 - y < wh; y0++)
		{
			COLORREF color_o = GetPixel(dc, x, y0);
			COLORREF color_n = color_o & RGB(128, 128, 128);
			dc.SetPixel(x, y0, color_n);
		}
		for (y0 = y; y - y0 < wh; y0--)
		{
			COLORREF color_o = GetPixel(dc, x, y0);
			COLORREF color_n = color_o & RGB(128, 128, 128);
			dc.SetPixel(x, y0, color_n);
		}
		x = x2 + 2;
		y = k * (x - x1) + y1;
		dc.SetPixel(x, y0, RGB(128, 128, 128));
		for (y0 = y; y0 - y < wh;y0++)
		{
			COLORREF color_o = GetPixel(dc, x, y0);
			COLORREF color_n = color_o & RGB(128, 128, 128);
			dc.SetPixel(x, y0, color_n);
		}
		for (y0 = y; y - y0 < wh;y0--)
		{
			COLORREF color_o = GetPixel(dc, x, y0);
			COLORREF color_n = color_o & RGB(128, 128, 128);
			dc.SetPixel(x, y0, color_n);
		}*/

		/*
		for (int x = x1; x > x1 - w; x--)
		{
			double y = k * (x - x1) + y1;
			int y0 = y;
			dc.SetPixel(x, y0, RGB(0, 0, 0));
			while (1)
			{
				y0++;
				if ((x - x1)*(x - x1) + (y0 - y1) * (y0 - y1) < w * w / 4)
				{
					dc.SetPixel(x, y0, RGB(0, 0, 0));
					continue;
				}
				else if (sqrt(double((x - x1)*(x - x1) + (y0 - y1) * (y0 - y1))) < w / 2 + 1)
				{
					double delta = sqrt(double((x - x1)*(x - x1) + (y0 - y1) * (y0 - y1))) - w / 2;
					int lightness = 255 * delta;
					dc.SetPixel(x, y0, RGB(lightness, lightness, lightness));
					continue;
				}
				else
					break;
			}
			y0 = y;
			while (1)
			{
				y0--;
				if ((x - x1)*(x - x1) + (y0 - y1) * (y0 - y1) < w * w / 4)
				{
					dc.SetPixel(x, y0, RGB(0, 0, 0));
					continue;
				}
				else if (sqrt(double((x - x1)*(x - x1) + (y0 - y1) * (y0 - y1))) < w / 2 + 1)
				{
					double delta = sqrt(double((x - x1)*(x - x1) + (y0 - y1) * (y0 - y1))) - w / 2;
					int lightness = 255 * delta;
					dc.SetPixel(x, y0, RGB(lightness, lightness, lightness));
					continue;
				}
				else
					break;
			}
		}
		for (int x = x2; x < x2 + w; x++)
		{
			double y = k * (x - x1) + y1;
			int y0 = y;
			dc.SetPixel(x, y0, RGB(0, 0, 0));
			while (1)
			{
				y0++;
				if ((x - x2)*(x - x2) + (y0 - y2) * (y0 - y2) < w * w / 4)
				{
					dc.SetPixel(x, y0, RGB(0, 0, 0));
					continue;
				}
				else if (sqrt(double((x - x2)*(x - x2) + (y0 - y2) * (y0 - y2))) < w / 2 + 1)
				{
					double delta = sqrt(double((x - x2)*(x - x2) + (y0 - y2) * (y0 - y2))) - w / 2;
					int lightness = 255 * delta;
					dc.SetPixel(x, y0, RGB(lightness, lightness, lightness));
					continue;
				}
				else
					break;
			}
			y0 = y;
			while (1)
			{
				y0--;
				if ((x - x2)*(x - x2) + (y0 - y2) * (y0 - y2) < w * w / 4)
				{
					dc.SetPixel(x, y0, RGB(0, 0, 0));
					continue;
				}
				else if (sqrt(double((x - x2)*(x - x2) + (y0 - y2) * (y0 - y2))) < w / 2 + 1)
				{
					double delta = sqrt(double((x - x2)*(x - x2) + (y0 - y2) * (y0 - y2))) - w / 2;
					int lightness = 255 * delta;
					dc.SetPixel(x, y0, RGB(lightness, lightness, lightness));
					continue;
				}
				else
					break;
			}
		}
	*/
	}
	else
	{
		double wh = (w - 1) / 2; /*(w - 1) / 2 * sqrt(k * k + 1) / abs(k);*/
		if (k == DBL_MAX) wh = w / 2;
		if (y1 > y2)//ensure that y1 < y2
		{
			int tem = y1;
			y1 = y2;
			y2 = tem;
			tem = x1;
			x1 = x2;
			x2 = tem;
			dy = -dy;
			dx = -dx;
		}
		for (int y = y1 - 1; y < y2 + 2; y++)
		{
			double x = x1;
			if (k != DBL_MAX)
				x = (y - y1) / k + x1;
			int x0 = x;
			dc.SetPixel(x0, y, RGB(0, 0, 0));
			while (1)
			{
				x0++;
				if (x0 - x < wh)
				{
					dc.SetPixel(x0, y, RGB(0, 0, 0));
					continue;
				}
				else if (x0 - x < wh + 1)
				{
					double delta = x0 - x - wh;
					int lightness = 255 * delta;
					COLORREF color_o = GetPixel(dc, x0, y);
					COLORREF color_n = color_o & RGB(lightness, lightness, lightness);
					dc.SetPixel(x0, y, color_n);
					continue;
				}
				else
					break;
			}
			x0 = x;
			while (1)
			{
				x0--;
				if (x - x0 < wh)
				{
					dc.SetPixel(x0, y, RGB(0, 0, 0));
					continue;
				}
				else if (x - x0 < wh + 1)
				{
					double delta = x - x0 - wh;
					int lightness = 255 * delta;
					COLORREF color_o = GetPixel(dc, x0, y);
					COLORREF color_n = color_o & RGB(lightness, lightness, lightness);
					dc.SetPixel(x0, y, color_n);
					continue;
				}
				else
					break;
			}
		}
		/*
		for (int y = y1; y > y1 - w; y--)
		{
			double x = (y - y1) / k + x1;
			int x0 = x;
			dc.SetPixel(x0, y, RGB(0, 0, 0));
			while (1)
			{
				x0++;
				if ((x0 - x1)*(x0 - x1) + (y - y1) * (y - y1) < w * w / 4)
				{
					dc.SetPixel(x0, y, RGB(0, 0, 0));
					continue;
				}
				else if (sqrt(double((x0 - x1)*(x0 - x1) + (y - y1) * (y - y1))) < w / 2 + 1)
				{
					double delta = sqrt(double((x0 - x1)*(x0 - x1) + (y - y1) * (y - y1))) - w / 2;
					int lightness = 255 * delta;
					dc.SetPixel(x0, y, RGB(lightness, lightness, lightness));
					continue;
				}
				else
					break;
			}
			x0 = x;
			while (1)
			{
				x0--;
				if ((x0 - x1)*(x0 - x1) + (y - y1) * (y - y1) < w * w / 4)
				{
					dc.SetPixel(x0, y, RGB(0, 0, 0));
					continue;
				}
				else if (sqrt(double((x0 - x1)*(x0 - x1) + (y - y1) * (y - y1))) < w / 2 + 1)
				{
					double delta = sqrt(double((x0 - x1)*(x0 - x1) + (y - y1) * (y - y1))) - w / 2;
					int lightness = 255 * delta;
					dc.SetPixel(x0, y, RGB(lightness, lightness, lightness));
					continue;
				}
				else
					break;
			}
		}
		for (int y = y2; y < y2 + w; y++)
		{
			double x = (y - y1) / k + x1;
			int x0 = x;
			dc.SetPixel(x0, y, RGB(0, 0, 0));
			while (1)
			{
				x0++;
				if ((x0 - x2)*(x0 - x2) + (y - y2) * (y - y2) < w * w / 4)
				{
					dc.SetPixel(x0, y, RGB(0, 0, 0));
					continue;
				}
				else if (sqrt(double((x0 - x2)*(x0 - x2) + (y - y2) * (y - y2))) < w / 2 + 1)
				{
					double delta = sqrt(double((x0 - x2) * (x0 - x2) + (y - y2) * (y - y2))) - w / 2;
					int lightness = 255 * delta;
					dc.SetPixel(x0, y, RGB(lightness, lightness, lightness));
					continue;
				}
				else
					break;
			}
			x0 = x;
			while (1)
			{
				x0--;
				if ((x0 - x2)*(x0 - x2) + (y - y2) * (y - y2) < w * w / 4)
				{
					dc.SetPixel(x0, y, RGB(0, 0, 0));
					continue;
				}
				else if (sqrt(double((x0 - x2) * (x0 - x2) + (y - y2) * (y - y2))) < w / 2 + 1)
				{
					double delta = sqrt(double((x0 - x2) * (x0 - x2) + (y - y2) * (y - y2))) - w / 2;
					int lightness = 255 * delta;
					dc.SetPixel(x0, y, RGB(lightness, lightness, lightness));
					continue;
				}
				else
					break;
			}
		}*/
	}
}


void CMFCDrawView::OnUpdateLine(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (m_nDrawType == 0)
		pCmdUI->SetCheck(0);
	else
		pCmdUI->SetCheck(1);
}


void CMFCDrawView::OnUpdateFreedraw(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (m_nDrawType == 0)
		pCmdUI->SetCheck(1);
	else
		pCmdUI->SetCheck(0);
}


