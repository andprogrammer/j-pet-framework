/**
 *  @copyright Copyright 2016 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetFrame.h
 */

#ifndef JPET_FRAME_H
#define JPET_FRAME_H

#include "TNamed.h"


/**
 * @brief Parametric class representing database information on a whole mechanical structure frame of the PET setup.
 *
 * The frame consists of one or more layers represented by JPetLayer objects.
 */
class JPetFrame: public TNamed
{
 protected:
  const int fId;
  bool fIsActive;
  std::string fStatus;
  std::string fDescription;
  const int fVersion;
  const int fCreator_id;
  
 public:

  /// The default constructor sets fId, fVersion, fCreator_id to -1.  
  JPetFrame();
  JPetFrame(int id, bool isActive, std::string status, std::string description, int version, int creator_id);

  inline bool operator==(const JPetFrame& frame) { return getId() == frame.getId(); }
  inline bool operator!=(const JPetFrame& frame) { return getId() != frame.getId(); }
  int getId() const { return fId; }
  bool getIsActive() const { return fIsActive; }
  std::string getStatus() const { return fStatus; }
  std::string getDescription() const { return fDescription; }
  int getVersion() const { return fVersion; }
  int getCreator() const { return fCreator_id; }

 private:
  ClassDef(JPetFrame, 1);
};

#endif // JPET_FRAME_H
