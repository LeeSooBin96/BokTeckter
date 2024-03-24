#pragma once
class CDetectDef
{

};

///* 1. 색상 - 초록색 검사
//	 * 그레이 레벨 변환해서
//	 * 건전지 테두리 따기
//	 * 2. 두께 길이 측정
//	 * 3. 극 여부 판단
//	 */
//CRect rect; //픽쳐 컨트롤의 크기를 저장할 rect
//m_picture_control.GetWindowRect(rect); //컨트롤 크기 가져오기
//CDC* dc; //픽쳐 컨트롤의 dc 포인터 --GDI에 접근하기 위함
//dc = m_picture_control.GetDC();
//
//CPngImage pngImg; //png파일은 리소스 파일로 다뤄야함
//pngImg.Load(IDB_PNG, AfxGetResourceHandle());
//CBitmap bitmap; //비트맵 이미지로 변환
//bitmap.Attach(pngImg.Detach());
//CImage image;
//image.Attach(bitmap);
//
//int nWidth = image.GetWidth();
//int nHeight = image.GetHeight();
//unsigned char* fm = (unsigned char*)image.GetBits();
//
////화면상 상대 위치값 구하기위함(화면상 좌표)
//double nRateX = (double)rect.Width() / nWidth;
//double nRateY = (double)rect.Height() / nHeight;
//
//CImage grayImg;
//grayImg.Create(nWidth, nHeight, 8);
//static RGBQUAD rgb[256];
//for (int i = 0; i < 256; i++)
//{
//	rgb[i].rgbRed = rgb[i].rgbBlue = rgb[i].rgbGreen = i;
//}
//grayImg.SetColorTable(0, 256, rgb);
//unsigned char* fmG = (unsigned char*)grayImg.GetBits();
//
//
//
//int nPitch = grayImg.GetPitch();
///* 색상 검사 - 초록색 머리 존재 */
//CArray<CPoint> arrGPoint;
///* */
//for (int j = 0; j < nHeight; j++) {
//	for (int i = 0; i < nWidth; i++) {
//		unsigned char r, g, b;
//		r = fm[j * 3 * nPitch + i * 3 + 2];
//		g = fm[j * 3 * nPitch + i * 3 + 1];
//		b = fm[j * 3 * nPitch + i * 3]; //bgr 순서
//		fmG[j * nPitch + i] = 0.299 * r + 0.587 * g + 0.114 * b;
//		/* 색상 검사 - 초록색 머리 존재 */
//		if (r == 0 && b == 0 && g > 100 && i > 240 && i < 400 && j < 240) //이미지 중앙 상단부에 초록색 탐지
//		{
//			arrGPoint.Add(CPoint(i * nRateX, j * nRateY));
//		}
//	}
//}
//cout << arrGPoint.GetCount() << endl;
//
////이미지를 픽쳐 컨트롤 크기로
//image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
//
//
///* 건전지 찾아내기 테두리 포인트 찾아냄*/
//CArray<CPoint> arrContour;
//
//for (int j = 50; j < 480; j++) {
//	for (int i = 200; i < 400; i++) {
//		if (abs(fmG[j * nPitch + i] - fmG[j * nPitch + i + 1]) > 5) { //명도차이가 10이상이면
//			arrContour.Add(CPoint(i * nRateX, j * nRateY));
//		}
//	}
//}
//
////선 그리기
//CPen pen;
//pen.CreatePen(PS_SOLID, 2, RGB(0xff, 0xff, 0)); //펜 노란색으로
//CPen* pOldPen = dc->SelectObject(&pen); //새펜으로 선택하고 기존 펜 반환
//CBrush* pOldBrush = (CBrush*)dc->SelectStockObject(NULL_BRUSH); //색채우기 끄기
////dc->Ellipse(CRect(300 * nRateX, 80 * nRateY, 360 * nRateX, 100 * nRateY));
////dc->MoveTo(280*nRateX, 100*nRateY);
////dc->LineTo(380*nRateX, 450*nRateY);
//
///* 색상 검출 결과 프린트 */
////for (int i = 0; i < arrGPoint.GetCount(); i++) {
////	dc->Ellipse(arrGPoint[i].x, arrGPoint[i].y, arrGPoint[i].x + 1, arrGPoint[i].y + 1);
////}
//int nLeftX = arrGPoint[0].x;
//int nLeftY = arrGPoint[0].y;
//int nRightX = arrGPoint[0].x;
//int nRightY = arrGPoint[0].y;
//
//for (int i = 0; i < arrGPoint.GetCount(); i++) {
//	if (arrGPoint[i].x < nLeftX) nLeftX = arrGPoint[i].x;
//	else if (arrGPoint[i].x > nRightX) nRightX = arrGPoint[i].x;
//	if (arrGPoint[i].y < nLeftY) nLeftY = arrGPoint[i].y;
//	else if (arrGPoint[i].y > nRightY) nRightY = arrGPoint[i].y;
//}
//int nGreenMinY = nLeftY;
//
//dc->Rectangle(nLeftX, nLeftY, nRightX, nRightY);
//dc->TextOutW(nRightX, nRightY, _T("Green Head"));
///* */
//
//CPen pen2;
//pen2.CreatePen(PS_SOLID, 2, RGB(0, 0xff, 0));
//dc->SelectObject(&pen2);
////for (int i = 0; i < arrContour.GetCount(); i++) {
////	dc->Ellipse(arrContour[i].x, arrContour[i].y, arrContour[i].x + 1, arrContour[i].y + 1);
////}
//for (int i = 0; i < arrContour.GetCount(); i++) {
//	if (arrContour[i].x < nLeftX) nLeftX = arrContour[i].x;
//	else if (arrContour[i].x > nRightX) nRightX = arrContour[i].x;
//	if (arrContour[i].y < nLeftY) nLeftY = arrContour[i].y;
//	else if (arrContour[i].y > nRightY) nRightY = arrContour[i].y;
//}
///*너비 출력*/
//dc->MoveTo(nLeftX, nLeftY + (nRightY - nLeftY) / 2);
//dc->LineTo(nLeftX + 5, nLeftY + (nRightY - nLeftY) / 2 - 5);
//dc->MoveTo(nLeftX, nLeftY + (nRightY - nLeftY) / 2);
//dc->LineTo(nLeftX + 5, nLeftY + (nRightY - nLeftY) / 2 + 5);
//dc->MoveTo(nLeftX, nLeftY + (nRightY - nLeftY) / 2);
//dc->LineTo(nRightX, nLeftY + (nRightY - nLeftY) / 2);
//dc->LineTo(nRightX - 5, nLeftY + (nRightY - nLeftY) / 2 - 5);
//dc->MoveTo(nRightX, nLeftY + (nRightY - nLeftY) / 2);
//dc->LineTo(nRightX - 5, nLeftY + (nRightY - nLeftY) / 2 + 5);
//
//CString strWidth;
//strWidth.Format(_T("Width : %d"), nRightX - nLeftX);
//dc->TextOutW(nRightX, nLeftY + (nRightY - nLeftY) / 2, strWidth);
//
///*높이 출력*/
//dc->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nLeftY);
//dc->LineTo(nLeftX + (nRightX - nLeftX) / 2 - 5, nLeftY + 5);
//dc->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nLeftY);
//dc->LineTo(nLeftX + (nRightX - nLeftX) / 2 + 5, nLeftY + 5);
//dc->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nLeftY);
//dc->LineTo(nLeftX + (nRightX - nLeftX) / 2, nRightY);
//dc->LineTo(nLeftX + (nRightX - nLeftX) / 2 - 5, nRightY - 5);
//dc->MoveTo(nLeftX + (nRightX - nLeftX) / 2, nRightY);
//dc->LineTo(nLeftX + (nRightX - nLeftX) / 2 + 5, nRightY - 5);
//
//CString strHeight;
//strWidth.Format(_T("Height : %d"), nRightY - nLeftY);
//dc->TextOutW(nLeftX + (nRightX - nLeftX) / 2, nRightY, strWidth);
//
//CPen pen3;
//pen3.CreatePen(PS_SOLID, 2, RGB(0xff, 0, 0));
//dc->SelectObject(&pen3);
//
//cout << nGreenMinY - nLeftY << endl;
//if (nGreenMinY - nLeftY < 5) {
//	dc->TextOutW(nLeftX + (nRightX - nLeftX) / 2, nLeftY - 20, _T("Pole : false"));
//}
//else {
//	dc->Ellipse(CRect(nLeftX + (nRightX - nLeftX) / 2 - 10, nLeftY + 10, nLeftX + (nRightX - nLeftX) / 2 + 10, nLeftY));
//	dc->TextOutW(nLeftX + (nRightX - nLeftX) / 2, nLeftY - 20, _T("Pole : true"));
//}
//
//dc->SelectObject(pOldPen); //기존 펜으로 복구
//dc->SelectObject(pOldBrush);
////UpdateData();
//
//ReleaseDC(dc); //dc할당 해제