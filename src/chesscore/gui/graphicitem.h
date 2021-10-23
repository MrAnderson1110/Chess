#ifndef GRAPHICITEM_H
#define GRAPHICITEM_H

#include <QQuickItem>

#include "../core/basevisitor.h"

// NOTE так как у нас устаявшаяся система классов фигур,
// самый простой вариант управлять графикой - обход коллекции фигур и клеток

class CHESSCORE_EXPORT GraphicItem : public QQuickItem, public BaseVisitable<void>
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *background READ background WRITE setBackground NOTIFY backgroundChanged)
    Q_PROPERTY(int rowIndex READ rowIndex WRITE setRowIndex NOTIFY rowIndexChanged)
    Q_PROPERTY(int columnIndex READ columnIndex WRITE setColumnIndex NOTIFY columnIndexChanged)
public:
    explicit GraphicItem(QQuickItem *parent = nullptr);

    QQuickItem *background() const;
    int columnIndex() const;
    int rowIndex() const;

    QRectF geometry() const;
    void setGeometry(const QRectF &geometry);

public slots:
    void setBackground(QQuickItem *newBackground);
    void setColumnIndex(int newColumnIndex);
    void setRowIndex(int newRowIndex);

protected:
    virtual void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    virtual void polishContent();

signals:
    void backgroundChanged(QQuickItem *);
    void rowIndexChanged(int);
    void columnIndexChanged(int);

private:
    QQuickItem *m_background;
    int m_rowIndex;
    int m_columnIndex;
};

#endif // GRAPHICITEM_H
