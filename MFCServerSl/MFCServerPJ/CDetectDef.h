#pragma once
class CDetectDef
{

};

///* 1. ���� - �ʷϻ� �˻�
//	 * �׷��� ���� ��ȯ�ؼ�
//	 * ������ �׵θ� ����
//	 * 2. �β� ���� ����
//	 * 3. �� ���� �Ǵ�
//	 */
//CRect rect; //���� ��Ʈ���� ũ�⸦ ������ rect
//m_picture_control.GetWindowRect(rect); //��Ʈ�� ũ�� ��������
//CDC* dc; //���� ��Ʈ���� dc ������ --GDI�� �����ϱ� ����
//dc = m_picture_control.GetDC();
//
//CPngImage pngImg; //png������ ���ҽ� ���Ϸ� �ٷ����
//pngImg.Load(IDB_PNG, AfxGetResourceHandle());
//CBitmap bitmap; //��Ʈ�� �̹����� ��ȯ
//bitmap.Attach(pngImg.Detach());
//CImage image;
//image.Attach(bitmap);
//
//int nWidth = image.GetWidth();
//int nHeight = image.GetHeight();
//unsigned char* fm = (unsigned char*)image.GetBits();
//
////ȭ��� ��� ��ġ�� ���ϱ�����(ȭ��� ��ǥ)
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
///* ���� �˻� - �ʷϻ� �Ӹ� ���� */
//CArray<CPoint> arrGPoint;
///* */
//for (int j = 0; j < nHeight; j++) {
//	for (int i = 0; i < nWidth; i++) {
//		unsigned char r, g, b;
//		r = fm[j * 3 * nPitch + i * 3 + 2];
//		g = fm[j * 3 * nPitch + i * 3 + 1];
//		b = fm[j * 3 * nPitch + i * 3]; //bgr ����
//		fmG[j * nPitch + i] = 0.299 * r + 0.587 * g + 0.114 * b;
//		/* ���� �˻� - �ʷϻ� �Ӹ� ���� */
//		if (r == 0 && b == 0 && g > 100 && i > 240 && i < 400 && j < 240) //�̹��� �߾� ��ܺο� �ʷϻ� Ž��
//		{
//			arrGPoint.Add(CPoint(i * nRateX, j * nRateY));
//		}
//	}
//}
//cout << arrGPoint.GetCount() << endl;
//
////�̹����� ���� ��Ʈ�� ũ���
//image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
//
//
///* ������ ã�Ƴ��� �׵θ� ����Ʈ ã�Ƴ�*/
//CArray<CPoint> arrContour;
//
//for (int j = 50; j < 480; j++) {
//	for (int i = 200; i < 400; i++) {
//		if (abs(fmG[j * nPitch + i] - fmG[j * nPitch + i + 1]) > 5) { //�����̰� 10�̻��̸�
//			arrContour.Add(CPoint(i * nRateX, j * nRateY));
//		}
//	}
//}
//
////�� �׸���
//CPen pen;
//pen.CreatePen(PS_SOLID, 2, RGB(0xff, 0xff, 0)); //�� ���������
//CPen* pOldPen = dc->SelectObject(&pen); //�������� �����ϰ� ���� �� ��ȯ
//CBrush* pOldBrush = (CBrush*)dc->SelectStockObject(NULL_BRUSH); //��ä��� ����
////dc->Ellipse(CRect(300 * nRateX, 80 * nRateY, 360 * nRateX, 100 * nRateY));
////dc->MoveTo(280*nRateX, 100*nRateY);
////dc->LineTo(380*nRateX, 450*nRateY);
//
///* ���� ���� ��� ����Ʈ */
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
///*�ʺ� ���*/
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
///*���� ���*/
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
//dc->SelectObject(pOldPen); //���� ������ ����
//dc->SelectObject(pOldBrush);
////UpdateData();
//
//ReleaseDC(dc); //dc�Ҵ� ����