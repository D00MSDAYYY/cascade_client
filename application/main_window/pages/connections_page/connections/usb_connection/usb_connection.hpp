#pragma once

#include "connection.hpp"

#include <QObject>

class usb_connection : public connection
{
	Q_OBJECT

public:
	explicit usb_connection( const std::string&	 name,
							 scripting::engine::ptr ngn_ptr,
							 quint16			 vendorId,
							 quint16			 productId,
							 QObject*			 parent = nullptr );
	~usb_connection() override;

	bool
	connect_device() override;
	void
	disconnect_device() override;
	bool
	is_connected() const override;
	bool
	send_data( const QByteArray& data ) override;

	quint16
	vendorId() const;
	quint16
	productId() const;

private:
	quint16 m_vendorId;
	quint16 m_productId;
	bool	m_connected;
	// Здесь должен быть указатель на конкретную реализацию USB
};

