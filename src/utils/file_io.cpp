#include "file_io.h"

#include <algorithm>

FileIO::FileIO(size_t block_size) : block_size_{block_size} {}

FileIO::~FileIO() {
    if (is_input_open()) {
        close_input();
    }
    if (is_output_open()) {
        close_output();
    }
}

bool FileIO::open_for_reading(const std::string& filename) {
    file_reader_.open(filename, std::ios::binary);
    return is_input_open();
}

std::vector<uint8_t> FileIO::read_next_block() {
    // check reader is open and in good state
    if (!file_reader_.is_open() || !file_reader_.good()) {
        return std::vector<uint8_t>{};
    }

    // create buffer
    std::vector<uint8_t> buffer(block_size_);

    // read to buffer
    char* buffer_ptr = reinterpret_cast<char*>(buffer.data());
    file_reader_.read(buffer_ptr, block_size_);

    // pad buffer to block size
    std::streamsize bytes_read = file_reader_.gcount();
    if (bytes_read < static_cast<std::streamsize>(block_size_)) {
        std::fill(buffer.begin() + bytes_read, buffer.end(), 0x00);
    }

    return buffer;
}

bool FileIO::has_more_blocks() { return !file_reader_.eof(); }

void FileIO::close_input() { file_reader_.close(); }

bool FileIO::open_for_writing(const std::string& filename) {
    file_writer_.open(filename, std::ios::binary);
    return is_output_open();
}

void FileIO::write_block(const std::vector<uint8_t>& data) {
    // check writer is open and in good state
    if (!file_writer_.is_open() || !file_writer_.good()) {
        return;
    }

    // write data
    const char* data_ptr = reinterpret_cast<const char*>(data.data());
    std::streamsize bytes_to_write = static_cast<std::streamsize>(data.size());
    file_writer_.write(data_ptr, bytes_to_write);
}

void FileIO::close_output() { file_writer_.close(); }

size_t FileIO::get_block_size() const { return block_size_; }

bool FileIO::is_input_open() const { return file_reader_.is_open(); }

bool FileIO::is_output_open() const { return file_writer_.is_open(); }
