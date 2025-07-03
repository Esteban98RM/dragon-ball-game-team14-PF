#include "Nivel3.h"
#include <QPixmap>
#include <QDebug>

Nivel3::Nivel3(QObject *parent)
    : Nivel(parent)
{
    tipo = TipoNivel::TRES;
    cargarFondo();
    cargarElementos();
}

void Nivel3::cargarFondo()
{
    QPixmap fondoPixmap(":/Recursos/backgraunds/BACKGRAUND NIVEL 3.png");

    if (!fondoPixmap.isNull()) {
        fondoPixmap = fondoPixmap.scaled(920, 570, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        fondo = new QGraphicsPixmapItem(fondoPixmap);
        addItem(fondo);
    } else {
        qDebug() << "[Nivel3] No se pudo cargar la imagen de fondo";
    }
}

void Nivel3::cargarElementos()
{
    // Aquí añadirás enemigos, plataformas, etc.
}

void Nivel3::crearPersonaje() {
    // Código para crear a Goku u otro personaje
}

void Nivel3::agregarItems() {
    // Agrega esferas, cajas, enemigos...
}

void Nivel3::reiniciarNivel() {
    // Lógica para reiniciar todo (vida, tiempo, etc.)
}

bool Nivel3::verificarObjetivoCompleto() {
    // Devuelve true si se recolectaron los ítems necesarios, etc.
    return false; // Por ahora, de ejemplo
}

Personaje* Nivel3::getPersonaje() const {
    return goku;
}

