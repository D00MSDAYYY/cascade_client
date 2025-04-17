#include <chrono>
#include <format>
#include <optional>
#include <iomanip>

std::optional< std::chrono::system_clock::time_point >
string_to_timepoint( const std::string& str  )
;

std::optional< std::string >
timepoint_to_string( std::chrono::system_clock::time_point tp )
;
