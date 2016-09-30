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

#ifndef UTILITIES_IDD_OS_PIPE_INDOOR_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_PIPE_INDOOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Pipe_IndoorFields
 *  \brief Enumeration of OS:Pipe:Indoor's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Pipe_IndoorFields, )
#else
class OS_Pipe_IndoorFields: public ::EnumBase<OS_Pipe_IndoorFields> {
 public: 
  enum domain 
  {
Handle, Name, Construction, FluidInletNode, FluidOutletNode, EnvironmentType, AmbientTemperatureZone, AmbientTemperatureSchedule, AmbientAirVelocitySchedule, PipeInsideDiameter, PipeLength,   };
  OS_Pipe_IndoorFields()
   : EnumBase<OS_Pipe_IndoorFields>(Handle) {} 
  OS_Pipe_IndoorFields(const std::string &t_name) 
   : EnumBase<OS_Pipe_IndoorFields>(t_name) {} 
  OS_Pipe_IndoorFields(int t_value) 
   : EnumBase<OS_Pipe_IndoorFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Pipe_IndoorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Pipe_IndoorFields>::value()); }
   private:
    friend class EnumBase<OS_Pipe_IndoorFields>;
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
{ OS_Pipe_IndoorFields::Handle, "Handle", "Handle"},
{ OS_Pipe_IndoorFields::Name, "Name", "Name"},
{ OS_Pipe_IndoorFields::Construction, "Construction", "Construction"},
{ OS_Pipe_IndoorFields::FluidInletNode, "FluidInletNode", "Fluid Inlet Node"},
{ OS_Pipe_IndoorFields::FluidOutletNode, "FluidOutletNode", "Fluid Outlet Node"},
{ OS_Pipe_IndoorFields::EnvironmentType, "EnvironmentType", "Environment Type"},
{ OS_Pipe_IndoorFields::AmbientTemperatureZone, "AmbientTemperatureZone", "Ambient Temperature Zone"},
{ OS_Pipe_IndoorFields::AmbientTemperatureSchedule, "AmbientTemperatureSchedule", "Ambient Temperature Schedule"},
{ OS_Pipe_IndoorFields::AmbientAirVelocitySchedule, "AmbientAirVelocitySchedule", "Ambient Air Velocity Schedule"},
{ OS_Pipe_IndoorFields::PipeInsideDiameter, "PipeInsideDiameter", "Pipe Inside Diameter"},
{ OS_Pipe_IndoorFields::PipeLength, "PipeLength", "Pipe Length"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Pipe_IndoorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Pipe_IndoorFields> OptionalOS_Pipe_IndoorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_PIPE_INDOOR_FIELDENUMS_HXX
