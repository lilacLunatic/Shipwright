#pragma once

#include "Resource.h"
#include "ResourceFactoryBinary.h"
#include "ResourceFactoryXML.h"

namespace SOH {
class ResourceFactoryBinaryAudioSampleV2 final : public Ship::ResourceFactoryBinary {
  public:
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file, std::shared_ptr<Ship::ResourceInitData> initData) override;
};

class ResourceFactoryXMLAudioSampleV0 : public Ship::ResourceFactoryXML {
  public:
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file, std::shared_ptr<Ship::ResourceInitData> initData) override;

  private:
    uint8_t CodecStrToInt(const char* str);
};

} // namespace SOH
