
// 3장 연습문제View.cpp: CMy3장연습문제View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "3장 연습문제.h"
#endif

#include "3장 연습문제Doc.h"
#include "3장 연습문제View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3장연습문제View

IMPLEMENT_DYNCREATE(CMy3장연습문제View, CView)

BEGIN_MESSAGE_MAP(CMy3장연습문제View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMy3장연습문제View 생성/소멸

CMy3장연습문제View::CMy3장연습문제View() noexcept
{
	m_strStopWatch = _T("00:00.00");
	m_nCount = 0;
	m_nMinute = 0;
	m_nSecond = 0;
	m_nMsec = 0;
	m_bStopWatchRun = false;
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMy3장연습문제View::~CMy3장연습문제View()
{
}

BOOL CMy3장연습문제View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy3장연습문제View 그리기

void CMy3장연습문제View::OnDraw(CDC* pDC)
{
	CMy3장연습문제Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);

	pDC->DrawText(m_strStopWatch, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	CRect recordRect = rect;
	recordRect.top = 0; // 첫 번째 기록 출력 위치 조정

	for (int i = 0; i < m_nCount-1; i++)
	{
		recordRect.top += 20; // 각 기록마다 세로로 20px 간격을 줌
		pDC->DrawText(m_strRecord[i], recordRect, DT_SINGLELINE | DT_LEFT);
	}	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CMy3장연습문제View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy3장연습문제View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy3장연습문제View 진단

#ifdef _DEBUG
void CMy3장연습문제View::AssertValid() const
{
	CView::AssertValid();
}

void CMy3장연습문제View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3장연습문제Doc* CMy3장연습문제View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3장연습문제Doc)));
	return (CMy3장연습문제Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy3장연습문제View 메시지 처리기


void CMy3장연습문제View::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bStopWatchRun == false)
	{
		SetTimer(0, 10, NULL);
		m_bStopWatchRun = true;
	}
	else
	{
		KillTimer(0);
		m_bStopWatchRun = false;
	}
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	

	CView::OnLButtonDown(nFlags, point);
}


void CMy3장연습문제View::OnTimer(UINT_PTR nIDEvent)
{
	m_nMsec++;
	if (m_nMsec >=100)
	{
		m_nSecond++;
		m_nMsec = 0;
	}

	if (m_nSecond == 60)
	{
		m_nMinute++;
		m_nSecond = 0;
	}
	
	m_strStopWatch.Format(_T("%02d: %02d, %02d"), m_nMinute, m_nSecond, m_nMsec);
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Invalidate();

	CView::OnTimer(nIDEvent);
}


void CMy3장연습문제View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bStopWatchRun == TRUE)
	{
		if (AfxMessageBox(_T("초기화 하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			m_nMinute = 0;
			m_nMsec = 0;
			m_nSecond = 0;
			m_strStopWatch.Format(_T("%02d: %02d, %02d"), m_nMinute, m_nSecond, m_nMsec);
			KillTimer(0);
			m_bStopWatchRun = false;
		}
	}
	else {
	
	
		AfxMessageBox(_T("작동 중에는 스톱워치를 초기화시킬수 없습니다."), MB_OK | MB_ICONWARNING);
		}
	
	Invalidate();
	CView::OnRButtonDown(nFlags, point);
}



void CMy3장연습문제View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bStopWatchRun)
	{
		if (nChar == VK_SPACE)
		{
			if (m_nCount < 30)
			{
				m_nCount++;
				m_strRecord[m_nCount - 1] = m_strStopWatch;
			
			}
			else
			{
				m_nCount = 0;
				m_nCount++;
				m_strRecord[m_nCount - 1] = m_strStopWatch;

			}
		}
	}
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
