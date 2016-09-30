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

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_DISTRIBUTION_COMPONENT_COIL_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_DISTRIBUTION_COMPONENT_COIL_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_Distribution_Component_CoilFields
 *  \brief Enumeration of AirflowNetwork:Distribution:Component:Coil's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_Distribution_Component_CoilFields, )
#else
class AirflowNetwork_Distribution_Component_CoilFields: public ::EnumBase<AirflowNetwork_Distribution_Component_CoilFields> {
 public: 
  enum domain 
  {
CoilName, CoilObjectType, AirPathLength, AirPathHydraulicDiameter,   };
  AirflowNetwork_Distribution_Component_CoilFields()
   : EnumBase<AirflowNetwork_Distribution_Component_CoilFields>(CoilName) {} 
  AirflowNetwork_Distribution_Component_CoilFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_Distribution_Component_CoilFields>(t_name) {} 
  AirflowNetwork_Distribution_Component_CoilFields(int t_value) 
   : EnumBase<AirflowNetwork_Distribution_Component_CoilFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_Distribution_Component_CoilFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_Distribution_Component_CoilFields>::value()); }
   private:
    friend class EnumBase<AirflowNetwork_Distribution_Component_CoilFields>;
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
{ AirflowNetwork_Distribution_Component_CoilFields::CoilName, "CoilName", "Coil Name"},
{ AirflowNetwork_Distribution_Component_CoilFields::CoilObjectType, "CoilObjectType", "Coil Object Type"},
{ AirflowNetwork_Distribution_Component_CoilFields::AirPathLength, "AirPathLength", "Air Path Length"},
{ AirflowNetwork_Distribution_Component_CoilFields::AirPathHydraulicDiameter, "AirPathHydraulicDiameter", "Air Path Hydraulic Diameter"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_Distribution_Component_CoilFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_Distribution_Component_CoilFields> OptionalAirflowNetwork_Distribution_Component_CoilFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_DISTRIBUTION_COMPONENT_COIL_FIELDENUMS_HXX
