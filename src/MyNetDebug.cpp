/**********************************************************************************************
 * MyNetDebug - Version 1.0.0
 * by Marcelo Aquino <marceloaqno@gmail.com> https://github.com/marceloaqno
 *
 * This code is licensed under the MIT License
 **********************************************************************************************/

#include "MyNetDebug.h"
#ifdef ARDUINO_ARCH_ESP8266
#include <ESP8266WiFi.h>
static WiFiServer _server(MYNETDEBUG_PORT);
static WiFiClient _client;
#else
#include <Ethernet.h>
EthernetServer _server(MYNETDEBUG_PORT);
EthernetClient _client;
#endif

// Declare a single default instance
MyNetDebug NetDebug = MyNetDebug();

MyNetDebug::MyNetDebug() : _echo(false), _crBeforeLF(false), _mstream(NULL)
{
}

void MyNetDebug::begin()
{
	_server.begin();
#ifdef ARDUINO_ARCH_ESP8266
	_server.setNoDelay(true);
#endif
}

void MyNetDebug::begin(unsigned long baud, uint8_t config, uint8_t mode, uint8_t tx_pin)
{
	(void)baud;
	(void)config;
	(void)mode;
	(void)tx_pin;
	begin();
}

int MyNetDebug::available()
{
#ifdef ARDUINO_ARCH_ESP8266
	if (_server.hasClient()) {
		_client.stop();
		_client = _server.available();
		_client.write("Hi!\r\n");
	}
#else
	EthernetClient client = _server.available();
	if (client) {
		_client.stop();
		_client = client;
	}
#endif
	if (_echo) {
		while (_client.available()) {
			_client.write(_client.read());
		}
	} else {
		if (_client.available()) {
			return 1;
		}
	}
	return 0;
}

int MyNetDebug::read()
{
	return _client.read();
}

size_t MyNetDebug::write(uint8_t b)
{
	if (_client.connected()) {
		if (_crBeforeLF && b == '\n') {
			_client.write('\r');
			if (_mstream) {
				_mstream->write('\r');
			}
		}
		if (_mstream) {
			_mstream->write(b);
		}
		return _client.write(b);
	} else if (_mstream) {
		if (_crBeforeLF && b == '\n') {
			_mstream->write('\r');
		}
		return _mstream->write(b);
	}
	return 0;
}

int MyNetDebug::peek()
{
	return _client.peek();
}

void MyNetDebug::flush()
{
	_client.flush();
}

void MyNetDebug::end()
{
	_client.stop();
#ifdef ARDUINO_ARCH_ESP8266
	_server.close();
#endif
}

void MyNetDebug::setDebugOutput(bool en)
{
	(void)en;
}

void MyNetDebug::echo(bool en)
{
	_echo = en;
}

void MyNetDebug::crBeforeLF(bool en)
{
	_crBeforeLF = en;
}

void MyNetDebug::mirror(Stream *mirror)
{
	_mstream = mirror;
}
