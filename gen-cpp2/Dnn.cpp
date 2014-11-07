/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "Dnn.h"

#include "Dnn.tcc"

namespace dnn { namespace cpp2 {

std::unique_ptr<apache::thrift::AsyncProcessor> DnnSvIf::getProcessor() {
  return std::unique_ptr<apache::thrift::AsyncProcessor>(new DnnAsyncProcessor((DnnSvIf*)this));
}

apache::thrift::concurrency::PriorityThreadManager::PRIORITY DnnSvIf::getprio_fwd(apache::thrift::Cpp2RequestContext* reqCtx) {
  apache::thrift::concurrency::PRIORITY prio8 = reqCtx->getCallPriority();
  if (prio8 != apache::thrift::concurrency::N_PRIORITIES) {
    return prio8;
  }
  return apache::thrift::concurrency::NORMAL;
}

folly::wangle::Future<std::unique_ptr<std::vector<double>>> DnnSvIf::future_fwd(std::unique_ptr< ::dnn::cpp2::Work> input) {
  folly::wangle::Promise<std::unique_ptr<std::vector<double>>> promise9;
  auto future10 = promise9.getFuture();
  apache::thrift::TApplicationException ex("Function fwd is unimplemented");
  promise9.setException(ex);
  return future10;
}

void DnnSvIf::async_eb_fwd(std::unique_ptr<apache::thrift::HandlerCallback<std::unique_ptr<std::vector<double>>>> callback, std::unique_ptr< ::dnn::cpp2::Work> input) {
  auto callbackp = callback.release();
  setConnectionContext(callbackp->getConnectionContext());
  setThreadManager(callbackp->getThreadManager());
  setEventBase(callbackp->getEventBase());
  try {
    auto future11 = future_fwd(std::move(input));
    future11.then([=](folly::wangle::Try<std::unique_ptr<std::vector<double>>>&& _return) {
      try {
        callbackp->resultInThread(std::move(_return.value()));
      } catch(...) {
        callbackp->exceptionInThread(std::current_exception());
      }
    }
    );
  } catch(const std::exception& ex) {
    callbackp->exceptionInThread(std::current_exception());
  }
}

std::string DnnAsyncProcessor::getServiceName() {
  return "Dnn";
}

void DnnAsyncProcessor::process(std::unique_ptr<apache::thrift::ResponseChannel::Request> req, std::unique_ptr<folly::IOBuf> buf, apache::thrift::protocol::PROTOCOL_TYPES protType,apache::thrift::Cpp2RequestContext* context,apache::thrift::async::TEventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  std::string fname;
  apache::thrift::MessageType mtype;
  int32_t protoSeqId = 0;
  switch(protType) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      std::unique_ptr<apache::thrift::BinaryProtocolReader> iprot(new apache::thrift::BinaryProtocolReader());
      iprot->setInput(buf.get());
      try {
        iprot->readMessageBegin(fname, mtype, protoSeqId);
      } catch(const apache::thrift::TException& ex) {
        LOG(ERROR) << "received invalid message from client: " << ex.what();
        apache::thrift::BinaryProtocolWriter prot;
        if (req) {
          LOG(ERROR) << "invalid message from client" << " in function process";
          apache::thrift::TApplicationException x("invalid message from client");
          folly::IOBufQueue queue = serializeException("process", &prot, protoSeqId, nullptr, x);
          queue.append(apache::thrift::transport::THeader::transform(queue.move(), context->getTransforms(), context->getMinCompressBytes()));
          auto queue_mw = folly::makeMoveWrapper(std::move(queue));
          auto req_mw = folly::makeMoveWrapper(std::move(req));
          eb->runInEventBaseThread([=]() mutable {
            (*req_mw)->sendReply(queue_mw->move());
          }
          );
          return;
        }
        else {
          LOG(ERROR) << "invalid message from client" << " in oneway function process";
        }
        return;
      }
      if (mtype != apache::thrift::T_CALL && mtype != apache::thrift::T_ONEWAY) {
        LOG(ERROR) << "received invalid message of type " << mtype;
        apache::thrift::BinaryProtocolWriter prot;
        if (req) {
          LOG(ERROR) << "invalid message arguments" << " in function process";
          apache::thrift::TApplicationException x("invalid message arguments");
          folly::IOBufQueue queue = serializeException("process", &prot, protoSeqId, nullptr, x);
          queue.append(apache::thrift::transport::THeader::transform(queue.move(), context->getTransforms(), context->getMinCompressBytes()));
          auto queue_mw = folly::makeMoveWrapper(std::move(queue));
          auto req_mw = folly::makeMoveWrapper(std::move(req));
          eb->runInEventBaseThread([=]() mutable {
            (*req_mw)->sendReply(queue_mw->move());
          }
          );
          return;
        }
        else {
          LOG(ERROR) << "invalid message arguments" << " in oneway function process";
        }
      }
      auto pfn = binaryProcessMap_.find(fname);
      if (pfn == binaryProcessMap_.end()) {
        const std::string exMsg = folly::stringPrintf( "Method name %s not found", fname.c_str());
        apache::thrift::BinaryProtocolWriter prot;
        if (req) {
          LOG(ERROR) << exMsg << " in function process";
          apache::thrift::TApplicationException x(exMsg);
          folly::IOBufQueue queue = serializeException("process", &prot, protoSeqId, nullptr, x);
          queue.append(apache::thrift::transport::THeader::transform(queue.move(), context->getTransforms(), context->getMinCompressBytes()));
          auto queue_mw = folly::makeMoveWrapper(std::move(queue));
          auto req_mw = folly::makeMoveWrapper(std::move(req));
          eb->runInEventBaseThread([=]() mutable {
            (*req_mw)->sendReply(queue_mw->move());
          }
          );
          return;
        }
        else {
          LOG(ERROR) << exMsg << " in oneway function process";
        }
        return;
      }
      (this->*(pfn->second))(std::move(req), std::move(buf), std::move(iprot), context, eb, tm);
      return;
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      std::unique_ptr<apache::thrift::CompactProtocolReader> iprot(new apache::thrift::CompactProtocolReader());
      iprot->setInput(buf.get());
      try {
        iprot->readMessageBegin(fname, mtype, protoSeqId);
      } catch(const apache::thrift::TException& ex) {
        LOG(ERROR) << "received invalid message from client: " << ex.what();
        apache::thrift::CompactProtocolWriter prot;
        if (req) {
          LOG(ERROR) << "invalid message from client" << " in function process";
          apache::thrift::TApplicationException x("invalid message from client");
          folly::IOBufQueue queue = serializeException("process", &prot, protoSeqId, nullptr, x);
          queue.append(apache::thrift::transport::THeader::transform(queue.move(), context->getTransforms(), context->getMinCompressBytes()));
          auto queue_mw = folly::makeMoveWrapper(std::move(queue));
          auto req_mw = folly::makeMoveWrapper(std::move(req));
          eb->runInEventBaseThread([=]() mutable {
            (*req_mw)->sendReply(queue_mw->move());
          }
          );
          return;
        }
        else {
          LOG(ERROR) << "invalid message from client" << " in oneway function process";
        }
        return;
      }
      if (mtype != apache::thrift::T_CALL && mtype != apache::thrift::T_ONEWAY) {
        LOG(ERROR) << "received invalid message of type " << mtype;
        apache::thrift::CompactProtocolWriter prot;
        if (req) {
          LOG(ERROR) << "invalid message arguments" << " in function process";
          apache::thrift::TApplicationException x("invalid message arguments");
          folly::IOBufQueue queue = serializeException("process", &prot, protoSeqId, nullptr, x);
          queue.append(apache::thrift::transport::THeader::transform(queue.move(), context->getTransforms(), context->getMinCompressBytes()));
          auto queue_mw = folly::makeMoveWrapper(std::move(queue));
          auto req_mw = folly::makeMoveWrapper(std::move(req));
          eb->runInEventBaseThread([=]() mutable {
            (*req_mw)->sendReply(queue_mw->move());
          }
          );
          return;
        }
        else {
          LOG(ERROR) << "invalid message arguments" << " in oneway function process";
        }
      }
      auto pfn = compactProcessMap_.find(fname);
      if (pfn == compactProcessMap_.end()) {
        const std::string exMsg = folly::stringPrintf( "Method name %s not found", fname.c_str());
        apache::thrift::CompactProtocolWriter prot;
        if (req) {
          LOG(ERROR) << exMsg << " in function process";
          apache::thrift::TApplicationException x(exMsg);
          folly::IOBufQueue queue = serializeException("process", &prot, protoSeqId, nullptr, x);
          queue.append(apache::thrift::transport::THeader::transform(queue.move(), context->getTransforms(), context->getMinCompressBytes()));
          auto queue_mw = folly::makeMoveWrapper(std::move(queue));
          auto req_mw = folly::makeMoveWrapper(std::move(req));
          eb->runInEventBaseThread([=]() mutable {
            (*req_mw)->sendReply(queue_mw->move());
          }
          );
          return;
        }
        else {
          LOG(ERROR) << exMsg << " in oneway function process";
        }
        return;
      }
      (this->*(pfn->second))(std::move(req), std::move(buf), std::move(iprot), context, eb, tm);
      return;
    }
    default:
    {
      LOG(ERROR) << "invalid protType: " << protType;
      return;
      break;
    }
  }
}

