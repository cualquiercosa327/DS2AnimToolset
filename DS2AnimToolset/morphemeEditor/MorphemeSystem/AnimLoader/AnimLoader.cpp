// Copyright (c) 2012 NaturalMotion.  All Rights Reserved.
// Not to be copied, adapted, modified, used, distributed, sold,
// licensed or commercially exploited in any manner without the
// written consent of NaturalMotion.
//
// All non public elements of this software are the confidential
// information of NaturalMotion and may not be disclosed to any
// person nor used for any purpose not expressly approved by
// NaturalMotion in writing.

//----------------------------------------------------------------------------------------------------------------------
#include "AnimLoader.h"

#include "../MorphemeSystem.h"
//----------------------------------------------------------------------------------------------------------------------
#include <sstream>
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
MR::AnimSourceBase* AnimLoader::requestAnim(const MR::RuntimeAnimAssetID animAssetID, void* userdata)
{
  MorphemeCharacterDef::AnimData* metadata = (MorphemeCharacterDef::AnimData*)userdata;

  MR::UTILS::SimpleAnimRuntimeIDtoFilenameLookup* info = metadata->m_animFileLookUp;
  const char* dir = metadata->m_bundleDir;

  NMP_ASSERT(info);

  //----------------------------
  // Get the animation file name
  const char* filename = info->getFilename(animAssetID);

  //----------------------------
  // Add the file extension to the start of the filename. By default this is hard coded to the ProjectData folder.
  char fullFilename[512];
  NMP_SPRINTF(fullFilename, 512, "%s\\%s", dir, filename);

  NMP_DEBUG_MSG("Attempting to load animation %s", fullFilename);

  const char* format   = info->getFormatType(animAssetID);

  void*    fileBuffer = 0;
  int64_t length      = 0;

  int64_t bytesRead = NMP::NMFile::allocAndLoad(fullFilename, &fileBuffer, &length, NMP_VECTOR_ALIGNMENT);
  if (bytesRead == -1)
  {
      std::filesystem::path parent_path = std::filesystem::path(dir).parent_path().string() + "\\c0001\\";

      if (std::filesystem::exists(parent_path))
      {
          for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(parent_path))
          {
              NMP_SPRINTF(fullFilename, 512, "%ws\\%s", dirEntry.path().c_str(), filename);

              if (std::filesystem::exists(fullFilename))
              {
                  NMP_DEBUG_MSG("Loading animation %s from extanibnd archive", fullFilename);
                  bytesRead = NMP::NMFile::allocAndLoad(fullFilename, &fileBuffer, &length, NMP_VECTOR_ALIGNMENT);
              }
          }
      }

      if (bytesRead == -1)
          return NULL;
  }

  //----------------------------
  // Locate the animation in memory
  MR::AnimSourceBase* animSource = (MR::AnimSourceBase*) fileBuffer;

  const MR::Manager::AnimationFormatRegistryEntry* animFormatRegistryEntry =
    MR::Manager::getInstance().findAnimationFormatRegistryEntry(format);
  if (!animFormatRegistryEntry)
  {
    //----------------------------
    // Unregistered anim format
    NMP_ASSERT_FAIL();
    return NULL;
  }

  animFormatRegistryEntry->m_locateAnimFormatFn(animSource);

  //----------------------------
  // Return the animation source
  return animSource;
}

//----------------------------------------------------------------------------------------------------------------------
void AnimLoader::releaseAnim(
  const MR::RuntimeAnimAssetID animAssetID,
  MR::AnimSourceBase*          loadedAnimation,
  void*                        NMP_UNUSED(userdata))
{
  if (loadedAnimation)
  {
    //----------------------------
    // Free the anim itself.
    MR::AnimSourceBase* animSource = (MR::AnimSourceBase*) loadedAnimation;
    animSource->dislocate();

    NMP::Memory::memFree(loadedAnimation);
  }
}