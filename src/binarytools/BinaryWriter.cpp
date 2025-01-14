#include "BinaryWriter.h"

Ship::BinaryWriter::BinaryWriter(Stream* nStream) {
    mStream.reset(nStream);
}

Ship::BinaryWriter::BinaryWriter(std::shared_ptr<Stream> nStream) {
    mStream = nStream;
}

void Ship::BinaryWriter::SetEndianness(Endianness endianness) {
    this->mEndianness = endianness;
}

void Ship::BinaryWriter::Close() {
    mStream->Close();
}

std::shared_ptr<Ship::Stream> Ship::BinaryWriter::GetStream() {
    return mStream;
}

uint64_t Ship::BinaryWriter::GetBaseAddress() {
    return mStream->GetBaseAddress();
}

uint64_t Ship::BinaryWriter::GetLength() {
    return mStream->GetLength();
}

void Ship::BinaryWriter::Seek(int32_t offset, SeekOffsetType seekType) {
    mStream->Seek(offset, seekType);
}

void Ship::BinaryWriter::Write(int8_t value) {
    mStream->Write((char*)&value, sizeof(int8_t));
}

void Ship::BinaryWriter::Write(uint8_t value) {
    mStream->Write((char*)&value, sizeof(uint8_t));
}

void Ship::BinaryWriter::Write(int16_t value) {
    if (mEndianness != Endianness::Native) {
        value = BSWAP16(value);
    }

    mStream->Write((char*)&value, sizeof(int16_t));
}

void Ship::BinaryWriter::Write(uint16_t value) {
    if (mEndianness != Endianness::Native) {
        value = BSWAP16(value);
    }

    mStream->Write((char*)&value, sizeof(uint16_t));
}

void Ship::BinaryWriter::Write(int32_t value) {
    if (mEndianness != Endianness::Native) {
        value = BSWAP32(value);
    }

    mStream->Write((char*)&value, sizeof(int32_t));
}

void Ship::BinaryWriter::Write(int32_t valueA, int32_t valueB) {
    Write(valueA);
    Write(valueB);
}

void Ship::BinaryWriter::Write(uint32_t value) {
    if (mEndianness != Endianness::Native) {
        value = BSWAP32(value);
    }

    mStream->Write((char*)&value, sizeof(uint32_t));
}

void Ship::BinaryWriter::Write(int64_t value) {
    if (mEndianness != Endianness::Native) {
        value = BSWAP64(value);
    }

    mStream->Write((char*)&value, sizeof(int64_t));
}

void Ship::BinaryWriter::Write(uint64_t value) {
    if (mEndianness != Endianness::Native) {
        value = BSWAP64(value);
    }

    mStream->Write((char*)&value, sizeof(uint64_t));
}

void Ship::BinaryWriter::Write(float value) {
    if (mEndianness != Endianness::Native) {
        float tmp;
        char* dst = (char*)&tmp;
        char* src = (char*)&value;
        dst[3] = src[0];
        dst[2] = src[1];
        dst[1] = src[2];
        dst[0] = src[3];
        value = tmp;
    }

    mStream->Write((char*)&value, sizeof(float));
}

void Ship::BinaryWriter::Write(double value) {
    if (mEndianness != Endianness::Native) {
        double tmp;
        char* dst = (char*)&tmp;
        char* src = (char*)&value;
        dst[7] = src[0];
        dst[6] = src[1];
        dst[5] = src[2];
        dst[4] = src[3];
        dst[3] = src[4];
        dst[2] = src[5];
        dst[1] = src[6];
        dst[0] = src[7];
        value = tmp;
    }

    mStream->Write((char*)&value, sizeof(double));
}

void Ship::BinaryWriter::Write(const std::string& str) {
    int strLen = str.size();
    Write(strLen);

    for (char c : str) {
        mStream->WriteByte(c);
    }
}

void Ship::BinaryWriter::Write(char* srcBuffer, size_t length) {
    mStream->Write(srcBuffer, length);
}
