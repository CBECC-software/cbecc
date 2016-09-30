/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_WATERUSE_WELL_FIELDENUMS_HXX
#define UTILITIES_IDD_WATERUSE_WELL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class WaterUse_WellFields
 *  \brief Enumeration of WaterUse:Well's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(WaterUse_WellFields, )
#else
class WaterUse_WellFields: public ::EnumBase<WaterUse_WellFields> {
 public: 
  enum domain 
  {
Name, StorageTankName, PumpDepth, PumpRatedFlowRate, PumpRatedHead, PumpRatedPowerConsumption, PumpEfficiency, WellRecoveryRate, NominalWellStorageVolume, WaterTableDepthMode, WaterTableDepth, WaterTableDepthScheduleName,   };
  WaterUse_WellFields()
   : EnumBase<WaterUse_WellFields>(Name) {} 
  WaterUse_WellFields(const std::string &t_name) 
   : EnumBase<WaterUse_WellFields>(t_name) {} 
  WaterUse_WellFields(int t_value) 
   : EnumBase<WaterUse_WellFields>(t_value) {} 
  static std::string enumName() 
  { return "WaterUse_WellFields"; }
  domain value() const { return static_cast<domain>(EnumBase<WaterUse_WellFields>::value()); }
   private:
    friend class EnumBase<WaterUse_WellFields>;
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
{ WaterUse_WellFields::Name, "Name", "Name"},
{ WaterUse_WellFields::StorageTankName, "StorageTankName", "Storage Tank Name"},
{ WaterUse_WellFields::PumpDepth, "PumpDepth", "Pump Depth"},
{ WaterUse_WellFields::PumpRatedFlowRate, "PumpRatedFlowRate", "Pump Rated Flow Rate"},
{ WaterUse_WellFields::PumpRatedHead, "PumpRatedHead", "Pump Rated Head"},
{ WaterUse_WellFields::PumpRatedPowerConsumption, "PumpRatedPowerConsumption", "Pump Rated Power Consumption"},
{ WaterUse_WellFields::PumpEfficiency, "PumpEfficiency", "Pump Efficiency"},
{ WaterUse_WellFields::WellRecoveryRate, "WellRecoveryRate", "Well Recovery Rate"},
{ WaterUse_WellFields::NominalWellStorageVolume, "NominalWellStorageVolume", "Nominal Well Storage Volume"},
{ WaterUse_WellFields::WaterTableDepthMode, "WaterTableDepthMode", "Water Table Depth Mode"},
{ WaterUse_WellFields::WaterTableDepth, "WaterTableDepth", "Water Table Depth"},
{ WaterUse_WellFields::WaterTableDepthScheduleName, "WaterTableDepthScheduleName", "Water Table Depth Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const WaterUse_WellFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<WaterUse_WellFields> OptionalWaterUse_WellFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_WATERUSE_WELL_FIELDENUMS_HXX
