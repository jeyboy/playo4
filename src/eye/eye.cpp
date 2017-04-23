#include "eye.h"

#include <qmath.h>
#include <qpainter.h>
#include <qdebug.h>


//# для дуги
//tc = @start + (@end - @start) * t
//x = @center.x + Math.cos(tс) * @radius
//y = @center.y + Math.sin(tс) * @radius

//# для отрезка
//x = @start.x + (@end.x - @start.x) * t
//y = @start.y + (@end.y - @start.y) * t

//    var step = 2 * M_PI / 20;  // see note 1
//        var h = 150;
//        var k = 150;
//        var r = 50;

//        ctx.beginPath();  //tell canvas to start a set of lines

//        for(var theta=0;  theta < 2*Math.PI;  theta+=step)
//         { var x = h + r*Math.cos(theta);
//           var y = k - r*Math.sin(theta);    //note 2.
//           ctx.lineTo(x,y);
//         }

//    int distancex = ep.x() - sp.x();
//    distancex *= distancex;

//    int distancey = (ep.y() - sp.y());
//    distancey *= distancey;

//    double distance = sqrt(distancex - distancey);

QPoint Eye::cursorPos() {
    QPoint point = QCursor::pos();
    return mapFromGlobal(point);
}

void Eye::addOpenedLashes(const QRectF & r, const float & angle, const QPolygonF & poly) {
    float new_angle = angle - 270;
    QPair<QPointF, QPointF> points = arcBorderPoints(
        opened.eye_rect,
        EYE_ANGLE_FACTOR * new_angle,
        -EYE_ANGLE_FACTOR * angle * 2
    );

    QPair<QPointF, QPointF> cpoints = arcBorderPoints(opened.eye_rect, 90 * EYE_ANGLE_FACTOR, 0);

    new_angle = qRadiansToDegrees(qAtan2(cpoints.first.y() - points.first.y(), cpoints.first.x() - points.first.x())) - 10;

    opened.polygons
        << rotate(r, -new_angle, points.second - cpoints.first, poly)
        << rotate(r, new_angle, points.first - cpoints.first, poly);
}

QPolygonF Eye::rotate(const QRectF & r, const float & angle, const QPointF & offset, const QPolygonF & poly) {
    float s = qSin(qDegreesToRadians(angle));
    float c = qCos(qDegreesToRadians(angle));

    QPointF center = r.center();
    QPointF coffset = center + offset;
    QPolygonF res;

  // translate point back to origin:
    for(QPolygonF::ConstIterator point = poly.cbegin(); point != poly.cend(); point++) {
        QPointF p = (*point) - center;

  // rotate point
        float xnew = p.x() * c - p.y() * s;
        float ynew = p.x() * s + p.y() * c;

  // translate point back:
        res << (coffset + QPointF(xnew, ynew));
    }

    return res;
}

QPair<QPointF, QPointF> Eye::arcBorderPoints(const QRectF & r, int a, int alen) {
    QPointF center = r.center();

    int rx = r.width() / 2;
    int ry = r.height() / 2;

    double da = qDegreesToRadians(a == 0 ? a : (a / EYE_ANGLE_FACTOR));
    double dalen = qDegreesToRadians(alen == 0 ? 1 : ((a + alen) / EYE_ANGLE_FACTOR));

    QPointF sp(
        center.x() + rx * qCos(da),
        center.y() - ry * qSin(da)
    );

    QPointF ep(
        center.x() + rx * qCos(dalen),
        center.y() - ry * qSin(dalen)
    );

    return QPair<QPointF, QPointF>(sp, ep);
}

void Eye::arcPoints(QPolygonF & points, const QRectF & r, float a, float alen, int steps_amount) {
    QPointF center = r.center();

    int rx = r.width() / 2;
    int ry = r.height() / 2;

    double da = qDegreesToRadians(a);
    double dalen = qDegreesToRadians(a + alen);
    float step = (dalen - da) / (alen < 25 ? steps_amount : (steps_amount * (alen / 25)));

    for(float theta = da; da < dalen ? theta < dalen : theta > dalen; theta += step) {
        float x = center.x() + rx * qCos(theta);
        float y = center.y() - ry * qSin(theta);

        points << QPointF(x, y);
    }
}

