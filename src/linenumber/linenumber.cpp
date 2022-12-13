#include "linenumber.h"
#include <QtWidgets>

LINESHOW::LINESHOW(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LINENUMBER(this);

    connect(this, &LINESHOW::blockCountChanged, this, &LINESHOW::update_line_number_area_width);
    connect(this, &LINESHOW::updateRequest, this, &LINESHOW::update_line_number_area);

    update_line_number_area_width(0);

    setLineWrapMode(QPlainTextEdit::NoWrap);//设置工作区不自动换行
}

/************************************************
函数名：line_number_area_width
功能：显示行数区域宽
************************************************/
int LINESHOW::line_number_area_width()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

/************************************************
函数名：update_line_number_area_width
功能：更新行数区域宽槽函数
参数：newBlockCount
返回值：NULL
************************************************/
void LINESHOW::update_line_number_area_width(int newBlockCount)
{
    setViewportMargins(line_number_area_width(), 0, 0, 0);
}

/************************************************
函数名：update_line_number_area
功能：更新行数区槽函数
参数：
返回值：
************************************************/
void LINESHOW::update_line_number_area(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        update_line_number_area_width(0);
}

/************************************************
函数名：resizeEvent
功能：行数区行号缩放事件
参数：event
返回值：NULL
************************************************/
void LINESHOW::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), line_number_area_width(), cr.height()));
}

/************************************************
函数名：line_number_area_paint_event
功能：行数区行号绘制事件
参数：event
返回值：NULL
************************************************/
void LINESHOW::line_number_area_paint_event(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::white);


    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignCenter, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
