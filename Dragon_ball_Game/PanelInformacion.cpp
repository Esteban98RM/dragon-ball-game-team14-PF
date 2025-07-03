#include "PanelInformacion.h"
#include "Goku.h"

#include <QFontDatabase>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>

PanelInformacion::PanelInformacion(QWidget *parent)
    : QWidget(parent), tiempoRestante(TIEMPO_NIVEL)
{
    setFixedSize(200, 570);

    // Layout principal
    layout = new QVBoxLayout(this);
    layout->setSpacing(15);
    layout->setContentsMargins(10, 20, 10, 20);

    // Crear labels
    labelTitulo = new QLabel("INFORMACION", this);
    labelTiempo = new QLabel("Tiempo: 03:00", this);
    labelNivel = new QLabel("Nivel: 1", this);
    labelVidas = new QLabel("Vidas: 3", this);
    labelEsferas = new QLabel("Esferas: 0/7", this);
    labelTiros = new QLabel("Tiros: 0", this);

    // Añadir widgets al layout
    layout->addWidget(labelTitulo);
    layout->addSpacing(10);
    layout->addWidget(labelTiempo);
    layout->addWidget(labelNivel);
    layout->addWidget(labelVidas);
    layout->addWidget(labelEsferas);
    layout->addWidget(labelTiros);
    layout->addStretch();

    // Configurar estilos
    configurarEstilo();

    // Timer
    timerTiempo = new QTimer(this);
    connect(timerTiempo, &QTimer::timeout, this, &PanelInformacion::actualizarTiempo);
}

void PanelInformacion::configurarEstilo()
{
    // Fuente personalizada estilo Dragon Ball
    int id = QFontDatabase::addApplicationFont(":/Recursos/fuente/Saiyan-Sans.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont fuenteDragonBall(fontFamily);
    fuenteDragonBall.setPointSize(14);

    // Estilo del panel
    setStyleSheet(
        "QWidget {"
        "    background-image: url(:/Recursos/backgraunds/fondo_panel.png);"
        "    background-repeat: no-repeat;"
        "    background-position: center;"
        "    background-color: rgba(0, 0, 0, 180);"
        "    border: 4px solid #FFD700;"
        "    border-radius: 20px;"
        "}"
        );

    // Efecto de borde brillante animado
    QGraphicsDropShadowEffect* efectoBrillo = new QGraphicsDropShadowEffect(this);
    efectoBrillo->setColor(Qt::yellow);
    efectoBrillo->setOffset(0);
    efectoBrillo->setBlurRadius(20);
    setGraphicsEffect(efectoBrillo);

    QPropertyAnimation* animacionBrillo = new QPropertyAnimation(efectoBrillo, "blurRadius", this);
    animacionBrillo->setStartValue(15);
    animacionBrillo->setEndValue(35);
    animacionBrillo->setDuration(1500);
    animacionBrillo->setEasingCurve(QEasingCurve::SineCurve);
    animacionBrillo->setLoopCount(-1);
    animacionBrillo->start();

    // Estilo de título
    labelTitulo->setFont(QFont(fontFamily, 18, QFont::Bold));
    labelTitulo->setAlignment(Qt::AlignCenter);
    labelTitulo->setStyleSheet(
        "QLabel {"
        "    color: #FFD700;"
        "    background-color: transparent;"
        "    padding: 5px;"
        "    border-bottom: 1px solid #FFD700;"
        "}"
        );

    // Estilo info
    QString estiloInfo =
        "QLabel {"
        "    color: white;"
        "    background-color: transparent;"
        "    padding: 3px;"
        "}";

    labelTiempo->setFont(fuenteDragonBall);
    labelNivel->setFont(fuenteDragonBall);
    labelVidas->setFont(fuenteDragonBall);
    labelEsferas->setFont(fuenteDragonBall);
    labelTiros->setFont(fuenteDragonBall);

    labelTiempo->setStyleSheet(estiloInfo + "QLabel { color: #00FF00; }"); // Inicialmente verde
    labelNivel->setStyleSheet(estiloInfo);
    labelVidas->setStyleSheet(estiloInfo);
    labelEsferas->setStyleSheet(estiloInfo);
    labelTiros->setStyleSheet(estiloInfo);
}

void PanelInformacion::actualizarInformacion(Goku* goku, int nivelActual)
{
    if (!goku) return;

    labelNivel->setText(QString("Nivel: %1").arg(nivelActual));
    labelVidas->setText(QString("Vidas: %1").arg(goku->getVidas()));
    labelEsferas->setText(QString("Esferas: %1/7").arg(goku->getEsferasRecolectadas()));
    labelTiros->setText(QString("Tiros: %1").arg(goku->getTirosDisponibles()));

    if (goku->getEsferasRecolectadas() >= 2) {
        labelEsferas->setStyleSheet("QLabel { color: #00FF00; background-color: transparent; padding: 3px; }");
    }

    if (nivelActual > 1 && goku->getTirosDisponibles() <= 0) {
        labelTiros->setStyleSheet("QLabel { color: #FF4444; background-color: transparent; padding: 3px; }");
    } else {
        labelTiros->setStyleSheet("QLabel { color: white; background-color: transparent; padding: 3px; }");
    }

}

void PanelInformacion::iniciarTiempo()
{
    timerTiempo->start(1000);
}

void PanelInformacion::pausarTiempo()
{
    timerTiempo->stop();
}

void PanelInformacion::reiniciarTiempo()
{
    tiempoRestante = TIEMPO_NIVEL;
    labelTiempo->setText("Tiempo: 03:00");
    labelTiempo->setStyleSheet("QLabel { color: #00FF00; background-color: transparent; padding: 3px; }");
}

int PanelInformacion::getTiempoRestante() const
{
    return tiempoRestante;
}

void PanelInformacion::actualizarTiempo()
{
    if (tiempoRestante > 0) {
        tiempoRestante--;
        labelTiempo->setText(QString("Tiempo: %1").arg(formatearTiempo(tiempoRestante)));

        if (tiempoRestante <= 30) {
            labelTiempo->setStyleSheet("QLabel { color: #FF4444; background-color: transparent; padding: 3px; }");
        } else if (tiempoRestante <= 60) {
            labelTiempo->setStyleSheet("QLabel { color: #FFAA00; background-color: transparent; padding: 3px; }");
        }
    } else {
        timerTiempo->stop();
        labelTiempo->setText("Tiempo: 00:00");
        labelTiempo->setStyleSheet("QLabel { color: #FF0000; background-color: transparent; padding: 3px; }");
        emit tiempoAgotado();
    }
}

QString PanelInformacion::formatearTiempo(int segundos)
{
    int minutos = segundos / 60;
    int segs = segundos % 60;
    return QString("%1:%2").arg(minutos, 2, 10, QChar('0')).arg(segs, 2, 10, QChar('0'));
}