void Eye::arcOpenedPoints(QHash<int, int> & points, const QRectF & r, float alen, int steps_amount) {
    QPointF center = r.center();

    int rx = r.width() / 2;
    int ry = r.height() / 2;

    double da = qDegreesToRadians(90.0);
    double dalen = qDegreesToRadians(90 + alen);
    float step = (dalen - da) / (alen < 25 ? steps_amount : (steps_amount * (alen / 25)));

    float base_x = center.x() + rx * qCos(da);
    float base_y = center.y() - ry * qSin(da);
    float border_offset = pupil_border / 2 + 2;

    points.insert(0, base_y);

    for(float theta = da; da < dalen ? theta < dalen : theta > dalen; theta += step) {
        float x = center.x() + rx * qCos(theta);
        float y = center.y() - ry * qSin(theta);

        float y_offset = y - base_y + border_offset;

        points.insert(x, y_offset);
        points.insert(base_x + (base_x - x), y_offset);
    }

    QPolygonF pupil_arc_points;
    arcPoints(pupil_arc_points, opened.pupil_rect, 90, -90, opened.pupil_rect.width() / 2);
    pupil_arc_points.translate(0, base_y - opened.pupil_rect.top() + points[base_x]);

    for(int x = base_x, sum = 0; ; x++) {
        if (!points.contains(x))
            break;

        float max_over = 0;

        for(QPolygonF::Iterator pp = pupil_arc_points.begin(); pp != pupil_arc_points.end(); pp++) {
            int px = (*pp).x();

            if (points.contains(px)) {
                float ppy = (*pp).y() - base_y;

                if(ppy <= points[px])
                    max_over = qMax(max_over, points[(*pp).x()] - ppy);
            }
        }

        sum += qRound(max_over);
        points[x] += sum;
        points[base_x + (base_x - x)] += sum;

        pupil_arc_points.translate(1, points[x] - points[x - 1]);
    }
}

QPolygonF Eye::arcPoints(const QPointF & sp, const QPointF & ep, bool left, bool revert) {
    QPolygonF points;

    int offset = 11;

    QRectF r;

    if (revert) {
        r = left ?
                QRectF(
                    QPointF(ep.x() - offset, sp.y() - offset),
                    QPointF(sp.x(), ep.y())
                )
                 :
                QRectF(
                    QPointF(ep.x(), ep.y() - offset),
                    QPointF(sp.x() + offset, sp.y())
                );
    } else {
        r = left ?
            QRectF(
                QPointF(sp.x() - offset, sp.y()),
                QPointF(ep.x(), ep.y() + offset)
            )
             :
            QRectF(
                QPointF(ep.x(), sp.y()),
                QPointF(sp.x() + offset, ep.y() + offset)
            );
    }

    QPointF center = r.center();

    int rx = r.width() / 2;
    int ry = r.height() / 2;

    int limit = 20;
    float step = 2 * M_PI / limit;
    float theta = left ? 0 : (M_PI + (revert ? M_1_PI : 0));

    for(int i = 0; i < limit; i++, theta += step) {
        float x = center.x() + rx * qCos(theta);
        float y = center.y() - ry * qSin(theta);

        if (
            (revert && ((left && x >= ep.x() && y >= sp.y()) || (!left && x <= sp.x() && y >= ep.y()))) ||
            (!revert && ((left && x >= sp.x() && y <= ep.y()) || (!left && x <= sp.x() && y <= ep.y())))
        ) continue;

        points << QPointF(x, y);
    }

    return points;
}

QPolygonF Eye::ellipsePoints(const QRectF & r) {
    QPolygonF points;

    QPointF center = r.center();

    int rx = r.width() / 2;
    int ry = r.height() / 2;

    int limit = 20;
    float step = 2 * M_PI / limit;
    float theta = left ? 0 : M_PI;

    for(int i = 0; i <= limit; i++, theta += step) {
        float x = center.x() + rx * qCos(theta);
        float y = center.y() - ry * qSin(theta);

        points << QPointF(x, y);
    }

    return points;
}

void Eye::updateEye() {
    QPoint point = cursorPos();

    QPointF rel_point = point - s;
    float pupil_half = pupil_size / 2;

    float px = point.x();
    float py = point.y();

    float rel_x = rel_point.x();
    float rel_y = rel_point.y();

    float left_pos, top_pos;

    if (rel_x == 0) {
        left_pos = px - pupil_half;
    } else if (rel_x > 0) {
        if (opened.pupil_zone_rect.right() - px < pupil_half)
            left_pos = opened.pupil_zone_rect.right() - pupil_size;
        else
            left_pos = px - pupil_half;
    } else {
        if (px - opened.pupil_zone_rect.left() < pupil_half)
            left_pos = opened.pupil_zone_rect.left();
        else
            left_pos = px - pupil_half;
    }

    opened.pupil_rect.moveLeft(left_pos);

    if (rel_y == 0) {
        top_pos = py - pupil_half;
    } else if (rel_y > 0) {
        if (opened.pupil_zone_rect.bottom() - py < pupil_half)
            top_pos = opened.pupil_zone_rect.bottom() - pupil_size;
        else
            top_pos = py - pupil_half;
    } else {
        if (py - opened.pupil_zone_rect.top() < pupil_half)
            top_pos = opened.pupil_zone_rect.top();
        else
            top_pos = py - pupil_half;

        float pupil_center_x = opened.pupil_rect.left() + pupil_half;
        float eye_brow_y = opened.eyebrow_pads[0] + opened.eyebrow_pads[pupil_center_x];

        if (top_pos < eye_brow_y)
            top_pos = top_pos + (eye_brow_y - top_pos);
    }

    opened.pupil_rect.moveTop(top_pos);

    QWidget::update();
}