bool DnnAsyncProcessor::isOnewayMethod(const folly::IOBuf* buf, const apache::thrift::transport::THeader* header) {
  std::string fname;
  apache::thrift::MessageType mtype;
  int32_t protoSeqId = 0;
  apache::thrift::protocol::PROTOCOL_TYPES protType = static_cast<apache::thrift::protocol::PROTOCOL_TYPES>(header->getProtocolId());
  switch(protType) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolReader iprot;
      iprot.setInput(buf);
      try {
        iprot.readMessageBegin(fname, mtype, protoSeqId);
        auto it = onewayMethods.find(fname);
        return it != onewayMethods.end();
      } catch(const apache::thrift::TException& ex) {
        LOG(ERROR) << "received invalid message from client: " << ex.what();
        return false;
      }
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolReader iprot;
      iprot.setInput(buf);
      try {
        iprot.readMessageBegin(fname, mtype, protoSeqId);
        auto it = onewayMethods.find(fname);
        return it != onewayMethods.end();
      } catch(const apache::thrift::TException& ex) {
        LOG(ERROR) << "received invalid message from client: " << ex.what();
        return false;
      }
    }
    default:
    {
      LOG(ERROR) << "invalid protType: " << protType;
      break;
    }
  }
  return false;
}

std::unordered_set<std::string> DnnAsyncProcessor::onewayMethods {};
DnnAsyncProcessor::binaryProcessMap DnnAsyncProcessor::binaryProcessMap_ {
  {"fwd", &DnnAsyncProcessor::process_fwd<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}
};
DnnAsyncProcessor::compactProcessMap DnnAsyncProcessor::compactProcessMap_ {
  {"fwd", &DnnAsyncProcessor::process_fwd<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>}
};

