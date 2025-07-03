#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsPixmapItem>

class Item :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Item();
    virtual ~Item() = default;

    bool isRecolectado() const;
    void setRecolectado(bool recolectado);

    // Nuevos métodos para efectos visuales
    void aplicarEfectoRecolectado();
    void restaurarAparienciaNormal();
    using QGraphicsPixmapItem::QGraphicsPixmapItem;

    virtual void efecto() = 0;  // función virtual pura

protected:
    float posX;
    float posY;
    bool recolectado;
    QPixmap spriteOriginal; // Para restaurar la apariencia
};

#endif // ITEM_H
