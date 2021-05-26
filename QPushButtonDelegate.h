//
// Created by mia on 5/24/2021.
//

#ifndef A10_915_MUSCALAGIU_ANCAIOANA_1_QPUSHBUTTONDELEGATE_H
#define A10_915_MUSCALAGIU_ANCAIOANA_1_QPUSHBUTTONDELEGATE_H

#endif //A10_915_MUSCALAGIU_ANCAIOANA_1_QPUSHBUTTONDELEGATE_H
#include <QItemDelegate>
#include <QPushButton>
#include <QStyledItemDelegate>
#include "QApplication"
#include <iostream>
#include "string"
using namespace std;

class QPushButtonDelegate : public QStyledItemDelegate{
    Q_OBJECT
public:
    explicit QPushButtonDelegate(QStyledItemDelegate *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        QStyleOptionButton button;
        QRect r = option.rect;//getting the rect of the cell
        int x,y,w,h;
        x = r.left() + r.width() - 100;//the X coordinate
        y = r.top();//the Y coordinate
        w = 100;//button width
        h = 30;//button height
        button.rect = QRect(x,y,w,h);
        button.text = "Play";
        button.state = QStyle::State_Enabled;


        QApplication::style()->drawControl( QStyle::CE_PushButton, &button, painter);
    }

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
    {
        if( event->type() == QEvent::MouseButtonRelease )
        {
       auto linkk = model->itemData(index)[0];
            string link = "start ";
            link = link + linkk.toString().toStdString();
            link = link + " 2> nul";
            system(link.c_str());
        }

        return true;
    }

};