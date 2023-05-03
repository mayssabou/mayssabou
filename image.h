#ifndef IMAGE_H
#define IMAGE_H
#include "patient.h"
class ImageDelegate : public QStyledItemDelegate {
public:
    ImageDelegate(QObject* parent = 0) : QStyledItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
        if (index.column() != IMAGE_COLUMN) { // IMAGE_COLUMN est l'indice de la colonne qui contient l'image
            QStyledItemDelegate::paint(painter, option, index);
            return;
        }

        QByteArray imageByteArray = index.data().toByteArray();
        QPixmap pixmap;
        pixmap.loadFromData(imageByteArray);
        QRect rect = option.rect.adjusted(2, 2, -2, -2);
        painter->drawPixmap(rect, pixmap);
    }

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
        if (index.column() != IMAGE_COLUMN) { // IMAGE_COLUMN est l'indice de la colonne qui contient l'image
            return QStyledItemDelegate::sizeHint(option, index);
        }

        return QSize(IMAGE_SIZE, IMAGE_SIZE);
    }

private:
    const int IMAGE_COLUMN = 7; // l'indice de la colonne qui contient l'image
    const int IMAGE_SIZE = 50; // la taille de l'image affichée
};

#endif // IMAGE_H
