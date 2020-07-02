/**
 * 自定义无边框窗体、对话框和提示框
 *
 * MuShadowWidget.cpp
 * 实现边框阴影
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 *
 */

#include <QPainter>
#include "MuShadowWidget.h"
#include <QtMath>

inline unsigned char MuMakeAlpha(int i, double f, int nSize)
{
    if (i == nSize)
        f *= 1.2;
    //

    double f2 = 1 - cos((double)i / nSize * 3.14 / 2);
    //
    return int(fabs((i * f) * f2));
}
QImage MuMakeShadowImage(int shadowSize, bool activated = false, int borderSize = 0)
{
    int size = shadowSize * 2 + 10;
    QImage image(size, size, QImage::Format_ARGB32);
    image.fill(QColor(Qt::black));
    //
    double f = activated ? 4.0 : 4.0;
    //
    QSize szImage = image.size();
    //
    //left
    for (int y = shadowSize; y < szImage.height() - shadowSize; y++) {
        for (int x = 0; x < shadowSize; x++) {
            int i = x;
            int alpha = MuMakeAlpha(i, f, shadowSize);
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
        }
    }
    //right
    for (int y = shadowSize; y < szImage.height() - shadowSize; y++) {
        for (int x = szImage.width() - shadowSize - 1; x < szImage.width(); x++) {
            int i = szImage.width() - x;
            int alpha = MuMakeAlpha(i, f, shadowSize);
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
        }
    }
    //top
    for (int y = 0; y < shadowSize; y++) {
        int i = y;
        for (int x = shadowSize; x < szImage.width() - shadowSize; x++) {
            int alpha = MuMakeAlpha(i, f, shadowSize);
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
        }
        //
    }
    //bottom
    for (int y = szImage.height() - shadowSize - 1; y < szImage.height(); y++) {
        int i = szImage.height() - y;
        for (int x = shadowSize; x < szImage.width() - shadowSize; x++) {
            int alpha = MuMakeAlpha(i, f, shadowSize);
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
        }
    }
    //
    int parentRoundSize = 3;
    //
    for (int x = 0; x < shadowSize + parentRoundSize; x++) {
        for (int y = 0; y < shadowSize + parentRoundSize; y++) {
            int xx = (shadowSize + parentRoundSize) - x;
            int yy = (shadowSize + parentRoundSize) - y;
            int i = int(sqrt(double(xx * xx + yy * yy)));
            i = std::min<int>(shadowSize + parentRoundSize, i);
            i -= parentRoundSize;
            i = shadowSize - i;
            //
            int alpha = MuMakeAlpha(i, f, shadowSize);
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
        }
    }
    //
    for (int x = szImage.width() - shadowSize - parentRoundSize; x < szImage.width(); x++) {
        for (int y = 0; y < shadowSize + parentRoundSize; y++) {
            int xx = (shadowSize + parentRoundSize) - (szImage.width() - x);
            int yy = (shadowSize + parentRoundSize) - y;
            int i = int(sqrt(double(xx * xx + yy * yy)));
            i = std::min<int>(shadowSize + parentRoundSize, i);
            i -= parentRoundSize;
            i = shadowSize - i;
            //
            int alpha = MuMakeAlpha(i, f, shadowSize);
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
        }
    }
    //
    for (int x = 0; x < shadowSize + parentRoundSize; x++) {
        for (int y = szImage.height() - shadowSize - parentRoundSize; y < szImage.height(); y++) {
            int xx = (shadowSize + parentRoundSize) - x;
            int yy = (shadowSize + parentRoundSize) - (szImage.height() - y);
            int i = int(sqrt(double(xx * xx + yy * yy)));
            i = std::min<int>(shadowSize + parentRoundSize, i);
            i -= parentRoundSize;
            i = shadowSize - i;
            //
            int alpha = MuMakeAlpha(i, f, shadowSize);
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
        }
    }
    //
    for (int x = szImage.width() - shadowSize - parentRoundSize; x < szImage.width(); x++) {
        for (int y = szImage.height() - shadowSize - parentRoundSize; y < szImage.height(); y++) {
            int xx = (shadowSize + parentRoundSize) - (szImage.width() - x);
            int yy = (shadowSize + parentRoundSize) - (szImage.height() - y);
            int i = int(sqrt(double(xx * xx + yy * yy)));
            i = std::min<int>(shadowSize + parentRoundSize, i);
            i -= parentRoundSize;
            i = shadowSize - i;
            //
            int alpha = MuMakeAlpha(i, f, shadowSize);
            image.setPixelColor(x, y, QColor(0, 0, 0, alpha));
        }
    }
    // 165
//    int borderR = 165;
//    int borderG = 165;
//    int borderB = 165;
    int borderR = 165;
    int borderG = 165;
    int borderB = 165;
    //
    if (activated) {
        borderR = 68;
        borderG = 138;
        borderB = 255;
//        borderR = 0;
//        borderG = 0;
//        borderB = 0;
    }
    //
    //left
    for (int i = 0; i < borderSize; i++) {
        for (int y = shadowSize - 1; y < szImage.height() - shadowSize + 1; y++) {
            int x = shadowSize - i - 1;
            image.setPixelColor(x, y, QColor(borderR, borderG, borderB, 255));
        }
    }
    //right
    for (int i = 0; i < borderSize; i++) {
        for (int y = shadowSize - 1; y < szImage.height() - shadowSize + 1; y++) {
            int x = szImage.width() - shadowSize - 1 + i + 1;
            image.setPixelColor(x, y, QColor(borderR, borderG, borderB, 255));
        }
    }
    //top
    for (int i = 0; i < borderSize; i++) {
        for (int x = shadowSize; x < szImage.width() - shadowSize; x++) {
            int y = shadowSize - i - 1;
            image.setPixelColor(x, y, QColor(borderR, borderG, borderB, 255));
        }
    }
    //bottom
    for (int i = 0; i < borderSize; i++) {
        for (int x = shadowSize; x < szImage.width() - shadowSize; x++) {
            int y = szImage.height() - shadowSize - 1 + i + 1;
            image.setPixelColor(x, y, QColor(borderR, borderG, borderB, 255));
        }
    }
    //
    return image;
}

