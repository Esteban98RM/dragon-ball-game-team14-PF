#include "Nivel2.h"
#include <QPixmap>
#include <QDebug>

Nivel2::Nivel2(QObject *parent)
    : Nivel(parent)
{
    tipo = TipoNivel::DOS;
    cargarFondo();
    cargarElementos();
}

void Nivel2::cargarFondo()
{
    QPixmap fondoPixmap(":/Recursos/backgraunds/BACKGRAUND NIVEL 2.png");

    if (!fondoPixmap.isNull()) {
        fondoPixmap = fondoPixmap.scaled(920, 570, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        fondo = new QGraphicsPixmapItem(fondoPixmap);
        addItem(fondo);
    } else {
        qDebug() << "[Nivel2] No se pudo cargar la imagen de fondo";
    }
}

void Nivel2::cargarElementos()
{
    // Aquí añadirás los objetos únicos de este nivel
}

void Nivel2::crearPersonaje() {
    // Código para crear a Goku u otro personaje
}

void Nivel2::agregarItems() {
    // Agrega esferas, cajas, enemigos...
}

void Nivel2::reiniciarNivel() {
    // Lógica para reiniciar todo (vida, tiempo, etc.)
}

bool Nivel2::verificarObjetivoCompleto() {
    // Devuelve true si se recolectaron los ítems necesarios, etc.
    return false; // Por ahora, de ejemplo
}

Personaje* Nivel2::getPersonaje() const {
    return goku;
}