void Eye::paintEvent(QPaintEvent * event) {
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

//    painter.setPen(QPen(QBrush(Qt::red), 3));
//    painter.drawRect(closed.eye_rect);


//    painter.setPen(QPen(QBrush(Qt::green), 3));
//    painter.drawRect(closed.eye_sub_rect);


    painter.setPen(QPen(QBrush(Qt::black), 3));

    if (state == eye_open) {
        painter.drawPolyline(opened.eyebrow_area);
    //    painter.drawArc(eye_rect, EYE_START_ANGLE_FACTOR, EYE_SPAN_ANGLE_FACTOR);
    //    painter.drawArc(eye_sub_rect, EYE_START_ANGLE_FACTOR, EYE_SPAN_ANGLE_FACTOR);

        for(QList<QPolygonF>::Iterator poly = opened.polygons.begin(); poly != opened.polygons.end(); poly++)
            painter.drawPolyline(*poly);

        painter.setPen(QPen(QBrush(Qt::darkGray), pupil_border));
        QRadialGradient radialGrad(opened.pupil_rect.center(), opened.pupil_rect.width() / 2);
        radialGrad.setColorAt(0, Qt::white);
        radialGrad.setColorAt(0.3, QColor::fromRgb(0, 90, 0));
        radialGrad.setColorAt(0.8, QColor::fromRgb(0, 50, 0));
        radialGrad.setColorAt(1, Qt::darkGray);

        painter.setBrush(radialGrad);
        painter.drawEllipse(opened.pupil_rect);
    } else {
        painter.drawPolyline(closed.eyebrow_area);

        for(QList<QPolygonF>::Iterator poly = closed.polygons.begin(); poly != closed.polygons.end(); poly++)
            painter.drawPolyline(*poly);
    }
}

void Eye::resizeEvent(QResizeEvent * e) {
    QWidget::resizeEvent(e);

    eyebrow_height = 20;
    pupil_border = 1;

    recalcOpenedCoords();
    recalcClosedCoords();
}

void Eye::mouseDoubleClickEvent(QMouseEvent * event) {
    QWidget::mouseDoubleClickEvent(event);

    if (state == eye_open)
        state = eye_close;
    else
        state = eye_open;

    QWidget::update();
}

