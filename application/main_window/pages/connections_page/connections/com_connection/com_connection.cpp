#include "com_connection.hpp"

com_connection::com_connection( const std::string&		 name,
								scripting::engine::ptr		 ngn_ptr,
								const QString&			 portName,
								qint32					 baudRate,
								QSerialPort::DataBits	 dataBits,
								QSerialPort::Parity		 parity,
								QSerialPort::StopBits	 stopBits,
								QSerialPort::FlowControl flowControl,
								QObject*				 parent )
	: connection( name, ngn_ptr, parent )
	, m_portName( portName )
	, m_baudRate( baudRate )
	, m_dataBits( dataBits )
	, m_parity( parity )
	, m_stopBits( stopBits )
	, m_flowControl( flowControl )
{
	m_serialPort = new QSerialPort( this );
	connect( m_serialPort, &QSerialPort::readyRead, this, &com_connection::on_ready_read );
	connect( m_serialPort,
			 &QSerialPort::errorOccurred,
			 this,
			 &com_connection::handleError );
}

com_connection::~com_connection() { disconnect_device(); }

bool
com_connection::connect_device()
{
	if ( is_connected() ) { return true; }

	m_serialPort->setPortName( m_portName );
	m_serialPort->setBaudRate( m_baudRate );
	m_serialPort->setDataBits( m_dataBits );
	m_serialPort->setParity( m_parity );
	m_serialPort->setStopBits( m_stopBits );
	m_serialPort->setFlowControl( m_flowControl );

	if ( m_serialPort->open( QIODevice::ReadWrite ) )
		{
			emit connection_status_changed( true );
			return true;
		}

	emit error_occurred( m_serialPort->errorString() );
	return false;
}

void
com_connection::disconnect_device()
{
	if ( m_serialPort->isOpen() )
		{
			m_serialPort->close();
			emit connection_status_changed( false );
		}
}

bool
com_connection::is_connected() const
{
	return m_serialPort->isOpen();
}

bool
com_connection::send_data( const QByteArray& data )
{
	if ( !is_connected() )
		{
			emit error_occurred( "Device is not connected" );
			return false;
		}

	qint64 bytesWritten = m_serialPort->write( data );
	if ( bytesWritten == -1 )
		{
			emit error_occurred( m_serialPort->errorString() );
			return false;
		}

	return m_serialPort->waitForBytesWritten( 1'000 );
}

QString
com_connection::port_name() const
{
	return m_portName;
}

QStringList
com_connection::available_ports() const
{
	QStringList ports;
	for ( const QSerialPortInfo& info : QSerialPortInfo::availablePorts() )
		{
			ports.append( info.portName() );
		}
	return ports;
}

void
com_connection::on_ready_read()
{
	QByteArray data = m_serialPort->readAll();
	while ( m_serialPort->waitForReadyRead( 10 ) ) { data += m_serialPort->readAll(); }
	emit data_received( data );
}

void
com_connection::handleError( QSerialPort::SerialPortError error )
{
	if ( error == QSerialPort::NoError ) { return; }

	emit error_occurred( m_serialPort->errorString() );

	if ( error == QSerialPort::ResourceError ) { disconnect_device(); }
}
