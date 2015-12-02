// ArduinoCompat/HardwareSerial.cpp
//
// Author: mikem@airspayce.com

#include "HardwareSerial.h"

///////////////////////////////////////////////////////////////
// RingBuffer
///////////////////////////////////////////////////////////////

RingBuffer::RingBuffer()
        : _head(0),
                _tail(0),
                _overruns(0),
                _underruns(0)
{
}

bool RingBuffer::isEmpty()
{
    return _head == _tail;
}

bool RingBuffer::isFull()
{
    return ((_head + 1) % ARDUINO_RINGBUFFER_SIZE) == _tail;
}

bool RingBuffer::write(uint8_t ch)
{
    if (isFull())
    {
        _overruns++;
        return false;
    }
    _buffer[_head] = ch;
    if (++_head >= ARDUINO_RINGBUFFER_SIZE)
        _head = 0;
    return true;
}

uint8_t RingBuffer::read()
{
    if (isEmpty())
    {
        _underruns++;
        return 0;        // What else can we do?
    }
    uint8_t ret = _buffer[_tail];
    if (++_tail >= ARDUINO_RINGBUFFER_SIZE)
        _tail = 0;
    return ret;
}

///////////////////////////////////////////////////////////////
// HardwareSerial
///////////////////////////////////////////////////////////////

// On STM32F4 Discovery, USART 1 is not very useful conflicts with the Green lED
//HardwareSerial::HardwareSerial(USART_TypeDef* usart)
HardwareSerial::HardwareSerial()
//        : _usart(usart)
{
}

void HardwareSerial::begin(unsigned long baud)
{
}

void HardwareSerial::end()
{
}

int HardwareSerial::available(void)
{
    return !_rxRingBuffer.isEmpty();
}

int HardwareSerial::read(void)
{
    return _rxRingBuffer.read();
}

size_t HardwareSerial::write(uint8_t ch)
{
    return 1;
}

extern "C"
{
void USART1_IRQHandler(void)
{
}
void USART2_IRQHandler(void)
{
}
void USART3_IRQHandler(void)
{
}
void UART4_IRQHandler(void)
{
}
void UART5_IRQHandler(void)
{
}
void USART6_IRQHandler(void)
{
}
}

