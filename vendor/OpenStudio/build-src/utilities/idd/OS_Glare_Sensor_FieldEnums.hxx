/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2020, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_GLARE_SENSOR_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_GLARE_SENSOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Glare_SensorFields
 *  \brief Enumeration of OS:Glare:Sensor's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Glare_SensorFields, )
#else
class OS_Glare_SensorFields: public ::EnumBase<OS_Glare_SensorFields> {
 public: 
  enum domain 
  {
Handle, Name, SpaceName, PositionXCoordinate, PositionYCoordinate, PositionZCoordinate, PsiRotationAroundXAxis, ThetaRotationAroundYAxis, PhiRotationAroundZAxis, NumberofGlareViewVectors, MaximumAllowableDaylightGlareProbability,   };
  OS_Glare_SensorFields()
   : EnumBase<OS_Glare_SensorFields>(Handle) {} 
  OS_Glare_SensorFields(const std::string &t_name) 
   : EnumBase<OS_Glare_SensorFields>(t_name) {} 
  OS_Glare_SensorFields(int t_value) 
   : EnumBase<OS_Glare_SensorFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Glare_SensorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Glare_SensorFields>::value()); }
   private:
    friend class EnumBase<OS_Glare_SensorFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ OS_Glare_SensorFields::Handle, "Handle", "Handle"},
{ OS_Glare_SensorFields::Name, "Name", "Name"},
{ OS_Glare_SensorFields::SpaceName, "SpaceName", "Space Name"},
{ OS_Glare_SensorFields::PositionXCoordinate, "PositionXCoordinate", "Position X-Coordinate"},
{ OS_Glare_SensorFields::PositionYCoordinate, "PositionYCoordinate", "Position Y-Coordinate"},
{ OS_Glare_SensorFields::PositionZCoordinate, "PositionZCoordinate", "Position Z-Coordinate"},
{ OS_Glare_SensorFields::PsiRotationAroundXAxis, "PsiRotationAroundXAxis", "Psi Rotation Around X-Axis"},
{ OS_Glare_SensorFields::ThetaRotationAroundYAxis, "ThetaRotationAroundYAxis", "Theta Rotation Around Y-Axis"},
{ OS_Glare_SensorFields::PhiRotationAroundZAxis, "PhiRotationAroundZAxis", "Phi Rotation Around Z-Axis"},
{ OS_Glare_SensorFields::NumberofGlareViewVectors, "NumberofGlareViewVectors", "Number of Glare View Vectors"},
{ OS_Glare_SensorFields::MaximumAllowableDaylightGlareProbability, "MaximumAllowableDaylightGlareProbability", "Maximum Allowable Daylight Glare Probability"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const OS_Glare_SensorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Glare_SensorFields> OptionalOS_Glare_SensorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_GLARE_SENSOR_FIELDENUMS_HXX
