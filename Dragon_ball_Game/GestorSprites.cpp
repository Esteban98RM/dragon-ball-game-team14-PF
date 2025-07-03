#include "GestorSprites.h"
#include <QDebug>
#include <QPainter>
#include <QGraphicsOpacityEffect>

GestorSprites& GestorSprites::getInstance()
{
    static GestorSprites instancia;
    return instancia;
}

bool GestorSprites::cargarSprite(const QString& nombre, const QString& rutaArchivo)
{
    QPixmap sprite(rutaArchivo);
    if (sprite.isNull()) {
        qDebug() << "[GestorSprites] Error al cargar sprite:" << rutaArchivo;
        return false;
    }

    sprites[nombre] = sprite;
    qDebug() << "[GestorSprites] Sprite cargado:" << nombre;
    return true;
}

bool GestorSprites::cargarAnimacion(TipoAnimacion tipo, const QStringList& rutas)
{
    QList<QPixmap> frames;

    for (const QString& ruta : rutas) {
        QPixmap frame(ruta);
        if (frame.isNull()) {
            qDebug() << "[GestorSprites] Error al cargar frame de animación:" << ruta;
            return false;
        }
        frames.append(frame);
    }

    if (!frames.isEmpty()) {
        animaciones[tipo] = frames;
        qDebug() << "[GestorSprites] Animación cargada con" << frames.size() << "frames";
        return true;
    }

    return false;
}

QPixmap GestorSprites::getSprite(const QString& nombre)
{
    if (sprites.contains(nombre)) {
        return sprites[nombre];
    }

    qDebug() << "[GestorSprites] Sprite no encontrado:" << nombre;
    return QPixmap();
}

QPixmap GestorSprites::getFrameAnimacion(TipoAnimacion tipo, int frame)
{
    if (animaciones.contains(tipo)) {
        const QList<QPixmap>& frames = animaciones[tipo];
        if (frame >= 0 && frame < frames.size()) {
            return frames[frame];
        }
    }

    return QPixmap();
}

int GestorSprites::getNumeroFramesAnimacion(TipoAnimacion tipo)
{
    if (animaciones.contains(tipo)) {
        return animaciones[tipo].size();
    }
    return 0;
}

QPixmap GestorSprites::aplicarEfectoSemiInvisible(const QPixmap& sprite, float opacidad)
{
    if (sprite.isNull()) return sprite;

    QPixmap resultado = sprite.copy();
    QPainter painter(&resultado);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter.fillRect(resultado.rect(), QColor(0, 0, 0, static_cast<int>(255 * opacidad)));
    painter.end();

    return resultado;
}

QPixmap GestorSprites::aplicarEfectoRecolectado(const QPixmap& sprite)
{
    if (sprite.isNull()) return sprite;

    QPixmap resultado = aplicarEfectoSemiInvisible(sprite, 0.4f);

    // Añadir un tinte verdoso para indicar que fue recolectado
    QPainter painter(&resultado);
    painter.setCompositionMode(QPainter::CompositionMode_Overlay);
    painter.fillRect(resultado.rect(), QColor(0, 255, 0, 50));
    painter.end();

    return resultado;
}

QPixmap GestorSprites::aplicarEfectoBrillo(const QPixmap& sprite)
{
    if (sprite.isNull()) return sprite;

    QPixmap resultado = sprite.copy();
    QPainter painter(&resultado);
    painter.setCompositionMode(QPainter::CompositionMode_Overlay);
    painter.fillRect(resultado.rect(), QColor(255, 255, 0, 30)); // Brillo amarillento
    painter.end();

    return resultado;
}

void GestorSprites::iniciarAnimacion(QGraphicsPixmapItem* item, TipoAnimacion tipo, int duracionFrame)
{
    if (!item || !animaciones.contains(tipo)) return;

    // Detener animación existente si la hay
    detenerAnimacion(item);

    // Crear nueva animación
    AnimacionActiva animacion;
    animacion.item = item;
    animacion.tipo = tipo;
    animacion.frameActual = 0;
    animacion.duracionFrame = duracionFrame;
    animacion.timer = new QTimer(this);

    // Conectar timer
    connect(animacion.timer, &QTimer::timeout, [this, item]() {
        for (int i = 0; i < animacionesActivas.size(); ++i) {
            if (animacionesActivas[i].item == item) {
                AnimacionActiva& anim = animacionesActivas[i];

                // Avanzar al siguiente frame
                anim.frameActual = (anim.frameActual + 1) % getNumeroFramesAnimacion(anim.tipo);

                // Actualizar sprite del item
                QPixmap frame = getFrameAnimacion(anim.tipo, anim.frameActual);
                if (!frame.isNull()) {
                    anim.item->setPixmap(frame);
                }
                break;
            }
        }
    });

    // Iniciar timer y añadir a la lista
    animacion.timer->start(duracionFrame);
    animacionesActivas.append(animacion);

    // Establecer primer frame
    QPixmap primerFrame = getFrameAnimacion(tipo, 0);
    if (!primerFrame.isNull()) {
        item->setPixmap(primerFrame);
    }

    qDebug() << "[GestorSprites] Animación iniciada para item";
}

void GestorSprites::detenerAnimacion(QGraphicsPixmapItem* item)
{
    for (int i = animacionesActivas.size() - 1; i >= 0; --i) {
        if (animacionesActivas[i].item == item) {
            animacionesActivas[i].timer->stop();
            animacionesActivas[i].timer->deleteLater();
            animacionesActivas.removeAt(i);
            qDebug() << "[GestorSprites] Animación detenida para item";
            break;
        }
    }
}

void GestorSprites::actualizarAnimacion()
{
    // Este método se puede usar para actualizaciones globales si es necesario
}

void GestorSprites::configurarAnimacionesDefault()
{
    // Cargar animaciones predefinidas si existen los archivos
    QStringList animacionCorrer = {
        ":/Recursos/goku1.png",
        ":/Recursos/goku2.png",
        ":/Recursos/goku3.png",
        ":/Recursos/goku4.png"
    };

    QStringList animacionSaltar = {
        ":/Recursos/goku5.png",
        ":/Recursos/goku6.png"
    };

    QStringList animacionNadar = {
        ":/Recursos/gokunadando1.png",
        ":/Recursos/gokunadando2.png",
        ":/Recursos/gokunadando3.png"
    };

    QStringList animacionLanzar = {
        ":/Recursos/gokulanzamiento1.png",
        ":/Recursos/gokulanzamiento2.png",
        ":/Recursos/gokulanzamiento3.png"
    };

    // Intentar cargar las animaciones
    cargarAnimacion(TipoAnimacion::CORRIENDO, animacionCorrer);
    cargarAnimacion(TipoAnimacion::SALTANDO, animacionSaltar);
    cargarAnimacion(TipoAnimacion::NADANDO, animacionNadar);
    cargarAnimacion(TipoAnimacion::LANZANDO, animacionLanzar);

    // Cargar sprite idle
    cargarSprite("goku_idle", ":/Recursos/personaje/goku.png");
}
