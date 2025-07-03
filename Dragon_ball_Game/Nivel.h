#ifndef NIVEL_H
#define NIVEL_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "Personaje.h"

enum class TipoNivel { UNO, DOS, TRES };

class Nivel : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Nivel(QObject *parent = nullptr);
    virtual ~Nivel() {}

    virtual void cargarElementos() = 0;
    virtual void cargarFondo() = 0;
    virtual void crearPersonaje() = 0;
    virtual void agregarItems() = 0;
    virtual void reiniciarNivel() = 0;
    virtual bool verificarObjetivoCompleto() = 0;
    virtual Personaje* getPersonaje() const = 0;

    TipoNivel getTipo() const;

signals:
    void regresarAlMenu();
    void objetivoCumplido();
    void vidasAgotadas();
    void pausarTiempo();

protected:
    QGraphicsPixmapItem* fondo;
    TipoNivel tipo;

};

#endif // NIVEL_H
