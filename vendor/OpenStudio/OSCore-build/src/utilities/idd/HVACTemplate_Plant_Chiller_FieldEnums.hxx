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

#ifndef UTILITIES_IDD_HVACTEMPLATE_PLANT_CHILLER_FIELDENUMS_HXX
#define UTILITIES_IDD_HVACTEMPLATE_PLANT_CHILLER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class HVACTemplate_Plant_ChillerFields
 *  \brief Enumeration of HVACTemplate:Plant:Chiller's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(HVACTemplate_Plant_ChillerFields, )
#else
class HVACTemplate_Plant_ChillerFields: public ::EnumBase<HVACTemplate_Plant_ChillerFields> {
 public: 
  enum domain 
  {
Name, ChillerType, Capacity, NominalCOP, CondenserType, Priority, SizingFactor, MinimumPartLoadRatio, MaximumPartLoadRatio, OptimumPartLoadRatio, MinimumUnloadingRatio, LeavingChilledWaterLowerTemperatureLimit,   };
  HVACTemplate_Plant_ChillerFields()
   : EnumBase<HVACTemplate_Plant_ChillerFields>(Name) {} 
  HVACTemplate_Plant_ChillerFields(const std::string &t_name) 
   : EnumBase<HVACTemplate_Plant_ChillerFields>(t_name) {} 
  HVACTemplate_Plant_ChillerFields(int t_value) 
   : EnumBase<HVACTemplate_Plant_ChillerFields>(t_value) {} 
  static std::string enumName() 
  { return "HVACTemplate_Plant_ChillerFields"; }
  domain value() const { return static_cast<domain>(EnumBase<HVACTemplate_Plant_ChillerFields>::value()); }
   private:
    friend class EnumBase<HVACTemplate_Plant_ChillerFields>;
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
{ HVACTemplate_Plant_ChillerFields::Name, "Name", "Name"},
{ HVACTemplate_Plant_ChillerFields::ChillerType, "ChillerType", "Chiller Type"},
{ HVACTemplate_Plant_ChillerFields::Capacity, "Capacity", "Capacity"},
{ HVACTemplate_Plant_ChillerFields::NominalCOP, "NominalCOP", "Nominal COP"},
{ HVACTemplate_Plant_ChillerFields::CondenserType, "CondenserType", "Condenser Type"},
{ HVACTemplate_Plant_ChillerFields::Priority, "Priority", "Priority"},
{ HVACTemplate_Plant_ChillerFields::SizingFactor, "SizingFactor", "Sizing Factor"},
{ HVACTemplate_Plant_ChillerFields::MinimumPartLoadRatio, "MinimumPartLoadRatio", "Minimum Part Load Ratio"},
{ HVACTemplate_Plant_ChillerFields::MaximumPartLoadRatio, "MaximumPartLoadRatio", "Maximum Part Load Ratio"},
{ HVACTemplate_Plant_ChillerFields::OptimumPartLoadRatio, "OptimumPartLoadRatio", "Optimum Part Load Ratio"},
{ HVACTemplate_Plant_ChillerFields::MinimumUnloadingRatio, "MinimumUnloadingRatio", "Minimum Unloading Ratio"},
{ HVACTemplate_Plant_ChillerFields::LeavingChilledWaterLowerTemperatureLimit, "LeavingChilledWaterLowerTemperatureLimit", "Leaving Chilled Water Lower Temperature Limit"},
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
  inline std::ostream &operator<<(std::ostream &os, const HVACTemplate_Plant_ChillerFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<HVACTemplate_Plant_ChillerFields> OptionalHVACTemplate_Plant_ChillerFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_HVACTEMPLATE_PLANT_CHILLER_FIELDENUMS_HXX
