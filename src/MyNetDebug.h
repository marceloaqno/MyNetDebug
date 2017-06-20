/**********************************************************************************************
 * MyNetDebug - Version 1.0.0
 * by Marcelo Aquino <marceloaqno@gmail.com> https://github.com/marceloaqno
 *
 * This code is licensed under the MIT License
 **********************************************************************************************/

#ifndef MyNetDebug_h
#define MyNetDebug_h

#include <inttypes.h>
#include <Stream.h>

#define MYNETDEBUG_PORT 2300 // @brief port to listen to.

/**
 * @brief A class equivalent to Serial in Arduino but outputs to a TCP connection.
 *
 * Supports only one client at a time.
 */
class MyNetDebug : public Stream
{

public:
	/**
	 * @brief MyNetDebug constructor.
	 */
	MyNetDebug();
	/**
	* @brief Begin the server.
	*/
	void begin();
	/**
	 * @brief Compatibility function.
	 *
	 * @param baud Ignored parameter.
	 */
	void begin(unsigned long baud)
	{
		begin(baud, 0, 0, 0);
	}
	/**
	 * @brief Compatibility function.
	 *
	 * @param baud Ignored parameter.
	 * @param config Ignored parameter.
	 */
	void begin(unsigned long baud, uint8_t config)
	{
		begin(baud, config, 0, 0);
	}
	/**
	 * @brief Compatibility function.
	 *
	 * @param baud Ignored parameter.
	 * @param config Ignored parameter.
	 * @param mode Ignored parameter.
	 */
	void begin(unsigned long baud, uint8_t config, uint8_t mode)
	{
		begin(baud, config, mode, 0);
	}
	/**
	 * @brief Compatibility function.
	 *
	 * @param baud Ignored parameter.
	 * @param config Ignored parameter.
	 * @param mode Ignored parameter.
	 * @param tx_pin Ignored parameter.
	 */
	void begin(unsigned long baud, uint8_t config, uint8_t mode, uint8_t tx_pin);
	/**
	 * @brief Writes a single byte.
	 *
	 * @param b byte to write.
	 * @return -1 if error else, number of bytes written.
	 */
	size_t write(uint8_t b);
	/**
	 * @brief Writes an unsigned long type.
	 *
	 * @param b byte to write.
	 * @return -1 if error else, number of bytes written.
	 */
	inline size_t write(unsigned long n)
	{
		return write((uint8_t) n);
	}
	/**
	 * @brief Writes a long type.
	 *
	 * @param b byte to write.
	 * @return -1 if error else, number of bytes written.
	 */
	inline size_t write(long n)
	{
		return write((uint8_t) n);
	}
	/**
	 * @brief Writes an unsigned int type.
	 *
	 * @param b byte to write.
	 * @return -1 if error else, number of bytes written.
	 */
	inline size_t write(unsigned int n)
	{
		return write((uint8_t) n);
	}
	/**
	 * @brief Writes an int type.
	 *
	 * @param b byte to write.
	 * @return -1 if error else, number of bytes written.
	 */
	inline size_t write(int n)
	{
		return write((uint8_t) n);
	}
	using Print::write; // pull in write(str) and write(buf, size) from Print
	/**
	* @brief Get the number of bytes available sent by the network client.
	*
	* @return number of bytes available to read.
	*/
	int available();
	/**
	 * @brief Reads a byte sent by the network client.
	 *
	 * @return first byte of incoming network data available.
	 */
	int read();
	/**
	* @brief Returns the next byte from the network client buffer.
	*
	* Returns the next byte (character) of incoming client network data without removing it from
	* the internal client buffer.
	*
	* @return -1 if no data else character in the buffer.
	*/
	int peek();
	/**
	* @brief Waits until all network outgoing characters in client buffer have been sent.
	*/
	void flush();
	/**
	* @brief Stops client and network server.
	*/
	void end();
	/**
	* @brief Compatibility function.
	*
	* @param en Ignored parameter.
	*/
	void setDebugOutput(bool en);
	/**
	* @brief Echo all data sent by the debug client.
	*
	* @param en true to enable, false to disable.
	*/
	void echo(bool en);
	/**
	* @brief Send a carriage return before each line feed.
	*
	* @param en true to enable, false to disable.
	*/
	void crBeforeLF(bool en);
	/**
	* @brief Data sent to the MyNetDebug object will also be written to the mirror stream.
	*
	* Useful in cases where you also want the data to be written in another stream, eg the 
	* Arduino Serial class.
	*
	* @param stream A stream pointer.
	*/
	void mirror(Stream *mirror);

private:
	bool _echo;	// @brief flag for echo functionality.
	bool _crBeforeLF; // @brief flag for CR before LF functionality.
	Stream *_mstream; // @brief mirror stream.
};

extern MyNetDebug NetDebug;

#endif
