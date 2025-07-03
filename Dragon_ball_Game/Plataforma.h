#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QRandomGenerator>

enum class TipoPlataforma {
    FIJA
};

class Plataforma : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Plataforma(TipoPlataforma tipo, float x, float y, float ancho, float tiempo = 0.0f);

    void mover();
    void cambiarMovimientoAleatorio();
    void detectarColisionConGoku(QGraphicsItem* goku);
    void setEsFinal(bool valor);
    TipoPlataforma getTipo() const;

signals:
    void alcanzadaFinal();

private:
    TipoPlataforma tipo;
    float ancho;
    float velocidad;
    float direccion;
    bool moverEnX;
    bool esFinal = false;

    float limiteX1, limiteX2;
    float limiteY1, limiteY2;

    QTimer* timerMovimiento;
    QTimer* timerCambioDireccion;
};

#endif // PLATAFORMA_H
