#pragma once

#define MAX_IMAGES 3

class CImageObject
{
public:
	CImageObject();
	~CImageObject();

	void	DrawObject(CDC* pDC);
	void	DrawObject(CDC* pDC, int nIndex);
	void	DrawObject(CDC* pDC, LPCTSTR lpszText, CFont* pFont, COLORREF clrFontColor, int nIndex = 0, UINT nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	void	RegisterImage(int nIndex, LPCTSTR lpszFileName);

	void	SetOver(BOOL bOver);
	void	SetXPosition(int nXPos);
	void	SetYPosition(int nYPos);

	BOOL	GetOver();
	int		GetXPosition();
	int		GetYPosition();
	int		GetWidth();
	int		GetHeight();

	BOOL	IsPtInRect(CPoint position);
private:
	int			m_nXPos;
	int			m_nYPos;
	BOOL		m_bOver;

	CBitmap		m_bitmap[MAX_IMAGES];
	BITMAP		m_bi[MAX_IMAGES];

};

