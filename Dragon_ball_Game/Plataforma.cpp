#include "Plataforma.h"
#include <QGraphicsScene>
#include <QtMath>

Plataforma::Plataforma(TipoPlataforma tipo, float x, float y, float ancho, float /*tiempo*/)
    : tipo(tipo), ancho(ancho)
{
    setPixmap(QPixmap(":/Recursos/objetos/plataforma.png").scaled(ancho, 20, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setPos(x, y);

    velocidad = 1.5f + QRandomGenerator::global()->generateDouble() * (2.5f - 1.0f);
    direccion = -1.0f + QRandomGenerator::global()->generateDouble() * 2.0f;
    if (qAbs(direccion) < 0.3f)
        direccion = direccion < 0 ? -0.5f : 0.5f;
    moverEnX = QRandomGenerator::global()->bounded(2);

    limiteX1 = x - 50;
    limiteX2 = x + 50;
    limiteY1 = y - 40;
    limiteY2 = y + 40;

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Plataforma::mover);
    timerMovimiento->start(50);

    timerCambioDireccion = new QTimer(this);
    connect(timerCambioDireccion, &QTimer::timeout, this, &Plataforma::cambiarMovimientoAleatorio);
    timerCambioDireccion->start(QRandomGenerator::global()->bounded(1000, 3000));
}

void Plataforma::mover() {
    if (moverEnX) {
        float nuevaX = x() + direccion * velocidad;
        if (nuevaX < limiteX1 || nuevaX > limiteX2)
            direccion *= -1;
        else
            setX(nuevaX);
    } else {
        float nuevaY = y() + direccion * velocidad;
        if (nuevaY < limiteY1 || nuevaY > limiteY2)
            direccion *= -1;
        else
            setY(nuevaY);
    }
}

void Plataforma::cambiarMovimientoAleatorio() {
    direccion = -1.0f + QRandomGenerator::global()->generateDouble() * 2.0f;
    if (std::abs(direccion) < 0.3f)
        direccion = direccion < 0 ? -0.5f : 0.5f;

    moverEnX = QRandomGenerator::global()->bounded(2);
    velocidad = 2.5f + QRandomGenerator::global()->generateDouble() * (5.0f - 2.5f);

    int nuevoIntervalo = QRandomGenerator::global()->bounded(1000, 2000);
    timerCambioDireccion->start(nuevoIntervalo);
}

void Plataforma::detectarColisionConGoku(QGraphicsItem* goku) {
    if (!goku) return;

    if (esFinal && collidesWithItem(goku)) {
        emit alcanzadaFinal();
    }
}

void Plataforma::setEsFinal(bool valor) {
    esFinal = valor;
}

TipoPlataforma Plataforma::getTipo() const {
    return tipo;
}

