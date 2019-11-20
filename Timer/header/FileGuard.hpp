#ifndef FILEGUARD_H
	#define FILEGUARD_H
	#include <fstream>
    namespace MuazKurt
	{
		/**
		 * This is a class that wraps an ofstream and ensures that file is 
		 * closed at the end of the context.
		 **/
        class FileGuard
		{
		public:
			/**
			 * Creates a file path to generate a FileGuard with ofstreams poins to the that path.
			 **/
			FileGuard(const std::string & path);
			/**
			 * Closes the opened file.
			 **/
			~FileGuard();
			/**
			 * Writes given string to the file and returns FileGuard object for further uses.
			 **/
			FileGuard& operator<<(const std::string & output);
			/**
			 * Writes given int to the file and returns FileGuard object for further uses.
			 **/
			FileGuard& operator<<(int output);
			FileGuard(FileGuard &) = delete;
			FileGuard & operator=(FileGuard&) = delete;
		private:
			// An ofstream to write.
			std::ofstream output_stream;
		};
    }
#endif