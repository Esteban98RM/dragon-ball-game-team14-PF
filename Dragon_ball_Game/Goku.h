#ifndef GOKU_H
#define GOKU_H

#include "Personaje.h"
#include "Item.h"
#include "Caparazon.h"
#include "GestorSprites.h"

#include <QList>
#include <QTimer>

class Goku : public Personaje
{
    Q_OBJECT

public:
    explicit Goku(QObject *parent = nullptr);
    void cargarImagen() override;

    void disparar(bool parabolico);
    void recolectar(Item* item);
    void saltar();
    void nadar();

    int getTirosDisponibles() const;
    Caparazon& getCaparazon();  // para poder modificar si se requiere
    float getVelocidad() const;

    // Nuevos métodos para seguimiento de objetivos
    int getEsferasRecolectadas() const;
    bool tieneCajaLecheObligatoria() const;
    void aumentarTiros(int cantidad);
    void marcarCajaLecheObligatoria();

    // Métodos para animaciones
    void iniciarAnimacion(TipoAnimacion tipo);
    void detenerAnimaciones();
    void actualizarAnimacionSegunEstado();

private:
    short tirosDisponibles;
    QList<Item*> esferasRecolectadas;
    Caparazon caparazon;
    bool cajaLecheObligatoriaRecolectada = false;

    // Control de animaciones
    TipoAnimacion animacionActual = TipoAnimacion::IDLE;
    QTimer* timerAnimacion;
};

#endif // GOKU_H