bool MuSkin9GridImage::clear()
{
    if (!m_img.isNull()) {
        m_img = QImage();
    }
    return true;
}

bool MuSkin9GridImage::splitRect(const QRect &rcSrc, QPoint ptTopLeft, QRect *parrayRect, int nArrayCount)
{
    Q_ASSERT(nArrayCount == 9);
    //
    QRect* arrayRect = parrayRect;
    //
    int nWidth = rcSrc.width();
    int nHeight = rcSrc.height();
    //
    if (ptTopLeft.x() <= 0)
        return false;
    if (ptTopLeft.y() <= 0)
        return false;
    if (ptTopLeft.x() >= nWidth / 2)
        return false;
    if (ptTopLeft.y() >= nHeight / 2)
        return false;
    //
    int x1 = rcSrc.left() + 0;
    int x2 = rcSrc.left() + ptTopLeft.x();
    int x3 = rcSrc.left() + nWidth - ptTopLeft.x();
    int x4 = rcSrc.left() + nWidth;
    //
    int y1 = rcSrc.top() + 0;
    int y2 = rcSrc.top() + ptTopLeft.y();
    int y3 = rcSrc.top() + nHeight - ptTopLeft.y();
    int y4 = rcSrc.top() + nHeight;
    //
    arrayRect[0] = QRect(QPoint(x1, y1), QPoint(x2, y2));
    arrayRect[1] = QRect(QPoint(x2 + 1, y1), QPoint(x3, y2));
    arrayRect[2] = QRect(QPoint(x3 + 1, y1), QPoint(x4, y2));

    arrayRect[3] = QRect(QPoint(x1, y2 + 1), QPoint(x2, y3));
    arrayRect[4] = QRect(QPoint(x2 + 1, y2 + 1), QPoint(x3, y3));
    arrayRect[5] = QRect(QPoint(x3 + 1, y2 + 1), QPoint(x4, y3));

    arrayRect[6] = QRect(QPoint(x1, y3 + 1), QPoint(x2, y4));
    arrayRect[7] = QRect(QPoint(x2 + 1, y3 + 1), QPoint(x3, y4));
    arrayRect[8] = QRect(QPoint(x3 + 1, y3 + 1), QPoint(x4, y4));
    //
    return true;
}

bool MuSkin9GridImage::setImage(const QImage &image, QPoint ptTopLeft)
{
    clear();
    //
    m_img = image;
    //
    int nImageWidth = m_img.width();
    int nImageHeight = m_img.height();
    //
    return splitRect(QRect(0, 0, nImageWidth, nImageHeight), ptTopLeft, m_arrayImageGrid, 9);
}

void MuSkin9GridImage::drawBorder(QPainter *p, QRect rc) const
{
    QRect arrayDest[9];
    //
    splitRect(rc, m_arrayImageGrid[0].bottomRight(), arrayDest, 9);
    //
    for (int i = 0; i < 9; i++) {
        if (i == 4)
            continue;
        //
        const QRect& rcSrc = m_arrayImageGrid[i];
        const QRect& rcDest = arrayDest[i];
        //
        p->drawImage(rcDest, m_img, rcSrc);
    }
}

MuShadowWidget::MuShadowWidget(int shadowSize, bool canResize, QWidget *parent)
    : m_shadowSize(shadowSize)
    , QWidget(parent)
    , m_shadow(new MuSkin9GridImage())
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlag(Qt::FramelessWindowHint);
    setMouseTracking(true);
    //
    QImage image = MuMakeShadowImage(shadowSize, false);
    m_shadow->setImage(image, QPoint(shadowSize + 1, shadowSize + 1));
}

void MuShadowWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    m_shadow->drawBorder(&painter, rect());
}
