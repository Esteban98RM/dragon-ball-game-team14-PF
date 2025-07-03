#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>
#include <QTimer>

class Personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Personaje(QObject *parent = nullptr);
    virtual ~Personaje() = default;

    virtual void cargarImagen() = 0;

    void mover(short dx, short dy);
    void saltar();
    void recibirDano();

    short getVidas() const;
    float getVelocidad() const;
    float getVelocidadSalto() const;
    void setVelocidadSalto(float nuevaVelocidadSalto);
    bool estaSaltando() const;
    void setEnSalto(bool estado);
    void setVidas(short nuevasVidas);

    float getVelocidadX() const;
    float getVelocidadY() const;
    void setVelocidad(float x, float y);

protected slots:
    void actualizarSalto();

protected:
    short velocidad;
    short vidas;
    float posX;
    float posY;

    bool enSalto;
    float velocidadSalto;
    float gravedad;

    float velocidadX = 0;
    float velocidadY = 0;

    // QTimer* timerSalto;
};

#endif // PERSONAJE_H
