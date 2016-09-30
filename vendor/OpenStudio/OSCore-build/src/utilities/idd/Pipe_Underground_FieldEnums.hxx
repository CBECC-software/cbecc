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

#ifndef UTILITIES_IDD_PIPE_UNDERGROUND_FIELDENUMS_HXX
#define UTILITIES_IDD_PIPE_UNDERGROUND_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Pipe_UndergroundFields
 *  \brief Enumeration of Pipe:Underground's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Pipe_UndergroundFields, )
#else
class Pipe_UndergroundFields: public ::EnumBase<Pipe_UndergroundFields> {
 public: 
  enum domain 
  {
Name, ConstructionName, FluidInletNodeName, FluidOutletNodeName, SunExposure, PipeInsideDiameter, PipeLength, SoilMaterialName, UndisturbedGroundTemperatureModelType, UndisturbedGroundTemperatureModelName,   };
  Pipe_UndergroundFields()
   : EnumBase<Pipe_UndergroundFields>(Name) {} 
  Pipe_UndergroundFields(const std::string &t_name) 
   : EnumBase<Pipe_UndergroundFields>(t_name) {} 
  Pipe_UndergroundFields(int t_value) 
   : EnumBase<Pipe_UndergroundFields>(t_value) {} 
  static std::string enumName() 
  { return "Pipe_UndergroundFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Pipe_UndergroundFields>::value()); }
   private:
    friend class EnumBase<Pipe_UndergroundFields>;
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
{ Pipe_UndergroundFields::Name, "Name", "Name"},
{ Pipe_UndergroundFields::ConstructionName, "ConstructionName", "Construction Name"},
{ Pipe_UndergroundFields::FluidInletNodeName, "FluidInletNodeName", "Fluid Inlet Node Name"},
{ Pipe_UndergroundFields::FluidOutletNodeName, "FluidOutletNodeName", "Fluid Outlet Node Name"},
{ Pipe_UndergroundFields::SunExposure, "SunExposure", "Sun Exposure"},
{ Pipe_UndergroundFields::PipeInsideDiameter, "PipeInsideDiameter", "Pipe Inside Diameter"},
{ Pipe_UndergroundFields::PipeLength, "PipeLength", "Pipe Length"},
{ Pipe_UndergroundFields::SoilMaterialName, "SoilMaterialName", "Soil Material Name"},
{ Pipe_UndergroundFields::UndisturbedGroundTemperatureModelType, "UndisturbedGroundTemperatureModelType", "Undisturbed Ground Temperature Model Type"},
{ Pipe_UndergroundFields::UndisturbedGroundTemperatureModelName, "UndisturbedGroundTemperatureModelName", "Undisturbed Ground Temperature Model Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const Pipe_UndergroundFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Pipe_UndergroundFields> OptionalPipe_UndergroundFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_PIPE_UNDERGROUND_FIELDENUMS_HXX