void Eye::recalcOpenedCoords() {
    opened.polygons.clear();
    opened.eyebrow_area.clear();
    opened.eyebrow_pads.clear();

    opened.eyelashes_rect = rect();

    int rheight = opened.eyelashes_rect.height();
    int top_offset = rheight * 0.3;

    opened.eyelashes_rect.setHeight(top_offset);
    opened.eye_rect = QRectF(0, top_offset, opened.eyelashes_rect.width(), rheight - top_offset);

    opened.eye_sub_rect = QRectF(eyebrow_height, top_offset + eyebrow_height, opened.eyelashes_rect.width() - eyebrow_height * 2, rheight - top_offset - eyebrow_height);

    opened.top_eye_corners = arcBorderPoints(opened.eye_rect, EYE_START_ANGLE_FACTOR, EYE_SPAN_ANGLE_FACTOR);
    opened.bottom_eye_corners = arcBorderPoints(opened.eye_sub_rect, EYE_START_ANGLE_FACTOR, EYE_SPAN_ANGLE_FACTOR);

    QPolygonF left_poly_points = arcPoints(opened.top_eye_corners.second, opened.bottom_eye_corners.second, true);
    QPolygonF right_poly_points = arcPoints(opened.top_eye_corners.first, opened.bottom_eye_corners.first, false);

    ////////////////////////////////////////////
    opened.eyebrow_area.append(right_poly_points);
    arcPoints(opened.eyebrow_area, opened.eye_rect, EYE_START_ANGLE, EYE_SPAN_ANGLE);
    opened.eyebrow_area.append(left_poly_points);
    arcPoints(opened.eyebrow_area, opened.eye_sub_rect, EYE_START_ANGLE + EYE_SPAN_ANGLE, -EYE_SPAN_ANGLE);
    ////////////////////////////////////////////

    QSizeF lash_size = QSizeF(opened.eyelashes_rect.width() / 30, opened.eyelashes_rect.height() / 2);
    QRectF clash_rect(opened.eyelashes_rect.center() - QPointF(lash_size.width() / 2, lash_size.height() / 2), lash_size);

    QPolygonF poly = ellipsePoints(clash_rect);
    opened.polygons << poly;

    addOpenedLashes(opened.eyelashes_rect, 28, poly);
    addOpenedLashes(opened.eyelashes_rect, 60, poly);

    opened.pupil_zone_rect = QRectF(
        QPointF(
            opened.bottom_eye_corners.second.x(),
            opened.eye_sub_rect.top()
        ),
        QPointF(
            opened.bottom_eye_corners.first.x(),
            opened.eye_sub_rect.bottom()
        )
    );

    s = opened.pupil_zone_rect.center();

    float pupil_width = opened.pupil_zone_rect.width() / 1.5;
    float pupil_height = opened.pupil_zone_rect.height() / 1.5;
    pupil_size = qMin(pupil_width, pupil_height);

    float new_pupil_height = pupil_size * 1.3;
    if (new_pupil_height < opened.pupil_zone_rect.height())
        opened.pupil_zone_rect.setHeight(new_pupil_height);

    float pupil_top = opened.pupil_zone_rect.y() + opened.pupil_zone_rect.height() / 2 - pupil_size / 2;
    float pupil_left = opened.pupil_zone_rect.x() + opened.pupil_zone_rect.width() / 2 - pupil_size / 2;

    opened.pupil_rect = QRectF(pupil_left, pupil_top, pupil_size, pupil_size);

    arcOpenedPoints(opened.eyebrow_pads, opened.eye_sub_rect, 90 - EYE_START_ANGLE, opened.pupil_zone_rect.width() / 2);
}

void Eye::recalcClosedCoords() {
    closed.polygons.clear();
    closed.eyebrow_area.clear();
    closed.eyebrow_pads.clear();

    closed.eye_sub_rect = QRectF(
        QPointF(0, opened.top_eye_corners.first.y()),
        QPointF(rect().width(), opened.pupil_zone_rect.bottom())
    );

    closed.eye_rect = QRectF(
        QPointF(eyebrow_height, closed.eye_sub_rect.top() + eyebrow_height),
        QPointF(rect().width() - eyebrow_height, opened.pupil_zone_rect.bottom() - eyebrow_height)
    );

    closed.eyelashes_rect = opened.eyelashes_rect.adjusted(0, 0, 0, 0);
    closed.eyelashes_rect.moveTop(closed.eye_rect.top());

    closed.top_eye_corners = arcBorderPoints(closed.eye_sub_rect, EYE_CLOSE_START_ANGLE_FACTOR + 29 * 16, -EYE_SPAN_ANGLE_FACTOR);
    closed.bottom_eye_corners = arcBorderPoints(closed.eye_rect, EYE_CLOSE_START_ANGLE_FACTOR + 29 * 16, -EYE_SPAN_ANGLE_FACTOR);

    QPolygonF left_poly_points = arcPoints(closed.bottom_eye_corners.second, closed.top_eye_corners.second, true, true);
    QPolygonF right_poly_points = arcPoints(closed.top_eye_corners.first, closed.bottom_eye_corners.first, false, true);

    ////////////////////////////////////////////
    closed.eyebrow_area.append(right_poly_points);
    arcPoints(closed.eyebrow_area, closed.eye_rect, EYE_CLOSE_START_ANGLE, -EYE_SPAN_ANGLE);
    closed.eyebrow_area.append(left_poly_points);
    arcPoints(closed.eyebrow_area, closed.eye_sub_rect, EYE_CLOSE_START_ANGLE - EYE_SPAN_ANGLE, EYE_SPAN_ANGLE);
    closed.eyebrow_area.append(closed.eyebrow_area.first());
    ////////////////////////////////////////////

//    QSizeF lash_size = QSizeF(opened.eyelashes_rect.width() / 30, opened.eyelashes_rect.height() / 2);
//    QRectF clash_rect(opened.eyelashes_rect.center() - QPointF(lash_size.width() / 2, lash_size.height() / 2), lash_size);

//    QPolygonF poly = ellipsePoints(clash_rect);
//    opened.polygons << poly;

//    addOpenedLashes(opened.eyelashes_rect, 28, poly);
//    addOpenedLashes(opened.eyelashes_rect, 60, poly);
}
