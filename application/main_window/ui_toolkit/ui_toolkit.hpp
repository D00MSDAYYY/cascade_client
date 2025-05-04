#pragma once

#include "scripting.hpp"

#include <memory>

struct ui_toolkit
{
	CLASS_NAME_AS_STRING( ui_toolkit )
	STATIC_REGISTER_IN_LUA()

	// template < typename TYPE >
	// class ptr_lc_guard
	// {
	// public:
	// 	ptr_lc_guard( TYPE* ptr )
	// 		: _ptr{ ptr }
	// 		, _is_ownership_stolen{ nullptr }
	// 		, _ref_count_ptr{ nullptr }
	// 	{
	// 		_ref_count_ptr		 = new int{ 1 };
	// 		_is_ownership_stolen = new bool{ false };
	// 	};

	// 	ptr_lc_guard( const ptr_lc_guard& other )
	// 		: _ptr( other._ptr )
	// 		, _ref_count_ptr( other._ref_count_ptr )
	// 		, _is_ownership_stolen( other._is_ownership_stolen )
	// 	{
	// 		if ( _ref_count_ptr ) { ++( *_ref_count_ptr ); }
	// 		else
	// 			{
	// 				std::cout << "!!!in ptr_lc_guard copy constructor _ref_count_ptr is nullptr. this can't "
	// 							 "be normal"
	// 						  << std::endl;
	// 			}
	// 	}

	// 	ptr_lc_guard( ptr_lc_guard&& other ) noexcept
	// 		: _ptr( other._ptr )
	// 		, _ref_count_ptr( other._ref_count_ptr )
	// 		, _is_ownership_stolen( other._is_ownership_stolen )
	// 	{
	// 		other._ptr				   = nullptr;
	// 		other._ref_count_ptr	   = nullptr;
	// 		other._is_ownership_stolen = true;
	// 	}

	// 	ptr_lc_guard&
	// 	operator= ( const ptr_lc_guard& other )
	// 	{
	// 		if ( this != &other )
	// 			{
	// 				_release_resources(); //! don't remove it's legit

	// 				_ptr				 = other._ptr;
	// 				_ref_count_ptr		 = other._ref_count_ptr;
	// 				_is_ownership_stolen = other._is_ownership_stolen;

	// 				if ( _ref_count_ptr ) { ++( *_ref_count_ptr ); }
	// 				else
	// 					{
	// 						std::cout << "!!!in ptr_lc_guard copy assign operator _ref_count_ptr is nullptr. "
	// 									 "this can't be normal"
	// 								  << std::endl;
	// 					}
	// 			}
	// 		return *this;
	// 	}

	// 	ptr_lc_guard&
	// 	operator= ( ptr_lc_guard&& other ) noexcept
	// 	{
	// 		if ( this != &other )
	// 			{
	// 				_release_resources();

	// 				_ptr					   = other._ptr;
	// 				_ref_count_ptr			   = other._ref_count_ptr;
	// 				_is_ownership_stolen	   = other._is_ownership_stolen;

	// 				other._ptr				   = nullptr;
	// 				other._ref_count_ptr	   = nullptr;
	// 				other._is_ownership_stolen = true;
	// 			}
	// 		return *this;
	// 	}

	// 	~ptr_lc_guard() { _release_resources(); }

	// 	auto
	// 	release()
	// 	{
	//  _is_o_st = true;
	// 		return _ptr;
	// 	}


	// private:
	// 	void
	// 	_release_resources()
	// 	{
	// 		if ( not _is_ownership_stolen )
	// 			{
	// 				if ( _ref_count_ptr and *_ref_count_ptr > 0 )
	// 					{
	// 						--( *_ref_count_ptr );

	// 						if ( *_ref_count_ptr == 0 )
	// 							{
	// 								if ( _ptr ) delete _ptr;
	// 								if ( _ref_count_ptr ) delete _ref_count_ptr;
	// 							}
	// 						_ref_count_ptr = nullptr;
	// 						_ptr		   = nullptr;
	// 					}
	// 			}
	// 	}

	// 	bool* _is_ownership_stolen{};
	// 	TYPE*  _ptr{};
	// 	int*  _ref_count_ptr{};
	// };

	template < typename TYPE >
	class ptr_lc_guard : private std::unique_ptr< TYPE >
	{
	public:
		ptr_lc_guard( TYPE* ptr )
			: std::unique_ptr< TYPE >{ ptr } { };

		TYPE*
		pass_lc_ownership()
		{
			std::unique_ptr< TYPE >::get_deleter() = []( TYPE* ) { /* do nothing */ };
			return std::unique_ptr< TYPE >::get();
		}

		TYPE*
		get() const
		{
			return std::unique_ptr< TYPE >::get();
		}

		TYPE
		operator* () const
		{
			return std::unique_ptr< TYPE >::operator* ();
		}

		TYPE*
		operator->() const
		{
			return std::unique_ptr< TYPE >::operator->();
		}
	};
};
