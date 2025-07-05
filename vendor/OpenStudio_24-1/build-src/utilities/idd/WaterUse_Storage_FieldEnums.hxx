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

#ifndef UTILITIES_IDD_WATERUSE_STORAGE_FIELDENUMS_HXX
#define UTILITIES_IDD_WATERUSE_STORAGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WaterUse_StorageFields
 *  \brief Enumeration of WaterUse:Storage's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WaterUse_StorageFields, )
#else
class WaterUse_StorageFields: public ::EnumBase<WaterUse_StorageFields> {
 public: 
  enum domain 
  {
Name, WaterQualitySubcategory, MaximumCapacity, InitialVolume, DesignInFlowRate, DesignOutFlowRate, OverflowDestination, TypeofSupplyControlledbyFloatValve, FloatValveOnCapacity, FloatValveOffCapacity, BackupMainsCapacity, OtherTankName, WaterThermalMode, WaterTemperatureScheduleName, AmbientTemperatureIndicator, AmbientTemperatureScheduleName, ZoneName, TankSurfaceArea, TankUValue, TankOutsideSurfaceMaterialName,   };
  WaterUse_StorageFields()
   : EnumBase<WaterUse_StorageFields>(Name) {} 
  WaterUse_StorageFields(const std::string &t_name) 
   : EnumBase<WaterUse_StorageFields>(t_name) {} 
  WaterUse_StorageFields(int t_value) 
   : EnumBase<WaterUse_StorageFields>(t_value) {} 
  static std::string enumName() 
  { return "WaterUse_StorageFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WaterUse_StorageFields>::value()); }
   private:
    friend class EnumBase<WaterUse_StorageFields>;
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
{ WaterUse_StorageFields::Name, "Name", "Name"},
{ WaterUse_StorageFields::WaterQualitySubcategory, "WaterQualitySubcategory", "Water Quality Subcategory"},
{ WaterUse_StorageFields::MaximumCapacity, "MaximumCapacity", "Maximum Capacity"},
{ WaterUse_StorageFields::InitialVolume, "InitialVolume", "Initial Volume"},
{ WaterUse_StorageFields::DesignInFlowRate, "DesignInFlowRate", "Design In Flow Rate"},
{ WaterUse_StorageFields::DesignOutFlowRate, "DesignOutFlowRate", "Design Out Flow Rate"},
{ WaterUse_StorageFields::OverflowDestination, "OverflowDestination", "Overflow Destination"},
{ WaterUse_StorageFields::TypeofSupplyControlledbyFloatValve, "TypeofSupplyControlledbyFloatValve", "Type of Supply Controlled by Float Valve"},
{ WaterUse_StorageFields::FloatValveOnCapacity, "FloatValveOnCapacity", "Float Valve On Capacity"},
{ WaterUse_StorageFields::FloatValveOffCapacity, "FloatValveOffCapacity", "Float Valve Off Capacity"},
{ WaterUse_StorageFields::BackupMainsCapacity, "BackupMainsCapacity", "Backup Mains Capacity"},
{ WaterUse_StorageFields::OtherTankName, "OtherTankName", "Other Tank Name"},
{ WaterUse_StorageFields::WaterThermalMode, "WaterThermalMode", "Water Thermal Mode"},
{ WaterUse_StorageFields::WaterTemperatureScheduleName, "WaterTemperatureScheduleName", "Water Temperature Schedule Name"},
{ WaterUse_StorageFields::AmbientTemperatureIndicator, "AmbientTemperatureIndicator", "Ambient Temperature Indicator"},
{ WaterUse_StorageFields::AmbientTemperatureScheduleName, "AmbientTemperatureScheduleName", "Ambient Temperature Schedule Name"},
{ WaterUse_StorageFields::ZoneName, "ZoneName", "Zone Name"},
{ WaterUse_StorageFields::TankSurfaceArea, "TankSurfaceArea", "Tank Surface Area"},
{ WaterUse_StorageFields::TankUValue, "TankUValue", "Tank U Value"},
{ WaterUse_StorageFields::TankOutsideSurfaceMaterialName, "TankOutsideSurfaceMaterialName", "Tank Outside Surface Material Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const WaterUse_StorageFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WaterUse_StorageFields> OptionalWaterUse_StorageFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WATERUSE_STORAGE_FIELDENUMS_HXX
