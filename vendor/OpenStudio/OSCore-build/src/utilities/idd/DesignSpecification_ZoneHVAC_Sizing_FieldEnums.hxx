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

#ifndef UTILITIES_IDD_DESIGNSPECIFICATION_ZONEHVAC_SIZING_FIELDENUMS_HXX
#define UTILITIES_IDD_DESIGNSPECIFICATION_ZONEHVAC_SIZING_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class DesignSpecification_ZoneHVAC_SizingFields
 *  \brief Enumeration of DesignSpecification:ZoneHVAC:Sizing's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(DesignSpecification_ZoneHVAC_SizingFields, )
#else
class DesignSpecification_ZoneHVAC_SizingFields: public ::EnumBase<DesignSpecification_ZoneHVAC_SizingFields> {
 public: 
  enum domain 
  {
Name, CoolingSupplyAirFlowRateMethod, CoolingSupplyAirFlowRate, CoolingSupplyAirFlowRatePerFloorArea, CoolingFractionofAutosizedCoolingSupplyAirFlowRate, CoolingSupplyAirFlowRatePerUnitCoolingCapacity, NoLoadSupplyAirFlowRateMethod, NoLoadSupplyAirFlowRate, NoLoadSupplyAirFlowRatePerFloorArea, NoLoadFractionofCoolingSupplyAirFlowRate, NoLoadFractionofHeatingSupplyAirFlowRate, HeatingSupplyAirFlowRateMethod, HeatingSupplyAirFlowRate, HeatingSupplyAirFlowRatePerFloorArea, HeatingFractionofHeatingSupplyAirFlowRate, HeatingSupplyAirFlowRatePerUnitHeatingCapacity, CoolingDesignCapacityMethod, CoolingDesignCapacity, CoolingDesignCapacityPerFloorArea, FractionofAutosizedCoolingDesignCapacity, HeatingDesignCapacityMethod, HeatingDesignCapacity, HeatingDesignCapacityPerFloorArea, FractionofAutosizedHeatingDesignCapacity,   };
  DesignSpecification_ZoneHVAC_SizingFields()
   : EnumBase<DesignSpecification_ZoneHVAC_SizingFields>(Name) {} 
  DesignSpecification_ZoneHVAC_SizingFields(const std::string &t_name) 
   : EnumBase<DesignSpecification_ZoneHVAC_SizingFields>(t_name) {} 
  DesignSpecification_ZoneHVAC_SizingFields(int t_value) 
   : EnumBase<DesignSpecification_ZoneHVAC_SizingFields>(t_value) {} 
  static std::string enumName() 
  { return "DesignSpecification_ZoneHVAC_SizingFields"; }
  domain value() const { return static_cast<domain>(EnumBase<DesignSpecification_ZoneHVAC_SizingFields>::value()); }
   private:
    friend class EnumBase<DesignSpecification_ZoneHVAC_SizingFields>;
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
{ DesignSpecification_ZoneHVAC_SizingFields::Name, "Name", "Name"},
{ DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRateMethod, "CoolingSupplyAirFlowRateMethod", "Cooling Supply Air Flow Rate Method"},
{ DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRate, "CoolingSupplyAirFlowRate", "Cooling Supply Air Flow Rate"},
{ DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRatePerFloorArea, "CoolingSupplyAirFlowRatePerFloorArea", "Cooling Supply Air Flow Rate Per Floor Area"},
{ DesignSpecification_ZoneHVAC_SizingFields::CoolingFractionofAutosizedCoolingSupplyAirFlowRate, "CoolingFractionofAutosizedCoolingSupplyAirFlowRate", "Cooling Fraction of Autosized Cooling Supply Air Flow Rate"},
{ DesignSpecification_ZoneHVAC_SizingFields::CoolingSupplyAirFlowRatePerUnitCoolingCapacity, "CoolingSupplyAirFlowRatePerUnitCoolingCapacity", "Cooling Supply Air Flow Rate Per Unit Cooling Capacity"},
{ DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRateMethod, "NoLoadSupplyAirFlowRateMethod", "No Load Supply Air Flow Rate Method"},
{ DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRate, "NoLoadSupplyAirFlowRate", "No Load Supply Air Flow Rate"},
{ DesignSpecification_ZoneHVAC_SizingFields::NoLoadSupplyAirFlowRatePerFloorArea, "NoLoadSupplyAirFlowRatePerFloorArea", "No Load Supply Air Flow Rate Per Floor Area"},
{ DesignSpecification_ZoneHVAC_SizingFields::NoLoadFractionofCoolingSupplyAirFlowRate, "NoLoadFractionofCoolingSupplyAirFlowRate", "No Load Fraction of Cooling Supply Air Flow Rate"},
{ DesignSpecification_ZoneHVAC_SizingFields::NoLoadFractionofHeatingSupplyAirFlowRate, "NoLoadFractionofHeatingSupplyAirFlowRate", "No Load Fraction of Heating Supply Air Flow Rate"},
{ DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRateMethod, "HeatingSupplyAirFlowRateMethod", "Heating Supply Air Flow Rate Method"},
{ DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRate, "HeatingSupplyAirFlowRate", "Heating Supply Air Flow Rate"},
{ DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRatePerFloorArea, "HeatingSupplyAirFlowRatePerFloorArea", "Heating Supply Air Flow Rate Per Floor Area"},
{ DesignSpecification_ZoneHVAC_SizingFields::HeatingFractionofHeatingSupplyAirFlowRate, "HeatingFractionofHeatingSupplyAirFlowRate", "Heating Fraction of Heating Supply Air Flow Rate"},
{ DesignSpecification_ZoneHVAC_SizingFields::HeatingSupplyAirFlowRatePerUnitHeatingCapacity, "HeatingSupplyAirFlowRatePerUnitHeatingCapacity", "Heating Supply Air Flow Rate Per Unit Heating Capacity"},
{ DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacityMethod, "CoolingDesignCapacityMethod", "Cooling Design Capacity Method"},
{ DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacity, "CoolingDesignCapacity", "Cooling Design Capacity"},
{ DesignSpecification_ZoneHVAC_SizingFields::CoolingDesignCapacityPerFloorArea, "CoolingDesignCapacityPerFloorArea", "Cooling Design Capacity Per Floor Area"},
{ DesignSpecification_ZoneHVAC_SizingFields::FractionofAutosizedCoolingDesignCapacity, "FractionofAutosizedCoolingDesignCapacity", "Fraction of Autosized Cooling Design Capacity"},
{ DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacityMethod, "HeatingDesignCapacityMethod", "Heating Design Capacity Method"},
{ DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacity, "HeatingDesignCapacity", "Heating Design Capacity"},
{ DesignSpecification_ZoneHVAC_SizingFields::HeatingDesignCapacityPerFloorArea, "HeatingDesignCapacityPerFloorArea", "Heating Design Capacity Per Floor Area"},
{ DesignSpecification_ZoneHVAC_SizingFields::FractionofAutosizedHeatingDesignCapacity, "FractionofAutosizedHeatingDesignCapacity", "Fraction of Autosized Heating Design Capacity"},
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
  inline std::ostream &operator<<(std::ostream &os, const DesignSpecification_ZoneHVAC_SizingFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<DesignSpecification_ZoneHVAC_SizingFields> OptionalDesignSpecification_ZoneHVAC_SizingFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DESIGNSPECIFICATION_ZONEHVAC_SIZING_FIELDENUMS_HXX
