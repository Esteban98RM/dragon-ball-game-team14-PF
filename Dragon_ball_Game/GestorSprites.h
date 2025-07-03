#ifndef GESTORSPRITES_H
#define GESTORSPRITES_H

#include <QPixmap>
#include <QMap>
#include <QString>
#include <QTimer>
#include <QObject>
#include <QGraphicsPixmapItem>

enum class TipoAnimacion {
    IDLE,           // Parado
    CORRIENDO,      // Corriendo
    SALTANDO,       // Saltando
    NADANDO,        // Nadando
    LANZANDO        // Lanzando proyectil
};

class GestorSprites : public QObject
{
    Q_OBJECT

public:
    static GestorSprites& getInstance();

    // Cargar sprites desde archivos
    bool cargarSprite(const QString& nombre, const QString& rutaArchivo);
    bool cargarAnimacion(TipoAnimacion tipo, const QStringList& rutas);

    // Obtener sprites
    QPixmap getSprite(const QString& nombre);
    QPixmap getFrameAnimacion(TipoAnimacion tipo, int frame);
    int getNumeroFramesAnimacion(TipoAnimacion tipo);

    // Efectos visuales para items
    QPixmap aplicarEfectoSemiInvisible(const QPixmap& sprite, float opacidad = 0.3f);
    QPixmap aplicarEfectoRecolectado(const QPixmap& sprite);
    QPixmap aplicarEfectoBrillo(const QPixmap& sprite);

    // Gestión de animaciones
    void iniciarAnimacion(QGraphicsPixmapItem* item, TipoAnimacion tipo, int duracionFrame = 150);
    void detenerAnimacion(QGraphicsPixmapItem* item);

private slots:
    void actualizarAnimacion();

private:
    GestorSprites() = default;
    ~GestorSprites() = default;
    GestorSprites(const GestorSprites&) = delete;
    GestorSprites& operator=(const GestorSprites&) = delete;

    void configurarAnimacionesDefault();

    // Almacenamiento de sprites
    QMap<QString, QPixmap> sprites;
    QMap<TipoAnimacion, QList<QPixmap>> animaciones;

    // Control de animaciones activas
    struct AnimacionActiva {
        QGraphicsPixmapItem* item;
        TipoAnimacion tipo;
        int frameActual;
        int duracionFrame;
        QTimer* timer;
    };

    QList<AnimacionActiva> animacionesActivas;
};

#endif // GESTORSPRITES_H
