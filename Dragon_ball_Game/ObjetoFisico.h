#ifndef OBJETOFISICO_H
#define OBJETOFISICO_H

#include <QGraphicsPixmapItem>

class ObjetoFisico : public QGraphicsPixmapItem
{
public:
    ObjetoFisico();

    void setMasa(float m);
    void setVelocidad(float vx, float vy);
    float getMasa() const;
    float getVelocidadX() const;
    float getVelocidadY() const;

protected:
    float masa;
    float velocidadX;
    float velocidadY;
};

#endif // OBJETOFISICO_H
