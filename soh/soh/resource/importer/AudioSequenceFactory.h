#pragma once

#include "Resource.h"
#include "ResourceFactoryBinary.h"
#include "ResourceFactoryXML.h"
#include "BinaryWriter.h"

namespace SOH {
class ResourceFactoryBinaryAudioSequenceV2 final : public Ship::ResourceFactoryBinary {
  public:
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file, std::shared_ptr<Ship::ResourceInitData> initData) override;
};

class ResourceFactoryXMLAudioSequenceV0 : public Ship::ResourceFactoryXML {
  public:
    std::shared_ptr<Ship::IResource> ReadResource(std::shared_ptr<Ship::File> file, std::shared_ptr<Ship::ResourceInitData> initData) override;

  private:
    int8_t MediumStrToInt(const char* str);
    int8_t CachePolicyToInt(const char* str);
};
} // namespace SOH
