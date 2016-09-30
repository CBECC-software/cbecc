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
