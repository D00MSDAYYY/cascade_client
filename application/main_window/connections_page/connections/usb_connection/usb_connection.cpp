#include "usb_connection.hpp"

usb_connection::usb_connection( const std::string&	name,
								scripting::engine::ptr ngn_ptr,
								quint16				vendorId,
								quint16				productId,
								QObject*			parent )
	: connection( name, ngn_ptr, parent )
	, m_vendorId( vendorId )
	, m_productId( productId )
	, m_connected( false )
{
}

usb_connection::~usb_connection() { disconnect_device(); }

bool
usb_connection::connect_device()
{
	m_connected = true; // Заглушка
	emit connection_status_changed( true );
	return true;
}

void
usb_connection::disconnect_device()
{
	// В реальном проекте здесь должно быть отключение USB устройства
	m_connected = false;
	emit connection_status_changed( false );
}

bool
usb_connection::is_connected() const
{
	return m_connected;
}

bool
usb_connection::send_data( const QByteArray& data )
{
	if ( !is_connected() )
		{
			emit error_occurred( "USB device is not connected" );
			return false;
		}

	// В реальном проекте здесь должна быть отправка данных через USB
	return true;
}

quint16
usb_connection::vendorId() const
{
	return m_vendorId;
}

quint16
usb_connection::productId() const
{
	return m_productId;
}
