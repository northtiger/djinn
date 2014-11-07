/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include "dnn_types.h"

#include <thrift/lib/cpp/TApplicationException.h>


namespace dnn { namespace cpp2 {

template <class Protocol_>
uint32_t Work::read(Protocol_* iprot) {
  uint32_t xfer = 0;
  std::string fname;
  apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using apache::thrift::TProtocolException;


  while (true) {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid) {
      case 1:
      {
        if (ftype == apache::thrift::protocol::T_LIST) {
          this->data.clear();
          uint32_t _size0;
          apache::thrift::protocol::TType _etype3;
          xfer += iprot->readListBegin(_etype3, _size0);
          this->data.resize(_size0);
          uint32_t _i4;
          for (_i4 = 0; _i4 < _size0; ++_i4) {
            xfer += iprot->readDouble(this->data[_i4]);
          }
          xfer += iprot->readListEnd();
          this->__isset.data = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      case 2:
      {
        if (ftype == apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->op);
          this->__isset.op = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      case 3:
      {
        if (ftype == apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->n_in);
          this->__isset.n_in = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      case 4:
      {
        if (ftype == apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->c_in);
          this->__isset.c_in = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      case 5:
      {
        if (ftype == apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->w_in);
          this->__isset.w_in = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      case 6:
      {
        if (ftype == apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->h_in);
          this->__isset.h_in = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      }
      default:
      {
        xfer += iprot->skip(ftype);
        break;
      }
    }
    xfer += iprot->readFieldEnd();
  }
  xfer += iprot->readStructEnd();

  return xfer;
}

template <class Protocol_>
uint32_t Work::serializedSize(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("Work");
  xfer += prot_->serializedFieldSize("data", apache::thrift::protocol::T_LIST, 1);
  xfer += prot_->serializedSizeListBegin(apache::thrift::protocol::T_DOUBLE, this->data.size());
  for (auto _iter5 = this->data.begin(); _iter5 != this->data.end(); ++_iter5) {
    xfer += prot_->serializedSizeDouble((*_iter5));
  }
  xfer += prot_->serializedSizeListEnd();
  xfer += prot_->serializedFieldSize("op", apache::thrift::protocol::T_STRING, 2);
  xfer += prot_->serializedSizeString(this->op);
  xfer += prot_->serializedFieldSize("n_in", apache::thrift::protocol::T_I32, 3);
  xfer += prot_->serializedSizeI32(this->n_in);
  xfer += prot_->serializedFieldSize("c_in", apache::thrift::protocol::T_I32, 4);
  xfer += prot_->serializedSizeI32(this->c_in);
  xfer += prot_->serializedFieldSize("w_in", apache::thrift::protocol::T_I32, 5);
  xfer += prot_->serializedSizeI32(this->w_in);
  xfer += prot_->serializedFieldSize("h_in", apache::thrift::protocol::T_I32, 6);
  xfer += prot_->serializedSizeI32(this->h_in);
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t Work::serializedSizeZC(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("Work");
  xfer += prot_->serializedFieldSize("data", apache::thrift::protocol::T_LIST, 1);
  xfer += prot_->serializedSizeListBegin(apache::thrift::protocol::T_DOUBLE, this->data.size());
  for (auto _iter6 = this->data.begin(); _iter6 != this->data.end(); ++_iter6) {
    xfer += prot_->serializedSizeDouble((*_iter6));
  }
  xfer += prot_->serializedSizeListEnd();
  xfer += prot_->serializedFieldSize("op", apache::thrift::protocol::T_STRING, 2);
  xfer += prot_->serializedSizeString(this->op);
  xfer += prot_->serializedFieldSize("n_in", apache::thrift::protocol::T_I32, 3);
  xfer += prot_->serializedSizeI32(this->n_in);
  xfer += prot_->serializedFieldSize("c_in", apache::thrift::protocol::T_I32, 4);
  xfer += prot_->serializedSizeI32(this->c_in);
  xfer += prot_->serializedFieldSize("w_in", apache::thrift::protocol::T_I32, 5);
  xfer += prot_->serializedSizeI32(this->w_in);
  xfer += prot_->serializedFieldSize("h_in", apache::thrift::protocol::T_I32, 6);
  xfer += prot_->serializedSizeI32(this->h_in);
  xfer += prot_->serializedSizeStop();
  return xfer;
}

template <class Protocol_>
uint32_t Work::write(Protocol_* prot_) const {
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("Work");
  xfer += prot_->writeFieldBegin("data", apache::thrift::protocol::T_LIST, 1);
  xfer += prot_->writeListBegin(apache::thrift::protocol::T_DOUBLE, this->data.size());
  for (auto _iter7 = this->data.begin(); _iter7 != this->data.end(); ++_iter7) {
    xfer += prot_->writeDouble((*_iter7));
  }
  xfer += prot_->writeListEnd();
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldBegin("op", apache::thrift::protocol::T_STRING, 2);
  xfer += prot_->writeString(this->op);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldBegin("n_in", apache::thrift::protocol::T_I32, 3);
  xfer += prot_->writeI32(this->n_in);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldBegin("c_in", apache::thrift::protocol::T_I32, 4);
  xfer += prot_->writeI32(this->c_in);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldBegin("w_in", apache::thrift::protocol::T_I32, 5);
  xfer += prot_->writeI32(this->w_in);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldBegin("h_in", apache::thrift::protocol::T_I32, 6);
  xfer += prot_->writeI32(this->h_in);
  xfer += prot_->writeFieldEnd();
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
}

}} // dnn::cpp2
namespace apache { namespace thrift {

}} // apache::thrift
namespace dnn { namespace cpp2 {

}} // dnn::cpp2