#ifndef EYE_H
#define EYE_H

#include <qhash.h>
#include <qwidget.h>
#include <qtimer.h>

#define EYE_ANGLE_FACTOR 16.0
#define EYE_START_ANGLE 30
#define EYE_START_ANGLE_FACTOR EYE_START_ANGLE * EYE_ANGLE_FACTOR
#define EYE_SPAN_ANGLE 120
#define EYE_SPAN_ANGLE_FACTOR EYE_SPAN_ANGLE * EYE_ANGLE_FACTOR

#define EYE_CLOSE_START_ANGLE EYE_START_ANGLE - EYE_START_ANGLE * 2
#define EYE_CLOSE_START_ANGLE_FACTOR EYE_CLOSE_START_ANGLE * EYE_ANGLE_FACTOR

struct EyeCoords {
    QRectF pupil_rect;
    QRectF pupil_zone_rect;

    QRectF eye_rect;
    QRectF eye_sub_rect;
    QRectF eyelashes_rect;

    QPair<QPointF, QPointF> top_eye_corners;
    QPair<QPointF, QPointF> bottom_eye_corners;

    QList<QPolygonF> polygons;

    QPolygonF eyebrow_area;

    QHash<int, int> eyebrow_pads;
};

class Eye : public QWidget {
    Q_OBJECT

    enum EyeState {
        eye_open = 0,
        eye_close
    };

    QTimer timer;
    QTimer blink_timer;

    EyeState state;
    EyeCoords opened, closed;
    float pupil_size, eyebrow_height, pupil_border;
    float open_size;
    QPointF s;

    QPoint cursorPos();

    void addOpenedLashes(const QRectF & r, const float & angle, const QPolygonF & poly);

    QPolygonF rotate(const QRectF & r, const float & angle, const QPointF & offset, const QPolygonF & poly);
    QPair<QPointF, QPointF> arcBorderPoints(const QRectF & r, int a, int alen);
    QPolygonF arcPoints(const QPointF & sp, const QPointF & cp, bool left, bool revert = false);
    void arcPoints(QPolygonF & points, const QRectF & r, float a, float alen, int steps_amount = 20);
    void arcOpenedPoints(QHash<int, int> & points, const QRectF & r, float alen, int steps_amount = 20);
    QPolygonF ellipsePoints(const QRectF & r);
  public:
    Eye(QWidget * parent = 0) : QWidget(parent), state(eye_open), open_size(1.0) {
        connect(&timer, SIGNAL(timeout()), this, SLOT(updateEye()));
        timer.start(25);
    }

    ~Eye() {
        timer.stop();
    }

  protected:
    void paintEvent(QPaintEvent * event);
    void resizeEvent(QResizeEvent * e);
    void mouseDoubleClickEvent(QMouseEvent * event);

    void recalcOpenedCoords();
    void recalcClosedCoords();

  protected slots:
    void updateEye();
};

#endif // EYE_H
