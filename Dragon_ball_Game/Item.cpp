#include "Item.h"
#include "GestorSprites.h"

Item::Item()
    : posX(0), posY(0), recolectado(false)
{
}

bool Item::isRecolectado() const {
    return recolectado;
}

void Item::setRecolectado(bool estado) {
    if (estado && !recolectado) {
        // Aplicar efecto visual cuando se recolecta por primera vez
        aplicarEfectoRecolectado();
    } else if (!estado && recolectado) {
        // Restaurar apariencia si se cancela la recolección
        restaurarAparienciaNormal();
    }

    recolectado = estado;
}

void Item::aplicarEfectoRecolectado() {
    // Guardar sprite original si no está guardado
    if (spriteOriginal.isNull()) {
        spriteOriginal = pixmap();
    }

    // Aplicar efecto semi-invisible
    GestorSprites& gestor = GestorSprites::getInstance();
    QPixmap spriteEfecto = gestor.aplicarEfectoRecolectado(spriteOriginal);
    setPixmap(spriteEfecto);

    qDebug() << "[Item] Efecto de recolección aplicado";
}

void Item::restaurarAparienciaNormal() {
    if (!spriteOriginal.isNull()) {
        setPixmap(spriteOriginal);
        qDebug() << "[Item] Apariencia normal restaurada";
    }
}
