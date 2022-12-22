#ifndef XMLSYNTAXHIGHLIGHTER_H
#define XMLSYNTAXHIGHLIGHTER_H

#include <QtCore/QRegExp>
#include <QtGui/QSyntaxHighlighter>

class HIGHLIGHTER : public QSyntaxHighlighter
{
public:
    explicit HIGHLIGHTER(QTextDocument *parent = nullptr);

protected:
    virtual void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat tagFormat;
    QTextCharFormat attributeFormat;
    QTextCharFormat attributeContentFormat;
    QTextCharFormat commentFormat;
};

#endif
