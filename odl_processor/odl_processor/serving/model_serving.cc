#include "odl_processor/serving/tf_predict.pb.h"
#include "odl_processor/serving/model_impl.h"
#include "odl_processor/serving/model_serving.h"
#include "odl_processor/serving/model_config.h"

namespace tensorflow {
namespace processor {

Model::~Model() {
  delete impl_;
}

Status Model::Init(const char* model_config, const char* model_dir) {
  ModelConfig* config = nullptr;
  auto status = ModelConfigFactory::Create(model_config, &config);
  if (!status.ok()) {
    return status;
  }

  impl_ = ModelImplFactory::Create(config);
  return impl_->Init(model_dir);
}

Status Model::Predict(const eas::PredictRequest& req,
                      eas::PredictResponse* resp) {
  return impl_->Predict(req, resp);
}

std::string Model::DebugString() {
  return impl_->DebugString();
}

} // processor
} // tensorflow
