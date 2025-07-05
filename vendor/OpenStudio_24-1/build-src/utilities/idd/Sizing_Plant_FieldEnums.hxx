/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#ifndef UTILITIES_IDD_SIZING_PLANT_FIELDENUMS_HXX
#define UTILITIES_IDD_SIZING_PLANT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Sizing_PlantFields
 *  \brief Enumeration of Sizing:Plant's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Sizing_PlantFields, )
#else
class Sizing_PlantFields: public ::EnumBase<Sizing_PlantFields> {
 public: 
  enum domain 
  {
PlantorCondenserLoopName, LoopType, DesignLoopExitTemperature, LoopDesignTemperatureDifference, SizingOption, ZoneTimestepsinAveragingWindow, CoincidentSizingFactorMode,   };
  Sizing_PlantFields()
   : EnumBase<Sizing_PlantFields>(PlantorCondenserLoopName) {} 
  Sizing_PlantFields(const std::string &t_name) 
   : EnumBase<Sizing_PlantFields>(t_name) {} 
  Sizing_PlantFields(int t_value) 
   : EnumBase<Sizing_PlantFields>(t_value) {} 
  static std::string enumName() 
  { return "Sizing_PlantFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Sizing_PlantFields>::value()); }
   private:
    friend class EnumBase<Sizing_PlantFields>;
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
{ Sizing_PlantFields::PlantorCondenserLoopName, "PlantorCondenserLoopName", "Plant or Condenser Loop Name"},
{ Sizing_PlantFields::LoopType, "LoopType", "Loop Type"},
{ Sizing_PlantFields::DesignLoopExitTemperature, "DesignLoopExitTemperature", "Design Loop Exit Temperature"},
{ Sizing_PlantFields::LoopDesignTemperatureDifference, "LoopDesignTemperatureDifference", "Loop Design Temperature Difference"},
{ Sizing_PlantFields::SizingOption, "SizingOption", "Sizing Option"},
{ Sizing_PlantFields::ZoneTimestepsinAveragingWindow, "ZoneTimestepsinAveragingWindow", "Zone Timesteps in Averaging Window"},
{ Sizing_PlantFields::CoincidentSizingFactorMode, "CoincidentSizingFactorMode", "Coincident Sizing Factor Mode"},
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
  inline std::ostream &operator<<(std::ostream &os, const Sizing_PlantFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Sizing_PlantFields> OptionalSizing_PlantFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SIZING_PLANT_FIELDENUMS_HXX