std::string DnnAsyncClient::getServiceName() {
  return "Dnn";
}

void DnnAsyncClient::fwd(std::unique_ptr<apache::thrift::RequestCallback> callback, const  ::dnn::cpp2::Work& input) {
  fwd(::apache::thrift::RpcOptions(), std::move(callback), input);
}

void DnnAsyncClient::callback_fwd(std::unique_ptr<apache::thrift::RequestCallback> callback, const  ::dnn::cpp2::Work& input) {
  fwd(::apache::thrift::RpcOptions(), std::move(callback), input);
}

void DnnAsyncClient::fwd(const apache::thrift::RpcOptions& rpcOptions, std::unique_ptr<apache::thrift::RequestCallback> callback, const  ::dnn::cpp2::Work& input) {
  switch(getChannel()->getProtocolId()) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolWriter writer;
      fwdT(&writer, rpcOptions, std::move(callback), input);
      break;
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolWriter writer;
      fwdT(&writer, rpcOptions, std::move(callback), input);
      break;
    }
    default:
    {
      throw apache::thrift::TApplicationException("Could not find Protocol");
    }
  }
}

void DnnAsyncClient::sync_fwd(std::vector<double>& _return, const  ::dnn::cpp2::Work& input) {
  sync_fwd(::apache::thrift::RpcOptions(), _return, input);
}

void DnnAsyncClient::sync_fwd(const apache::thrift::RpcOptions& rpcOptions, std::vector<double>& _return, const  ::dnn::cpp2::Work& input) {
  apache::thrift::ClientReceiveState _returnState;
  std::unique_ptr<apache::thrift::RequestCallback> callback12(new apache::thrift::ClientSyncCallback(&_returnState, getChannel()->getEventBase(), false));
  fwd(rpcOptions, std::move(callback12), input);
  getChannel()->getEventBase()->loopForever();
  if (!_returnState.buf()) {
    assert(_returnState.exception());
    std::rethrow_exception(_returnState.exception());
  }
  recv_fwd(_return, _returnState);
}

