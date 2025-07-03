#include "Personaje.h"
#include <QDebug>

Personaje::Personaje(QObject *parent)
    : QObject(parent),
    QGraphicsPixmapItem(),
    velocidad(5),
    vidas(3),
    velocidadSalto(0.0f),
    gravedad(1.0f),
    enSalto(false)
{
    setPos(0, 0);  // Posición inicial
}

void Personaje::mover(short dx, short dy)
{
    setX(x() + dx * velocidad);
    setY(y() + dy * velocidad);
}

void Personaje::saltar()
{
    if (!enSalto) {
        enSalto = true;
        velocidadSalto = -15.0f;
        qDebug() << "[Personaje] Inicia salto con velocidad:" << velocidadSalto;
    }
}

void Personaje::recibirDano()
{
    vidas--;
    qDebug() << "[Personaje] Daño recibido. Vidas restantes:" << vidas;

    if (vidas <= 0) {
        qDebug() << "[Personaje] Eliminado";
    }
}

void Personaje::actualizarSalto() {
    setY(y() + velocidadSalto);
    velocidadSalto += gravedad;

    if (velocidadSalto >= 10.0f) {
        enSalto = false;
        velocidadSalto = -10.0f;
    }
}

short Personaje::getVidas() const { return vidas; }
void Personaje::setVidas(short nuevasVidas) { vidas = nuevasVidas; }

float Personaje::getVelocidad() const { return velocidad; }

float Personaje::getVelocidadSalto() const { return velocidadSalto; }
void Personaje::setVelocidadSalto(float nuevaVelocidadSalto) { velocidadSalto = nuevaVelocidadSalto; }

bool Personaje::estaSaltando() const { return enSalto; }
void Personaje::setEnSalto(bool estado) { enSalto = estado; }

float Personaje::getVelocidadX() const {
    return velocidadX;
}

float Personaje::getVelocidadY() const {
    return velocidadY;
}

void Personaje::setVelocidad(float x, float y) {
    velocidadX = x;
    velocidadY = y;
}

