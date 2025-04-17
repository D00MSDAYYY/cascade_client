#include "tcp_connection.hpp"

tcp_connection::tcp_connection( const std::string&	name,
								scripting::engine::ptr ngn_ptr,
								const QString&		hostAddress,
								quint16				port,
								QObject*			parent )
	: connection( name, ngn_ptr, parent )
	, m_hostAddress( hostAddress )
	, m_port( port )
{
	m_socket = new QTcpSocket( this );
	connect( m_socket, &QTcpSocket::readyRead, this, &tcp_connection::on_ready_read );
	connect( m_socket,
			 &QTcpSocket::stateChanged,
			 this,
			 &tcp_connection::on_socket_state_changed );

	connect( m_socket,
			 &QTcpSocket::errorOccurred,
			 this,
			 &tcp_connection::on_socket_error );

	self_register();
}

tcp_connection::~tcp_connection() { disconnect_device(); }

bool
tcp_connection::connect_device()
{
	if ( is_connected() ) { return true; }

	m_socket->connectToHost( m_hostAddress, m_port );
	if ( !m_socket->waitForConnected( 3'000 ) )
		{
			emit error_occurred( m_socket->errorString() );
			return false;
		}

	return true;
}

void
tcp_connection::disconnect_device()
{
	if ( m_socket->state() != QAbstractSocket::UnconnectedState )
		{
			m_socket->disconnectFromHost();
			if ( m_socket->state() != QAbstractSocket::UnconnectedState )
				{
					m_socket->waitForDisconnected( 1'000 );
				}
		}
}

bool
tcp_connection::is_connected() const
{
	return m_socket->state() == QAbstractSocket::ConnectedState;
}

bool
tcp_connection::send_data( const QByteArray& data )
{
	if ( !is_connected() )
		{
			emit error_occurred( "Device is not connected" );
			return false;
		}

	qint64 bytesWritten = m_socket->write( data );
	if ( bytesWritten == -1 )
		{
			emit error_occurred( m_socket->errorString() );
			return false;
		}

	return m_socket->waitForBytesWritten( 1'000 );
}

QString
tcp_connection::hostAddress() const
{
	return m_hostAddress;
}

quint16
tcp_connection::port() const
{
	return m_port;
}

void
tcp_connection::self_register()
{
	if ( can_self_register() )
		{
			auto type
				= _ngn_ptr->new_usertype< tcp_connection >( class_name(),
															sol::base_classes,
															sol::bases< connection >() );

			type [ "connect" ]		= &tcp_connection::connect_device;
			type [ "disconnect" ]	= &tcp_connection::disconnect_device;
			type [ "is_connected" ] = &tcp_connection::is_connected;
			type [ "send" ] = []( tcp_connection* self, const std::string& data ) {
				return self->send_data(QByteArray::fromStdString( data ) );
			};

			type [ "host" ] = &tcp_connection::hostAddress;
			type [ "port" ] = &tcp_connection::port;

			type [ "on_data_received" ]
				= []( tcp_connection* self, sol::function callback ) {
					  QObject::connect( self,
										&tcp_connection::data_received,
										[ callback ]( const QByteArray& data ) mutable {
											callback( data.toStdString() );
										} );
				  };

			type [ "on_connection_changed" ]
				= []( tcp_connection* self, sol::function callback ) {
					  QObject::connect( self,
										&tcp_connection::connection_status_changed,
										[ callback ]( bool connected ) mutable {
											callback( connected );
										} );
				  };

			type [ "on_error" ] = []( tcp_connection* self, sol::function callback ) {
				QObject::connect( self,
								  &tcp_connection::error_occurred,
								  [ callback ]( const QString& error ) mutable {
									  callback( error.toStdString() );
								  } );
			};
		}
}

void
tcp_connection::on_ready_read()
{
	QByteArray data = m_socket->readAll();
	while ( m_socket->waitForReadyRead( 10 ) ) { data += m_socket->readAll(); }
	emit data_received( data );
}

void
tcp_connection::on_socket_state_changed( QAbstractSocket::SocketState state )
{
	if ( state == QAbstractSocket::ConnectedState )
		{
			emit connection_status_changed( true );
		}
	else if ( state == QAbstractSocket::UnconnectedState )
		{
			emit connection_status_changed( false );
		}
}

void
tcp_connection::on_socket_error( QAbstractSocket::SocketError error )
{
	Q_UNUSED( error )
	emit error_occurred( m_socket->errorString() );
}