void DnnAsyncClient::fwd(std::function<void (::apache::thrift::ClientReceiveState&&)> callback, const  ::dnn::cpp2::Work& input) {
  fwd(std::unique_ptr<apache::thrift::RequestCallback>(new apache::thrift::FunctionReplyCallback(std::move(callback))),input);
}

void DnnAsyncClient::functor_fwd(std::function<void (::apache::thrift::ClientReceiveState&&)> callback, const  ::dnn::cpp2::Work& input) {
  fwd(std::unique_ptr<apache::thrift::RequestCallback>(new apache::thrift::FunctionReplyCallback(std::move(callback))),input);
}

folly::wangle::Future<std::vector<double>> DnnAsyncClient::future_fwd(const  ::dnn::cpp2::Work& input) {
  return future_fwd(::apache::thrift::RpcOptions(), input);
}

folly::wangle::Future<std::vector<double>> DnnAsyncClient::future_fwd(const apache::thrift::RpcOptions& rpcOptions, const  ::dnn::cpp2::Work& input) {
  folly::wangle::Promise<std::vector<double>> promise13;
  auto future14 = promise13.getFuture();
  std::unique_ptr<apache::thrift::RequestCallback> callback15(new apache::thrift::FutureCallback<std::vector<double>>(std::move(promise13), recv_fwd));
  fwd(rpcOptions, std::move(callback15), input);
  return std::move(future14);
}

folly::exception_wrapper DnnAsyncClient::recv_wrapped_fwd(std::vector<double>& _return, ::apache::thrift::ClientReceiveState& state) {
  auto ew = state.exceptionWrapper();
  if (ew) {
    return ew;
  }
  if (!state.buf()) {
    return folly::make_exception_wrapper<apache::thrift::TApplicationException>("recv_ called without result");
  }
  switch(state.protocolId()) {
    case apache::thrift::protocol::T_BINARY_PROTOCOL:
    {
      apache::thrift::BinaryProtocolReader reader;
      return recv_wrapped_fwdT(&reader, _return, state);
    }
    case apache::thrift::protocol::T_COMPACT_PROTOCOL:
    {
      apache::thrift::CompactProtocolReader reader;
      return recv_wrapped_fwdT(&reader, _return, state);
    }
    default:
    {
    }
  }
  return folly::make_exception_wrapper<apache::thrift::TApplicationException>("Could not find Protocol");
}

void DnnAsyncClient::recv_fwd(std::vector<double>& _return, ::apache::thrift::ClientReceiveState& state) {
  auto ew = recv_wrapped_fwd(_return, state);
  if (ew) {
    ew.throwException();
  }
}

void DnnAsyncClient::recv_instance_fwd(std::vector<double>& _return, ::apache::thrift::ClientReceiveState& state) {
  return recv_fwd(_return, state);
}

folly::exception_wrapper DnnAsyncClient::recv_instance_wrapped_fwd(std::vector<double>& _return, ::apache::thrift::ClientReceiveState& state) {
  return recv_wrapped_fwd(_return, state);
}

template uint32_t Dnn_fwd_args::read<apache::thrift::BinaryProtocolReader>(apache::thrift::BinaryProtocolReader*);
template uint32_t Dnn_fwd_args::write<apache::thrift::BinaryProtocolWriter>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Dnn_fwd_args::serializedSize<apache::thrift::BinaryProtocolWriter>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Dnn_fwd_args::serializedSizeZC<apache::thrift::BinaryProtocolWriter>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Dnn_fwd_args::read<apache::thrift::CompactProtocolReader>(apache::thrift::CompactProtocolReader*);
template uint32_t Dnn_fwd_args::write<apache::thrift::CompactProtocolWriter>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Dnn_fwd_args::serializedSize<apache::thrift::CompactProtocolWriter>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Dnn_fwd_args::serializedSizeZC<apache::thrift::CompactProtocolWriter>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Dnn_fwd_args::write<apache::thrift::DebugProtocolWriter>(apache::thrift::DebugProtocolWriter*) const;
template uint32_t Dnn_fwd_args::read<apache::thrift::VirtualReaderBase>(apache::thrift::VirtualReaderBase*);

