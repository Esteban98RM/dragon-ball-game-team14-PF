#include "Fisica.h"
#include "Goku.h"
#include "Plataforma.h"

#include <QtMath>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

Fisica::Fisica() {}

void Fisica::aplicarGravedad(Personaje* personaje)
{
    if (!personaje) return;

    float nuevaY = personaje->y() + 5.0;  // Caída por gravedad base
    personaje->setY(nuevaY);
    // En un mundo real, aquí usarías delta time y aceleración
}

bool Fisica::verificarColisionSuelo(Personaje* personaje, Plataforma* plataforma)
{
    if (!personaje || !plataforma) return false;

    return personaje->collidesWithItem(plataforma);
}

void Fisica::calcularTiroParabolico(float angulo, float velocidad)
{
    // Este método puede usarse para inicializar trayectorias de proyectiles
    float rad = qDegreesToRadians(angulo);
    float vx = velocidad * qCos(rad);
    float vy = velocidad * qSin(rad);

    qDebug() << "[Fisica] Tiro parabólico -> Vx:" << vx << " Vy:" << vy;
    // Luego deberías animar el movimiento con timer o física
}

void Fisica::calcularTiroRecto(float velocidad)
{
    float vx = velocidad;
    qDebug() << "[Fisica] Tiro recto -> Vx:" << vx;
    // Movimiento horizontal puro
}

void Fisica::aplicarResistencia(Personaje* personaje, const Caparazon& caparazon)
{
    if (!personaje) return;

    float factor = caparazon.getFactorVelocidad();
    personaje->setX(personaje->x() + 1.0 * factor);  // Ejemplo básico
}

void Fisica::afectarObjeto(ObjetoFisico* objeto)
{
    if (!objeto) return;

    // Pendiente: efecto físico sobre plataforma u obstáculo
    qDebug() << "[Fisica] Afectando objeto físico";
}


void Fisica::actualizarFisicaSalto(Personaje* personaje, const QList<QGraphicsItem*>& colisiones)
{
    if (personaje->parentItem() && personaje->scene() &&
        !personaje->scene()->items().contains(personaje->parentItem())) {
        personaje->setParentItem(nullptr);
    }

    if (!personaje) return;

    bool soporteEncontrado = false;

    for (QGraphicsItem* item : colisiones) {
        if (dynamic_cast<Plataforma*>(item) || dynamic_cast<QGraphicsRectItem*>(item)) {
            soporteEncontrado = true;
            break;
        }
    }

    float velSalto = personaje->getVelocidadSalto();

    if (personaje->estaSaltando()) {
        // Si está en salto activo (subiendo o cayendo)
        personaje->setY(personaje->y() + velSalto);
        personaje->setVelocidadSalto(velSalto + 1.0f);  // gravedad

        // Limitar velocidad de caída
        if (personaje->getVelocidadSalto() > 10.0f)
            personaje->setVelocidadSalto(10.0f);

        // Si hay soporte y está cayendo, aterriza
        if (soporteEncontrado && personaje->getVelocidadSalto() >= 0) {
            personaje->setVelocidadSalto(0);
            personaje->setEnSalto(false);

            for (QGraphicsItem* item : colisiones) {
                if (Plataforma* plataforma = dynamic_cast<Plataforma*>(item)) {
                    QGraphicsItem* plataformaActual = personaje->parentItem();
                    QGraphicsItem* nuevaPlataforma = plataforma;

                    if (plataformaActual != nuevaPlataforma) {
                        // Cambia de plataforma solo si es diferente
                        QPointF posicionGlobal = personaje->scenePos();
                        personaje->setParentItem(nuevaPlataforma);
                        personaje->setPos(nuevaPlataforma->mapFromScene(posicionGlobal));
                    }

                    QRectF platRect = plataforma->boundingRect();
                    personaje->setY(platRect.top() - personaje->boundingRect().height());
                    break;
                } else if (QGraphicsRectItem* suelo = dynamic_cast<QGraphicsRectItem*>(item)) {
                    personaje->setParentItem(nullptr);
                    QRectF rect = suelo->boundingRect().translated(suelo->scenePos());
                    personaje->setY(rect.top() - personaje->boundingRect().height());
                    break;
                }
            }

            qDebug() << "[Fisica] Aterrizó. EnSalto desactivado.";
        }
    }
    else if (!soporteEncontrado) {
        // Si no está en salto pero no hay soporte (se cayó)
        personaje->setY(personaje->y() + velSalto);
        personaje->setVelocidadSalto(velSalto + 1.0f);

        if (personaje->getVelocidadSalto() > 10.0f)
            personaje->setVelocidadSalto(10.0f);
    }

    // qDebug() << "[Fisica] Y:" << personaje->y()
    //          << " VelSalto:" << personaje->getVelocidadSalto()
    //          << " EnSalto:" << personaje->estaSaltando()
    //          << " Soporte:" << soporteEncontrado;

}




