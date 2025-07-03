#ifndef PANELINFORMACION_H
#define PANELINFORMACION_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QFont>

class Goku;

class PanelInformacion : public QWidget
{
    Q_OBJECT

public:
    explicit PanelInformacion(QWidget *parent = nullptr);

    void actualizarInformacion(Goku* goku, int nivelActual);
    void iniciarTiempo();
    void pausarTiempo();
    void reiniciarTiempo();
    int getTiempoRestante() const;

private slots:
    void actualizarTiempo();

signals:
    void tiempoAgotado();

private:
    void configurarEstilo();
    QString formatearTiempo(int segundos);

    // Labels de información
    QLabel* labelTitulo;
    QLabel* labelTiempo;
    QLabel* labelNivel;
    QLabel* labelVidas;
    QLabel* labelEsferas;
    QLabel* labelTiros;

    QVBoxLayout* layout;

    // Timer y tiempo
    QTimer* timerTiempo;
    int tiempoRestante; // en segundos (3 minutos = 180 segundos)
    static const int TIEMPO_NIVEL = 180; // 3 minutos por nivel
};

#endif // PANELINFORMACION_H