void Dnn_fwd_args::__clear() {
  ::apache::thrift::Cpp2Ops<  ::dnn::cpp2::Work>::clear(&input);
  __isset.__clear();
}

bool Dnn_fwd_args::operator==(const Dnn_fwd_args& rhs) const {
  if (!((input == rhs.input))) {
    return false;
  }
  return true;
}

template uint32_t Dnn_fwd_pargs::read<apache::thrift::BinaryProtocolReader>(apache::thrift::BinaryProtocolReader*);
template uint32_t Dnn_fwd_pargs::write<apache::thrift::BinaryProtocolWriter>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Dnn_fwd_pargs::serializedSize<apache::thrift::BinaryProtocolWriter>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Dnn_fwd_pargs::serializedSizeZC<apache::thrift::BinaryProtocolWriter>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Dnn_fwd_pargs::read<apache::thrift::CompactProtocolReader>(apache::thrift::CompactProtocolReader*);
template uint32_t Dnn_fwd_pargs::write<apache::thrift::CompactProtocolWriter>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Dnn_fwd_pargs::serializedSize<apache::thrift::CompactProtocolWriter>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Dnn_fwd_pargs::serializedSizeZC<apache::thrift::CompactProtocolWriter>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Dnn_fwd_pargs::write<apache::thrift::DebugProtocolWriter>(apache::thrift::DebugProtocolWriter*) const;
template uint32_t Dnn_fwd_pargs::read<apache::thrift::VirtualReaderBase>(apache::thrift::VirtualReaderBase*);

template uint32_t Dnn_fwd_presult::read<apache::thrift::BinaryProtocolReader>(apache::thrift::BinaryProtocolReader*);
template uint32_t Dnn_fwd_presult::write<apache::thrift::BinaryProtocolWriter>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Dnn_fwd_presult::serializedSize<apache::thrift::BinaryProtocolWriter>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Dnn_fwd_presult::serializedSizeZC<apache::thrift::BinaryProtocolWriter>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Dnn_fwd_presult::read<apache::thrift::CompactProtocolReader>(apache::thrift::CompactProtocolReader*);
template uint32_t Dnn_fwd_presult::write<apache::thrift::CompactProtocolWriter>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Dnn_fwd_presult::serializedSize<apache::thrift::CompactProtocolWriter>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Dnn_fwd_presult::serializedSizeZC<apache::thrift::CompactProtocolWriter>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Dnn_fwd_presult::write<apache::thrift::DebugProtocolWriter>(apache::thrift::DebugProtocolWriter*) const;
template uint32_t Dnn_fwd_presult::read<apache::thrift::VirtualReaderBase>(apache::thrift::VirtualReaderBase*);

template uint32_t Dnn_fwd_result::read<apache::thrift::BinaryProtocolReader>(apache::thrift::BinaryProtocolReader*);
template uint32_t Dnn_fwd_result::write<apache::thrift::BinaryProtocolWriter>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Dnn_fwd_result::serializedSize<apache::thrift::BinaryProtocolWriter>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Dnn_fwd_result::serializedSizeZC<apache::thrift::BinaryProtocolWriter>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Dnn_fwd_result::read<apache::thrift::CompactProtocolReader>(apache::thrift::CompactProtocolReader*);
template uint32_t Dnn_fwd_result::write<apache::thrift::CompactProtocolWriter>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Dnn_fwd_result::serializedSize<apache::thrift::CompactProtocolWriter>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Dnn_fwd_result::serializedSizeZC<apache::thrift::CompactProtocolWriter>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Dnn_fwd_result::write<apache::thrift::DebugProtocolWriter>(apache::thrift::DebugProtocolWriter*) const;
template uint32_t Dnn_fwd_result::read<apache::thrift::VirtualReaderBase>(apache::thrift::VirtualReaderBase*);

void Dnn_fwd_result::__clear() {
  success.clear();
  __isset.__clear();
}

bool Dnn_fwd_result::operator==(const Dnn_fwd_result& rhs) const {
  if (!((success == rhs.success))) {
    return false;
  }
  return true;
}

}} // dnn::cpp2
namespace apache { namespace thrift {

}} // apache::thrift