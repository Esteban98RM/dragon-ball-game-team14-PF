#include "Goku.h"
#include "EsferaDragon.h"
#include "CajaLeche.h"
#include <QDebug>

Goku::Goku(QObject *parent)
    : Personaje(parent), tirosDisponibles(0)
{
    cargarImagen();
    caparazon.actualizarPeso(1);

    // Configurar timer para actualizar animaciones
    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &Goku::actualizarAnimacionSegunEstado);
    timerAnimacion->start(100); // Actualizar cada 100ms

    // Configurar animaciones predeterminadas en el gestor
    GestorSprites& gestor = GestorSprites::getInstance();
}

void Goku::cargarImagen()
{
    QPixmap imagen(":/Recursos/personaje/goku.png");
    setPixmap(imagen.scaled(60, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Goku::disparar(bool parabolico)
{
    if (tirosDisponibles <= 0) {
        qDebug() << "[Goku] Sin tiros.";
        return;
    }

    if (parabolico)
        qDebug() << "[Goku] Disparo parabólico.";
    else
        qDebug() << "[Goku] Disparo recto.";

    tirosDisponibles--;
}

void Goku::recolectar(Item* item)
{
    if (item && !item->isRecolectado()) {
        item->efecto();
        item->setRecolectado(true);

        // Verificar tipo de item específico
        if (EsferaDragon* esfera = dynamic_cast<EsferaDragon*>(item)) {
            esferasRecolectadas.append(item);
            qDebug() << "[Goku] Esfera del Dragon recolectada. Total:" << esferasRecolectadas.size();
        }
        else if (CajaLeche* caja = dynamic_cast<CajaLeche*>(item)) {
            // Verificar si es la caja obligatoria (5 tiros)
            if (caja->property("cantidadTiros").toInt() == 5) {
                cajaLecheObligatoriaRecolectada = true;
                aumentarTiros(5);
                qDebug() << "[Goku] Caja de leche obligatoria (5 tiros) recolectada!";
            } else {
                aumentarTiros(caja->property("cantidadTiros").toInt());
                qDebug() << "[Goku] Caja de leche opcional recolectada.";
            }
        }

        qDebug() << "[Goku] Item recolectado.";
    }
}

// void Goku::saltar() {
//     if (!estaSaltando()) {
//         float fuerzaSaltoY = -12.0f * caparazon.getFactorSalto(); // Fuerza vertical
//         float fuerzaSaltoX = getVelocidadX() * 0.8f; // Mantener momentum horizontal

//         setVelocidad(fuerzaSaltoX, fuerzaSaltoY);
//         setEnSalto(true);

//         qDebug() << "[Goku] Salto parabólico iniciado - Vx:" << fuerzaSaltoX << " Vy:" << fuerzaSaltoY;
//     }
// }

// void Goku::saltar() {
//     if (!estaSaltando()) {
//         float fuerzaBaseSaltoY = -50.0f; // Aumentar fuerza vertical de salto
//         float fuerzaSaltoY = fuerzaBaseSaltoY * caparazon.getFactorSalto();
//         float fuerzaSaltoX = getVelocidadX() * 1.5f;

//         setVelocidad(fuerzaSaltoX, fuerzaSaltoY);
//         setEnSalto(true);

//         qDebug() << "[Goku] Salto parabólico iniciado - Vx:" << fuerzaSaltoX << " Vy:" << fuerzaSaltoY;
//     }
// }

void Goku::saltar() {
    if (!estaSaltando()) {
        float fuerzaSalto = -10.0f * caparazon.getFactorSalto();
        setVelocidadSalto(fuerzaSalto);
        setEnSalto(true);
    }
}

void Goku::nadar()
{
    qDebug() << "[Goku] Nadando...";
}

int Goku::getTirosDisponibles() const {
    return tirosDisponibles;
}

float Goku::getVelocidad() const {
    return velocidad;
}

Caparazon& Goku::getCaparazon() {
    return caparazon;
}

int Goku::getEsferasRecolectadas() const {
    return esferasRecolectadas.size();
}

bool Goku::tieneCajaLecheObligatoria() const {
    return cajaLecheObligatoriaRecolectada;
}

void Goku::aumentarTiros(int cantidad) {
    tirosDisponibles += cantidad;
    qDebug() << "[Goku] Tiros aumentados en" << cantidad << ". Total:" << tirosDisponibles;
}

void Goku::marcarCajaLecheObligatoria() {
    cajaLecheObligatoriaRecolectada = true;
}

void Goku::iniciarAnimacion(TipoAnimacion tipo) {
    if (animacionActual != tipo) {
        animacionActual = tipo;
        GestorSprites& gestor = GestorSprites::getInstance();
        gestor.iniciarAnimacion(this, tipo);
        qDebug() << "[Goku] Animación cambiada a tipo:" << static_cast<int>(tipo);
    }
}

void Goku::detenerAnimaciones() {
    GestorSprites& gestor = GestorSprites::getInstance();
    gestor.detenerAnimacion(this);
    animacionActual = TipoAnimacion::IDLE;
}

void Goku::actualizarAnimacionSegunEstado() {
    TipoAnimacion nuevaAnimacion = TipoAnimacion::IDLE;

    // Determinar qué animación usar según el estado actual
    if (estaSaltando()) {
        nuevaAnimacion = TipoAnimacion::SALTANDO;
    } else if (qAbs(getVelocidadX()) > 0.1f) {
        nuevaAnimacion = TipoAnimacion::CORRIENDO;
    } else {
        nuevaAnimacion = TipoAnimacion::IDLE;
    }

    // Cambiar animación si es necesario
    if (nuevaAnimacion != animacionActual) {
        iniciarAnimacion(nuevaAnimacion);
    }
}


