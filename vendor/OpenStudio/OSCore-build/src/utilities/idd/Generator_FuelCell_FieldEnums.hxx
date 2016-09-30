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

#ifndef UTILITIES_IDD_GENERATOR_FUELCELL_FIELDENUMS_HXX
#define UTILITIES_IDD_GENERATOR_FUELCELL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Generator_FuelCellFields
 *  \brief Enumeration of Generator:FuelCell's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Generator_FuelCellFields, )
#else
class Generator_FuelCellFields: public ::EnumBase<Generator_FuelCellFields> {
 public: 
  enum domain 
  {
Name, PowerModuleName, AirSupplyName, FuelSupplyName, WaterSupplyName, AuxiliaryHeaterName, HeatExchangerName, ElectricalStorageName, InverterName, StackCoolerName,   };
  Generator_FuelCellFields()
   : EnumBase<Generator_FuelCellFields>(Name) {} 
  Generator_FuelCellFields(const std::string &t_name) 
   : EnumBase<Generator_FuelCellFields>(t_name) {} 
  Generator_FuelCellFields(int t_value) 
   : EnumBase<Generator_FuelCellFields>(t_value) {} 
  static std::string enumName() 
  { return "Generator_FuelCellFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Generator_FuelCellFields>::value()); }
   private:
    friend class EnumBase<Generator_FuelCellFields>;
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
{ Generator_FuelCellFields::Name, "Name", "Name"},
{ Generator_FuelCellFields::PowerModuleName, "PowerModuleName", "Power Module Name"},
{ Generator_FuelCellFields::AirSupplyName, "AirSupplyName", "Air Supply Name"},
{ Generator_FuelCellFields::FuelSupplyName, "FuelSupplyName", "Fuel Supply Name"},
{ Generator_FuelCellFields::WaterSupplyName, "WaterSupplyName", "Water Supply Name"},
{ Generator_FuelCellFields::AuxiliaryHeaterName, "AuxiliaryHeaterName", "Auxiliary Heater Name"},
{ Generator_FuelCellFields::HeatExchangerName, "HeatExchangerName", "Heat Exchanger Name"},
{ Generator_FuelCellFields::ElectricalStorageName, "ElectricalStorageName", "Electrical Storage Name"},
{ Generator_FuelCellFields::InverterName, "InverterName", "Inverter Name"},
{ Generator_FuelCellFields::StackCoolerName, "StackCoolerName", "Stack Cooler Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Generator_FuelCellFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Generator_FuelCellFields> OptionalGenerator_FuelCellFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GENERATOR_FUELCELL_FIELDENUMS_HXX
