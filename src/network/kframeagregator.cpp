#include "kframeagregator.h"

KFrameAgregator::KFrameAgregator(QObject *parent) : QObject(parent) {}

KFrameAgregator::KFrameAgregator(QAbstractSocket *parent) : QObject(parent) {
    setSocket(parent);
}

bool KFrameAgregator::hasFrameBuffered() {
    if(uncovered.isEmpty()) {
        recieveFrameData();
        return !uncovered.isEmpty();
    }
    return true;
}

QByteArray KFrameAgregator::readFrame() {
    QByteArray result = uncovered;
    uncovered.clear();
    return result;
}

void KFrameAgregator::writeFrame(QByteArray data) {
    if(hash.contains(data)) {
        socket()->write(hash[data]);
    } else {
        QByteArray frame = cover(data);
        hash[data] = frame;
        socket()->write(frame);
    }
}

QAbstractSocket *KFrameAgregator::socket() const {
    return m_socket;
}

void KFrameAgregator::setSocket(QAbstractSocket *socket) {
    m_socket = socket;
}

void KFrameAgregator::recieveFrameData() {
    unsigned i = 0;
    while(socket()->bytesAvailable() > 0) {
        char byte;
        socket()->read(&byte, 1);
        buffer.push_back(byte);
        if(i > 2 && byte == 0x7E) {
            uncovered = uncover(buffer);
            buffer.clear();
            break;
        }
        i++;
    }
}

QByteArray KFrameAgregator::cover(QByteArray data) {
    QByteArray frame;
    char checksum = 0;

    frame.push_back(0x7E);
    for (char c : data) {
        checksum += c;
        if (c == 0x7E || c == 0x7D) {
            frame.push_back(0x7D);
            c ^= 0x40;
        }
        frame.push_back(c);
    }

    char covered_checksum = -checksum;
    if (covered_checksum == 0x7E || covered_checksum == 0x7D) {
        frame.push_back(0x7D);
        covered_checksum ^= 0x40;
    }
    frame.push_back(covered_checksum);
    frame.push_back(0x7E);

    return frame;
}

QByteArray KFrameAgregator::uncover(QByteArray frame) {
    QByteArray result;
    char checksum = 0;
    bool checkNext = false;
    int i = 0;
    for(char c : frame) {
        if (c == 0x7E) {
            if (i >= 2) {
                result.resize(result.size() - 1);
                return result;
            }
        } else if(c == 0x7D) {
            checkNext = true;
        } else {
            if(checkNext) {
                if(c == 0x3D) result.push_back(0x7D);
                else if(c == 0x3E) result.push_back(0x7E);
            } else {
                result.push_back(c);
            }
            checksum += c;
            checkNext = false;
        }
        i++;
    }
    printf("Frame checksum error\n");
    return QByteArray();
}
