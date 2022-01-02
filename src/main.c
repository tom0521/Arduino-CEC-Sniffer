#include <avr/io.h>
#include <util/delay.h>

void pulse(unsigned int pulses);
void send_byte(unsigned char data);
void send_header();

void main () {
    DDRD |= _BV(DDD3);
    PORTD |= ~_BV(PORTD3);

    // TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
    // TCCR2B = _BV(WGM22) | _BV(CS21);

    // OCR2A = 51;
    // OCR2B = 17;
    // TCCR2A ^= _BV(COM2B1);

    send_header();
    send_byte(0x03);
    send_byte(0x17);
    pulse(20);
    _delay_ms(20.82);
    send_byte(0x03);
    send_byte(0x17);
    pulse(20);
    _delay_ms(20.82);
}

void pulse(unsigned int pulses) {
    for (int i = 0; i < pulses; ++i) {
        // Set the output
        PORTD |= _BV(PORTD3);
        _delay_us(8.79);
        // Reset the output
        PORTD &= ~_BV(PORTD3);
        _delay_us(17.6);
    }
}

void send_byte(unsigned char data) {
    for (int i = 0; i < 8; ++i) {
        pulse(20);
        if (0x01 & data)
            _delay_us(1583);
        else
            _delay_us(528);
        data >>= 1;
    }
}

void send_header () {
    pulse(320);
    _delay_us(4220);
}
