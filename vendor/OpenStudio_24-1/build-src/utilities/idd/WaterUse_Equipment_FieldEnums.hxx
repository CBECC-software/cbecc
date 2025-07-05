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

#ifndef UTILITIES_IDD_WATERUSE_EQUIPMENT_FIELDENUMS_HXX
#define UTILITIES_IDD_WATERUSE_EQUIPMENT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WaterUse_EquipmentFields
 *  \brief Enumeration of WaterUse:Equipment's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WaterUse_EquipmentFields, )
#else
class WaterUse_EquipmentFields: public ::EnumBase<WaterUse_EquipmentFields> {
 public: 
  enum domain 
  {
Name, EndUseSubcategory, PeakFlowRate, FlowRateFractionScheduleName, TargetTemperatureScheduleName, HotWaterSupplyTemperatureScheduleName, ColdWaterSupplyTemperatureScheduleName, ZoneName, SensibleFractionScheduleName, LatentFractionScheduleName,   };
  WaterUse_EquipmentFields()
   : EnumBase<WaterUse_EquipmentFields>(Name) {} 
  WaterUse_EquipmentFields(const std::string &t_name) 
   : EnumBase<WaterUse_EquipmentFields>(t_name) {} 
  WaterUse_EquipmentFields(int t_value) 
   : EnumBase<WaterUse_EquipmentFields>(t_value) {} 
  static std::string enumName() 
  { return "WaterUse_EquipmentFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WaterUse_EquipmentFields>::value()); }
   private:
    friend class EnumBase<WaterUse_EquipmentFields>;
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
{ WaterUse_EquipmentFields::Name, "Name", "Name"},
{ WaterUse_EquipmentFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
{ WaterUse_EquipmentFields::PeakFlowRate, "PeakFlowRate", "Peak Flow Rate"},
{ WaterUse_EquipmentFields::FlowRateFractionScheduleName, "FlowRateFractionScheduleName", "Flow Rate Fraction Schedule Name"},
{ WaterUse_EquipmentFields::TargetTemperatureScheduleName, "TargetTemperatureScheduleName", "Target Temperature Schedule Name"},
{ WaterUse_EquipmentFields::HotWaterSupplyTemperatureScheduleName, "HotWaterSupplyTemperatureScheduleName", "Hot Water Supply Temperature Schedule Name"},
{ WaterUse_EquipmentFields::ColdWaterSupplyTemperatureScheduleName, "ColdWaterSupplyTemperatureScheduleName", "Cold Water Supply Temperature Schedule Name"},
{ WaterUse_EquipmentFields::ZoneName, "ZoneName", "Zone Name"},
{ WaterUse_EquipmentFields::SensibleFractionScheduleName, "SensibleFractionScheduleName", "Sensible Fraction Schedule Name"},
{ WaterUse_EquipmentFields::LatentFractionScheduleName, "LatentFractionScheduleName", "Latent Fraction Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const WaterUse_EquipmentFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WaterUse_EquipmentFields> OptionalWaterUse_EquipmentFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WATERUSE_EQUIPMENT_FIELDENUMS_HXX
