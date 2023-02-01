#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string_view>
#include <fstream>
#include <cerrno>

using namespace std;
    
// Returns the size of the file
long file_size(FILE *file) {
  // If file is not open, return 0
  if (!file) { return 0; }

  // Save the original position of the file
  fpos_t original = 0;

  // Get the position of the file and save it to original
  // If getting the position fails, print an error and return 0
  if (fgetpos(file, &original) != 0) {
    cerr << "fgetpos() failed: " << errno << endl;
    return 0;
  }

  // Move to the end of the file
  fseek(file, 0, SEEK_END);

  // Get the position (size) of the file
  long size = ftell(file);

  // Set the position back to original
  // If setting the position fails, print an error
  if (fsetpos(file, &original) != 0) {
    cerr << "fsetpos() failed: " << errno << endl;
  }

  return size;
}

// Returns the contents of a file as a C string (null-terminated string)
char *file_contents(const char *path) {
  FILE *file = fopen(path, "r");

  // If file couldn't be opened, print an error and return null
  if (!file) {
    cerr << "Could not open file at " << path << endl;
    return nullptr;
  }

  // Get the size of the file
  long size = file_size(file);

  // Allocate memory for the contents of the file
  char *contents = new char[size + 1];

  // Pointer for writing to the contents of the file
  char *write_it = contents;

  // Number of bytes read so far
  size_t bytes_read = 0;

  // Read the contents of the file
  while (bytes_read < size) {
    size_t bytes_read_this_iteration = fread(write_it, 1, size - bytes_read, file);

    // If there was an error while reading, print an error, free the memory, and return null
    if (ferror(file)) {
      cerr << "Error while reading: " << errno << endl;
      delete[] contents;
      return nullptr;
    }

    // Update the number of bytes read
    bytes_read += bytes_read_this_iteration;

    // Update the write_it pointer
    write_it += bytes_read_this_iteration;

    // If end of file is reached, break
    if (feof(file)) {
      break;
    }
  }

  // Null terminate the contents of the file
  contents[bytes_read] = '\0';

  return contents;
}

// Prints the usage of the program
void print_usage(const char *program_name) {
  cout << "USAGE: " << program_name << " <path_to_file_to_compile>" << endl;
}

// Returns the size of the file in bytes
long GetFileSize(ifstream& file) {
  // Check if the file is open
  if (!file.is_open()) {
    return 0;
  }

  // Save the current position in the file
  file.seekg(0, ios::end);
  long size = file.tellg();

  // Restore the original position in the file
  file.seekg(0, ios::beg);
  return size;
}

// Returns the contents of the file as a string
string GetFileContents(const string& filePath) {
  // Open the file
  ifstream file(filePath);
  if (!file.is_open()) {
    cout << "Could not open file at " << filePath << endl;
    return "";
  }

  // Get the size of the file
  long size = GetFileSize(file);

  // Read the contents of the file into a string
  string contents;
  contents.resize(size);
  file.read(&contents[0], size);

  return contents;
}

// Prints the usage message
void PrintUsage(const string& programName) {
  cout << "USAGE: " << programName << " <path_to_file_to_compile>" << endl;
}

// Represents an error that occurred during the compilation process
struct Error {
  // The type of error
  enum ErrorType {
    ERROR_NONE = 0,
    ERROR_TYPE,
    ERROR_TODO,
    ERROR_GENERIC,
    ERROR_SYNTAX,
    ERROR_ARGUMENTS,
  } type;

  // A message describing the error
  string msg;
};

const Error ok = { Error::ERROR_NONE, "" };

// Lexes the source code and returns the next token
Error Lex(const string& source, string& beg, string& end) {
  Error err = ok;
  if (source.empty()) {
    err.type = Error::ERROR_ARGUMENTS;
    err.msg = "Cannot lex empty source.";
    return err;
  }
  return ok;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    PrintUsage(argv[0]);
    return 0;
  }

  string filePath = argv[1];
  string contents = GetFileContents(filePath);
  cout << "Contents of " << filePath << ":" << endl;
  cout << "---" << endl << contents << endl << "---" << endl;

  return 0;
}