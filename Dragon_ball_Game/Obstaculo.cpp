#include "Obstaculo.h"
#include <QDebug>

Obstaculo::Obstaculo(const QString& tipo, float dano)
    : tipoVisual(tipo), dano(dano)
{
    QString rutaImagen;

    if (tipo == "pincho") {
        rutaImagen = ":/Recursos/obstaculos/pincho.png";
    } else if (tipo == "pez") {
        rutaImagen = ":/Recursos/obstaculos/pez.png";
    } else if (tipo == "escombro") {
        rutaImagen = ":/Recursos/obstaculos/escombro.png";
    } else {
        rutaImagen = ":/Recursos/obstaculos/obstaculo_generico.png";
    }

    setPixmap(QPixmap(rutaImagen).scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Obstaculo::afectarPersonaje(Personaje* personaje)
{
    if (!personaje) return;
    personaje->recibirDano();
    qDebug() << "[Obstaculo:" << tipoVisual << "] Daña al personaje con" << dano;
}

float Obstaculo::getDano() const { return dano; }
void Obstaculo::setDano(float nuevoDano) { dano = nuevoDano; }
QString Obstaculo::getTipo() const { return tipoVisual; }
