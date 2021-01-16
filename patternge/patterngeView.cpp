// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// patterngeView.cpp : implementation of the CpatterngeView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "patternge.h"
#endif

#include "patterngeDoc.h"
#include "patterngeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CpatterngeView

IMPLEMENT_DYNCREATE(CpatterngeView, CView)

BEGIN_MESSAGE_MAP(CpatterngeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CpatterngeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON2_start, &CpatterngeView::OnButton2start)
	ON_COMMAND(ID_BUTTON3_stop, &CpatterngeView::OnButton3stop)
	ON_COMMAND(ID_BUTTON_resume, &CpatterngeView::OnButtonresume)
END_MESSAGE_MAP()

// CpatterngeView construction/destruction

CpatterngeView::CpatterngeView() noexcept
{
	// TODO: add construction code here
	currentthread = NULL;
	m_counter = 0;

		
}

CpatterngeView::~CpatterngeView()
{
}

BOOL CpatterngeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CpatterngeView drawing

void CpatterngeView::OnDraw(CDC* pDC)
{
	CpatterngeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CString strcounter;
	pDC->TextOut(100, 100, strcounter);
	pDC->MoveTo(100, 50);
	pDC->LineTo(100, 200);
	pDC->MoveTo(100, 200);
	pDC->LineTo(1000, 200);
	if (m_counter < 900)
	{
		for (int i = 0; i < m_array.GetSize() - 2; i++)
		{
			pDC->MoveTo(m_array[i].x, m_array[i].y);
			pDC->LineTo(m_array[i + 1].x, m_array[i + 1].y);
		}


	}
	
	// TODO: add draw code for native data here
}


// CpatterngeView printing


void CpatterngeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CpatterngeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CpatterngeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CpatterngeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CpatterngeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CpatterngeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CpatterngeView diagnostics

#ifdef _DEBUG
void CpatterngeView::AssertValid() const
{
	CView::AssertValid();
}

void CpatterngeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CpatterngeDoc* CpatterngeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CpatterngeDoc)));
	return (CpatterngeDoc*)m_pDocument;
}
#endif //_DEBUG


// CpatterngeView message handlers


void CpatterngeView::OnButton2start()
{
	// TODO: Add your command handler code here
	currentthread = AfxBeginThread(CpatterngeView::StartThread, this);
}


void CpatterngeView::OnButton3stop()
{
	// TODO: Add your command handler code here
	currentthread->SuspendThread();

}


void CpatterngeView::OnButtonresume()
{
	// TODO: Add your command handler code here
	currentthread->ResumeThread();
}


UINT CpatterngeView::StartThread(LPVOID Para)
{
	// TODO: Add your implementation code here.
	CpatterngeView* pviwe = (CpatterngeView*)Para;
	CPoint mypoint(0, 0);
	int v = 10;

	while (1)
	{
		mypoint.y = 200+50*sin(pviwe->m_counter);
		mypoint.x =100+pviwe->m_counter;
		pviwe->m_array.Add(mypoint);
		pviwe->m_counter = pviwe->m_counter + 100;
		pviwe->Invalidate();
		Sleep(500);
	}
	return 0;
}
