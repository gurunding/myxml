#ifndef LINE_H
#define LINE_H

#include <QPlainTextEdit>
#include <QObject>

class LINENUMBER;

class LINESHOW : public QPlainTextEdit
{
	Q_OBJECT
	
public:
    LINESHOW(QWidget *parent = 0);

    void line_number_area_paint_event(QPaintEvent *event);
    int line_number_area_width();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void update_line_number_area_width(int newBlockCount);
    void update_line_number_area(const QRect &, int);

private:
    QWidget *lineNumberArea;
};

class LINENUMBER : public QWidget
{
public:
    LINENUMBER(LINESHOW *ls) : QWidget(ls)
	{
        lineshow = ls;
	}

    QSize sizeHint() const Q_DECL_OVERRIDE
    {
        return QSize(lineshow->line_number_area_width(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE
    {
        lineshow->line_number_area_paint_event(event);
    }
	
private:
    LINESHOW *lineshow;
};

#endif // LINE_H
