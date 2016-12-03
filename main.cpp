#include "mbed.h"

DigitalOut led1(LED1);
InterruptIn sw1(p18);

// イベントキューを作成する
EventQueue queue;

// LEDのON/OFFを切り替える関数
void toggle_led() {
    led1 = !led1;
}

// タクトスイッチが押されたときに実行される関数
void pushed() {
    // 即実行されるイベント
    queue.call(&toggle_led);
    // 2000ms後に実行されるイベント
    queue.call_in(2000, &toggle_led);
}

int main() {
    // スイッチピンをPullUpにする
    sw1.mode(PullUp);

    // タクトスイッチが押されたときの割り込み処理
    sw1.fall(&pushed);

    // 1000msごとに定期実行するイベント
    queue.call_every(1000, &toggle_led);

    // イベントループが廻り続ける
    queue.dispatch();
}
