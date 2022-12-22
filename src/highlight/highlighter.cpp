#include "highlighter.h"

HIGHLIGHTER::HIGHLIGHTER(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    // 标记格式
    tagFormat.setForeground(Qt::darkYellow);
    tagFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegExp("(<[a-zA-Z:]+\\b|<\\?[a-zA-Z:]+\\b|\\?>|>|/>|</[a-zA-Z:]+>)");
    rule.format = tagFormat;
    highlightingRules.append(rule);

    // 属性格式
    attributeFormat.setForeground(Qt::darkGreen);
    attributeFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegExp("[a-zA-Z:]+=");
    rule.format = attributeFormat;
    highlightingRules.append(rule);

    // 属性内容格式
    attributeContentFormat.setForeground(Qt::red);
    attributeContentFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegExp("(\"[^\"]*\"|'[^']*')");
    rule.format = attributeContentFormat;
    highlightingRules.append(rule);

    // 注释格式
    commentFormat.setForeground(Qt::gray);
    commentFormat.setFontWeight(QFont::Bold);
    commentFormat.setFontItalic(true);
    commentStartExpression = QRegExp("<!--");
    commentEndExpression = QRegExp("-->");
}

void HIGHLIGHTER::highlightBlock(const QString &text)
{
     for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
         QRegExp expression(rule.pattern);
         int index = text.indexOf(expression);
         while (index >= 0) {
             int length = expression.matchedLength();
             setFormat(index, length, rule.format);
             index = text.indexOf(expression, index + length);
         }
     }
     setCurrentBlockState(0);

     int startIndex = 0;
     if (previousBlockState() != 1)
         startIndex = text.indexOf(commentStartExpression);

     while (startIndex >= 0) {
         int endIndex = text.indexOf(commentEndExpression, startIndex);
         int commentLength;
         if (endIndex == -1) {
             setCurrentBlockState(1);
             commentLength = text.length() - startIndex;
         } else {
             commentLength = endIndex - startIndex
                             + commentEndExpression.matchedLength();
         }
         setFormat(startIndex, commentLength, commentFormat);
         startIndex = text.indexOf(commentStartExpression,
                                                 startIndex + commentLength);
     }
}
