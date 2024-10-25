
// 3장 연습문제View.h: CMy3장연습문제View 클래스의 인터페이스
//

#pragma once


class CMy3장연습문제View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMy3장연습문제View() noexcept;
	DECLARE_DYNCREATE(CMy3장연습문제View)

// 특성입니다.
public:
	CMy3장연습문제Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CMy3장연습문제View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CString m_strStopWatch;
	int m_nCount;
	int m_nMinute;
	int m_nSecond;
	int m_nMsec;
	bool m_bStopWatchRun;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	CString m_strRecord[30];
};

#ifndef _DEBUG  // 3장 연습문제View.cpp의 디버그 버전
inline CMy3장연습문제Doc* CMy3장연습문제View::GetDocument() const
   { return reinterpret_cast<CMy3장연습문제Doc*>(m_pDocument); }
#endif

