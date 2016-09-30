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

#ifndef UTILITIES_IDD_GENERATOR_MICROCHP_FIELDENUMS_HXX
#define UTILITIES_IDD_GENERATOR_MICROCHP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Generator_MicroCHPFields
 *  \brief Enumeration of Generator:MicroCHP's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Generator_MicroCHPFields, )
#else
class Generator_MicroCHPFields: public ::EnumBase<Generator_MicroCHPFields> {
 public: 
  enum domain 
  {
Name, PerformanceParametersName, ZoneName, CoolingWaterInletNodeName, CoolingWaterOutletNodeName, AirInletNodeName, AirOutletNodeName, GeneratorFuelSupplyName, AvailabilityScheduleName,   };
  Generator_MicroCHPFields()
   : EnumBase<Generator_MicroCHPFields>(Name) {} 
  Generator_MicroCHPFields(const std::string &t_name) 
   : EnumBase<Generator_MicroCHPFields>(t_name) {} 
  Generator_MicroCHPFields(int t_value) 
   : EnumBase<Generator_MicroCHPFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_MicroCHPFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_MicroCHPFields>::value()); }
   private:
    friend class EnumBase<Generator_MicroCHPFields>;
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
{ Generator_MicroCHPFields::Name, "Name", "Name"},
{ Generator_MicroCHPFields::PerformanceParametersName, "PerformanceParametersName", "Performance Parameters Name"},
{ Generator_MicroCHPFields::ZoneName, "ZoneName", "Zone Name"},
{ Generator_MicroCHPFields::CoolingWaterInletNodeName, "CoolingWaterInletNodeName", "Cooling Water Inlet Node Name"},
{ Generator_MicroCHPFields::CoolingWaterOutletNodeName, "CoolingWaterOutletNodeName", "Cooling Water Outlet Node Name"},
{ Generator_MicroCHPFields::AirInletNodeName, "AirInletNodeName", "Air Inlet Node Name"},
{ Generator_MicroCHPFields::AirOutletNodeName, "AirOutletNodeName", "Air Outlet Node Name"},
{ Generator_MicroCHPFields::GeneratorFuelSupplyName, "GeneratorFuelSupplyName", "Generator Fuel Supply Name"},
{ Generator_MicroCHPFields::AvailabilityScheduleName, "AvailabilityScheduleName", "Availability Schedule Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_MicroCHPFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_MicroCHPFields> OptionalGenerator_MicroCHPFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GENERATOR_MICROCHP_FIELDENUMS_HXX
