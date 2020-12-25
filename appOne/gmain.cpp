#if 0
#include"libOne.h"
#include<time.h>
void gmain() {
    window(1920, 1080, full);
    float second = 0, minute=0, hour=0;
    float cx = width / 2;
    float cy = height / 2;
    float x, y, deg = 0;
    float len = 400;
    angleMode(DEGREES);
    colorMode(HSV);
    float hue = 0;
    while (notQuit) {
        hue = map(mouseX, 0, width, 0, 360);
        if (!isPress(KEY_SPACE)) {
            time_t curTime = time(NULL);
            struct tm local;
            localtime_s(&local, &curTime);
            second = local.tm_sec;
            minute = local.tm_min;
            hour = local.tm_hour;
        }
        else {
            second += 10;
            if (second >= 60) { second = 0; minute += 1; }
            if (minute >= 60) { minute = 0; hour += 1; }
        }
        clear(50);
        //â~î’
        fill(hue,50,255);
        stroke(hue, 200, 255);
        strokeWeight(80);
        circle(cx, cy, (len+100) * 2 );
        //éûêj
        deg = 30 * hour + 30 * minute / 60;
        x = cx + sin(deg) * len * 0.7f;
        y = cy - cos(deg) * len * 0.7f;
        stroke(hue, 200, 255);
        strokeWeight(25);
        line(cx, cy, x, y);
        //ï™êj
        deg = 6 * minute + 6 * second / 60;
        x = cx + sin(deg) * len;
        y = cy - cos(deg) * len;
        stroke(hue, 128, 255);
        strokeWeight(20);
        line(cx, cy, x, y);
        //ïbêj
        deg = 6 * second;
        x = cx + sin(deg) * len;
        y = cy - cos(deg) * len;
        stroke(hue, 128, 128);
        strokeWeight(5);
        line(cx, cy, x, y);
    }
}

















#else
#include"libOne.h"
#include<time.h>
//ïbêjÅAï™êjÅAéûêjÇÃÉfÅ[É^ÅiâpåÍÇ≈êjÇÕhandÅj
struct HAND {
    float deg, len, satulation, value, weight;
};
//éûåvÉfÅ[É^
struct CLOCK {
    float cx=0, cy=0, scale=1, hue=0;
    int hour=0, minute=0, second=0;
    struct HAND hourHand   = { 0, 280, 200,  255, 30 };
    struct HAND minuteHand = { 0, 400, 100,  255, 20 };
    struct HAND secondHand = { 0, 400, 255,  128,  5 };
};
//åªç›éûçèÇÉfÅ[É^Ç…ÉZÉbÉgÇ∑ÇÈ
void setTime(struct CLOCK& c) {
    if (!isPress(KEY_SPACE)) {
        //éûÅAï™ÅAïbÇéÊìæ
        time_t curTime= time(NULL);//åªç›éûçèÇéÊìæ
        struct tm local;
        localtime_s(&local, &curTime);//ÉçÅ[ÉJÉãéûçèÇ…
        c.hour = local.tm_hour;
        c.minute = local.tm_min;
        c.second = local.tm_sec;
    }
    else {
        //ÉXÉyÅ[ÉXÇâüÇ∑Ç∆êjÇ™ë¨Ç≠ìÆÇ≠
        c.second += 5;
        if (c.second >= 60) {
            c.second = 0;
            c.minute += 1;
        }
        if (c.minute >= 60) {
            c.minute = 0;
            c.hour += 1;
        }
        if (c.hour >= 24) {
            c.hour = 0;
        }
    }
}
//êjÇÃï`âÊ
void draw(const struct CLOCK& c, const struct HAND& h) {
    strokeWeight(h.weight * c.scale);
    stroke(c.hue, h.satulation, h.value);
    float x = c.cx + sin(h.deg) * h.len * c.scale;
    float y = c.cy - cos(h.deg) * h.len * c.scale;
    line(c.cx, c.cy, x, y);
}
//éûåvÇÃï`âÊ
void draw(struct CLOCK& c) {
    //â~
    fill(c.hue, 30, 255);
    stroke(c.hue, 200, 255);
    strokeWeight(60 * c.scale);
    circle(c.cx, c.cy, 500 * 2 * c.scale);
    //ï™
    c.minuteHand.deg = (c.minute * 6) + 6 * (c.second / 60.0f);
    draw(c, c.minuteHand);
    //éû
    c.hourHand.deg = (c.hour * 30) + 30 * (c.minute / 60.0f);
    draw(c, c.hourHand);
    //ïb
    c.secondHand.deg = c.second * 6;
    draw(c, c.secondHand);
    //ïbêjÇÃóv
    strokeWeight(30 * c.scale);
    point(c.cx, c.cy);
}

void gmain() {
    window(1920, 1080, full);
    angleMode(DEGREES);
    colorMode(HSV);
    int rows = 1;
    int cols = 1;
    float distX = width / 2;
    float distY = height / 2;
    struct CLOCK clock;
    while (notQuit) {
        if (isTrigger(KEY_D) || isTrigger(KEY_A) ||
            isTrigger(KEY_W) || isTrigger(KEY_S)) {
            if (isTrigger(KEY_D))cols++;
            if (isTrigger(KEY_A) && cols > 1)cols--;
            if (isTrigger(KEY_W))rows++;
            if (isTrigger(KEY_S) && rows > 1)rows--;
            distY = height / (rows + 1);
            distX = width / (cols + 1);
            clock.scale = (distY < distX ? distY : distX) / 1080;
        }
        setTime(clock);
        clear(55);
        for (int j = 0; j < rows; j++) {
            clock.cy = distY * (j+1);
            for (int i = 0; i < cols; i++) {
                clock.cx = distX * (i+1);
                clock.hue = 360.0f / (cols*rows) * (j*cols+i);
                draw(clock);
            }
        }
    }
}
#endif