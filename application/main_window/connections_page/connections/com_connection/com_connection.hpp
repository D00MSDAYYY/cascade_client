#pragma once

#include "connection.hpp"

#include <QSerialPort>
#include <QSerialPortInfo>

class com_connection : public connection
{
	Q_OBJECT

public:
	explicit com_connection( const std::string&	 name,
							 script::engine::ptr ngn_ptr,
							 const QString&		 portName,
							 qint32				 baudRate	= QSerialPort::Baud9600,
							 QSerialPort::DataBits dataBits = QSerialPort::Data8,
							 QSerialPort::Parity parity		= QSerialPort::NoParity,
							 QSerialPort::StopBits stopBits = QSerialPort::OneStop,
							 QSerialPort::FlowControl flowControl
							 = QSerialPort::NoFlowControl,
							 QObject* parent = nullptr );
	~com_connection() ;

	bool
	connect_device() override;
	void
	disconnect_device() override;
	bool
	is_connected() const override;
	bool
	send_data( const QByteArray& data ) override;

	QString
	port_name() const;
	QStringList
	available_ports() const;

private slots:
	void
	on_ready_read();
	void
	handleError( QSerialPort::SerialPortError error );

private:
	QSerialPort*			 m_serialPort;
	QString					 m_portName;
	qint32					 m_baudRate;
	QSerialPort::DataBits	 m_dataBits;
	QSerialPort::Parity		 m_parity;
	QSerialPort::StopBits	 m_stopBits;
	QSerialPort::FlowControl m_flowControl;
};

