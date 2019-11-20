#include <FileGuard.hpp>

MuazKurt::FileGuard::FileGuard(const std::string & path) : output_stream(path, std::ofstream::out)
{/*-.-*/}

MuazKurt::FileGuard::~FileGuard()
{
	output_stream.close();
}

MuazKurt::FileGuard & MuazKurt::FileGuard::operator<<(const std::string & output)
{
	output_stream << output;
	return *this;
}
MuazKurt::FileGuard & MuazKurt::FileGuard::operator<<(int output)
{
	output_stream << output;
	return *this;
}