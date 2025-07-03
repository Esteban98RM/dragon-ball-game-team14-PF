#include "Juego.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Nivel3.h"
#include "Goku.h"

#include <QKeyEvent>

Juego::Juego(QWidget *parent)
    : QWidget(parent), nivelActual(nullptr)
{
    layoutPrincipal = new QStackedLayout(this);

    // Crear menú principal
    menu = new VentanaMenuPrincipal(this);

    // Crear contenedor para el juego (panel + vista nivel)
    widgetJuego = new QWidget(this);
    layoutJuego = new QHBoxLayout(widgetJuego);
    layoutJuego->setContentsMargins(0, 0, 0, 0);
    layoutJuego->setSpacing(0);

    // Crear panel de información (izquierda)
    panelInfo = new PanelInformacion(widgetJuego);

    // Crear vista del nivel (centro)
    vistaNivel = new QGraphicsView(widgetJuego);
    vistaNivel->setFixedSize(920, 570);

    // Agregar elementos al layout de juego
    layoutJuego->addWidget(panelInfo);
    layoutJuego->addWidget(vistaNivel);

    // Agregar juego y menú al layout principal
    layoutPrincipal->addWidget(menu);
    layoutPrincipal->addWidget(widgetJuego);
    setLayout(layoutPrincipal);

    // Timer para actualizar la interfaz cada 100ms
    timerActualizacionPanel = new QTimer(this);
    connect(timerActualizacionPanel, &QTimer::timeout, this, &Juego::actualizarPanelInfo);

    // Conectar señales del menú
    conectarSenales();

    // Inicialmente mostrar el menú
    layoutPrincipal->setCurrentWidget(menu);

    // Configuración general
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

void Juego::conectarSenales()
{
    connect(menu, &VentanaMenuPrincipal::mostrarNivel1, this, &Juego::mostrarNivel1);
    connect(menu, &VentanaMenuPrincipal::mostrarNivel2, this, &Juego::mostrarNivel2);
    connect(menu, &VentanaMenuPrincipal::mostrarNivel3, this, &Juego::mostrarNivel3);
    connect(menu, &VentanaMenuPrincipal::iniciarJuegoCompleto, this, &Juego::iniciarJuegoCompleto);
}

void Juego::mostrarNivel1() {
    cargarNivel(TipoNivel::UNO);
}

void Juego::mostrarNivel2() {
    cargarNivel(TipoNivel::DOS);
}

void Juego::mostrarNivel3() {
    cargarNivel(TipoNivel::TRES);
}

void Juego::iniciarJuegoCompleto() {
    cargarNivel(TipoNivel::UNO);
}


void Juego::cargarNivel(TipoNivel tipo)
{
    eliminarNivelActual();

    // Crear el nivel correspondiente
    switch (tipo) {
    case TipoNivel::UNO:
        nivelActual = new Nivel1(this);
        break;
    case TipoNivel::DOS:
        nivelActual = new Nivel2(this);
        break;
    case TipoNivel::TRES:
        nivelActual = new Nivel3(this);
        break;
    }

    if (!nivelActual) return;

    //Conectar señal de objetivo cumplido (Nivel Completado)
    connect(nivelActual, &Nivel::objetivoCumplido, this, &Juego::mostrarTransicionNivel);

    //Conectar señal para pausar el tiempo
    connect(nivelActual, &Nivel::pausarTiempo, panelInfo, &PanelInformacion::pausarTiempo);

    //Conectar señal de regreso al menu
    connect(nivelActual, &Nivel::regresarAlMenu, this, &Juego::volverAlMenu);

    //Conectar señal de vidas agotadas (debes emitirla desde el Nivel cuando Goku pierde todas las vidas)
    connect(nivelActual, &Nivel::vidasAgotadas, this, &Juego::verificarGameOver);

    //Conectar señal de tiempo agotado
    connect(panelInfo, &PanelInformacion::tiempoAgotado, this, &Juego::verificarGameOver);

    // Establecer escena y enfoque
    vistaNivel->setScene(nivelActual);
    vistaNivel->setFocus();

    // Configurar e iniciar panel de información
    panelInfo->reiniciarTiempo();
    panelInfo->iniciarTiempo();

    // Iniciar actualización periódica del panel
    timerActualizacionPanel->start(100); // cada 100ms

    // Cambiar a la vista del juego
    layoutPrincipal->setCurrentWidget(widgetJuego);
}

void Juego::volverAlMenu()
{
    timerActualizacionPanel->stop();
    panelInfo->pausarTiempo();
    eliminarNivelActual();
    layoutPrincipal->setCurrentWidget(menu);
}

void Juego::eliminarNivelActual()
{
    if (nivelActual) {
        nivelActual->deleteLater();
        nivelActual = nullptr;
    }
}

void Juego::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "[Juego] keyPressEvent detectado. Tecla:" << event->key();

    if (!nivelActual) return;

    Goku* goku = dynamic_cast<Goku*>(nivelActual->getPersonaje());
    if (!goku) return;

    qDebug() << "[Goku] posición actual:" << goku->pos();

    float velocidad = goku->getVelocidad();
    float factorVelocidad = goku->getCaparazon().getFactorVelocidad();
    float factorSalto = goku->getCaparazon().getFactorSalto();

    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_A:
        if (goku->estaSaltando()) {
            float velocidadX = goku->getVelocidadX() - (velocidad * factorVelocidad * 0.3f);
            goku->setVelocidad(velocidadX, goku->getVelocidadY());
        } else {
            goku->setX(goku->x() - velocidad * factorVelocidad);
            goku->setVelocidad(-velocidad * factorVelocidad * 0.5f, goku->getVelocidadY());
        }
        break;

    case Qt::Key_Right:
    case Qt::Key_D:
        if (goku->estaSaltando()) {
            float velocidadX = goku->getVelocidadX() + (velocidad * factorVelocidad * 0.3f);
            goku->setVelocidad(velocidadX, goku->getVelocidadY());
        } else {
            goku->setX(goku->x() + velocidad * factorVelocidad);
            goku->setVelocidad(velocidad * factorVelocidad * 0.5f, goku->getVelocidadY());
        }
        break;

    case Qt::Key_Space:
        if (!goku->estaSaltando()) {
            goku->saltar();
            qDebug() << "[Movimiento] Salto parabólico activado";
        }
        break;

    case Qt::Key_Z:
        goku->disparar(false);
        break;

    case Qt::Key_X:
        goku->disparar(true);
        break;

    case Qt::Key_Escape:
        volverAlMenu();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void Juego::actualizarPanelInfo()
{
    if (!nivelActual) return;

    Goku* goku = dynamic_cast<Goku*>(nivelActual->getPersonaje());
    if (!goku) return;

    int numeroNivel = 1;
    switch (nivelActual->getTipo()) {
    case TipoNivel::UNO: numeroNivel = 1; break;
    case TipoNivel::DOS: numeroNivel = 2; break;
    case TipoNivel::TRES: numeroNivel = 3; break;
    }

    panelInfo->actualizarInformacion(goku, numeroNivel);
}

// Implementa el nuevo método:
void Juego::mostrarVentanaEmergente(VentanaEmergente::TipoMensaje tipo, int siguienteNivel) {
    VentanaEmergente *ventana = new VentanaEmergente(tipo, this);

    connect(ventana, &VentanaEmergente::volverAlMenu, this, &Juego::volverAlMenu);
    connect(ventana, &VentanaEmergente::reintentarNivel, [=]() {
        cargarNivel(nivelActual->getTipo());
    });
    connect(ventana, &VentanaEmergente::siguienteNivel, [=]() {
        cargarNivel(static_cast<TipoNivel>(siguienteNivel));
    });

    ventana->exec();
}

// Modifica los métodos de transición:
void Juego::mostrarTransicionNivel() {
    if (!nivelActual) return;

    switch (nivelActual->getTipo()) {
    case TipoNivel::UNO:
        mostrarVentanaEmergente(VentanaEmergente::NIVEL_COMPLETADO, static_cast<int>(TipoNivel::DOS));
        break;
    case TipoNivel::DOS:
        mostrarVentanaEmergente(VentanaEmergente::NIVEL_COMPLETADO, static_cast<int>(TipoNivel::TRES));
        break;
    case TipoNivel::TRES:
        mostrarVentanaEmergente(VentanaEmergente::JUEGO_COMPLETADO);
        break;
    }
}

void Juego::mostrarGameOver() {
    mostrarVentanaEmergente(VentanaEmergente::GAME_OVER);
}

void Juego::verificarGameOver() {
    if (!nivelActual) return;

    Goku* goku = dynamic_cast<Goku*>(nivelActual->getPersonaje());
    if (!goku) return;

    if (goku->getVidas() <= 0 || panelInfo->getTiempoRestante() <= 0) {
        panelInfo->pausarTiempo();
        timerActualizacionPanel->stop();
        mostrarGameOver();
    }
}
